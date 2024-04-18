nameAndBirthYears = [["Mark", 1973], ["Laura", 1973], ["Buddy", 2004], ["Patrick", 2007]] 
currentYear = 2018 
 
for nameAndBirthYear in nameAndBirthYears: 
    print(nameAndBirthYear[0] + "'s age is " + str(currentYear - nameAndBirthYear[1]))