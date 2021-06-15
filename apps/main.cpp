#pragma once
#include <cstdio>
#include <cstdlib>
#include <map>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <algorithm>
#include <random>
#include <thread>
#include <future>
#include <drawers/Drawer.hpp>
#include <drawers/EllipseDrawer.hpp>
#include <drawers/TriangleDrawer.hpp>
#include <drawers/CircleDrawer.hpp>
#include <drawers/SquareDrawer.hpp>
#include <drawers/RectangleDrawer.hpp>
#include <distanceCalculators/DistanceCalculator.hpp>
#include <distanceCalculators/EuclidianDistance.hpp>
#include <distanceCalculators/ManhattanDistance.hpp>
using namespace std;

cv::Mat do_attempts(const int ATTEMPTS,const cv::Mat image,const cv::Mat target,Drawer* drawer,DistanceCalculator* distanceCalculator){
    cv::Mat best = image.clone();
    long long best_dist = distanceCalculator->distance(image,target);
    
    for(int j = 0;j < ATTEMPTS;j++){
        cv::Mat attempt = drawer->getNextFrame(image);
        long long attempt_dist = distanceCalculator->distance(target,attempt);
        if(attempt_dist < best_dist){
            best = attempt.clone();
            best_dist = attempt_dist;
        }
    }

    return best;
}

cv::Mat process(const string ID,const string NAME,const int GENERATIONS_PER_SAVE,const int GENERATIONS,const int ATTEMPTS,cv::Mat target,Drawer* drawer,DistanceCalculator* distanceCalculator, int THREADS){
    cv::Mat image = cv::Mat(target.size(),CV_8UC3,cv::Scalar(0,0,0));

    for(int i = 0;i < GENERATIONS;i++){
        fprintf(stderr,"doing image %s generation %d with cost %lld\n",NAME.c_str(),i,distanceCalculator->distance(image,target));
        cv::Mat best = image.clone();
        long long best_dist = distanceCalculator->distance(image,target);
        
        std::vector<std::future<cv::Mat>> futures;
        for(int i = 0;i < THREADS;i++){
            int attempts = (ATTEMPTS / THREADS) + (i < (ATTEMPTS % THREADS));
            futures.push_back(std::async(do_attempts,attempts,image,target,drawer,distanceCalculator));
        }

        for(int i = 0;i < (int)futures.size();i++){
            cv::Mat local_best = futures[i].get();
            long long local_dist = distanceCalculator->distance(local_best,target);
            if(local_dist < best_dist){
                best_dist = local_dist;
                best = local_best;
            }
        }

        image = best.clone();
        
        if(i % GENERATIONS_PER_SAVE == 0 || i == GENERATIONS - 1){
            char savename[100];
            sprintf(savename,"%s_generation_%d.jpg",ID.c_str(),i);
            cv::imwrite(savename,image);
        }
        char currSavename[100];
        sprintf(currSavename,"%s.jpg",ID.c_str());
        cv::imwrite(currSavename,image);
    }
    return image;
}

void parse_args(map<string,string> &args,int argc,char** argv){
    int id = 1;

    while(id < argc){
        if(argv[id][0] != '-' || argv[id][1] != '-'){
            fprintf(stderr,"Error: argument %s not recognized\n",argv[id]);
            exit(0);
        }
        if(strcmp(argv[id],"--help") == 0){
            printf("Description: this is a tool that, given an image, tries its best to aproximate is using various shapes\n");
            printf("Usage: ./main\n \
            --path PATH(path to the image to be processed)[REQUIRED]\n \
            --distance DISTANCE(the distance calculator: euclidian, manhattan)[REQUIRED]\n \
            --drawer DRAWER(the drawer with which the app will try to aproximate the image: ellipse, triangle, circle, square, rectangle)[REQUIRED]\n \
            --help (displays help for the app)[OPTIONAL]\n \
            --name NAME(the name of the current program instance, default:main)[OPTIONAL]\n \
            --generations GENERATIONS(number of generations the program will attempt untill in exits,default:1000)[OPTIONAL]\n \
            --attempts ATTEMPTS(number of new image attempts per generation,default:1000)[OPTIONAL] \n \
            --generations_per_save GENERATIONS_PER_SAVE(number of generations between to saves, default:100) [OPTIONAL]  \n \
            --threads THREADS(number of threads to be used, default:1)\n");
            exit(0);
        }
        else if(strcmp(argv[id],"--path") == 0){
            id++;
            if(args.count("path")){
                fprintf(stderr,"Error: path mentioned multiple times\n");
                exit(0);
            }
            args["path"] = argv[id];
        }else if(strcmp(argv[id],"--distance") == 0){
            id++;
            if(args.count("distance")){
                fprintf(stderr,"Error: distance calculator mentioned multiple times\n");
                exit(0);
            }
            args["distance"] = argv[id];
        }else if(strcmp(argv[id], "--drawer") == 0){
            id++;
            if(args.count("drawer")){
                fprintf(stderr,"Error: drawer mentioned multiple times\n");
                exit(0);
            }
            args["drawer"] = argv[id];
        }else if(strcmp(argv[id],"--generations") == 0){
            id++;
            if(args.count("generations")){
                fprintf(stderr,"Error: generations mentioned multiple times\n");
                exit(0);
            }
            args["generations"] = argv[id];
        }else if(strcmp(argv[id],"--attempts") == 0){
            id++;
            if(args.count("attempts")){
                fprintf(stderr,"Error: attempts mentioned multiple times\n");
                exit(0);
            }
            args["attempts"] = argv[id];
        }else if(strcmp(argv[id],"--generations_per_save") == 0){
            id++;
            if(args.count("generations_per_save")){
                fprintf(stderr,"Error: generations_per_save mentioned multiple times\n");
                exit(0);
            }
            args["generations_per_save"] = argv[id];
        }else if(strcmp(argv[id],"--name") == 0){
            id++;
            if(args.count("name")){
                fprintf(stderr,"Error: name mentioned multiple times\n");
                exit(0);
            }
            args["name"] = argv[id];
        }else if(strcmp(argv[id],"--threads") == 0){
            id++;
            if(args.count("threads")){
                fprintf(stderr,"Error: threads mentioned multiple times\n");
                exit(0);
            }
            args["threads"] = argv[id];
        }else{
            fprintf(stderr,"Error: argument %s not recognized\n",argv[id]);
            exit(0);
        }
        id++;
    }
}

int StringToInt(map<string,string> &args,string name){
    int ans = 0;
    for(int i = 0;i < (int)args[name].size();i++){
        if(i > 8){///TODO this doesnt work i think
            fprintf(stderr,"error, number given for %s is too long",name.c_str());
            exit(0);
        }
        if(args[name][i] < '0' || args[name][i] > '9'){
            fprintf(stderr,"error, number given for %s is invalid or badly formated",name.c_str());
            exit(0);
        }
        ans = ans * 10 + args[name][i] - '0';
    }
    return ans;
}

int main(int argc, char** argv ){

    map<string,string> args;
    parse_args(args,argc,argv);

    if(args.count("path") == 0){
        fprintf(stderr,"Error: no path mentioned\n");
        return 0;
    }
    if(args.count("distance") == 0){
        fprintf(stderr,"Error: distance calculator not mentioned\n");
        return 0;
    }
    if(args.count("drawer") == 0){
        fprintf(stderr,"Error: drawer type not mentioned\n");
        return 0;
    }

    cv::Mat target;
    target = cv::imread( args["path"], 1 );
    if ( !target.data )
    {
        fprintf(stderr,"Error: no image found \n");
        return -1;
    }

    Drawer* drawer;
    DistanceCalculator* distanceCalculator;

    if(args["drawer"] == "ellipse"){
        drawer = new EllipseDrawer();
    }else if(args["drawer"] == "triangle"){
        drawer = new TriangleDrawer();
    }else if(args["drawer"] == "circle"){
        drawer = new CircleDrawer();
    }else if(args["drawer"] == "square"){
        drawer = new SquareDrawer();
    }else if(args["drawer"] == "rectangle"){
        drawer = new RectangleDrawer();
    }else{
        fprintf(stderr,"Error: drawer not recognized\n");
        return 0;
    }
    
    if(args["distance"] == "euclidian"){
        distanceCalculator = new EuclidianDistance();
    }else if(args["distance"] == "manhattan"){
        distanceCalculator = new ManhattanDistance();
    }else{
        fprintf(stderr,"Error: distance calculator not recognized\n");
        return 0;
    }

    distanceCalculator = new ManhattanDistance();


    int GENERATIONS = 1e3;
    int ATTEMPTS = 1e3;
    int GENERATIONS_PER_SAVE = 100;
    int THREADS = 1;
    string name = "main";

    if(args.count("generations")){
        GENERATIONS = StringToInt(args,"generations");
    }

    if(args.count("attempts")){
        ATTEMPTS = StringToInt(args,"attempts");
    }

    if(args.count("generations_per_save")){
        GENERATIONS_PER_SAVE = StringToInt(args,"generations_per_save");
    }

    if(args.count("name")){
        name = args["name"];
    }

    if(args.count("threads")){
        THREADS = StringToInt(args,"threads");
        if(THREADS < 1){
            fprintf(stderr,"Error: threads cannot be less than 1\n");
            return 0;
        }
    }

    cv::Mat image = process(name,args["path"],GENERATIONS_PER_SAVE,GENERATIONS,ATTEMPTS,target,drawer,distanceCalculator,THREADS);
    
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Display Image", image);
    cv::waitKey(0);
    return 0;
}
