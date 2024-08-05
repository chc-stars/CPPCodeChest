//#include <iostream>
//#include "utils.h"
//
//#include <pcl/point_types.h>
//#include <pcl/point_cloud.h>
//#include <pcl/kdtree/kdtree_flann.h>
//#include <pcl/io/pcd_io.h>
//#include <opencv2/opencv.hpp>
//#include <pcl/common/point_tests.h>
//#include <future>
//#include <filesystem>
//#include <algorithm>
//#include <vector>
//#include <fstream>
//
//#include <pcl/filters/passthrough.h>
//#include <pcl/common/common.h>
//
//using namespace std;
//namespace fs = std::filesystem;
//
//
//cv::Mat convertPointCloudToDepthMap(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, int width, int height) {
//    // �������ͼ
//    cv::Mat depthMap = cv::Mat::zeros(height, width, CV_16U);
//
//    // �������ͼ��������С���ֵ
//    float minDepth = std::numeric_limits<float>::max();
//    float maxDepth = std::numeric_limits<float>::min();
//
//    for (const auto& point : cloud->points) {
//        if (pcl::isFinite(point)) {
//            minDepth = std::min(minDepth, point.z);
//            maxDepth = std::max(maxDepth, point.z);
//        }
//    }
//
//    // ����������ӳ�䵽���ͼ
//    for (const auto& point : cloud->points) {
//
//        if (pcl::isFinite(point)) {
//            // ���������ӳ�䵽���ͼ������λ��
//            int x = static_cast<int>((point.x - cloud->sensor_origin_[0]) * width / (cloud->sensor_origin_[0] + cloud->sensor_origin_[3]));
//            int y = static_cast<int>((point.y - cloud->sensor_origin_[1]) * height / (cloud->sensor_origin_[1] + cloud->sensor_origin_[4]));
//
//            // �����ֵӳ�䵽���ͼ������ֵ��Χ
//            uint16_t depthValue = static_cast<uint16_t>((point.z - minDepth) / (maxDepth - minDepth) * std::numeric_limits<uint16_t>::max());
//
//            // �߽��飬ȷ��x��y��ͼ��Χ��
//            if (x >= 0 && x < width && y >= 0 && y < height) {
//                // �������ͼ�ϵ�����ֵ
//                depthMap.at<uint16_t>(y, x) = depthValue;
//            }
//            else {
//                std::cerr << "Pixel coordinates out of bounds: (" << x << ", " << y << ")" << std::endl;
//            }
//        }
//    }
//
//    return depthMap;
//}
//
//
//pcl::PointCloud<pcl::PointXYZ>::Ptr extractPointsInRegionKDTree(const pcl::PointCloud<pcl::PointXYZ>::Ptr& inputCloud,
//    float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
//{
//    pcl::PointCloud<pcl::PointXYZ>::Ptr outputCloud(new pcl::PointCloud<pcl::PointXYZ>);
//
//    // ���� KD-Tree
//    pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
//    kdtree.setInputCloud(inputCloud);
//
//    // �����ѯ��
//    pcl::PointXYZ queryPoint;
//    queryPoint.x = (minX + maxX) / 2.0;
//    queryPoint.y = (minY + maxY) / 2.0;
//    queryPoint.z = (minZ + maxZ) / 2.0;
//
//    // �����ѯ�뾶
//    float radius = std::max({ (maxX - minX) / 2.0, (maxY - minY) / 2.0, (maxZ - minZ) / 2.0 });
//
//    // ��ѯ���ڵ�
//    std::vector<int> pointIndices;
//    std::vector<float> pointDistances;
//    kdtree.radiusSearch(queryPoint, radius, pointIndices, pointDistances);
//
//    // ��ȡ���ڵ�
//    for (const auto& index : pointIndices) {
//        outputCloud->points.push_back(inputCloud->points[index]);
//    }
//
//    return outputCloud;
//}
//
//
//pcl::PointCloud<pcl::PointXYZ>::Ptr extractPointsInRegion(const pcl::PointCloud<pcl::PointXYZ>::Ptr& inputCloud,
//    float minX, float maxX,
//    float minY, float maxY,
//    float minZ, float maxZ) {
//    pcl::PointCloud<pcl::PointXYZ>::Ptr outputCloud(new pcl::PointCloud<pcl::PointXYZ>);
//
//    // ����������ƣ���ȡ�������������ĵ�
//    for (const auto& point : inputCloud->points) {
//        if (point.x >= minX && point.x <= maxX &&
//            point.y >= minY && point.y <= maxY &&
//            point.z >= minZ && point.z <= maxZ) {
//            outputCloud->points.push_back(point);
//        }
//    }
//    return outputCloud;
//}
//
//
//pcl::PointCloud<pcl::PointXYZ>::Ptr mergePCDFiles(const std::vector<std::string>& fileNames) {
//    // ����һ�����ƶ������ڴ洢�ϲ���ĵ�������
//    pcl::PointCloud<pcl::PointXYZ>::Ptr mergedCloud(new pcl::PointCloud<pcl::PointXYZ>);
//
//    // ��������ÿ�� PCD �ļ����������ݺϲ���һ�����ƶ�����
//    for (const auto& fileName : fileNames) {
//        // ����һ����ʱ�ĵ��ƶ������ڼ��ص�ǰ�ļ�������
//        pcl::PointCloud<pcl::PointXYZ>::Ptr tempCloud(new pcl::PointCloud<pcl::PointXYZ>);
//
//        // ���ص�ǰ�ļ��ĵ�������
//        if (pcl::io::loadPCDFile<pcl::PointXYZ>(fileName, *tempCloud) == -1) {
//            PCL_ERROR("Couldn't read file %s\n", fileName.c_str());
//            return nullptr;
//        }
//
//        // ����ǰ���Ƶ����ݺϲ����ܵĵ��ƶ�����
//        *mergedCloud += *tempCloud;
//    }
//
//    return mergedCloud;
//}