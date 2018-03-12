#include "../include/cube_data.h"
#include "../include/cube_block.h"
#include "../include/cube_corner.h"
#include "../include/cube_squares.h"
#include "../include/cube_bound.h"
#include "../include/color_operation.h"

using namespace cv;
using namespace std;

std::vector<std::vector<cv::Point> > front_squares;
std::array<cv::Point2f,CUBESHAPE> front_corner;
std::vector<std::array<cv::Point2f,CUBESHAPE> > f_corners;
std::array<char, BLOCKSIZE>f_stickers;
std::vector<std::vector<cv::Point> > down_squares;
std::array<cv::Point2f,CUBESHAPE> down_corner;
std::vector<std::array<cv::Point2f,CUBESHAPE> > d_corners;
std::array<char, BLOCKSIZE>d_stickers;
std::vector<std::vector<cv::Point> > right_squares;
std::array<cv::Point2f,CUBESHAPE> right_corner;
std::vector<std::array<cv::Point2f,CUBESHAPE> > r_corners;
std::array<char, BLOCKSIZE>r_stickers;

int main(){
    //VideoCapture cap(1); // open webcam

    /*if (!cap.isOpened()){
        return -1;
    }*/

    Mat frame;
    Mat mean_frame;
    vector<vector<Point> > squares;

    //waitKey(3000);
    //cap >> mean_frame;
    frame = imread("/Users/qinkai/Desktop/cube.JPG");
    resize(frame,frame,Size(frame.cols/3,frame.rows/3));
    //printf("%d",frame.channels());
    //waitKey(10000);
    time_t start,stop;
    start = time(NULL);
    //while (true){
        //cap >> frame;
        //frame = imread("/Users/qinkai/Desktop/cube.JPG");
        if (frame.empty()){
            return -1;
        }
        printf("detecting...\n");
        findSquares(frame, squares);
        //drawSquares(frame, front_squares);
        //drawSquares(frame, right_squares);
        //drawSquares(frame, down_squares);
        printf("sum: %ld,front:\t%ld\n",squares.size(),front_squares.size());
        printf("sum: %ld,right:\t%ld\n",squares.size(),right_squares.size());
        printf("sum: %ld,down:\t%ld\n",squares.size(),down_squares.size());
        printf("finishing detcetion...\n");
        //addWeighted(mean_frame,0.9,frame,0.1,0,mean_frame);
        mean_frame = frame;

        /*stop = time(NULL);
        if(stop - start>3){
            break;
        }
        waitKey(1);*/
    //}

    Point2f pts_dst[] = {
        Point(0,0),
        Point(PICSIZE,0),
        Point(0,PICSIZE) ,
        Point(PICSIZE,PICSIZE)
    };

    printf("cutting...\n");
    int f_index,r_index,d_index;
    findFrontCorner(front_squares,f_corners);
    findBound(f_corners,front_corner,3);
    findFrontKeyBlock(f_corners,f_index);
    findRightCorner(right_squares,r_corners);
    findBound(r_corners,right_corner,2);
    findRightKeyBlock(r_corners,r_index);
    findDownCorner(down_squares,d_corners);
    findBound(d_corners,down_corner,1);
    findDownKeyBlock(d_corners,d_index);

    /*for(int i=0;i<4;i++){
        circle(frame,Point((int)f_corners[f_index][i].x,(int)f_corners[f_index][i].y),5,Scalar(0,0,0),3);
        circle(frame,Point((int)r_corners[r_index][i].x,(int)r_corners[r_index][i].y),5,Scalar(0,0,0),3);
        circle(frame,Point((int)d_corners[d_index][i].x,(int)d_corners[d_index][i].y),5,Scalar(0,0,0),3);
        //circle(frame,Point((int)front_corner[i].x,(int)front_corner[i].y),5,Scalar(0,255,255),3);
        //circle(frame,Point((int)right_corner[i].x,(int)right_corner[i].y),5,Scalar(0,255,255),3);
        //circle(frame,Point((int)down_corner[i].x,(int)down_corner[i].y),5,Scalar(0,255,255),3);
        //printf("(%d,%d) ",(int)front_corner[i].x,(int)front_corner[i].y);
        //printf("(%d,%d) ",(int)f_corners[index][i].x,(int)f_corners[index][i].y);
    }*/
    //imshow("Rubik's Detection -ygowill", frame);

    Mat front_m = getPerspectiveTransform(front_corner.data(),pts_dst);
    Mat front_image;
    warpPerspective(mean_frame,front_image,front_m,mean_frame.size());
    Mat roi_front = front_image(Rect(0,0,PICSIZE,PICSIZE));
    //imshow("roi front",roi_front);
    Mat right_m = getPerspectiveTransform(right_corner.data(),pts_dst);
    Mat right_image;
    warpPerspective(mean_frame,right_image,right_m,mean_frame.size());
    Mat roi_right = right_image(Rect(0,0,PICSIZE,PICSIZE));
    //imshow("roi right",roi_right);
    Mat down_m = getPerspectiveTransform(down_corner.data(),pts_dst);
    Mat down_image;
    warpPerspective(mean_frame,down_image,down_m,mean_frame.size());
    Mat roi_down = down_image(Rect(0,0,PICSIZE,PICSIZE));
    //imshow("roi down",roi_down);
    printf("processing done...\n");

    /*for(int i=0;i<f_corners.size();i++){
        circle(frame,Point((int)f_corners[i][0].x,(int)f_corners[i][0].y),5,Scalar(255,255,255),5);
        circle(frame,Point((int)f_corners[i][1].x,(int)f_corners[i][1].y),5,Scalar(0,0,255),5);
        circle(frame,Point((int)f_corners[i][2].x,(int)f_corners[i][2].y),5,Scalar(0,255,0),5);
        circle(frame,Point((int)f_corners[i][3].x,(int)f_corners[i][3].y),5,Scalar(255,0,255),5);

        circle(frame,Point((int)r_corners[i][0].x,(int)r_corners[i][0].y),5,Scalar(255,255,255),5);
        circle(frame,Point((int)r_corners[i][1].x,(int)r_corners[i][1].y),5,Scalar(0,0,255),5);
        circle(frame,Point((int)r_corners[i][2].x,(int)r_corners[i][2].y),5,Scalar(0,255,0),5);
        circle(frame,Point((int)r_corners[i][3].x,(int)r_corners[i][3].y),5,Scalar(255,0,255),5);

        circle(frame,Point((int)d_corners[i][0].x,(int)d_corners[i][0].y),5,Scalar(255,255,255),5);
        circle(frame,Point((int)d_corners[i][1].x,(int)d_corners[i][1].y),5,Scalar(0,0,255),5);
        circle(frame,Point((int)d_corners[i][2].x,(int)d_corners[i][2].y),5,Scalar(0,255,0),5);
        circle(frame,Point((int)d_corners[i][3].x,(int)d_corners[i][3].y),5,Scalar(255,0,255),5);
    }*/
    //imshow("Rubik's Detection -ygowill", frame);

    Mat down_color;
    cube_color_reduce(roi_down,down_color);
    imshow("reduced color",down_color);
    get_cube_color(down_color,d_stickers);
    Mat test_roi=down_color(Rect(150,50,50,50));
    //imshow("test roi",test_roi);
    printf("color: %c\n",get_block_color(test_roi));

    waitKey(30);
    while(true){
        stop = time(NULL);
        if(stop - start>60){
            break;
        }
    }
    //TODO cube solve algorithm
    return 0;
}