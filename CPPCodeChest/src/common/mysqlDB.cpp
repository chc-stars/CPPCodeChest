#include "mysqlDB.h"


// 插入数据

int insertToReportData(MYSQL* conn, StrReportData data, unsigned long& rowId, char& errorInfo) {

    char insert_stmt[12800];  // 设置长度
    int ret_ = snprintf(insert_stmt, sizeof(insert_stmt), "INSERT INTO reportData (userName, email) VALUES ('%s', '%s')", data.username.c_str(), data.email.c_str());

    if (ret_ < 0) {
        fprintf(stderr, "Failed to format insert statement\n");
        return -1;
    }
    int ret = mysql_query(conn, insert_stmt);
    if (ret) {
        fprintf(stderr, "mysql_query() failed - find \n");
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        errorInfo = mysql_errno(conn);
        return -1;
    }
    unsigned long long insert_id;
    // 获取插入数据的行ID
    insert_id = mysql_insert_id(conn);
    printf("Inserted row ID: %llu\n", insert_id);

    rowId = insert_id;

    return 0;
}


// 删除数据

int deleteReportData(MYSQL* conn, StrReportData data, char& errorInfo) {

    // 删除数据
    char delete_stmt[12800];

    int ret_ = snprintf(delete_stmt, sizeof(delete_stmt), "DELETE FROM reportData WHERE 1=1");
    if (ret_ < 0) {
        fprintf(stderr, "Failed to format delete statement\n");
        // errorInfo = "Failed to format delete statement\n";
        return -1;
    }

    if (data.arrVild[0]) {
        snprintf(delete_stmt + strlen(delete_stmt), sizeof(delete_stmt) - strlen(delete_stmt), " AND username = '%s'", data.username.c_str());
    }
    if (data.arrVild[1]) {
        snprintf(delete_stmt + strlen(delete_stmt), sizeof(delete_stmt) - strlen(delete_stmt), " AND email = '%s'", data.email.c_str());
    }

    if (mysql_query(conn, delete_stmt)) {
        fprintf(stderr, "mysql_query() delete failed\n");
        // errorInfo = "Failed to format delete statement\n";
        mysql_close(conn);
        return -1;
    }

    return 0;

}

