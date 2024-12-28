#  known exception 
import os

try:
    # Open 'ajay.txt' and read its contents
    with open("ajay.txt", "r") as fd:
        data = fd.read()
        print(data)

    # Open 'poem.txt' and read its contents
    with open("poem.txt", "r") as fd:
        data = fd.read()
        print(data)

except FileNotFoundError :
    print(f"File not found")
except Exception as e:
    print(f"An error occurred: {e}")
    print("unlock the permissiion")
    os.system("sudo chmod 666 poem.txt") # by this you can run any comman 
