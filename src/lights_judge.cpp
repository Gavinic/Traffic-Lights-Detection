#include "lights_judge.hpp"

#include <opencv2/opencv.hpp>
using namespace cv;


namespace traffic{
    LightsJudge::LightsJudge()
    {

    }

    LightsJudge::~LightsJudge()
    {

    }

    vector<int>  LightsJudge::judge(Mat &src,vector<Mat> imgcollection,vector<Rect_<float>> &lightrect,vector<Rect_<float>> &lightsPoint)
    {
        /*-----------------------------------------------------------------------------------
         * function name:judge
         * Input:第一步定位定位得到的交通灯图像
         * Output:通过训练好的模型对区域的预测值
         * function: 判定交通灯区域与非交通灯区域
         * Author:Richard Tseng
         * Date:2018.07.09
         *-------------------------------------------------------------------------------------*/

        svm_instance = ml::SVM::load("xmldata/module/svm.xml");
       
        float width = src.cols;
        float height = src.rows;
        vector<int> responsevec;

        for (int i = 0; i < imgcollection.size(); i++)
        {
            Mat img = imgcollection[i];
            Mat features,featurestd;        
            int response = 0;
            gethogfeature(img,features);
            
            features.convertTo(featurestd,CV_32FC1);
            featurestd = featurestd.reshape(1,1);
            response = svm_instance->predict(featurestd); 
            
            if(response)
            {
                responsevec.push_back(response);
                lightrect[i].x = (lightrect[i].x + width / 10) > width ? width : lightrect[i].x + width / 10;
                lightrect[i].y = (lightrect[i].y + height / 10) > height ? height : lightrect[i].y + height / 10;
                lightsPoint.push_back(lightrect[i]);
            }
        }
        
        return responsevec;
        
        
#if 0
        //霍夫变换检测圆形
        //霍夫变换  
        
            HoughCircles函数的原型为：
            void HoughCircles(InputArray image,OutputArray circles, int method, double dp, double minDist, double param1=100, double param2=100, int minRadius=0,int maxRadius=0 )
            image为输入图像，要求是灰度图像
            circles为输出圆向量，每个向量包括三个浮点型的元素——圆心横坐标，圆心纵坐标和圆半径
            method为使用霍夫变换圆检测的算法，Opencv2.4.9只实现了2-1霍夫变换，它的参数是CV_HOUGH_GRADIENT
            dp为第一阶段所使用的霍夫空间的分辨率，dp=1时表示霍夫空间与输入图像空间的大小一致，dp=2时霍夫空间是输入图像空间的一半，以此类推
            minDist为圆心之间的最小距离，如果检测到的两个圆心之间距离小于该值，则认为它们是同一个圆心
            param1、param2为阈值
            minRadius和maxRadius为所检测到的圆半径的最小值和最大值
            
        Mat temp_mat = thresh_mat*255;
        Mat edge;
        Canny(temp_mat,edge,10,150);
        dispImage(edge,"edge",true);
        vector<Vec3f> circles;
        cout << "hough" << endl;
        HoughCircles(temp_mat,circles,CV_HOUGH_GRADIENT,2,10,10,150,0,0);
        cout << "circles size: " << circles.size() << endl;
        
        for (size_t i = 0; i < circles.size(); i++)
        {
            //提取出圆心坐标  
            Point center(round(circles[i][0]), round(circles[i][1]));
            //提取出圆半径  
            int radius = round(circles[i][2]);
            //圆心  
            circle(img, center, 3, Scalar(0, 255, 0), -1, 4, 0);
            //圆  
            circle(gray_mat, center, radius, Scalar(0, 0, 255), 3, 4, 0);
        }
#endif             
    }
}
