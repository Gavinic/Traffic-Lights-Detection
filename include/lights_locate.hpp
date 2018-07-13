#ifndef _LIGHTS_LOCATE_HPP_
#define _LIGHTS_LOCATE_HPP_
#include <opencv2/opencv.hpp>
#include "config.hpp"
#include "core_fun.hpp"

using namespace cv;
using namespace std;

namespace traffic{

  static const int DEFAULT_GAUSSIANBLUR_SIZE = 5;
  static const int SOBEL_SCALE = 1;
  static const int SOBEL_DELTA = 0;
  static const int SOBEL_DDEPTH = CV_16S;
  static const int SOBEL_X_WEIGHT = 1;
  static const int SOBEL_Y_WEIGHT = 0;
  static const int DEFAULT_MORPH_SIZE_WIDTH = 17;  // 17
  static const int DEFAULT_MORPH_SIZE_HEIGHT = 3;  // 3


class LightsLocate{
public:
    LightsLocate();
    ~LightsLocate();
    int histgram(const vector<Mat> &src,const Mat &space,bool flag,string name);
    int testValue(const Mat &src, int minValue, int maxValue);
    int colorSearch(const Mat &src,vector<Mat> &roi_mat,vector<Rect_<float>> &outRects,bool debug);
    int colorMatch(const Mat &src,Color color,Mat &match_mat,bool apaptive_minsv);
    int shapeSearch(const Mat &src,vector<Mat> &outRects);
    int sobelFrtSearch(const Mat &src,vector<Mat> &outRects);
    int sobelSearch(const Mat& src,std::vector<Mat>& outRects,int blurSize,int morphW,int morphH);
    void paraSet(bool para);
    
    void enlargeROi(const Mat src,const Rect_<float> &roi_rect,Rect_<float> &large_roi);
    void enlargeROisecond(const Mat src,const Rect_<float> &roi_rect,Rect_<float> &large_roi);
    int searchsecond(vector<Mat> firstresult,vector<Rect_<float>> firstrect,vector<Mat> &imgcollection,vector<Rect_<float>> &roirect,bool debug);
    bool verifySizes(RotatedRect mr); 
    bool veritycontours(Mat src,RotatedRect &rotarec);  
    inline void setGaussianBlurSize(int param) {GaussianBlurSize = param;}
    inline void setMorphSizeWidth(int param) {MorphSizeWidth = param;}
    inline void setMOrphSizeHeight(int param) {MorphSizeHeight = param;}

protected:  
    int GaussianBlurSize;
    int MorphSizeWidth;
    int MorphSizeHeight;
};
}
#endif
