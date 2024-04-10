SELECT Locations.name
FROM Locations, Dogs
WHERE (Dogs.name = "Puddy")
AND Dogs.locationId = Locations.id
