waterTemp = 5.0 
scale = "C" 
 
if(scale == "F"): 
    if(waterTemp <= 32.0): 
        print("Ice") 
    elif(waterTemp < 212.0): 
        print("Water") 
    else: 
        print("Steam") 
elif(scale == "C"): 
    if(waterTemp <= 0.0): 
        print("Ice") 
    elif(waterTemp < 100.0): 
        print("Water") 
    else: 
        print("Steam") 
else:  
    print("There is a problem with the scale.")