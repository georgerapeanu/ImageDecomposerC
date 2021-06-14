#include "Drawer.hpp"

class SquareDrawer:public Drawer{
public:
    SquareDrawer():Drawer(){
        ;
    }
    virtual cv::Mat getNextFrame(cv::Mat frame);
};