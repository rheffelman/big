-- 5. Who are all the employees who manage others and how many people do they manage?
SELECT Managers.LastName, Managers.FirstName, COUNT(*) AS numEmployeesManaged
FROM Employees AS Managers
JOIN Employees AS ManagedEmployees
ON Managers.EmployeeID = ManagedEmployees.ReportsTo
GROUP BY Managers.EmployeeID;