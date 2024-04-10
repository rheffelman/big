-- 6. What are the names of the products that were ever ordered by the customer "The Big Cheese" in quantities of 10 or more?
SELECT Products.ProductName
FROM Products, Customers, Orders, "Order Details" AS orderDetails
WHERE orderDetails.ProductID = Products.ProductID
AND orderDetails.OrderID = Orders.OrderID
AND Orders.CustomerID = Customers.CustomerID
AND Customers.CompanyName = "The Big Cheese"
AND orderDetails.Quantity > 9