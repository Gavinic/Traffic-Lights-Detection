#ifndef _LIGHTS_JUDGE_HPP_
#define _LIGHTS_JUDGE_HPP_

#include "core_fun.hpp"
#include "feature.hpp"

    namespace traffic{
        class LightsJudge{
        public:
            LightsJudge();
            ~LightsJudge();
            vector<int> judge(Mat &src,vector<Mat> imgcollection,vector<Rect_<float>> &lightrect,vector<Rect_<float>> &lightsPoint);
            
        private:
            cv::Ptr<cv::ml::SVM> svm_instance;
        };
    }
#endif
