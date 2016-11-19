//
//  main.cpp
//  AffineTransformation 仿射变换
//
//  Created by ZHHJemotion on 2016/11/18.
//  Copyright © 2016年 Lukas_Zhang. All rights reserved.
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

#define PATH string("/Users/zhangxingjian/Desktop/Programming/C++/OpenCV/opencv_AffineMapAndSURF/AffineTransformation/AffineTransformation/")

// 窗口标题宏定义
#define WINDOW_NAME1 "原始图窗口"
#define WINDOW_NAME2 "经过Warp后的图像"
#define WINDOW_NAME3 "经过Warp和Rotate后的图像"

using namespace cv;
using namespace std;

//全局函数声明
static void showHelpText();

// =================== main() function ================================
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //显示帮助文字
    showHelpText();
    
    //参数准备
    //定义两组点，代表两个三角形
    Point2f srcTriangle[3];
    Point2f dstTriangle[3];
    //定义一些 Mat 变量
    Mat rotMat(2, 3, CV_32FC1);
    Mat warpMat(2, 3, CV_32FC1);
    Mat srcImage, dstImageWarp, dstImageWarpRotate;
    
    //加载源图像并做一些初始化
    srcImage = imread(PATH+string("1.jpg"),1);
    //异常处理
    if (!srcImage.data)
    {
        printf("Error!!! We can't read the source image!!!");
        return false;
    }
    //设置目标图像的大小和类型与源图像一致
    dstImageWarp = Mat::zeros(srcImage.size(), srcImage.type());
    
    //设置源图像和目标图像上的三组点以计算仿射变换
    //源图像
    srcTriangle[0] = Point2f(0,0);
    srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
    srcTriangle[2] = Point2f(0, static_cast<float>(srcImage.rows - 1));
    //目标图像
    dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols*0.0), static_cast<float>(srcImage.rows*0.33));
    dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols*0.65), static_cast<float>(srcImage.rows*0.35));
    dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols*0.15), static_cast<float>(srcImage.rows*0.6));
    
    //求得仿射变换矩阵
    warpMat = getAffineTransform(srcTriangle, dstTriangle);
    
    //对源图像进行仿射变换
    warpAffine(srcImage, dstImageWarp, warpMat, dstImageWarp.size());
    
    //对图像进行缩放后再旋转
    //
    
    return 0;
}
