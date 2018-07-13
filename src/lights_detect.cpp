#include "lights_detect.hpp"

namespace traffic{

    //这里的构造函数至关重要
    LightsDetect::LightsDetect()
    {
        m_lightslocate = new LightsLocate();
        m_type = 0;
        m_maxSigns = 4;
    }

    LightsDetect::~LightsDetect()
    {
        delete m_lightslocate;
    }

    int LightsDetect::SDetect(Mat &src,vector<Mat>& resultVec,bool showDetectArea)
    {
        std::vector<Mat> firstroi;
        std::vector<Mat> color_lights;
        vector<Rect_<float>> lightsrect;
        vector<Rect_<float>> firstrect;
        vector<Rect_<float>> resultPoint;
        vector<int> responseVec;

        color_lights.reserve(16);
        std::vector<Mat> shape_lights;
        shape_lights.reserve(16);
        std::vector<Mat> all_result_lights;
        all_result_lights.reserve(48);

        int type = m_type;
        cout << "m_type:  " << type  << endl;
        cout << "SDtect" << endl;

    #pragma omp parallal sections
        {
    #pragma omp section
             {
                 if(!type || type & SR_DETECT_COLOR)
                 {
                     cout << "color locate" << endl;
                     m_lightslocate->colorSearch(src,firstroi,firstrect,false);
                     m_lightslocate->searchsecond(firstroi,firstrect,color_lights,lightsrect,false);
                 }
             }
    #pragma omp section
            {
                if(!type || type & SR_DETECT_SHAPE)
                {
                    m_lightslocate->shapeSearch(src,shape_lights);
                }
            }
        }

        for (auto light : color_lights)
        {
            all_result_lights.push_back(light);
        }

        for (auto light : shape_lights)
        {
            all_result_lights.push_back(light);
        }
        
        LightsJudge lightsjudge;
        responseVec = lightsjudge.judge(src,all_result_lights,lightsrect,resultPoint);

        if(!responseVec.empty())
        {
            for(auto recti : resultPoint)
            {
                rectangle(src,recti,Scalar(0,255,0),2,8,0);   
            }
        }else{
        }

        dispImage(src,"result",true);
        return 0;

    }
}
