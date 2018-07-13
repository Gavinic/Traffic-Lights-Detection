#include <feature.hpp>

namespace traffic{
    void gethogfeature(const Mat& src,Mat& feature)
    {   
        Mat image;
        resize(src,image,Size(32,32),0,0,INTER_LINEAR);
        int step = 1;
        int i,j;
        const uchar* p;
        float *p_dst;
        Mat gray_mat,thresh_mat,gaussian_mat;
        GaussianBlur(image,gaussian_mat,Size(3,3),0,0,BORDER_DEFAULT);

        if(gaussian_mat.channels() == 3)
        {
            cvtColor(image,gray_mat,CV_RGB2GRAY);
        }
        else{
            gray_mat = gaussian_mat;
        }
        
        cv::threshold(gray_mat,thresh_mat,0,255,CV_THRESH_OTSU + CV_THRESH_BINARY);

        Mat featuretemp = Mat::zeros(image.rows,image.cols,CV_8UC1);
        
        for (i = 0; i < image.rows; i+=step)
        {
            p = image.ptr<uchar> (i);
            p_dst = featuretemp.ptr<float>(i);     
            p_dst[0] = 0;                      
            for(j = 0; j < image.cols; j+=step)
            {
                p_dst[0] += p[j];                
            }
        }   
        featuretemp.convertTo(feature,CV_32FC1);
    }

    void caculIntegral(const Mat &src,Mat integralImg)
    {
        /*---------------------------------------------------------------------------------------------
        * function name: caculIntegral
        * Input:灰度图像
        * Output:积分图像
        * function:函数的主要目的是为了计算图像的积分图，进而来计算图像的harrlike特征。似乎opencv 已经有封装好的
        *          函数，来直接计算harrlike特征，既然自己学习，就还是自己来实现吧
        * Date: 2018.07.02
        *----------------------------------------------------------------------------------------------*/ 
       
    }

    inline double setCorner(const Mat &integralImage,int X,int Y,int M,int K)
    {
        /*---------------------------------------------------------------------------------------------
        * function name: setCorner
        * Input:A,B,C,D 四个点，以及积分图
        * Output:积分图像
        * function:设置计算harr-like特征时需要的A,B,C,D四个点,同时返回这四个点构成的矩形的intensity,之所以可以直接设置X,Y,K,M这四个值来表征一个
        * 矩形，原因就是实际上一个矩形的四个脚的点中只有四个不同的值，也就是说X,Y,K,M这四个值的不同组合就直接构成了一个矩形
        * 
        *            (X,Y) A                    (X,K) B
        *              ----------------------------
        *              |                          |
        *              |                          |
        *              |                          |
        *              ----------------------------
        *            (M,Y) C                     (M,K) D
        * Date: 2018.07.02
        *----------------------------------------------------------------------------------------------*/ 
        Point A,B,C,D;
        double intensity = 0;

        //注意Point的数据中其x,y和图像的和图像坐标系是不同的；
        //在图像坐标系中(rows = height,cols = width);
        /*----------------------------------------------------------------------------------------------
         *   Point(x,y)  (0,0) |-------------->x                  (0,0)-----------------> j
         *                     |                                       |
         *                     |  (x,y)列扫描                           |   (i,j) 行扫描---->
         *                     |                                       |
         *                     \/ y                                    \/ i (rows)
         * 
         * 所以 x 对应着 j --> cols   y  对应着 i ---->rows
         * ----------------------------------------------------------------------------------*/


        A.x = Y;     A.y = X;
        B.x = K;     B.y = X;
        C.x = Y;     C.y = M;
        D.x = K;     D.y = M;
        
        intensity = integralImage.at<float>(D) - integralImage.at<float>(B)
                    - integralImage.at<float>(C) + integralImage.at<float>(A);     
        return intensity;
    }

    void harrlikefeature(const cv::Mat &src,cv::Mat &features)
    {   
        
    }
}
