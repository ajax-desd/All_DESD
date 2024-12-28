"""
def function_name(arg1):
    return value

#function call
function_name(arg1)

"""

def calculate_area(radius):
    return 3.14 * radius ** 2 # ** for power

radius = (int)(input("Enter the  radius of the circle: "))
print("Sum :",calculate_area(radius))

def add(num1:int,num2:int)-> int:            #-> return type int Latest recommdation
    return num1 + num2
print("Addditin: ",add(5,7))  # Output: 12