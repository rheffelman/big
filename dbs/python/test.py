import math


x1, y1 = 2.0, 1.0
x2, y2 = 4.0, 3.0
x1 = float(input("Enter in an X value for the first point:"))

sideA = x2 - x1
sideB = y2 - y1
sideC = math.sqrt((sideA * sideA) + (sideB * sideB))

print(sideC)