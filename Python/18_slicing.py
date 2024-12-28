my_list = [100,20,50]
#start to the end by default ndex between two number is 1
print(my_list[3::])
#start:stop:index
print(my_list[2::-1])
print(my_list[2:1:1])

"""
Python map negative index to positive equivalents
using formula : index = len(sequence) + negative_index

so mylist[2] having element 3 is equal  to  
index = 3 + (-1)
index = 2

so value of mylist [2] = mylist[-1]

"""
#start = none end = node index = -1 it assume it start with last indexing
print(my_list[::-1])
#EOD is end of data
my_list = [100,20,50]
print(my_list[1::-1])

# start = 1: Start at index 1, which is the value 20 in my_list.
# stop = None (default): The slice will go until the start of the list (because the step is negative).
# step = -1: This means we will traverse the list in reverse.
my_list = [100,20,50]
print(f"(my_list) --",my_list)
print(my_list[:0:-1])
# Start at index 2 (value 50).
# Move backwards to index 1 (value 20).
# Stop before reaching index 0.