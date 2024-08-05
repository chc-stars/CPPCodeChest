#pragma once
#include <opencv2/opencv.hpp>

// ����ͼ�����ȡ�para1��ԭʼͼ�� para2������ֵ�� ���ص����������ͼ
cv::Mat adjustBrightness(const cv::Mat& inputImage, double alpha);

// ��ȡͼ������ֵ
double getImageBrightnessValue(const cv::Mat& inputImage);