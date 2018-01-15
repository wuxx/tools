//check http://blog.csdn.net/u012385733/article/details/41379855
//https://www.cnblogs.com/xia-weiwen/archive/2017/05/04/6806709.html
#include <stdio.h>  
#include <stdlib.h>  
#include <sqlite3.h>  

void dump_table(sqlite3 *db)
{
  	int nrow = 0, ncolumn = 0;  
	int i = 0;
 	char **azResult;
	char *zErrMsg = 0;
	char *sql3 = "SELECT * FROM SensorData ";  

	sqlite3_get_table(db , sql3, &azResult, &nrow, &ncolumn, &zErrMsg);

	printf( "row:%d column=%d \n" , nrow, ncolumn);  
	printf( "\nThe result of querying is : \n");  

	for(i = 0; i < ( nrow + 1 ) * ncolumn ; i++) {

        if (i != 0 && i % ncolumn == 0) { printf("\n"); }

		//printf( "azResult[%d] = %s\n", i , azResult[i]);  
		printf( "%s ", azResult[i]);  
	}

    printf("\n");

	sqlite3_free_table(azResult);  

}

int main( void )  
{  
	sqlite3 *db = NULL;
	char *zErrMsg = 0;
	int rc;

	//打开指定的数据库文件,如果不存在将创建一个同名的数据库文件  
	rc = sqlite3_open("hello.db", &db);

	if( rc )
	{  
		fprintf(stderr, "Can't open database: %s/n", sqlite3_errmsg(db));  
		sqlite3_close(db);  
		exit(1);  
	}  
	else printf("You have opened a sqlite3 database named hello.db successfully!\nCongratulations! Have fun !  ^-^ \n");  

	//sqlite3_close(db); //关闭数据库  

    char *sql = "CREATE TABLE SensorData(ID INTEGER PRIMARY KEY, SensorID INTEGER, SiteNum INTEGER, Time VARCHAR(12), SensorParameter REAL);";
    sqlite3_exec(db, sql, 0, 0, &zErrMsg);  

    char* sql1 = "INSERT INTO \"SensorData\" VALUES(NULL, 1, 1, '200605011206', 18.9);";  
    sqlite3_exec(db, sql1, 0, 0, &zErrMsg);  

    char* sql2 = "INSERT INTO \"SensorData\" VALUES(NULL, 1, 1, '200605011306', 16.4);";  
    sqlite3_exec(db, sql2, 0, 0, &zErrMsg);  

    dump_table(db);

    char *sql4 = "DELETE FROM SensorData WHERE SensorID = 1 ;";
    sqlite3_exec(db, sql4, 0, 0, &zErrMsg);  

    dump_table(db);

	sqlite3_close(db);

    return 0;  
}  
