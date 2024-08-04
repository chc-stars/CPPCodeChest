#include "nms.h"
//


static bool cmp(const Detection& a, const Detection& b) {
	return a.conf > b.conf;
}

static float iou(float lbox[4], float rbox[4]) {
	float interBox[] = {
	  (std::max)(lbox[0] - lbox[2] / 2.f , rbox[0] - rbox[2] / 2.f), //left
	  (std::min)(lbox[0] + lbox[2] / 2.f , rbox[0] + rbox[2] / 2.f), //right
	  (std::max)(lbox[1] - lbox[3] / 2.f , rbox[1] - rbox[3] / 2.f), //top
	  (std::min)(lbox[1] + lbox[3] / 2.f , rbox[1] + rbox[3] / 2.f), //bottom
	};

	if (interBox[2] > interBox[3] || interBox[0] > interBox[1])
		return 0.0f;

	float interBoxS = (interBox[1] - interBox[0]) * (interBox[3] - interBox[2]);
	return interBoxS / (lbox[2] * lbox[3] + rbox[2] * rbox[3] - interBoxS);
}

void NMS(std::vector<Detection>& res, float* output, const float& conf_thresh, const float& nms_thresh) {
	int det_size = sizeof(Detection) / sizeof(float);
	std::map<float, std::vector<Detection>> m;
	for (int i = 0; i < output[0]; i++) {
		if (output[1 + det_size * i + 4] <= conf_thresh) continue;
		Detection det;
		memcpy(&det, &output[1 + det_size * i], det_size * sizeof(float));
		if (m.count(det.class_id) == 0) m.emplace(det.class_id, std::vector<Detection>());
		m[det.class_id].push_back(det);
	}
	for (auto it = m.begin(); it != m.end(); it++) {
		auto& dets = it->second;
		std::sort(dets.begin(), dets.end(), cmp);
		for (size_t m = 0; m < dets.size(); ++m) {
			auto& item = dets[m];
			res.push_back(item);
			for (size_t n = m + 1; n < dets.size(); ++n) {
				if (iou(item.bbox, dets[n].bbox) > nms_thresh) {
					dets.erase(dets.begin() + n);
					--n;
				}
			}
		}
	}
}


