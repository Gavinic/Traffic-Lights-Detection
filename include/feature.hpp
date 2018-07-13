#ifndef _FEATURE_H_
#define _FEATURE_H_

#include <iostream>
#include "config.hpp"
#include "core_fun.hpp"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

namespace traffic{
    void gethogfeature(const Mat& src,Mat& feature);       
    void caculIntegral(const Mat &src,Mat integralImg);
    inline double setCorner(const Mat &integralImage,int X,int Y,int M,int K);
    void harrlikefeature(const cv::Mat &src,cv::Mat &features);
}
#endif
