#include "core_fun.hpp"

namespace traffic{

    inline void threSelf(Mat &src,Mat &dst,double threValue)
    {
        /*-----------------------------------------------------------------------------------
         * function name:threSelf
         * Input:灰度图像
         * Output:二值化之后的图像
         * function: 通过给定的阈值进行二值化
         * Author:Richard Tseng
         * Date:2018.07.01
         *-------------------------------------------------------------------------------------*/
        
    }


    void dispImage(const Mat &src,string imagename,bool flag)
    {
        if(flag)
        {
            namedWindow(imagename,WINDOW_NORMAL);
            imshow(imagename,src);
            waitKey(0);
        }
    }

    vector<double> multithrelevel(Mat &src,int classnum)
    {
        /*-----------------------------------------------------------------------------------
         * function name:multithrelevel
         * Input:灰度图像
         * Output:类间的阈值，用一个vector存储的
         * function: 通过计算多个类的类间方差得到划分多个类的阈值；目前函数实现的是对于4个类别的划分输出的阈值有三个
         * Author:Richard Tseng
         * Date:2018.07.01
         *-------------------------------------------------------------------------------------*/
        
    }

    vector<cv::Mat> threshMutil(Mat &src,int classnum,bool flag)
    {
        /*-----------------------------------------------------------------------------------
         * function name:multithrelevel
         * Input:灰度图像
         * Output:按计算得到的阈值分割得到的图像，用一个vector存储的
         * function: 通过计算多个类的类间方差得到划分多个类的阈值；目前函数实现的是对于4个类别的划分输出的阈值有三个
         * Author:Richard Tseng
         * Date:2018.07.01
         *-------------------------------------------------------------------------------------*/
        
    }

    void dispMat(Mat &src,MatDataType type, bool flag)
    {
        int nRows = src.rows;
        int nCols = src.cols;
        
        if (flag)
        {
            switch(type)
            {
                case D_8U:
                    {
                        cout << "Matrix type is CV_8UC1!"<< endl;;
                        for (int i = 0; i < nRows; i++)
                        {
                            uchar *dataptr = src.ptr<uchar>(i);
                            for (int j = 0; j < nCols; j++)
                            {
                                if(j / 20 == 0)
                                cout << (int)dataptr[j] <<" ";
                            }
                            cout << endl;
                        }

                    }
                    break;
                case D_32F:
                   {
                        cout << "Matrix type is CV_32FC1!"<< endl;;
                        for (int i = 0; i < nRows; i++)
                        {
                            float *dataptr = src.ptr<float>(i);
                            for (int j = 0; j < nCols; j++)
                            {
                                if(j / 20 == 0)
                                cout << dataptr[j] <<" ";
                            }
                            cout << endl;
                        }

                    }
                    break; 
                default:
                    cout << "There is no match type!" << endl;
                    break;
            }
        }    
    }

    void XmlFilesave(Mat src,string filename,string label)
    {
        cv::FileStorage fs(filename,FileStorage::WRITE);
        fs << label << src;
        fs.release();
    }   

    void dispImage(const Mat &src,vector<Rect_<float>> rects,string windowname,bool flag)
    {
        if (flag)
        {
            Mat temp_mat;
            src.copyTo(temp_mat);
            
            for (size_t i = 0; i < rects.size(); i++ )
            {   
                rectangle(temp_mat, rects[i], Scalar(255, 0, 0), 2);
            }
            dispImage(temp_mat,windowname,flag);
        }
    }

    void imageSave(const Mat &src,string filepath)
    {
        static int count = 0;
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        ss << "result" << "/" << filepath  <<  "/"<< count++ << ".jpg";
        cout << "save image: " << ss.str() << endl;
        imwrite(ss.str(),src);
    }


    bool calcSafeRect(const RotatedRect &roi_rect, const Mat &src,
                    Rect_<float> &safeBoundRect)
    {
        Rect_<float> boundRect = roi_rect.boundingRect();
        float tl_x = boundRect.x > 0 ? boundRect.x : 0;
        float tl_y = boundRect.y > 0 ? boundRect.y : 0;

        float br_x = boundRect.x + boundRect.width < src.cols ? boundRect.x + boundRect.width - 1 : src.cols - 1;
        float br_y = boundRect.y + boundRect.height < src.rows ? boundRect.y + boundRect.height - 1 : src.rows - 1;

        float roi_width = br_x - tl_x;
        float roi_height = br_y - tl_y;

        if (roi_width <= 0 || roi_height <= 0)
        {
            return false;
        }

        safeBoundRect = Rect_<float>(tl_x,tl_y,roi_width,roi_height);
        return true;
    }
}
