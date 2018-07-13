#include "lights_locate.hpp"
namespace traffic{

LightsLocate::LightsLocate()
{
    GaussianBlurSize = DEFAULT_GAUSSIANBLUR_SIZE;
    MorphSizeWidth = DEFAULT_MORPH_SIZE_WIDTH;
    MorphSizeHeight = DEFAULT_MORPH_SIZE_HEIGHT;
}

LightsLocate::~LightsLocate()
{

}

//定义一个存储交通标志相关操作的类；这个类的作用就是1,locate 2，对找到的区域进行倾斜矫正等操作
//这个类的设计思想就是为了解决交通标志定位的问题；类的成员变量设定为在定位过程中opencv操作的所需要的相关的参数
int LightsLocate::sobelSearch(const Mat& src,std::vector<Mat>& outRects,
        int blurSize,int morphW,int morphH)
{
    if(src.empty())
    {
        cout << "pic is empty!" << endl;
    }
    //1,高斯滤波
    Mat mat_blur;
    mat_blur = src.clone();
     
    GaussianBlur(src,mat_blur,Size(blurSize,blurSize),0,0,BORDER_DEFAULT);
    
    //2.灰度转换
    Mat mat_gray;
    if(mat_blur.channels() == 3)
        cvtColor(mat_blur,mat_gray,CV_RGB2GRAY);
    else
        mat_gray = mat_blur;
    namedWindow("gray");
    imshow("gray",mat_gray);
    //进行soble检测
    int scale = SOBEL_SCALE;
    int delta = SOBEL_DELTA;
    int ddepth = SOBEL_DDEPTH;

    Mat grad_x,grad_y;
    Mat abs_grad_x,abs_grad_y;

    Sobel(mat_gray,grad_x,ddepth,1,0,3,scale,delta,BORDER_DEFAULT);
    convertScaleAbs(grad_x,abs_grad_x);
    namedWindow("sobel");
    imshow("sobel",abs_grad_x);

    Mat grad;
    //addWeighted(abs_grad_x,SOBEL_X_WEIGHT,0,0,0,grad);
    addWeighted(abs_grad_x,0.5,0,0,0,grad);
    namedWindow("addWeight");
    imshow("addWeight",grad);
   

    Mat mat_threshold;
    double ostu_thresh_val = threshold(grad,mat_threshold,0,255,CV_THRESH_OTSU + CV_THRESH_BINARY);
    namedWindow("threshold");
    imshow("threshold",mat_threshold);
   
    Mat element = getStructuringElement(MORPH_RECT,Size(morphW,morphH));
    morphologyEx(mat_threshold,mat_threshold,MORPH_CLOSE,element);
    namedWindow("morph");
    imshow("morph",mat_threshold);
    waitKey(0);
    outRects.push_back(mat_threshold);
    
    return 0;
}

int LightsLocate::histgram(const vector<Mat> &src,const Mat &space,bool flag,string name)
{
    if(flag == true) 
    {
        vector<Mat> channels; 
        channels = src;   
        //MatND dstHist; 
        Mat   tempChannel1,tempChannel2,tempChannel3; 
        int histBinNum = 256;
        int histSize[] = { histBinNum };       //如果写成int histSize = 256;调用计算直方图的函数的时，该变量需写成&histSize    
        float midRanges[] = { 0, 256 };    
        const float *ranges[] = { midRanges };    
        calcHist(&channels[0], 1, 0, Mat(), tempChannel1, 1, histSize, ranges, true, false);  
        calcHist(&channels[1], 1, 0, Mat(), tempChannel2, 1, histSize, ranges, true, false);   
        calcHist(&channels[2], 1, 0, Mat(), tempChannel3, 1, histSize, ranges, true, false);
        
        Mat drawImage = Mat::zeros(Size(256, 256), CV_8UC3);    
        Mat colorSpace;
        merge(channels,colorSpace);
        double g_dHistMaxValue;    
        minMaxLoc(colorSpace, 0, &g_dHistMaxValue, 0, 0);    
        int nrows = channels[0].rows;
        int ncols = channels[0].cols;
        int bin_w = cvRound((double)ncols /histBinNum);
        for (int i = 1; i < histBinNum; i++)    
        {    
            line(drawImage, Point(bin_w*(i-1), nrows - cvRound(tempChannel1.at<float>(i-1))),
            Point(bin_w*(i), nrows - cvRound(tempChannel1.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
            line(drawImage, Point(bin_w*(i-1), nrows - cvRound(tempChannel2.at<float>(i-1))),
            Point(bin_w*(i), nrows - cvRound(tempChannel2.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
            line(drawImage, Point(bin_w*(i-1), nrows - cvRound(tempChannel3.at<float>(i-1))),
            Point(bin_w*(i), nrows - cvRound(tempChannel3.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
        } 

        namedWindow("H-S Histogram", 1 );
        imshow( "H-S Histogram", drawImage );
        waitKey();
    }else{
        int channels = 0;    
        MatND dstHist;    
        int histSize[] = { 256 };          
        float midRanges[] = { 0, 256 };    
        const float *ranges[] = { midRanges };    
        calcHist(&space, 1, &channels, Mat(), dstHist, 1, histSize, ranges, true, false);    
            
         Mat drawImage = Mat::zeros(Size(256, 256), CV_8UC3);    
        double g_dHistMaxValue;    
        minMaxLoc(dstHist, 0, &g_dHistMaxValue, 0, 0);    
        for (int i = 0; i < 256; i++)    
        {    
            int value = cvRound(dstHist.at<float>(i) * 256 * 0.9 / g_dHistMaxValue);    
            line(drawImage, Point(i, drawImage.rows - 1), Point(i, drawImage.rows - 1 - value), Scalar(100, 0, 255),2,8,0);    
        }    

        namedWindow( name, 1 );
        imshow( name, drawImage );
        waitKey();
    }
}

int LightsLocate::colorMatch(const Mat &src,Color color,Mat &match_mat,bool apaptive_minsv)
{
    const float max_sv = 255;
    const float minref_sv = 45; //30 45
    const float minabs_sv = 30; //30 45

    //H range of green
    const int min_green = 65;   //65
    const int max_green = 120;  //115

    //H range of yellow 
    const int min_yellow = 5;
    const int max_yellow = 55;

    //H range of red 
    const int min_red = 145;  //145
    const int max_red = 200;     //175

    Mat hsvSpace ;
    vector<Mat> hsvChannels(3);

    //equalizeHist(src,src);
    cvtColor(src,hsvSpace,CV_BGR2HSV);
    split(hsvSpace,hsvChannels);
    equalizeHist(hsvChannels[2],hsvChannels[2]);
    merge(hsvChannels,hsvSpace);

    int min_h = 0;
    int max_h = 0;

    switch(color){
        case GREEN:
            min_h = min_green;
            max_h = max_green;
            break;
        
        case YELLOW:
            min_h = min_yellow;
            max_h = max_yellow;
            break;

        case RED:
            min_h = min_red;
            max_h = max_red;
            break;

        default:
            break;
    }

    float diff_h = float((max_h - min_h) / 2);
    float avg_h = min_h + diff_h;

    int nRows = hsvSpace.rows;
    int nCols = hsvSpace.cols*hsvSpace.channels();
    if (hsvSpace.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    for (int i = 0; i < nRows; i++)
    {
        uchar *dataptr = hsvSpace.ptr<uchar>(i);
        for (int j = 0; j < nCols; j += 3)
        {
            int Hvalue = int (dataptr[j]);       //0-180
            int Svalue = int (dataptr[j+1]);     //0-255
            int Value =  int (dataptr[j+2]);     //0-255

            bool colorMatched = false;

            if(Hvalue > min_h && Hvalue < max_h)
            {
                float Hdiff = 0;
                if( Hvalue > avg_h)
                {
                    Hdiff = Hvalue - avg_h;
                }else{
                    Hdiff = avg_h - Hvalue;
                }
   
                float Hdiff_p = float(Hdiff) / diff_h;          
                float min_sv = 0;
                if(apaptive_minsv == true)
                {
                    min_sv = minref_sv - minref_sv / 2 * (1 - Hdiff_p);
                }else{
                    min_sv = minabs_sv;
                }

                if((Svalue > min_sv && Svalue < max_sv) && (Value > min_sv && Value < max_sv))
                    colorMatched = true;
            }

            if(colorMatched == true)
            {
                dataptr[j] = 0;
                dataptr[j+1] = 0;
                dataptr[j + 2] = 255;
            }else{
                dataptr[j] = 0;
                dataptr[j+1] = 0;
                dataptr[j+2] = 0;
            }
        }
    }

    vector<Mat> hsvSplit;
    split(hsvSpace,hsvSplit);
    match_mat = hsvSplit[2];
    return 0;
}

int LightsLocate::testValue(const Mat &src, int minValue, int maxValue)
{
    int nRows = src.rows;
    int nCols = src.cols;
    Mat colorSpace;
    map<int,int> hashmap;
    Mat tempChannel1,tempChannel2,tempChannel3;
    vector<Mat> SpaceChannel;
    cvtColor(src,colorSpace,CV_BGR2HSV);
    split(colorSpace,SpaceChannel);
    tempChannel1 = SpaceChannel[0];
    tempChannel2 = SpaceChannel[1];
    tempChannel3 = SpaceChannel[2];

    histgram(SpaceChannel,tempChannel1,false,"H-histgram");
    histgram(SpaceChannel,tempChannel2,false,"S-histgram");
    histgram(SpaceChannel,tempChannel3,false,"V-histgram");

    for (int i = 0; i < nRows; i++)
    {
        uchar *dataptr = tempChannel1.ptr<uchar>(i);
        for (int j = 0; j < nCols; j++)
        {
            if(++hashmap[dataptr[j]] >= hashmap[0]) maxValue = dataptr[j];

            if(j / 20 == 0)
            cout << (int)dataptr[j] <<" ";
        }
        cout << endl;
    }

    for (int i = 0; i < nRows; i++)
    {
        uchar *dataptr = tempChannel2.ptr<uchar>(i);
        for (int j = 0; j < nCols; j++)
        {
            if(++hashmap[dataptr[j]] >= hashmap[0]) maxValue = dataptr[j];
            if(j / 20 == 0)
            cout << (int)dataptr[j] <<" ";
        }
        cout << endl;
    }

    for (int i = 0; i < nRows; i++)
    {
        uchar *dataptr = tempChannel3.ptr<uchar>(i);
        for (int j = 0; j < nCols; j++)
        {
             if(++hashmap[dataptr[j]] >= hashmap[0]) maxValue = dataptr[j];
            if(j / 20 == 0)
            cout << (int)dataptr[j] <<" ";
        }
        cout << endl;
    }
    

    namedWindow("src");
    imshow("src",src);
    waitKey(0);
    return maxValue;

}


bool LightsLocate::verifySizes(RotatedRect mr)
{
    float width  = (float) mr.size.width;
    float height = (float) mr.size.height;
    float aspect = 2;
    float error = 0.8;
    
    float area = width*height;
    float whratio = width / height;

    if (whratio < 1)
    {
        whratio = height / width;
    }
    
    if ( area > 8000 || whratio > 3 || whratio < 0.9  || area < 100/whratio )
    {
        return false;
    }

    return true;
}

void LightsLocate::enlargeROi(const Mat src,const Rect_<float> &roi_rect,Rect_<float> &large_roi)
{
    int nRows = src.rows;
    int nCols = src.cols;

    float width = roi_rect.width;
    float height = roi_rect.height;

    if(width > height)
    {
        swap(width,height);
    }

    float x = roi_rect.x - 40 > 0 ? roi_rect.x - 40: 0;
    float y = roi_rect.y - 20  > 0 ? roi_rect.y - 20 : 0 ;
    

    width = x + width + 100 > src.cols ? src.cols - x -1 : width + 100;
    height = y + height + 140 > src.rows ? src.rows - y -1 : height + 140;

    
    large_roi.x = x;
    large_roi.y = y;
    large_roi.width = width;
    large_roi.height = height ;
}


bool LightsLocate::veritycontours(Mat src,RotatedRect &rotarec)
{
    float width = rotarec.size.width;
    float height = rotarec.size.height;

    if (width > height)
    {
        swap(width,height);
    }

    float hwratio = height / width;
    float area = width * height;
    
    if (area > 550*hwratio || hwratio > 1.5 || area < 20/hwratio)   
    {
        return false;
    }
    
    return true;

}


void LightsLocate::enlargeROisecond(const Mat src,const Rect_<float> &roi_rect,Rect_<float> &large_roi)
{
    float x = roi_rect.x - 10 > 0 ? roi_rect.x - 10: 0;
    float y = roi_rect.y - 10 > 0 ? roi_rect.y - 10 :0;
    
    float    width = x + roi_rect.width + 20 > src.cols ? src.cols - x -1 : roi_rect.width + 20 - 1;
    float    height = y + roi_rect.height + 20 > src.rows ? src.rows - y -1 : roi_rect.height + 20 -1;

    large_roi.x = x;
    large_roi.y = y;
    large_roi.width = width;
    large_roi.height = height;
}


int LightsLocate::colorSearch(const Mat &src,vector<Mat> &roi_mat,vector<Rect_<float>> &outRects,bool debug)
{   
        int rows = src.rows;
    int cols = src.cols;
    const int erosion_size = 5; // 3  灯的大小大约为10*10
    const int erosion_size1 = 1;

    Mat thresh_mat,gray_mat,fixed_mat;
    Mat dilat_mat,erode_mat,morph_mat;
    Mat gaussianMat;
    Mat darkChannel;

    Mat element = getStructuringElement(MORPH_RECT,Size(2*erosion_size + 1,2*erosion_size + 1),Point(erosion_size,erosion_size));

    if(src.empty())
    {
        cerr << "Image data error!";
        return 0;
    }
    
    fixed_mat = src(Rect(Point(cols / 10,rows / 10),Size(cols*9 / 10 ,rows /2))); //Size((cols *2 )/ 3,rows /2))
    
    
    GaussianBlur(fixed_mat,gaussianMat,Size(3,3),0,0,BORDER_DEFAULT);
    
    if (gaussianMat.channels() == 3)
    {
        cvtColor(gaussianMat,gray_mat,CV_RGB2GRAY);
    }
    else{
        gray_mat = gaussianMat;
    }

    threshold(gray_mat,thresh_mat,0,255,THRESH_BINARY+THRESH_OTSU);

    dilate(thresh_mat,dilat_mat,element);
    
    morph_mat =  255 - dilat_mat ; 

    dilate(morph_mat,morph_mat,element);

    medianBlur(morph_mat,morph_mat,7);
    
    vector<vector<Point>>contours;
    vector<Vec4i>hierarchy; 
    findContours(morph_mat,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE);
    vector<cv::RotatedRect> rocatedrect;
    vector<vector<cv::Point>>::iterator itc = contours.begin();

    while( itc != contours.end())
    {
        RotatedRect mr = minAreaRect(Mat(*itc));
        if(!verifySizes(mr))
        {
            itc = contours.erase(itc);   
        }else{
            ++itc;
            rocatedrect.push_back(mr);
        }
    }

    for (size_t i = 0; i < rocatedrect.size(); i++)
    {
        RotatedRect Roi_rect = rocatedrect[i];
        Rect_<float> safeBoundRect;
        Rect_<float> enlargeRect;
        if(!calcSafeRect(Roi_rect,fixed_mat,safeBoundRect)) 
        {
            continue;
        }else{
            enlargeROi(fixed_mat,safeBoundRect,enlargeRect);
        }
        outRects.push_back(enlargeRect);
        roi_mat.push_back(fixed_mat(enlargeRect));
    }
    
    if(debug)
    {
        dispImage(fixed_mat,outRects,"locate_first",true);
    }

    return 0;

}

int LightsLocate::searchsecond(vector<Mat> firstresult,vector<Rect_<float>> firstrect,vector<Mat> &imgcollection,vector<Rect_<float>> &roirect,bool debug)
{
    /*-----------------------------------------------------------------------------------
     * function name:searchsecond
     * Input:firstresult 第一次搜索之后找到的大面积的交通灯区域,
     *       firstrect   第一次搜索之后得到的最终的矩形区域
     * Output: imgcollection 小区域找到的经过筛选之后的交通灯区域的vector<Mat> 
     *         roirect 第二次精确搜索之后得到的矩形区域   这里传出的roirect的坐标是相对于原始图像的
     *         roirect.x = firstrect.x + roirect.x;
     *         roirect.y = firstrect.y + roirect.y;
     * function: 经过精细化的二次搜索，找到更加精确的交通灯区域
     * Author:Richard Tseng
     * Date:2018.07.09
     *-------------------------------------------------------------------------------------*/

    int erosion_size = 5;  
    Mat src_mat;
    Mat thresh_mat,morph_mat,tophat,gray_mat;
    Mat element = getStructuringElement(MORPH_RECT,Size(2*erosion_size + 1,2*erosion_size + 1),Point(erosion_size,erosion_size));
    for(int i = 0; i < firstresult.size(); i++)
    {
        float x1 = firstrect[i].x;
        float y1 = firstrect[i].y;

        Mat img = firstresult[i];
        if(img.channels() == 3)
        {
            cvtColor(img,gray_mat,COLOR_BGR2GRAY);
        }else{
            gray_mat = img;
        }

        morphologyEx(gray_mat,morph_mat,MORPH_OPEN,element,Point(-1,-1),2,BORDER_CONSTANT,Scalar(0));
        tophat = gray_mat - morph_mat;
    
        threshold(tophat,thresh_mat,0,255,CV_THRESH_BINARY + CV_THRESH_OTSU); 
        medianBlur(thresh_mat,thresh_mat,3);     

                vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(thresh_mat,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE);
        vector<vector<Point>>::iterator itc = contours.begin();

        vector<RotatedRect> rectvec;
        while(itc != contours.end())
        {
            RotatedRect  rotarect = minAreaRect(*itc);
            
            if(!veritycontours(thresh_mat,rotarect))
            {
                contours.erase(itc);
            }else{
                ++itc;
                rectvec.push_back(rotarect);
            }
        }

        vector<Rect_<float>> originalrect;
        for(int j = 0; j < rectvec.size(); j++)
        {
            RotatedRect   rectrote = rectvec[j];
            Rect_<float> saferect;
            Rect_<float> enlargeRect;

            if(!calcSafeRect(rectrote,thresh_mat,saferect))
            {
                continue;
            }else{
                enlargeROisecond(img,saferect,enlargeRect);
            }
            imgcollection.push_back(img(enlargeRect));  
            originalrect.push_back(enlargeRect);
            enlargeRect.x = enlargeRect.x + x1;
            enlargeRect.y = enlargeRect.y + y1;
            roirect.push_back(enlargeRect);
        }
        dispImage(img,originalrect,"second",debug); 
    }
    return 0; 
}

int LightsLocate::shapeSearch(const Mat &src,vector<Mat> &outRects)
{

}

int LightsLocate::sobelFrtSearch(const Mat &src,vector<Mat> &outRects)
{
    int result = sobelSearch(src,outRects,GaussianBlurSize,MorphSizeWidth,MorphSizeHeight);
    return 0;
}

void LightsLocate::paraSet(bool para)
{
    if (para)
    {
        setGaussianBlurSize(5);
        setMorphSizeWidth(10);
        setMOrphSizeHeight(3);
    }
    else{
        setGaussianBlurSize(DEFAULT_GAUSSIANBLUR_SIZE);
        setMorphSizeWidth(DEFAULT_MORPH_SIZE_WIDTH);
        setMOrphSizeHeight(DEFAULT_MORPH_SIZE_HEIGHT);
    }
}
}
