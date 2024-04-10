SELECT Locations.id, Locations.name, COUNT(*) AS numDogs
FROM Dogs, Locations
WHERE Dogs.locationId = Locations.id
GROUP BY Locations.id, Locations.name;
