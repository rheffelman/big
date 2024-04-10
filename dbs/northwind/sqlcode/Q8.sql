-- 8. Which product that was ever sold at a discount of 25% or more has the most units in stock (and how many units are in stock)?
SELECT Products.ProductName, Products.UnitsInStock
FROM Products, 'Order Details' AS orderDetails
WHERE Products.ProductID = orderDetails.ProductID
AND orderDetails.Discount >= 0.25
ORDER BY Products.UnitsInStock DESC
LIMIT 1;