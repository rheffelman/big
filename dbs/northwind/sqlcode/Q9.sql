-- 9. What is the name of the company that had the largest discount on any order, how much was that discount, how much did the company pay minus the discount, and how much would they have paid without the discount?
WITH DiscountedOrders AS (
    SELECT OrderID,
           SUM(UnitPrice * Quantity) AS beforeDiscount,
           SUM(UnitPrice * Quantity * (1 - Discount)) AS afterDiscount
    FROM `Order Details`
    GROUP BY OrderID)
SELECT DISTINCT Customers.CompanyName, (beforeDiscount - afterDiscount) AS discAmount, afterDiscount, beforeDiscount
FROM DiscountedOrders, Customers, Orders, `Order Details` AS orderDetails
WHERE Customers.CustomerID = Orders.CustomerID
AND Orders.OrderID = DiscountedOrders.OrderID
AND orderDetails.OrderID = Orders.OrderID
ORDER BY discAmount DESC
LIMIT 1;