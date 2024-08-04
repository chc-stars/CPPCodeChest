#pragma once

#include <opencv2/opencv.hpp>
#include <map>


struct alignas(float) Detection {
	float bbox[4];
	float conf;
	float class_id;
};


static bool cmp(const Detection& a, const Detection& b);
static float iou(float lbox[4], float rbox[4]);
	
void NMS(std::vector<Detection>& res, float* output, const float& conf_thresh, const float& nms_thresh);

