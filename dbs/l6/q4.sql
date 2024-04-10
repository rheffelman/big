SELECT Dogs.name, Dogs.age, Locations.name
FROM Dogs, Locations
WHERE Dogs.locationId = Locations.id
AND (Dogs.breed = "Schnauzer")
ORDER BY Locations.name;
