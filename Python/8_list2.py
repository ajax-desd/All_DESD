my_list = ["vamsi",1000,True]
print(my_list)   # prints vamsi
new_list = my_list
new_list.append("swajal")
print(my_list)   # prints vamsi swajal
print(new_list)  # prints vamsi swajal

#append impact the original list also 
#Deep copy and shallow copy



"""
shallow copy duplictae the outer lost 
but references the ssame inner list

"""