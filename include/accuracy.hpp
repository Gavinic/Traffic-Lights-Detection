#ifndef _ACCURACY_HPP_
#define _ACCURACY_HPP_

#include "config.hpp"
#include "util.hpp"
#include "lights_recognize.hpp"

namespace traffic{
    namespace demo{
        int accuracyTest(const char* testfolder)
        {   
            LightsRecognize lights;  
            lights.setDetectType(SR_DETECT_COLOR);
            lights.setModel(false);                   
            std::vector<cv::Mat>outrects;
            std::vector<std::string> fileslist;
            fileslist = traffic::Utils::getFiles(testfolder,true);
            cout << "filelist: "  << fileslist.size() << endl;
            for(auto file : fileslist)
            {
                cout << "files name :" << file.c_str() << endl;
                cv::Mat src = imread(file.c_str());
                int result = lights.SDetect(src,outrects,false); 
            }
            return 0;
        }
    }
}
#endif
