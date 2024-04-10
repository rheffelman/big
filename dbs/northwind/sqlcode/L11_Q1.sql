SELECT SUM((UnitPrice * Quantity * (1 - Discount))) AS sumOfOrders
FROM "Order Details"