#IOT for archituce for perrli
"""

"r":read only mode
"w":write mode
"x":execute mode
"r+":Read and write
"w+":Write and read


"""

fd = open("poem.txt","r")
data = fd.read()
print(data)
#fd.close()

#recommended way - file gets automatically closed
with open ("poem.txt","r") as fd:
    data = fd.read()
    print(data)
print(fd.close)