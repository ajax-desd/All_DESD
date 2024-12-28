"""
shallow copy duplictae the outer lost 
but references the same inner list
"""
import copy
main_list = [[1,2],[3,4],[5,6]]
new_list = copy.copy(main_list)
print(id(main_list)) # it has diffrent id different from new_list
print(id(new_list))

print(id(main_list[0]))
print(id(new_list[0])) #has same adress as main list

new_list.append([7,8])

print(new_list)  # it list is appended to new list
print(main_list) # new list has been modified