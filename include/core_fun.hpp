#ifndef _CORE_FUN_HPP_
#define _CORE_FUN_HPP_

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <sstream>
#include "config.hpp"
using namespace std;
using namespace cv;
namespace traffic{

    void imageSave(const Mat &src,string filepath);
    void dispImage(const Mat &src,string imagename,bool flag);
    void dispImage(const Mat &src,vector<Rect_<float>> rects,string windowname,bool flag);
    void XmlFilesave(Mat src,string filename,string label); 
    bool calcSafeRect(const RotatedRect &roi_rect, const Mat &src,
                    Rect_<float> &safeBoundRect);
}

#endif
