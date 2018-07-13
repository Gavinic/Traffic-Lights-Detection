#ifndef _LIGHTS_DETECT_HPP_
#define _LIGHTS_DETECT_HPP_

#include "lights_locate.hpp"
#include "lights_judge.hpp"
#include "config.hpp"

namespace traffic{
class LightsDetect{
public:
    LightsDetect();
    ~LightsDetect();
    int SDetect(Mat &src,vector<Mat>&resultVec,bool showDetectArea);
    void setModel(bool para){m_lightslocate->paraSet(para);}
    int setDetectType(int param){ m_type = param;}
private:
   LightsLocate *m_lightslocate;
    int m_type;
    int m_maxSigns;
};

}
#endif
