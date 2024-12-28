my_list = [1,2,3,4,5,"ajay","ajj hai "]
for item in my_list:
    print( f"{item}",end=" ")

x = 2 #immutable
print("X1=",x); 
x = 4 
print("x2-",x)
print("x-id=",id(x));


# string is also immutable
str1 = ["ajay","singh"]
print(str1)
print(id(str1))
str1=["singh","ajay"]
#str1[0]=["singh","ajay"]
print(str1)   
print(id(str1))

print(x)
x = x+2
y = 6
print("x2-id",id(x))
print("x3-id",id(y))
x=9
print("x4-id",id(x))
print(y)
print(id(y))



