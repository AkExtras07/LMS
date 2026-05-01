#include "Database.h"
#include <iostream>

	using namespace std;
	
	Database::Database() {
	    con = nullptr;
	}
	
	Database::~Database() {
	    if (con) {
	        delete con;
	        con = nullptr;
	    }
	}
	
	void Database::connect() {
	    try {
	        sql::mysql::MySQL_Driver* driver;
	        driver = sql::mysql::get_mysql_driver_instance();
	
	        con = driver->connect("tcp://127.0.0.1:3306", "root", "admin1234");
	        con->setSchema("my_project_db");
	
	        cout << "Database connected successfully!\n";
	    }
	    catch (sql::SQLException &e) {
	        cout << "Connection Error: " << e.what() << endl;
	    }
	}
	
	void Database::execute(const string& query) {
	    try {
	        sql::Statement* stmt = con->createStatement();
	        stmt->execute(query);
	        delete stmt;
	    }
	    catch (sql::SQLException &e) {
	        cout << "Execute Error: " << e.what() << endl;
	    }
	}
	
	sql::ResultSet* Database::query(const string& query) {
	    try {
	        sql::Statement* stmt = con->createStatement();
	        return stmt->executeQuery(query);
	    }
	    catch (sql::SQLException &e) {
	        cout << "Query Error: " << e.what() << endl;
	        return nullptr;
	    }
	}
	
	void Database::executePrepared(const string& query, vector<string> params) {
	    try {
	        sql::PreparedStatement* pstmt = con->prepareStatement(query);
	
	        for (int i = 0; i < params.size(); i++) {
	            pstmt->setString(i + 1, params[i]);
	        }
	
	        pstmt->execute();
	        delete pstmt;
	    }
	    catch (sql::SQLException &e) {
	        cout << "Prepared Execute Error: " << e.what() << endl;
	    }
	}
	
	sql::ResultSet* Database::queryPrepared(const string& query, vector<string> params) {
	    try {
	        sql::PreparedStatement* pstmt = con->prepareStatement(query);
	
	        for (int i = 0; i < params.size(); i++) {
	            pstmt->setString(i + 1, params[i]);
	        }
	
	        return pstmt->executeQuery();
	    }
	    catch (sql::SQLException &e) {
	        cout << "Prepared Query Error: " << e.what() << endl;
	        return nullptr;
	    }
	}