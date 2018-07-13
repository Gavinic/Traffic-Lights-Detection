#ifndef _TEST_HPP_
#define _TEST_HPP_

#include <opencv2/opencv.hpp>
#include <opencv2/ml/ml.hpp> 
#include "util.hpp"
#include "feature.hpp"
#include <algorithm>

using namespace cv;

namespace traffic{

    typedef enum{
        kFord = 1,
        kInve = 0,
    }Labels;

    typedef struct{
        string filename;
        Labels label;
    }Item;

    
    void datacollection(const char* file_folder,vector<Item> &file_list);
    void test(const char* file_folder,string svmpath);
}
    
#endif
