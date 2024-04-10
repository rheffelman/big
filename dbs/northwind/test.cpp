#include <iostream> 
#include <sqlite3.h>
//#include <string>
using namespace std;

void initializeQueryArray();
void prompting();
int promptingHelper();


sqlite3* db;
const char * queryArray[10] {nullptr}; // bad practice but at this scale it doesn't matter.
                                       // boohoo 80 stack bytes ;(
static int callback2(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

static int hasPrinted = 0;
static int callback(void* data, int argc, char** argv, char** colName){

    if (!hasPrinted){
        for (int i = 0; i < argc; i++){
            if (i != (argc - 1)) printf("%s, ", colName[i]);
            else printf("%s\n", colName[i]);
        }
        hasPrinted = 1; //return 1;
    }

    for (int i = 0; i < argc; i++){
        if (i != (argc - 1)) printf("%s, ", argv[i]);
        else{
            printf("%s\n", argv[i]);
        } 
        hasPrinted = 0;
    } 
    return 0; 
}
//--
int main(){

    const char* pathToDB = "NorthwindLimited.sqlite";

    // open database at pathToDB
    int exit = sqlite3_open_v2(pathToDB, &db, 1, 0);
  
    // check if it opened properly
    if (exit){
        cout<<"DB Open Error: " << sqlite3_errmsg(db) << endl;
        return 0;
    } 
    else cout << "Opened Database Successfully!\n";

    initializeQueryArray();

    sqlite3_exec(db, queryArray[5], callback, nullptr, nullptr);
    // for (int i = 0; i < 10; i++){
    //     printf("Query %d:\n", i + 1);
    //     sqlite3_exec(db, queryArray[i], callback, nullptr, nullptr);
    //     printf("\n");
    // }
    
    //sqlite3_exec(db, queryArray[0], callback, nullptr, nullptr);
    printf("\n");
    sqlite3_close(db);
}
//--
void initializeQueryArray(){

    queryArray[0]="SELECT COUNT(*) AS numCustomers\nFROM Customers\nWHERE Country IN ('UK', 'USA', 'Spain');";
    queryArray[1]="SELECT CompanyName, Phone FROM Suppliers WHERE Phone LIKE '(514%' OR Phone LIKE '514%'";
    queryArray[2]="SELECT COUNT(*) AS n\nFROM Products\nWHERE UnitsInStock > UnitsOnOrder;";
    queryArray[3]="SELECT ProductName FROM 'Order Details' AS orderDetails, Products WHERE Products.ProductID = orderDetails.ProductID AND orderDetails.OrderID = '10275';";
    queryArray[4]="SELECT Managers.LastName, Managers.FirstName, COUNT(*) AS numEmployeesManaged\nFROM Employees AS Managers\nJOIN Employees AS ManagedEmployees\nON Managers.EmployeeID = ManagedEmployees.ReportsTo\nGROUP BY Managers.EmployeeID;";
    queryArray[5]="SELECT Products.ProductName\nFROM Products, Customers, Orders, 'Order Details' AS orderDetails\nWHERE orderDetails.ProductID = Products.ProductID\nAND orderDetails.OrderID = Orders.OrderID\nAND Orders.CustomerID = Customers.CustomerID\nAND Customers.CompanyName = 'The Big Cheese'\nAND orderDetails.Quantity > 9;";
    queryArray[6]="SELECT SUM(orderDetails.UnitPrice * orderDetails.Quantity * (1 - orderDetails.Discount))\nAS orderPrice\nFROM Orders, 'Order Details' AS orderDetails\nWHERE Orders.OrderDate LIKE '1997-01-16%'\nAND Orders.CustomerID = 'SIMOB'\nAND Orders.OrderID = orderDetails.OrderID;";
    queryArray[7]="SELECT Products.ProductName, Products.UnitsInStock\nFROM Products, 'Order Details' AS orderDetails\nWHERE Products.ProductID = orderDetails.ProductID\nAND orderDetails.Discount >= 0.25\nORDER BY Products.UnitsInStock DESC\nLIMIT 1;";
    queryArray[8]="WITH DiscountedOrders AS (SELECT OrderID,\n             SUM(UnitPrice * Quantity) AS beforeDiscount,\n          SUM(UnitPrice * Quantity * (1 - Discount)) AS afterDiscount\n    FROM `Order Details`\n      GROUP BY OrderID)\nSELECT DISTINCT Customers.CompanyName, (beforeDiscount - afterDiscount) AS discAmount, afterDiscount, beforeDiscount\nFROM DiscountedOrders, Customers, Orders, `Order Details` AS orderDetails\nWHERE Customers.CustomerID = Orders.CustomerID\nAND Orders.OrderID = DiscountedOrders.OrderID\nAND orderDetails.OrderID = Orders.OrderID\nORDER BY discAmount DESC\nLIMIT 1;";
    queryArray[9]="SELECT DISTINCT Suppliers.CompanyName, Products.ProductName, Products.UnitsOnOrder\nFROM Suppliers, Products\nWHERE Suppliers.SupplierID = Products.SupplierID\nAND Products.UnitsOnOrder > 99;";

    // :() <- Bob's here to help you collapse this code.
    // Here are my Lab 11/Lab 12 queries just for funsies:
    // Lab 11 Queries 1-10:
        // "SELECT Suppliers.ContactName\nFROM Suppliers\nWHERE Suppliers.HomePage IS NOT NULL AND LENGTH(Suppliers.HomePage) > 0;";
        // "SELECT Orders.OrderID\nFROM Orders, Employees\nWHERE Orders.EmployeeID = Employees.EmployeeID\nAND Employees.FirstName = \"Janet\"\nAND Employees.LastName = \"Leverling\";";
        // "SELECT DISTINCT Customers.ContactName\nFROM Customers, Orders, Shippers\nWHERE Shippers.ShipperID = Orders.ShipVia\nAND Shippers.CompanyName = \"United Package\"\nAND Orders.CustomerID = Customers.CustomerID;";
        // "SELECT Employees.*\nFROM Employees\nORDER BY Employees.LastName, Employees.FirstName;";
        // "SELECT COUNT(*)\nFROM Orders;";
        // "SELECT p.ProductName\nFROM Products p\nORDER BY p.UnitPrice\nLIMIT 1;";
        // "SELECT AVG(UnitPrice)\nFROM Products;";
        // "SELECT *\nFROM Products\nWHERE UnitsInStock > 0\nORDER BY UnitPrice DESC;";
        // "SELECT COUNT(Employees.EmployeeID)\nFROM Employees;";
        // "SELECT Employees.FirstName, Employees.LastName\nFROM Employees\nORDER BY Employees.BirthDate\nLIMIT 1;";
    // Lab 12 Queries 11-20:
        // "SELECT FirstName, LastName FROM Employees WHERE BirthDate < \"1969-04-06\";";
        // "SELECT DISTINCT Products.ProductName, Suppliers.CompanyName FROM Products, Suppliers, Categories WHERE Products.SupplierID = Suppliers.SupplierID AND Products.CategoryID = Categories.CategoryID AND Categories.CategoryName IN ("Meat/Poultry", "Produce");";
        // "SELECT FirstName, LastName, Notes FROM Employees WHERE ReportsTo = "2"";
        // "SELECT DISTINCT Employees.FirstName, Employees.LastName FROM Employees, Orders WHERE Employees.EmployeeID = Orders.EmployeeID AND Orders.ShipName = "The Cracker Box"";
        // "SELECT FirstName, LastName, ("2024-04-06 00:00:00" - HireDate) AS yearsEmployed FROM Employees ORDER BY HireDate";
        // "SELECT SUM("2024-04-06 00:00:00" - HireDate) as TotalYears FROM Employees";
        // "SELECT EmployeeID, COUNT(OrderID) AS numOrders FROM Orders GROUP BY EmployeeID;";
        // "SELECT ProductName, UnitsInStock FROM Products WHERE UnitsInStock = (SELECT MAX(UnitsInStock) FROM Products);";
        // "SELECT SUM((UnitPrice * Quantity * (1 - Discount))) AS sumOfOrdersFROM "Order Details";";   
}
//--
// Prints query "menu" for user to select from, then enters recursive promptingHelper() function
// to handle the other prompting related stuff in the assignment.
void prompting(){

    const char* queryDescriptions[10]{
    "Q1: Customers in the UK, USA, and Spain.",
    "Q2: Names and phone numbers of suppliers who are in the 514 area code.",
    "Q3: Products which have a greater value of in-stock items compared to the value of items on order.",
    "Q4: Names of the products in order #10275?",
    "Q5: All the employees who manage others and how many people they manage.",
    "Q6: Names of the products that were ever ordered by the customer \"The Big Cheese\" in quantities of 10 or more.",
    "Q7: Final order price for all items ordered by the customer \"Simons bistro\" on January 16th 1997.",
    "Q8: The product that was sold at a discount of 25% or more which has the most units in stock (and how many units are in stock).",
    "Q9: The name of the company that had the largest discount on any order, how much the discount was, how much the company paid minus the discount, and how much would they have paid without the discount?",
    "Q10: The suppliers whose products have 100 units or more on order."};
    
    // for (int i = 0; i < 10; i++){
    //     printf("%s\n", queryDescriptions[i]);
    // }

    if (promptingHelper() == -1){
        printf("That input is invalid.\nPlease try again, entering an integer 1-10 inclusive, corresponding with the query you'd like to see.\n");
    }
    sqlite3_close(db);
}
//--
int promptingHelper(){

    printf("\nChoose a query to execute (-1 to quit):");

    int userIn = 0;
    cin >> userIn;

    if (userIn == -1) return 0; // user typed "-1"
    if (userIn < 1 or userIn > 10) return -1; // userIn outside of acceptable input (return -1 to print an error message).

    userIn--; // off-by-one
    sqlite3_exec(db, queryArray[userIn], callback, nullptr, nullptr);
    //printf("%s\n", queryArray[userIn]);

    return promptingHelper();
}
//--