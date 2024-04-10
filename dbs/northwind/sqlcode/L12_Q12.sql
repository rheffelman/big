--12. Find all the product names and supplier names for the meat, poultry, and produce categories.
SELECT DISTINCT Products.ProductName, Suppliers.CompanyName
FROM Products, Suppliers, Categories
WHERE Products.SupplierID = Suppliers.SupplierID
AND Products.CategoryID = Categories.CategoryID 
AND Categories.CategoryName IN ("Meat/Poultry", "Produce");