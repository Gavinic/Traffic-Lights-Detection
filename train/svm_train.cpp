#include "svm_train.hpp"

using cv::ml::SVM;

namespace traffic{
    SvmTrain::SvmTrain(const char* signs_folder,const char* xml)
        :file_folder(signs_folder),svm_xml(xml)
    {
        assert(signs_folder);
        assert(xml);
        extractFeature = gethogfeature;
        //extractFeature = harrlikefeature;
    }
     
    void SvmTrain::datapre()
    {
        char buffer[260];
        cv::FileStorage fs1("xmldata/traindata.xml",FileStorage::WRITE);
        cv::FileStorage fs2("xmldata/testdata.xml",FileStorage::WRITE);
        sprintf(buffer,"%s/has/train",file_folder);
        auto has_file_train_list = traffic::Utils::getFiles(buffer);
        std::random_shuffle(has_file_train_list.begin(),has_file_train_list.end());

        sprintf(buffer,"%s/no/train",file_folder);
        auto no_file_train_list = traffic::Utils::getFiles(buffer);
        std::random_shuffle(no_file_train_list.begin(),no_file_train_list.end());

        sprintf(buffer,"%s/has/test",file_folder);
        auto has_file_test_list = traffic::Utils::getFiles(buffer);
        std::random_shuffle(has_file_test_list.begin(),has_file_test_list.end());

        sprintf(buffer,"%s/no/test",file_folder);
        auto no_file_test_list = traffic::Utils::getFiles(buffer);
        std::random_shuffle(no_file_test_list.begin(),no_file_test_list.end());
        
        cout << ">> Collecting train data...." << endl;      
        for (auto file : has_file_train_list)
        {
            train_file_list.push_back({file,kForward});           
        }
           
        for (auto file : no_file_train_list)
        {
            train_file_list.push_back({file,kInverse});           
        }
            
        for(auto item : train_file_list)
        {
            fs1 << "traindata-lables" << item.label;
        }   
        fs1.release();    
        

        cout << ">> Collecting test data...." << endl;
        for (auto file : has_file_test_list)
        {
            test_file_list.push_back({file,kForward});     
        }
           
        
        for(auto file : no_file_test_list) 
        {
            test_file_list.push_back({file,kInverse});
        }
             

        for(auto item : test_file_list)
        {
            fs2 << "testdata-lables" << item.label;
        }   
        fs2.release();    

    }

    cv::Ptr<cv::ml::TrainData>  SvmTrain::traindata()
    {
        Mat samples;            
        std::vector<int> labels;
        cv::FileStorage fs("xmldata/feature.xml",FileStorage::WRITE);
        cout << "traindata start" << endl;\
        cout << "train_file_list size : "  << train_file_list.size() << endl;
        for(auto item : train_file_list)
        {
            cout << "train_file_list: " << item.file << endl;
            auto image = imread(item.file);
            if(image.empty())
            {
                cout << "Invalid image: %s ignore. " << item.file.c_str() << endl;
            }

            Mat feature;
            extractFeature(image,feature);         
            feature = feature.reshape(1,1);         
            fs << "feature"  << feature ;
            samples.push_back(feature);              
            labels.push_back(item.label);
        }
        fs.release();
        Mat features_,labels_;
        samples.convertTo(features_,CV_32FC1);
        
        Mat(labels).convertTo(labels_,CV_32SC1);        
        
        return cv::ml::TrainData::create(features_, cv::ml::SampleTypes::ROW_SAMPLE, labels_);
    }

    void SvmTrain::train()
    {
        
        svm_instance = cv::ml::SVM::create();
        svm_instance->setType(cv::ml::SVM::C_SVC);
        svm_instance->setKernel(cv::ml::SVM::RBF);
        svm_instance->setDegree(0.1);
        svm_instance->setGamma(0.1);
        svm_instance->setCoef0(0.1);
        svm_instance->setC(1);
        svm_instance->setNu(0.1);
        svm_instance->setP(0.1);
        svm_instance->setTermCriteria(cvTermCriteria(CV_TERMCRIT_ITER, 20000, 0.0001));       
        
        this->datapre();                           

        if(train_file_list.size() == 0)
        {
            cout << "NO file found in the train folder!" << endl;
        }

        auto train_data = traindata();              

        cout << "Train SVM Model,Please wait...." << endl;
        
        long start = traffic::Utils::getTimestamp();
        svm_instance->trainAuto(train_data,10,
                        SVM::getDefaultGrid(SVM::C),
                        SVM::getDefaultGrid(SVM::GAMMA), 
                        SVM::getDefaultGrid(SVM::P),
                        SVM::getDefaultGrid(SVM::NU), 
                        SVM::getDefaultGrid(SVM::COEF),
                        SVM::getDefaultGrid(SVM::DEGREE), true);
        long end = Utils::getTimestamp();
        cout << "Training done. Time elapse: " << end - start << "ms" <<  endl;
        cout << "Saving model file...." << endl;
        svm_instance->save(svm_xml);

        cout << "Your SVM model file was saved to: . " << svm_xml << endl;

        this -> test();
    }

    void SvmTrain::test()
    {
        svm_instance->load(svm_xml);
        if(test_file_list.empty())    
        {
            this->datapre();
        }
    
        double count_all = test_file_list.size();
        double ptrue_rtrue = 0;
        double ptrue_rfalse = 0;
        double pfalse_rtrue = 0;
        double pfalse_rfalse = 0;
        
        
        for(auto item : test_file_list)
        {
            cout << "test_file_list: " << item.file << endl;
            auto image = imread(item.file);

            if(image.empty())
            {
                cout << "no image!" << endl;
                continue;
            }

            Mat feature,features_;
            extractFeature(image,feature);
            feature = feature.reshape(1,1);
            feature.convertTo(features_,CV_32FC1);
            auto predict = int (svm_instance->predict(features_));
        
            auto real = item.label;
            if(predict == kForward && real == kForward) ptrue_rtrue++;
            if(predict == kForward && real == kInverse) ptrue_rfalse++;
            if(predict == kInverse && real == kForward) pfalse_rtrue++;
            if(predict == kInverse && real == kInverse) pfalse_rfalse++;
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
