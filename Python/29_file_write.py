# writing data to a file
file_name = "sensor_data.txt"
file_mode ="w"
with open (file_name, file_mode) as fd:
    fd.write("temperature : 22\n")
    fd.write("humidity : 60\n")
    fd.write("pressure : 1013\n")
    print(fd.closed) #give false

# outside  th eloop because it automatically close
print(fd.closed) # give True
# Append data to a file


# in binary but cant be loss 
file_mode ="a"
with open (file_name, file_mode) as fd:
     fd.write("aiq : 62\n")

# seek and teel like Fseek in c     lseek in sycalls

file_mode = "r"
with open (file_name, file_mode) as fd:
     fd.seek(1) # skip the first character like indexing
      # read all the data
     print("cursor is at",fd.tell());
     print(fd.read())

# end of file
# 1 mean currect position
"""
file.seek()
.seek -> (offset,whence)
whence define the position of the offset
0-> SOF
1->current
2->EOF

"""

file_mode = "a+"
with open (file_name, file_mode) as fd:
     fd.seek(0,2) # Move to end of file we cant write negative of file
      # read all the data
     print("cursor is at",fd.tell())
     fd.write("home : uttarakhand\n")
     fd.seek(0,0)
     print(fd.read())
