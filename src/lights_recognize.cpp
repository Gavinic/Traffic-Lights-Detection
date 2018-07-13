#include "lights_recognize.hpp"

namespace traffic{
    LightsRecognize::LightsRecognize()
    {

    }

    LightsRecognize::~LightsRecognize()
    {

    }
    
    int LightsRecognize::SRecognize(Mat &src,vector<Mat>& outRects)
    {
        int result = m_lightslocate->sobelFrtSearch(src,outRects);
        return result;
    } 
}
