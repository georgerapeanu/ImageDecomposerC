#include "DistanceCalculator.hpp"

class EuclidianDistance:public DistanceCalculator{
public:
    EuclidianDistance():DistanceCalculator(){
        ;
    }
    virtual long long distance(cv::Mat first,cv::Mat second);
};