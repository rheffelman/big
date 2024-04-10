--2. What are the names and phone numbers of suppliers who are in the 514 area code?
SELECT CompanyName, Phone 
FROM Suppliers 
WHERE Phone LIKE '(514%' 
OR Phone LIKE '514%'