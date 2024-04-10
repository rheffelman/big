SELECT DISTINCT Clients.firstName, Clients.lastName
FROM Clients, ClientMeetsDog
WHERE ClientMeetsDog.clientId = Clients.id
