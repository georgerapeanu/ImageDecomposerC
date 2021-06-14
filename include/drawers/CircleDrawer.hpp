#include "Drawer.hpp"

class CircleDrawer:public Drawer{
public:
    CircleDrawer():Drawer(){
        ;
    }
    virtual cv::Mat getNextFrame(cv::Mat frame);
};