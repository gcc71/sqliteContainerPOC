#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <vector>
//go here for more examples -> https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
using namespace std;

string dbName = "sqliteCPPTest.db";
vector<string> &split(const string &s, char delim, vector<string> &elems) {

    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        elems.push_back(item);

        // if (item.length() > 0) {

        //     elems.push_back(item);
        // }

    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

class cEmp{
public:
  string Name;
  int Age;
  string Address;
  long Salary;
  cEmp(string name, int age, string address, long salary);
};
cEmp :: cEmp(string name, int age, string address, long salary){
  Name = name;
  Age = age;
  Address = address;
  Salary = salary;
}
vector<cEmp> v;
void buildCEmp(string s){
  vector<string> d = split(s, ',');
  //cout << d[1] << " " << d[2] << " " << d[3] << " " << d[4] << endl;
  cEmp ce(d[1], stoi(d[2]), d[3], stol(d[4]));
  v.push_back(ce);
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   stringstream ss;
   string s;
   for(i = 0; i<argc; i++) {
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      s += argv[i];
      s += ",";

      //buildCEmp(ss.str());

   }
   buildCEmp(s);
   printf("\n");
   return 0;
}

int createTable(){
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  //char *sql;
  string sql;

  /* Open database */
  rc = sqlite3_open(dbName.c_str(), &db);

  if( rc ) {
     fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
     return(0);
  } else {
     fprintf(stdout, "Opened database successfully\n");
  }

  /* Create SQL statement */
  sql = "CREATE TABLE COMPANY("  \
     "ID INT PRIMARY KEY     NOT NULL," \
     "NAME           TEXT    NOT NULL," \
     "AGE            INT     NOT NULL," \
     "ADDRESS        CHAR(50)," \
     "SALARY         REAL );";


  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

  if( rc != SQLITE_OK ){
     fprintf(stderr, "SQL error: %s\n", zErrMsg);
     sqlite3_free(zErrMsg);
  } else {
     fprintf(stdout, "Table created successfully\n");
  }
  sqlite3_close(db);
  return 0;
}//end createTable()

int insertData(){
  sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   //char *sql;
   string sql;

   /* Open database */
   rc = sqlite3_open(dbName.c_str(), &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
   sqlite3_close(db);
  return 0;
}

int selectData(){
  sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   string sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open(dbName.c_str(), &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "SELECT * from COMPANY";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);

   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
  return 0;
}
//main***********************************************************************************//
int main(int argc, char *argv[])
{
  createTable();
  insertData();
  selectData();
  for(auto e : v){
    cout << e.Name << " " << e.Age << " " << e.Address << " " << e.Salary << endl;
  }
  return 0;
}
//end main******************************************************************************//
