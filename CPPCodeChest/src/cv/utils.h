#pragma once
#include <opencv2/opencv.hpp>

// 调整图像亮度。para1：原始图， para2：亮度值， 返回调整后的亮度图
cv::Mat adjustBrightness(const cv::Mat& inputImage, double alpha);

// 获取图像亮度值
double getImageBrightnessValue(const cv::Mat& inputImage);