#Deep copy if we want to change in both list difrently not impact on others
import copy
main_list = [[1,2],[3,4],[5,6]]#list inside list 
new_list = copy.deepcopy(main_list)
print("--id of the outer list main --",id(main_list))
print("--id of the outer list new --",id(new_list))
print("--id of the first inner list main --",id(main_list[0]))
print("--id of the first inner list new --",id(new_list[0]))
new_list.append([7,8])
new_list[0][0]= 10 #only second one list
print("main list after append",main_list)
print("new list after append",new_list)

print("update new list first element of first inner list")
