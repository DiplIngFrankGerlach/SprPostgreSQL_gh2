#include <iostream>
#include <string>
#include <libpq-fe.h>

using namespace std;

void checkPQstatus(PGconn* conn) {
    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        exit(1);
    }
}

void checkPQresult(PGresult* res, PGconn* conn) {
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "No data retrieved: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
}

int main() {
    string pw;
    cout << "PW eingeben" << endl;
    cin >> pw;

    string connStr("dbname=frank user=frank password=");
    connStr.append(pw);
    connStr.append(" host=di-fg.de");
    // Connection parameters

    // Connect to the database
    PGconn* conn = PQconnectdb(connStr.c_str());

    // Check the status of the connection
    checkPQstatus(conn);

    // Execute a SQL command
    const char* query = "SELECT * FROM yourtable2";
    PGresult* res = PQexec(conn, query);

    // Check the result of the query
    checkPQresult(res, conn);

    // Get the number of rows and columns
    int nRows = PQntuples(res);
    int nFields = PQnfields(res);

    // Print the rows and columns
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nFields; j++) {
            std::cout << PQgetvalue(res, i, j) << "\t";
        }
        std::cout << std::endl;
    }

    // Clear the result
    PQclear(res);

    // Close the connection
    PQfinish(conn);

    return 0;
}
