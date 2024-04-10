--11. Find the first and last name of every employee who is 55 years old or older.
SELECT FirstName, LastName
FROM Employees
WHERE BirthDate < "1969-04-06"