#include <drawers/EllipseDrawer.hpp>

cv::Mat EllipseDrawer::getNextFrame(cv::Mat frame){
    cv::Point center_coordinates = cv::Point(myRand(0,frame.size().width),myRand(0,frame.size().height));
    cv::Size axesLength = cv::Size(myRand(0,frame.size().width),myRand(0,frame.size().height));
    double angle = myRand(0,360 - 1);
    double startAngle = 0;
    double endAngle = 360;
    cv::Scalar color = cv::Scalar(myRand(0,255),myRand(0,255),myRand(0,255));
    int thickness = -1;

    cv::Mat answer = frame.clone();
    cv::ellipse(answer,center_coordinates,axesLength,angle,startAngle,endAngle,color,thickness);
    //svgString = '<ellipse cx="%d" cy="%d" rx="%d" ry="%d" style="fill:rgb(%d,%d,%d)" transform="rotate(%d %d %d)"></ellipse>' % (*center_coordinates,*axesLength,color[2],color[1],color[0],angle,*center_coordinates);
    return answer;
}