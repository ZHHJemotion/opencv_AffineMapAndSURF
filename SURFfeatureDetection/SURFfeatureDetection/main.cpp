//
//  main.cpp
//  SURFfeatureDetection --- SURF特征检测
//
//  Created by ZHHJemotion on 2016/11/18.
//  Copyright © 2016年 Lukas_Zhang. All rights reserved.
//

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>

#define PATH string("/Users/zhangxingjian/Desktop/Programming/C++/OpenCV/opencv_AffineMapAndSURF/SURFfeatureDetection/SURFfeatureDetection/")

using namespace cv;
using namespace std;

//全局函数申明
static void showHelpText(); //输出帮助文字

// ----------------------- main() function ------------------------------
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    showHelpText();
    
    //载入图像
    Mat srcImage1 = imread(PATH+string("1.jpg"),1);
    Mat srcImage2 = imread(PATH+string("2.jpg"),1);
    //异常处理
    if (!srcImage1.data || !srcImage2.data)
    {
        printf("Error! We cannot read these two source images!!!\n\n");
        return false;
    }
    
    //使用SURF算子检测关键点
    int minHessian = 700; //SURF算法中的hessian阈值
    SurfFeatureDetector detector(minHessian); //定义一个SurfFeatureDetector(SURF)特征检测类对象
    std::vector<KeyPoint> keyPoint1, keyPoint2; //Vector模板类，存放任意类型的动态数组
    
    //调用detect函数检测出SURF特征关键点，保存在vector容器中
    detector.detect(srcImage1, keyPoint1);
    detector.detect(srcImage2, keyPoint2);
    
    //========================= Features Description ======================================
    //Use the DescriptorExtractor interface in order to find the feature vector correspondent to the keypoints. Specifically:
    // 1】Use SurfDescriptorExtractor and its function compute to perform the required calculations.
    // 2】Use a BFMatcher to match the features vector
    // 3】Use the function drawMatches to draw the detected matches.
    
    // 1】计算描述符（特征向量）
    SurfDescriptorExtractor extractor;
    Mat descriptors1, descriptors2;
    extractor.compute(srcImage1, keyPoint1, descriptors1);
    extractor.compute(srcImage2, keyPoint2, descriptors2);
    
    // 2】使用Bruteforce进行匹配
    //实例化一个匹配器
    BruteForceMatcher<L2<float>> matcher;
    //BFMatcher matcher(NORM_L2); //这个表述方式和上面的相同
    // NORM_L2 见 link：http://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html#norm
    std::vector<DMatch> matches;
    //struct DMatch is the Class for matching keypoint descriptors: query descriptor index, train descriptor index, train image index, and distance between descriptors.
    //匹配两幅图中的描述子（descriptors）
    matcher.match(descriptors1, descriptors2, matches);
    //void DescriptorMatcher::match(const Mat& queryDescriptors, const Mat& trainDescriptors, vector<DMatch>& matches, const Mat& mask=Mat())
    
    // 3】绘制从两个图像中匹配出的特征关键点
    Mat matchesImage;
    drawMatches(srcImage1, keyPoint1, srcImage2, keyPoint2, matches, matchesImage);
    // =====================================================================================
    
    //显示匹配图
    namedWindow("the match image", WINDOW_AUTOSIZE);
    imshow("the match image", matchesImage);
    //保存匹配图
    imwrite(PATH+string("matchesImage.jpg"), matchesImage);
    
    waitKey(0);
    
    return 0;
}


// ------------------------ showHelpText() function -------------------------
static void showHelpText()
{
    //输出一些帮助信息
    printf("\n\n\n\t欢迎来到【SURF特征描述】示例程序~\n\n");
    std::cout<<"\t当前使用的OpenCV版本为 OpenCV"<<CV_VERSION;
    printf("\n\n\t\t\t\t\t\t\t\t by ZHHJemotion\n\n\n");
}
