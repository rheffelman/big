-- 1. How many customers are in the UK, USA, and Spain?
SELECT COUNT(*) AS numCustomers
FROM Customers
WHERE Country IN ('UK', 'USA', 'Spain')