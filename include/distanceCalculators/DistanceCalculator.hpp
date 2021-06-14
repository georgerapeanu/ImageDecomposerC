#pragma once
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <chrono>
#include <random>

class DistanceCalculator{
    public:
    DistanceCalculator(){
        ;
    }
    virtual long long distance(cv::Mat first,cv::Mat second) = 0;
};