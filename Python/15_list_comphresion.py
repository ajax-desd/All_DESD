square = [] #empty lis15t
for number in range (1,11):
    square.append(number ** 2)
print(square)

#comprehesion
squares =[]
squares = [ number **2 for number in range(1,11)]
print(squares)

numbers = [1,2,3,4,5]
even_numbers = []
for number in numbers:
    if number % 2 == 0:
        even_numbers.append(number)
print(even_numbers)

even_numberr = []
# first write 2 block if condition then loop  thne the number store in  list
#even_numberr = [number (1 for number in  numbers) (2 if number % 2 == 0)]
even_numberr = [number for number in  numbers if number % 2 == 0] # it return the number
print(even_numberr)

#odd number 