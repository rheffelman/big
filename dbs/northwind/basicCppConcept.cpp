#include <iostream> 
#include <sqlite3.h>
#include <limits>
#include <string>
using namespace std;

sqlite3 *db = nullptr;
const char * queryArray[20] {nullptr};
void queryArrayInitialization();

int main(){
    queryArrayInitialization();

    string pathToDB = "NorthwindLimited.sqlite";
    // open db at filepath
    int o = sqlite3_open(pathToDB.c_str(), &db);

    if (o == SQLITE_OK){
        sqlite3_stmt* myStatement = nullptr;

        // "prepare" myStatement for execution
        int p = sqlite3_prepare_v2(db, queryArray[0], -1, &myStatement, nullptr);
        if (p == SQLITE_OK){
            // "step" myStatement which basically just executes the sql
            int s = sqlite3_step(myStatement);
            if (s == SQLITE_ROW or SQLITE_DONE){
                cout << sqlite3_column_name(myStatement, 0) << endl;
                cout << sqlite3_column_text(myStatement, 0) << endl;
            }
            else cout << "sqlite3_step() failed. result code: " << s << endl;
        }
        else cout << "sqlite3_prepare_v2() failed. result code: " << p << endl;
    }
    else cout << "sqlite3_open() failed. result code: " << o << endl;

}

void queryArrayInitialization(){
    // SQL queries
    queryArray[0]="SELECT COUNT(*) AS numCustomers\nFROM Customers\nWHERE Country IN ('UK', 'USA', 'Spain');";
    queryArray[1]="SELECT CompanyName, Phone\nFROM Suppliers\nWHERE Phone LIKE '(514%' OR Phone LIKE '514%';";
    queryArray[2]="SELECT COUNT(*) AS n\nFROM Products\nWHERE UnitsInStock > UnitsOnOrder;";
    queryArray[3]="SELECT ProductName\nFROM 'Order Details' AS orderDetails, Products\nWHERE Products.ProductID = orderDetails.ProductID\nAND orderDetails.OrderID = '10275';";
    queryArray[4]="SELECT Managers.FirstName, Managers.LastName, COUNT(*) AS numEmployeesManaged\nFROM Employees AS Managers\nJOIN Employees AS ManagedEmployees\nON Managers.EmployeeID = ManagedEmployees.ReportsTo\nGROUP BY Managers.EmployeeID;";
    queryArray[5]="SELECT Products.ProductName\nFROM Products, Customers, Orders, 'Order Details' AS orderDetails\nWHERE orderDetails.ProductID = Products.ProductID\nAND orderDetails.OrderID = Orders.OrderID\nAND Orders.CustomerID = Customers.CustomerID\nAND Customers.CompanyName = 'The Big Cheese'\nAND orderDetails.Quantity > 9;";
    queryArray[6]="SELECT SUM(orderDetails.UnitPrice * orderDetails.Quantity * (1 - orderDetails.Discount)) AS orderPrice\nFROM Orders, 'Order Details' AS orderDetails\nWHERE Orders.OrderDate LIKE '1997-01-16%'\nAND Orders.CustomerID = 'SIMOB'\nAND Orders.OrderID = orderDetails.OrderID;";
    queryArray[7]="SELECT Products.ProductName, Products.UnitsInStock\nFROM Products, 'Order Details' AS orderDetails\nWHERE Products.ProductID = orderDetails.ProductID\nAND orderDetails.Discount >= 0.25\nORDER BY Products.UnitsInStock DESC\nLIMIT 1;";
    queryArray[8]="WITH DiscountedOrders AS(\n    SELECT OrderID,\n    SUM(UnitPrice * Quantity) AS beforeDiscount,\n    SUM(UnitPrice * Quantity * (1 - Discount)) AS afterDiscount\n    FROM `Order Details`\n    GROUP BY OrderID\n)\n\nSELECT DISTINCT Customers.CompanyName, (beforeDiscount - afterDiscount) AS discAmount, afterDiscount, beforeDiscount\nFROM DiscountedOrders, Customers, Orders, `Order Details` AS orderDetails\nWHERE Customers.CustomerID = Orders.CustomerID\nAND Orders.OrderID = DiscountedOrders.OrderID\nAND orderDetails.OrderID = Orders.OrderID\nORDER BY discAmount DESC\nLIMIT 1;";
    queryArray[9]="SELECT DISTINCT Suppliers.CompanyName, Products.ProductName, Products.UnitsOnOrder\nFROM Suppliers, Products\nWHERE Suppliers.SupplierID = Products.SupplierID\nAND Products.UnitsOnOrder > 99;";
}
