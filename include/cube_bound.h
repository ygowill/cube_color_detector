#ifndef CUBE_SOLVER_CUBE_BOUND_H
#define CUBE_SOLVER_CUBE_BOUND_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "cube_data.h"
#include "cube_block.h"

void number_signal(cv::Point2f src,cv::Point2f dst,int sig[]);
void findBound(std::vector<std::array<cv::Point2f,4> >& corners,std::array<cv::Point2f,4>& bounds,int mode);
cv::Point reMapBound(cv::Mat roi_img);
cv::Point cross_point(cv::Point p1,cv::Point p2,cv::Point p3,cv::Point p4);


#endif //CUBE_SOLVER_CUBE_BOUND_H


