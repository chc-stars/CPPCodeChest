//#pragma once
//
//#pragma once
//#include <pcl/point_cloud.h>
//#include <pcl/point_types.h>
//#include <opencv2/opencv.hpp>
//#include <filesystem>
//
//// ����ṹ��
//struct pointCloudXYZAxisRange {
//    Eigen::Vector2f xRange;
//    Eigen::Vector2f yRange;
//    Eigen::Vector2f zRange;
//
//    Eigen::Array3i xyzSize;  // �洢x�� y�� z������ֵ
//};
//
//struct Point2D {
//    double x;
//    double z;
//};
//
//struct matchResult {
//    cv::Rect boundingBox;
//    double score;
//};
//
//void getPointCloudRangeAndSize(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, pointCloudXYZAxisRange& XYZAxisRange_);
//
//cv::Mat convertPointCloudToDepthMap(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, int width, int height);
//pcl::PointCloud<pcl::PointXYZ>::Ptr extractPointsInRegion(const pcl::PointCloud<pcl::PointXYZ>::Ptr& inputCloud,
//    float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
//
//pcl::PointCloud<pcl::PointXYZ>::Ptr extractPointsInRegionKDTree(const pcl::PointCloud<pcl::PointXYZ>::Ptr& inputCloud,
//    float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
//
//pcl::PointCloud<pcl::PointXYZ>::Ptr mergePCDFiles(const std::vector<std::string>& fileNames);        //  �������������ݴ洢Ϊһ���µĵ���