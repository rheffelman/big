-- 3. How many products have a greater value of in-stock items compared to the value of items on order?
SELECT COUNT(*) AS n
FROM Products
WHERE UnitsInStock > UnitsOnOrder;