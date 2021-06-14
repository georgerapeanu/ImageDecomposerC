#include <distanceCalculators/ManhattanDistance.hpp>

long long ManhattanDistance::distance(cv::Mat first,cv::Mat second){
    cv::Mat _first,_second;
    first.convertTo(_first,CV_32SC3);
    second.convertTo(_second,CV_32SC3);
    _first = (_first - _second);
    _first = cv::abs(_first);
    auto tmp = (cv::sum(_first));
    long long ans = tmp[0] + tmp[1] + tmp[2];
    return ans;
}