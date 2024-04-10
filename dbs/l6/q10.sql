SELECT DISTINCT Locations.name
FROM Locations, Dogs, Clients
WHERE Dogs.adoptedByClientID IS NOT NULL
AND Dogs.locationId = Locations.id
