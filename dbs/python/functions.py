def square(numberToSquare): 
    return numberToSquare * numberToSquare 
 
def cube(numberToCube): 
    return numberToCube * numberToCube * numberToCube 
 
def power(base, exponent): 
    product = 1 
    counter = 1 
    while(counter <= exponent): 
        product = product * base 
        counter = counter + 1 
 
    return product 
 
def squareRoot(numberToRoot): 
    start = 1.0 
    end = numberToRoot 
     
    while(start <= end): 
        guess = (start + end) / 2.0 
        guessSquared = square(guess) 
        if(abs(guessSquared - numberToRoot) < .001): 
            root = guess 
            break 
        elif(guessSquared > numberToRoot): 
            end = guess 
        else: 
            start = guess 
    return root 
 
def isPrime(primeCheck): 
    prime = True 
    for number in range(2, int(squareRoot(primeCheck))): 
        if(primeCheck % number == 0): 
            prime = False 
            break 
 
    return prime 
 
 
print(square(10)) 
print(cube(2)) 
print(power(2, 8)) 
print(squareRoot(110)) 
print(isPrime(7)) 
print(isPrime(12))