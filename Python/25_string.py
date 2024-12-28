"""
def function_name(arg1):
    return value

#function call
function_name(arg1)

"""

def add(num1:int,num2:int)-> int:            #-> return type int Latest recommdation for redability
    return num1 + num2
print("Addditin: ",add(5,7))  # Output: 12

def greeetings(first:str,lastname:str)->str:
    return f"Hello , Mr {first} {lastname}"

print(greeetings("ajay","singh"))

