#include "Drawer.hpp"

class RectangleDrawer:public Drawer{
public:
    RectangleDrawer():Drawer(){
        ;
    }
    virtual cv::Mat getNextFrame(cv::Mat frame);
};