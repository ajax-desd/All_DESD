"""
extern type of module 
"""
import constant  #constant file you cant write with number 
print(constant.url)


#add basic module + sum_of

#name magling concept

#if __name__ == "__main__":
    # function: use as standalone when it is not called by other functions
    # if __name__ == "__main__": allows you to have code that only runs when the script is
    # executed directly, but not when it is imported as a module.

# Standalone Execution: When the script is run directly (e.g., python myscript.py), the code inside if __name__ == "__main__": will execute.
# Module Usage: When the file is imported as a module (e.g., import myscript), the code inside if __name__ == "__main__": will not run, but the functions 
# defined in the script (like sum_of_num) can still be used in the importing script.


# Use case of this:
# This construct is useful when a file is used as a program (standalone execution) or as a module (imported into another script).
# When the file is used as a standalone program, the code inside `if __name__ == "__main__":` will run.
# But if the file is imported as a module, the code inside this block will not execute.

# Noticeable thing:
# When you define functions like `sum_of_num(num1, num2)`, they can be called when the module is imported.
# However, the code inside `if __name__ == "__main__":` will only execute if the script is run directly (not imported).




