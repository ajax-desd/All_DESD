#tuple are not mutable - not changeable
#list are mutable - can be changed
#set are mutable - can be changed
#dict are mutable - can be changed
#frozenset are immutable - cannot be changed
# in tuple we use () brakets where as [] tthis is list 

fruits = ("banna","guava","apple")
print(type(fruits))
# fruits[0] = "mango" #it doesnt chnage because of immutable

fruit_list = list(fruits)
fruit_list.append("kela")
print(fruit_list) #it is list

fruit_list = tuple(fruit_list)
print(fruit_list)  # tuple

number = (1)  #only for one
print(type(number))  #int

#create a tuple with 1 number
number = (1,)# , change into typefor single element
print(type(number))  #tuple


#packed tuple
subject = "python" ,"iot"
print(subject)  #tuple
print(type(subject))
subject = ("python" ,"iot")
print(type(subject))

#tuple unpacking
name,age = (subject)
#in this 
print(name)
print(age)

print("")
name,age = "ajay",20
print(name) # it is string


subject = "python" ,"iot","5g94"
print(subject)  #tuple
print(type(subject))
name, *lp,age =subject
print("NAme ",name)
print("how type work ",type(lp))
print(age)