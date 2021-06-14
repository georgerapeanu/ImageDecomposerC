#include <drawers/SquareDrawer.hpp>

cv::Mat SquareDrawer::getNextFrame(cv::Mat frame){
    cv::Point center_coordinates = cv::Point(myRand(0,frame.size().width),myRand(0,frame.size().height));
    int length1 = myRand(0,frame.size().width);
    int length2 = myRand(0,frame.size().height);
    int length = length1;
    if(myRand(0,1) == 1){
        length = length2;
    }
    cv::Size lengths = cv::Size(length,length);
    double angle = myRand(0,360 - 1);
    cv::Scalar color = cv::Scalar(myRand(0,255),myRand(0,255),myRand(0,255));

    cv::RotatedRect rect(center_coordinates,lengths,angle);

    cv::Point2f vertices2f[4];
    rect.points(vertices2f);

    cv::Point vertices[4];    
    for(int i = 0; i < 4; ++i){
        vertices[i] = vertices2f[i];
    }

    cv::Mat answer = frame.clone();
    cv::fillConvexPoly(answer,vertices,4,color);
    //svgString = '<ellipse cx="%d" cy="%d" rx="%d" ry="%d" style="fill:rgb(%d,%d,%d)" transform="rotate(%d %d %d)"></ellipse>' % (*center_coordinates,*axesLength,color[2],color[1],color[0],angle,*center_coordinates);
    return answer;
}