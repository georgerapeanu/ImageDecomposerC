#include "Drawer.hpp"

class TriangleDrawer:public Drawer{
public:
    TriangleDrawer():Drawer(){
        ;
    }
    virtual cv::Mat getNextFrame(cv::Mat frame);
};