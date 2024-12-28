list = [1,2]
list.extend([3,4])
print(list)
#so what is append vs extend
# append() adds the entire argument as a single element.
# extend() adds each element from an iterable to the list individually.
# ctrl + shift --> for commenting
#Differnce in thse two


list1 =["ajay",10]
list.extend(list1)
list.extend("harshu") # output [1, 2, 3, 4, 'h', 'a', 'r', 's', 'h', 'u']
print(list)

#remove froma an element fromdict
list.remove(10) # output [1, 2, 3, 4, 'h', 'a',] 10 omittted

list3 =[1,2,3,1,4,5,5]
list3.remove(1)  # it remove 1 which came first
#if you want to remove all
#you can alter and delete it

list.pop() # remove last element of 
list.insert(2,"gautum")# give two arugment
print(list)
list.clear()
print(list) #elemty all list
print(list3)

number = [1,2,3,4,5,5,6,76,7]
print("Number of count ",number.count(1))

#want to find first occurence of it
print("first occurence",number.index(5))