#include "utils.h"


cv::Mat adjustBrightness(const cv::Mat& inputImage, double alpha) {
    cv::Mat adjustedImage;
    inputImage.convertTo(adjustedImage, -1, alpha, 0); // ���ȵ���

    return adjustedImage;
}


double getImageBrightnessValue(const cv::Mat& inputImage) {
    if (inputImage.empty()) {
        // ͼ��Ϊ�գ����д�����
        throw std::runtime_error("����ͼ��Ϊ��");
    }

    if (inputImage.channels() != 3) {
        // �ǲ�ɫͼ�񣬽��д�����
        throw std::runtime_error("����ͼ���ǲ�ɫͼ��");
    }

    cv::Scalar avg_intensity = cv::mean(inputImage);
    double brightness = 0.299 * avg_intensity[2] + 0.587 * avg_intensity[1] + 0.114 * avg_intensity[0];
    return brightness;
}
