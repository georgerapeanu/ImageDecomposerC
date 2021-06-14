#include <drawers/CircleDrawer.hpp>

cv::Mat CircleDrawer::getNextFrame(cv::Mat frame){
    cv::Point center_coordinates = cv::Point(myRand(0,frame.size().width),myRand(0,frame.size().height));
    int radius1 = myRand(0,frame.size().width);
    int radius2 = myRand(0,frame.size().height);
    int radius = radius1;
    if(myRand(0,1) == 1){
        radius = radius2;
    }
    cv::Scalar color = cv::Scalar(myRand(0,255),myRand(0,255),myRand(0,255));
    int thickness = -1;

    cv::Mat answer = frame.clone();
    cv::circle(answer,center_coordinates,radius,color,thickness);
    //svgString = '<ellipse cx="%d" cy="%d" rx="%d" ry="%d" style="fill:rgb(%d,%d,%d)" transform="rotate(%d %d %d)"></ellipse>' % (*center_coordinates,*axesLength,color[2],color[1],color[0],angle,*center_coordinates);
    return answer;
}