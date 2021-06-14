#pragma once
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <algorithm>
#include <random>
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

const int GENERATIONS = 1e3;
const int ATTEMPTS = 1e3;

cv::Mat process(const char* PATH,const int GENERATIONS_PER_SAVE,const int GENERATIONS,const int ATTEMPTS,cv::Mat target,Drawer* drawer,DistanceCalculator* distanceCalculator){
    cv::Mat image = cv::Mat(target.size(),CV_8UC3,cv::Scalar(0,0,0));

    for(int i = 0;i < GENERATIONS;i++){
        fprintf(stderr,"doing image %s generation %d with cost %lld\n",PATH,i,distanceCalculator->distance(image,target));
        cv::Mat best = image;
        long long best_dist = distanceCalculator->distance(image,target);
        for(int j = 0;j < ATTEMPTS;j++){
            cv::Mat attempt = drawer->getNextFrame(image);
            long long attempt_dist = distanceCalculator->distance(target,attempt);
            if(attempt_dist < best_dist){
                best = attempt;
                best_dist = attempt_dist;
            }
        }
        image = best;
        if(i % GENERATIONS_PER_SAVE == 0 || i == GENERATIONS - 1){
            char savename[30];
            sprintf(savename,"%s_generation_%d.jpg",PATH,i);
            cv::imwrite(savename,image);
        }
    }
    return image;
}

int main(int argc, char** argv ){
    if(argc != 2){
        printf("weird number of arguments");
        return 0;
    }
    cv::Mat target;
    const char* path = argv[1];
    target = cv::imread( path, 1 );
    if ( !target.data )
    {
        printf("No image data \n");
        return -1;
    }

    Drawer* drawer = new RectangleDrawer();
    DistanceCalculator* distanceCalculator = new ManhattanDistance();

    cv::Mat image = process(path,100,GENERATIONS,ATTEMPTS,target,drawer,distanceCalculator);
    
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Display Image", image);
    cv::waitKey(0);
    return 0;
}
