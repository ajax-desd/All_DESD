try:
    num1 = 10
    num2 = 0
    result = num1 / num2
    print(result)
except ZeroDivisionError:
    print("Error: Division by zero is not allowed.")
#This block executed even exception occur use in database 
finally:
    print("This is the finally block.")