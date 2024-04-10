-- 4. What are the names of the products in order #10275?
SELECT Products.ProductName
FROM 'Order Details' AS orderDetails, Products
WHERE Products.ProductID = orderDetails.ProductID
AND orderDetails.OrderID = '10275';