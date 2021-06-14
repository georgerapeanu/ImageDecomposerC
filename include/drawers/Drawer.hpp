#pragma once
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <chrono>
#include <random>

class Drawer{
    protected:
    std::mt19937 rng;
    int myRand(int low,int high){
        std::uniform_int_distribution<int> gen(low,high);
        return gen(rng);
    }
    public:
    Drawer(){
        rng = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());
    }
    virtual cv::Mat getNextFrame(cv::Mat frame) = 0;
};