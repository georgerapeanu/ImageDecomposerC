#include <drawers/TriangleDrawer.hpp>

cv::Mat TriangleDrawer::getNextFrame(cv::Mat frame){
    const int CNT_POINTS = 3;
    int npt[] = {CNT_POINTS};
    cv::Point points[1][CNT_POINTS];
    for(int i = 0;i < CNT_POINTS;i++){
        points[0][i] = cv::Point(myRand(0,frame.size().width),myRand(0,frame.size().height));
    }
    const cv::Point* points_PTR[1] = {points[0]};
    cv::Scalar color = cv::Scalar(myRand(0,255),myRand(0,255),myRand(0,255));
    
    cv::Mat answer = frame.clone();
    cv::fillPoly(answer,points_PTR,npt,1,color);
    //svgString = '<ellipse cx="%d" cy="%d" rx="%d" ry="%d" style="fill:rgb(%d,%d,%d)" transform="rotate(%d %d %d)"></ellipse>' % (*center_coordinates,*axesLength,color[2],color[1],color[0],angle,*center_coordinates);
    return answer;
}