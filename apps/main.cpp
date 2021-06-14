#pragma once
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <algorithm>
#include <random>
#include <drawers/Drawer.hpp>
#include <drawers/EllipseDrawer.hpp>
#include <drawers/TriangleDrawer.hpp>
#include <distanceCalculators/DistanceCalculator.hpp>
#include <distanceCalculators/EuclidianDistance.hpp>
using namespace std;

const int GENERATIONS = 1e3;
const int ATTEMPTS = 1e3;

int main(int argc, char** argv ){
    Drawer* drawer = new TriangleDrawer();
    DistanceCalculator* distanceCalculator = new EuclidianDistance();
    cv::Mat target;
    const char* path = "/home/georgerapeanu/Desktop/tmp/monteCarlo/examples/peter.png";
    target = cv::imread( path, 1 );
    if ( !target.data )
    {
        printf("No image data \n");
        return -1;
    }
    cv::Mat image = cv::Mat(target.size(),CV_8UC3,cv::Scalar(0,0,0));

    for(int i = 0;i < GENERATIONS;i++){
        printf("doing %d with cost %lld\n",i,distanceCalculator->distance(image,target));
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
        if(i % 100 == 0){
            char savename[30];
            sprintf(savename,"generation_%d.jpg",i);
            cv::imwrite(savename,image);
        }
    }

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Display Image", image);
    cv::waitKey(0);
    return 0;
}
