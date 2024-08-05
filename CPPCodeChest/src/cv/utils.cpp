#include "utils.h"


cv::Mat adjustBrightness(const cv::Mat& inputImage, double alpha) {
    cv::Mat adjustedImage;
    inputImage.convertTo(adjustedImage, -1, alpha, 0); // 亮度调整

    return adjustedImage;
}


double getImageBrightnessValue(const cv::Mat& inputImage) {
    if (inputImage.empty()) {
        // 图像为空，进行错误处理
        throw std::runtime_error("输入图像为空");
    }

    if (inputImage.channels() != 3) {
        // 非彩色图像，进行错误处理
        throw std::runtime_error("输入图像不是彩色图像");
    }

    cv::Scalar avg_intensity = cv::mean(inputImage);
    double brightness = 0.299 * avg_intensity[2] + 0.587 * avg_intensity[1] + 0.114 * avg_intensity[0];
    return brightness;
}
