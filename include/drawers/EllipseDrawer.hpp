#include "Drawer.hpp"

class EllipseDrawer:public Drawer{
public:
    EllipseDrawer():Drawer(){
        ;
    }
    virtual cv::Mat getNextFrame(cv::Mat frame);
};