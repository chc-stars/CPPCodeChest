#pragma once

#include <iostream>
#include "mysql.h"

// ͨ��mysql��ʵ�ֶ����ݿ������ɾ���ġ���

// eg:

struct StrReportData   // ��ṹ
{
    std::string username;   // �ֶ�1
    std::string email;      // �ֶ�2

    bool arrVild[2] = { false, false };     
};


int insertToReportData(MYSQL* conn, StrReportData data, unsigned long& rowId, char& errorInfo);
int deleteReportData(MYSQL* conn, StrReportData data, char& errorInfo);


// ************************************** ���� ***********************************

//int main() {
//
//    MYSQL* conn = mysql_init(NULL);
//    if (conn == NULL) {
//        fprintf(stderr, "mysql_init() failed\n");
//        return 1;
//    }
//
//    if (mysql_real_connect(conn, "127.0.0.1", "root", "950827", "2daoidb", 0, NULL, 0) == NULL) {   // �������ݿ����
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
//    insertToReportData(conn, where, rowid, err);  // ����
//
//    deleteReportData(conn, where, err);  // ɾ��
//
//    return 0;
//}

