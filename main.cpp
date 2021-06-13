#include <cstdio>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <algorithm>
#include <random>
using namespace std;

const int GENERATIONS = 1e3;
const int ATTEMPTS = 1e3;

mt19937 rng(0);

int myRand(int low,int high){
    uniform_int_distribution<int> gen(low,high);
    return gen(rng);
}

cv::Mat randomElipse(cv::Mat input){
    cv::Point center_coordinates = cv::Point(myRand(0,input.size().width),myRand(0,input.size().height));
    cv::Size axesLength = cv::Size(myRand(0,input.size().width),myRand(0,input.size().height));
    double angle = myRand(0,360 - 1);
    double startAngle = 0;
    double endAngle = 360;
    cv::Scalar color = cv::Scalar(myRand(0,255),myRand(0,255),myRand(0,255));
    int thickness = -1;

    cv::Mat answer = input.clone();
    cv::ellipse(answer,center_coordinates,axesLength,angle,startAngle,endAngle,color,thickness);
    //svgString = '<ellipse cx="%d" cy="%d" rx="%d" ry="%d" style="fill:rgb(%d,%d,%d)" transform="rotate(%d %d %d)"></ellipse>' % (*center_coordinates,*axesLength,color[2],color[1],color[0],angle,*center_coordinates);
    return answer;
}
long long dist(cv::Mat a,cv::Mat b){
    cv::Mat _a,_b;
    a.convertTo(_a,CV_32SC3);
    b.convertTo(_b,CV_32SC3);
    _a = (_a - _b);
    _a = _a.mul(_a);
    auto tmp = (cv::sum(_a));
    long long ans = tmp[0] + tmp[1] + tmp[2];
    return ans;
}

int main(int argc, char** argv )
{
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
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
        printf("doing %d with cost %lld\n",i,dist(image,target));
        cv::Mat best = image;
        long long best_dist = dist(image,target);
        for(int j = 0;j < ATTEMPTS;j++){
            cv::Mat attempt = randomElipse(image);
            long long attempt_dist = dist(target,attempt);
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
