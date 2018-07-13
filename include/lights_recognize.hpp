#ifndef _LIGHTS_RECOGNIZE_HPP_
#define _LIGHTS_RECOGNIZE_HPP_

#include "lights_locate.hpp"
#include "lights_detect.hpp"
using namespace std;

namespace traffic{
    class LightsRecognize : public LightsDetect 
    {
        public:
        LightsRecognize();
        ~LightsRecognize();
        int  SRecognize(Mat &src,vector<Mat>& outrects);
        private:
        LightsLocate *m_lightslocate;
    };
}

#endif
