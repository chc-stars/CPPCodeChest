#pragma once

#include <iostream>
#include "mysql.h"

// 通过mysql包实现对数据库的增、删、改、查

// eg:

struct StrReportData   // 表结构
{
    std::string username;   // 字段1
    std::string email;      // 字段2

    bool arrVild[2] = { false, false };     
};


int insertToReportData(MYSQL* conn, StrReportData data, unsigned long& rowId, char& errorInfo);
int deleteReportData(MYSQL* conn, StrReportData data, char& errorInfo);


// ************************************** 用例 ***********************************

//int main() {
//
//    MYSQL* conn = mysql_init(NULL);
//    if (conn == NULL) {
//        fprintf(stderr, "mysql_init() failed\n");
//        return 1;
//    }
//
//    if (mysql_real_connect(conn, "127.0.0.1", "root", "950827", "2daoidb", 0, NULL, 0) == NULL) {   // 设置数据库参数
//        fprintf(stderr, "mysql_real_connect() failed\n");
//        fprintf(stderr, "Error: %s\n", mysql_error(conn));
//        mysql_close(conn);
//        return 1;
//    }
//
//    StrReportData where;
//    where.username = "value1";
//    where.email = "value555552";
//    where.arrVild[1] = true;
//    where.arrVild[0] = true;
//    unsigned long rowid;
//    char err;
//
//    insertToReportData(conn, where, rowid, err);  // 插入
//
//    deleteReportData(conn, where, err);  // 删除
//
//    return 0;
//}

