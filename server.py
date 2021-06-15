#!/usr/bin/python3

import cv2;
from flask import Flask,Response,render_template,Markup,request;
import threading;

admin = Flask("admin");
client = Flask("client");

@client.route("/",methods=['GET'])
def index():
  output_image = cv2.imread('main.jpg');
  ret, buffer = cv2.imencode('.jpg',output_image);
  response = Response(buffer.tobytes());
  response.headers['Content-Type'] = 'image/jpg';
  return response;

@admin.route("/",methods=['GET','POST'])
def index():
    if request.method == "POST":
        print(request.form.get('generations'));
    return render_template('index.html');    

def start_server_admin():
  admin.run(host='0.0.0.0',port='8001');
def start_server_client():
  client.run(host='0.0.0.0',port='8000');
  
def __main__():
  threading.Thread(target=start_server_admin).start();
  threading.Thread(target=start_server_client).start();

__main__();

