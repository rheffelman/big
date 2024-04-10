SELECT ProductName, UnitsInStock
FROM Products
WHERE UnitsInStock = (
	SELECT MAX(UnitsInStock)
	FROM Products);
-- Depends how you define "items". This is what made sense to me.