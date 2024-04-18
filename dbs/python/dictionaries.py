grades = { "Laura": 98, "Buddy": 94, "Patrick": 95 } 
 
print("Laura earned: " + str(grades["Laura"])) 
 
studentNameKey = "Buddy" 
print(studentNameKey + " earned: " + str(grades[studentNameKey])) 
 
studentNameKey = "Patrick" 
print(studentNameKey + " earned: " + str(grades[studentNameKey])) 
 
grades["Mark"] = 85 
studentNameKey = "Mark" 
print(studentNameKey + " earned: " + str(grades[studentNameKey])) 
 
studentNameKey = "Juan Pablo" 
#print(studentNameKey + " earned: " + str(grades.get(studentNameKey))) 
 
if(studentNameKey in grades): 
    print(studentNameKey + " is in the dictionary") 
    print(studentNameKey + " earned: " + str(grades[studentNameKey])) 
else: 
    print(studentNameKey + " is NOT in the dictionary") 
 
print("") 
print("All values") 
allValues = grades.values() 
for value in allValues: 
    print(value) 
 
print("") 
print("All keys and values") 
allKeys = grades.keys() 
for key in allKeys: 
    print("key: " + key + ", value: " + str(grades[key])) 
 
print("") 
print("All keys and values sorted by key") 
for key in sorted(grades.keys()): 
    print("key: " + key + ", value: " + str(grades[key])) 
 
# print("") 
# print("All items") 
# for item in grades.items(): 
#     print(item) 
 
print("") 
print("All keys and values sorted by value") 
newGrades = [] 
for item in grades.items(): 
    newGrades.append( (item[1], item[0]) ) 
for pair in sorted(newGrades, reverse=True): 
    print("Name: " + pair[1] + ", grade: " + str(pair[0])) 
