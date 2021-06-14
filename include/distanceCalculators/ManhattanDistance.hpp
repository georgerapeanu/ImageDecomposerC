#include "DistanceCalculator.hpp"

class ManhattanDistance:public DistanceCalculator{
public:
    ManhattanDistance():DistanceCalculator(){
        ;
    }
    virtual long long distance(cv::Mat first,cv::Mat second);
};