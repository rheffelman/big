// Ryan Heffelman
// Mark Mahoney
// CSC 2810 - Database Design and Management
// 2024-04-08
// Northwind Queries Assignment

#include <iostream> 
#include <sqlite3.h>
#include <limits>
using namespace std;

sqlite3 *db = nullptr;
const char * queryArray[20] {nullptr};

void queryArrayInitialization();
void promptUser();
void executeSelectedQuery(int userQuery);

int main(){

    const char* pathToDB = "NorthwindLimited.sqlite";
    int o = sqlite3_open(pathToDB, &db);

    if (o == SQLITE_OK){
        printf("Database opened succesfully!\n");
        queryArrayInitialization();
        // this loop prints query menu.
        for (int i = 10; i < 20; i++){
            printf("%s\n", queryArray[i]);
        }
        printf("\n");
        promptUser();
    }
    else {
        printf("sqlite3_open() failed to open the database and returned result code: %d\n", 0);
        return 0;
    }

    // Not sure if I even need to explicitly call destructor. valgrind says I possibly leak data w/o closing.
    // It's done in playbackpress.com/books/12/chapter/2/1 so I'm doing it in this program, but I'd love clarification.
    sqlite3_close(db);
    //printf("exited main\n");
}

//--
// promptUser() reads an integer input from stdin meant to correspond to a query to open.
// It ensures that the input is valid and prints the query the user selected in plain English,
// then footballs the flow-of-control over to executeSelectedQuery() to execute/print that query.
void promptUser(){

    printf("Choose a query to execute (-1 to quit): ");
    int userIn = 0;
    cin >> userIn;
    if (userIn == -1) return;

    while (cin.fail() or userIn < 1 or userIn > 10){
        printf("\nYou must enter an integer 1-10 inclusive or -1 to quit. Please try again :)\n\n");
        printf("Choose a query to execute (-1 to quit): ");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> userIn;
        if (userIn == -1) return;
    }
    userIn--;

    // Prints the English version of the query the user selected directly after selection.
    // The magic numbers manipulate my strings to more closely match the example output.
    if (userIn == 9) printf("%s\n", queryArray[userIn + 10] + 4);
    else printf("%s\n", queryArray[userIn + 10] + 3);

    executeSelectedQuery(userIn);
}

//--
// executeSelectedQuery() executes and prints the output of a query userQuery in a csv-like format.
// Then it prints the actual SQL code of the query.
// Finally, if all goes well, it footballs it back to promptUser() to see if the user wants another query.
void executeSelectedQuery(int userQuery){
    sqlite3_stmt* myStatement = nullptr;

    // good ol' prep n step
    int p = sqlite3_prepare_v2(db, queryArray[userQuery], -1, &myStatement, nullptr);
    if (p == SQLITE_OK){
        int s = sqlite3_step(myStatement);
        if (s == SQLITE_ROW){
            printf("\n");
            int cc = sqlite3_column_count(myStatement);

            // this loop prints the column names
            for (int i = 0; i < cc; i++){
                if (i == (cc - 1)){
                    printf("%s\n", sqlite3_column_name(myStatement, i));
                    break;
                }
                printf("%s, ", sqlite3_column_name(myStatement, i));
            }

            // this loop and its inner loop print each row of each column
            for (;s == SQLITE_ROW;){
                for (int i = 0;1; i++){
                    if (i == (cc - 1)){
                        printf("%s\n", sqlite3_column_text(myStatement, i));
                        break;
                    }
                    printf("%s, ", sqlite3_column_text(myStatement, i));
                }
                s = sqlite3_step(myStatement);
            }
            printf("\n");
        }
        else{
            printf("Failed initial step() call\n");
            printf("sqlite3_step()'s result code: %d\n", s);
            if (s == SQLITE_DONE) printf("Your query may have returned 0 rows.\n");
            exit(0);
        }
    }
    else{
        printf("Failed to prepare requested statement\n");
        printf("sqlite3_prepare_v2()'s result code: %d\n", p);
        exit(0);
    }
    sqlite3_finalize(myStatement);
    printf("%s\n\n", queryArray[userQuery]);
    promptUser();
}

//--
// Down here is where I hide my horde of explicit const char ** assignment statements.
void queryArrayInitialization(){
    // SQL queries
    queryArray[0]="SELECT COUNT(*) AS numCustomers\nFROM Customers\nWHERE Country IN ('UK', 'USA', 'Spain');";
    queryArray[1]="SELECT CompanyName, Phone\nFROM Suppliers\nWHERE Phone LIKE '(514%' OR Phone LIKE '514%';";
    queryArray[2]="SELECT COUNT(*) AS n\nFROM Products\nWHERE UnitsInStock > UnitsOnOrder;";
    queryArray[3]="SELECT ProductName\nFROM 'Order Details' AS orderDetails, Products\nWHERE Products.ProductID = orderDetails.ProductID\nAND orderDetails.OrderID = '10275';";
    queryArray[4]="SELECT Managers.FirstName, Managers.LastName, COUNT(*) AS numEmployeesManaged\nFROM Employees AS Managers\nJOIN Employees AS ManagedEmployees\nON Managers.EmployeeID = ManagedEmployees.ReportsTo\nGROUP BY Managers.EmployeeID;";
    queryArray[5]="SELECT Products.ProductName\nFROM Products, Customers, Orders, 'Order Details' AS orderDetails\nWHERE orderDetails.ProductID = Products.ProductID\nAND orderDetails.OrderID = Orders.OrderID\nAND Orders.CustomerID = Customers.CustomerID\nAND Customers.CompanyName = 'The Big Cheese'\nAND orderDetails.Quantity > 9;";
    queryArray[6]="SELECT SUM(orderDetails.UnitPrice * orderDetails.Quantity * (1 - orderDetails.Discount)) AS orderPrice\nFROM Orders, 'Order Details' AS orderDetails\nWHERE Orders.OrderDate LIKE '1997-01-16%'\nAND Orders.CustomerID = 'SIMOB'\nAND Orders.OrderID = orderDetails.OrderID;";
    queryArray[7]="SELECT ProductName, UnitsInStock\nFROM Products\nWHERE UnitsInStock = (\n    SELECT MAX(Products.UnitsInStock)\n    FROM Products, 'Order Details' AS orderDetails\n    WHERE Products.ProductID = orderDetails.ProductID\n    AND orderDetails.Discount >= 0.25);";
    queryArray[8]="WITH DiscountedOrders AS(\n    SELECT OrderID,\n    SUM(UnitPrice * Quantity) AS beforeDiscount,\n    SUM(UnitPrice * Quantity * (1 - Discount)) AS afterDiscount\n    FROM `Order Details`\n    GROUP BY OrderID\n)\n\nSELECT DISTINCT Customers.CompanyName, (beforeDiscount - afterDiscount) AS discAmount, afterDiscount, beforeDiscount\nFROM DiscountedOrders, Customers, Orders, `Order Details` AS orderDetails\nWHERE Customers.CustomerID = Orders.CustomerID\nAND Orders.OrderID = DiscountedOrders.OrderID\nAND orderDetails.OrderID = Orders.OrderID\nORDER BY discAmount DESC\nLIMIT 1;";
    queryArray[9]="SELECT Suppliers.CompanyName, SUM(Products.UnitsOnOrder) AS productsOnOrder\nFROM Suppliers, Products\nWHERE Suppliers.SupplierID = Products.SupplierID\nGROUP BY Suppliers.SupplierID\nHAVING productsOnOrder >= 100\nORDER BY productsOnOrder DESC;";

    // The queries in plain English
    queryArray[10]="1: How many customers are in the UK, USA, and Spain?";
    queryArray[11]="2: What are the names and phone numbers of suppliers who are in the 514 area code?";
    queryArray[12]="3: How many products have a greater value of in-stock items compared to the value of items on order?";
    queryArray[13]="4: What are the names of the products in order #10275?";
    queryArray[14]="5: Who are all the employees who manage others and how many people do they manage?";
    queryArray[15]="6: What are the names of the products that were ever ordered by the customer \"The Big Cheese\" in quantities of 10 or more?";
    queryArray[16]="7: What was the final order price for all items ordered by the customer \"Simons bistro\" on January 16th 1997?";
    queryArray[17]="8: Which product that was ever sold at a discount of 25% or more has the most units in stock (and how many units are in stock)?";
    queryArray[18]="9: What is the name of the company that had the largest discount on any order, how much was that discount, how much did the company pay minus the discount, and how much would they have paid without the discount?";
    queryArray[19]="10: Who are the suppliers whose products have 100 units or more on order.";
}