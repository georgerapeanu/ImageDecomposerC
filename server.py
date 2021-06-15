#!/usr/bin/python3

from os import popen
import cv2;
from flask import Flask,Response,render_template,Markup,request;
from flask_wtf.file import FileField,FileRequired,FileAllowed;
from flask_wtf import FlaskForm;
from wtforms import IntegerField,validators,SelectField;
from werkzeug.utils import secure_filename;
import threading;
import subprocess;

class ImageForm(FlaskForm):
  image = FileField('image',[FileRequired(),FileAllowed(['jpg','png','jpeg','webp'],'Image type not supported')]);
  generations = IntegerField('generations',[validators.DataRequired()]);
  attempts = IntegerField('attempts',[validators.DataRequired()]);
  threads = IntegerField('threads',[validators.DataRequired(),validators.NumberRange(min=1,max=8)]);
  distanceCalculator = SelectField('distance',choices=['euclidian','manhattan'],validators=[validators.DataRequired()]);
  drawer = SelectField('drawer',choices=['ellipse','triangle','square','rectangle','circle'],validators=[validators.DataRequired()]);
  generations_per_save = IntegerField('generations per save',[validators.DataRequired()]);

admin = Flask("admin");
client = Flask("client");

activeProcess = None;
def setImage(savename,generations,attempts,distanceCalculator,drawer,threads,generations_per_save):
  command = "./build/apps/main --path %s --generations %d --attempts %d --distance %s --drawer %s --threads %d --generations_per_save %d" % (savename,generations,attempts,distanceCalculator,drawer,threads,generations_per_save);
  popen_command = command.split(' ');
  
  global activeProcess;

  if activeProcess != None and activeProcess.poll() == None:
    activeProcess.kill();
  activeProcess = subprocess.Popen(popen_command);
  

@client.route("/video_feed",methods=['GET'])
def video_feed():
  output_image = cv2.imread('main.jpg');
  ret, buffer = cv2.imencode('.jpg',output_image);
  response = Response(buffer.tobytes());
  response.headers['Content-Type'] = 'image/jpg';
  return response;

@client.route("/",methods=['GET'])
def index(): 
  return render_template('client_index.html');


@admin.route("/",methods=['GET','POST'])
def index():
    form = ImageForm(meta={'csrf':False});
    if request.method == "POST" and form.validate_on_submit():
      filename = secure_filename(form.image.data.filename);
      tmp = filename.split('.');
      extension = tmp[len(tmp) - 1];
      savename = 'upload.' + extension;
      form.image.data.save(savename);
      setImage(savename,form.generations.data,form.attempts.data,form.distanceCalculator.data,form.drawer.data,form.threads.data,form.generations_per_save.data);
    return render_template('index.html',form=form);    

def start_server_admin():
  admin.run(host='0.0.0.0',port='8001');
def start_server_client():
  client.run(host='0.0.0.0',port='8000');
  
def __main__():
  threading.Thread(target=start_server_admin).start();
  threading.Thread(target=start_server_client).start();

__main__();

