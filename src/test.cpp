#include "test.hpp"
#include "feature.hpp"

namespace traffic{

    void datacollection(const char* file_folder,vector<Item> &file_list)
    {
        char buffer[260];
        sprintf(buffer,"%s/has/train",file_folder);
        auto has_file_test_list = traffic::Utils::getFiles(buffer);
        std::random_shuffle(has_file_test_list.begin(),has_file_test_list.end());
        cout << "has_file_test_list size: " << has_file_test_list.size() << endl;

        sprintf(buffer,"%s/no/train",file_folder);
        auto no_file_test_list = traffic::Utils::getFiles(buffer);
        std::random_shuffle(no_file_test_list.begin(),no_file_test_list.end());
                
        std::vector<traffic::Item> test_file_list;
        cout << ">> Collecting test data...." << endl;
        for (auto file : has_file_test_list)
        {
            test_file_list.push_back({file,kFord});     
        }
        

        for (auto file : no_file_test_list) 
        {
            test_file_list.push_back({file,kInve});
        }

        file_list = test_file_list;
        cout << "test_file_list size: " << test_file_list.size() << endl;
    }

    void test(const char* file_folder,string svmpath)
    {   
        vector<Item> filelist;
        cv::Ptr<ml::SVM> svm = ml::SVM::load(svmpath);
        datacollection(file_folder,filelist);

        double count_all = filelist.size();
        double ptrue_rtrue = 0;
        double ptrue_rfalse = 0;
        double pfalse_rtrue = 0;
        double pfalse_rfalse = 0;
       
        for(auto item : filelist)
        {
            cout << "test_file_list: " << item.filename << endl;
            auto image = imread(item.filename);

            if(image.empty())
            {
                cout << "no image!" << endl;
                continue;
            }

            Mat feature,featurestd;
            //harrlikefeature(image,feature);
            gethogfeature(image,feature);
            feature = feature.reshape(1,1);
            feature.convertTo(featurestd,CV_32FC1);
            auto predict = int (svm->predict(featurestd));

#if 1
            vector<Rect_<float>> rects;
            if(predict)
            {
                imageSave(image,"haslights");
            }else{

                imageSave(image,"nolights");
            }
#endif
            
            auto real = item.label;
            if(predict == kFord && real == kFord) ptrue_rtrue++;
            if(predict == kFord && real == kInve) ptrue_rfalse++;
            if(predict == kInve && real == kFord) pfalse_rtrue++;
            if(predict == kInve && real == kInve) pfalse_rfalse++;
        }

        cout << "count_all: " << count_all << endl; 
        cout << "ptrue_rtrue: " << ptrue_rtrue << endl;
        cout << "ptrue_rfalse: " << ptrue_rfalse << endl;
        cout << "pfalse_rtrue: " << pfalse_rtrue << endl;
        cout << "pflase_rfalse: " << pfalse_rfalse << endl;

        double precise = 0;        
        if (ptrue_rtrue + ptrue_rfalse != 0)
        {
            precise = ptrue_rtrue / (ptrue_rtrue + ptrue_rfalse);     
            cout << "precise: " << precise << endl;
        }
        else{
            cout << "precise: " << "NA" << endl; 
        }

        double recall = 0;      
        if(ptrue_rtrue + pfalse_rtrue != 0)
        {
            recall = ptrue_rtrue / (ptrue_rtrue + pfalse_rtrue);      
            cout << "recall: " << recall << endl;
        }
        else {
            cout << "recall: " << "NA" << endl;
        }

        double Fscore = 0; 
        if (precise + recall != 0)
        {
            Fscore = 2*(precise*recall) / (precise + recall);
            cout << "Fscore: " << Fscore << endl;
        }
        else{
            cout << "Fscore: " << "NA" << endl;
        }
    }    
}
