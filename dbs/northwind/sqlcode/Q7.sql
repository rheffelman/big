-- 7. What was the final order price for all items ordered by the customer "Simons bistro" on January 16th 1997?
SELECT SUM(orderDetails.UnitPrice * orderDetails.Quantity * (1 - orderDetails.Discount))
AS orderPrice
FROM Orders, "Order Details" AS orderDetails
WHERE Orders.OrderDate REGEXP '1997-01-16'
AND Orders.CustomerID = 'SIMOB'
AND Orders.OrderID = orderDetails.OrderID;