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
//    // 创建深度图
//    cv::Mat depthMap = cv::Mat::zeros(height, width, CV_16U);
//
//    // 计算深度图的最大和最小深度值
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
//    // 将点云数据映射到深度图
//    for (const auto& point : cloud->points) {
//
//        if (pcl::isFinite(point)) {
//            // 将点的坐标映射到深度图的像素位置
//            int x = static_cast<int>((point.x - cloud->sensor_origin_[0]) * width / (cloud->sensor_origin_[0] + cloud->sensor_origin_[3]));
//            int y = static_cast<int>((point.y - cloud->sensor_origin_[1]) * height / (cloud->sensor_origin_[1] + cloud->sensor_origin_[4]));
//
//            // 将深度值映射到深度图的像素值范围
//            uint16_t depthValue = static_cast<uint16_t>((point.z - minDepth) / (maxDepth - minDepth) * std::numeric_limits<uint16_t>::max());
//
//            // 边界检查，确保x和y在图像范围内
//            if (x >= 0 && x < width && y >= 0 && y < height) {
//                // 设置深度图上的像素值
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
//    // 创建 KD-Tree
//    pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
//    kdtree.setInputCloud(inputCloud);
//
//    // 定义查询点
//    pcl::PointXYZ queryPoint;
//    queryPoint.x = (minX + maxX) / 2.0;
//    queryPoint.y = (minY + maxY) / 2.0;
//    queryPoint.z = (minZ + maxZ) / 2.0;
//
//    // 定义查询半径
//    float radius = std::max({ (maxX - minX) / 2.0, (maxY - minY) / 2.0, (maxZ - minZ) / 2.0 });
//
//    // 查询近邻点
//    std::vector<int> pointIndices;
//    std::vector<float> pointDistances;
//    kdtree.radiusSearch(queryPoint, radius, pointIndices, pointDistances);
//
//    // 提取近邻点
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
//    // 遍历输入点云，提取符合区间条件的点
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
//    // 创建一个点云对象，用于存储合并后的点云数据
//    pcl::PointCloud<pcl::PointXYZ>::Ptr mergedCloud(new pcl::PointCloud<pcl::PointXYZ>);
//
//    // 遍历加载每个 PCD 文件并将其数据合并到一个点云对象中
//    for (const auto& fileName : fileNames) {
//        // 创建一个临时的点云对象，用于加载当前文件的数据
//        pcl::PointCloud<pcl::PointXYZ>::Ptr tempCloud(new pcl::PointCloud<pcl::PointXYZ>);
//
//        // 加载当前文件的点云数据
//        if (pcl::io::loadPCDFile<pcl::PointXYZ>(fileName, *tempCloud) == -1) {
//            PCL_ERROR("Couldn't read file %s\n", fileName.c_str());
//            return nullptr;
//        }
//
//        // 将当前点云的数据合并到总的点云对象中
//        *mergedCloud += *tempCloud;
//    }
//
//    return mergedCloud;
//}