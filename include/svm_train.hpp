#ifndef _SVM_TRAIN_H_
#define _SVM_TRAIN_H_
#include <string>
#include <opencv2/opencv.hpp>
#include "util.hpp"
#include "feature.hpp"
#include <algorithm>
using namespace cv;
using namespace std;


namespace traffic{
    typedef  void (*svmCallback) (const cv::Mat &image,cv::Mat &features);      

    typedef enum{
        kForward = 1,
        kInverse = 0
    }SvmLabel;

    class SvmTrain{
    public:
        typedef struct{
            std::string file;
            SvmLabel label;
        }TrainItem;

        SvmTrain(const char* signs_folder,const char* xml);
        virtual void train();
        virtual void test();

    private:
        void datapre();
        virtual cv::Ptr<cv::ml::TrainData> traindata(); 
        cv::Ptr<cv::ml::SVM> svm_instance;
        
        const char* file_folder;
        const char* svm_xml;
        std::vector<TrainItem> train_file_list;
        std::vector<TrainItem> test_file_list;
        svmCallback extractFeature;                                     
    };
}

#endif
