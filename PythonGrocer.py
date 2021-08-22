import re
import sys
import string
from datetime import date #date display

# corner grocer logo display
def CornerSplash():
    print("      |\nCORNER|\nGROCER|\n______|\n\n\n") 

# program terminate [menu option 4]
def PyExit():
    CornerSplash()
    print("Goodbye !!\n\n\n\n\n\n\n")

# prints the date
def PyDate():
    today = date.today()                # declare date variable
    today2 = today.strftime("%d-%B-%Y") # modify output
    print(today2)                       # output



# ------------------------------------------------------------ CHOICE 1 -- PRODUCT PURCHASE COUNT FUNCTION

def PyPurchaseCount():


    # confirmation of choice and date display
    print("  INDIVIDUAL  PRODUCT  SALES\n  ---------> ", end = " "), PyDate()
    

    # open product list
    try:
        foodFile = open(r"productFile.txt", "r") #raw; read
       
            
        # read text file to list
        with open(r"productFile.txt") as f: # open file
                foodContent = f.readlines() # read lines
    
        # remove spaces at first and last index (if any)
        foodContent = [sku.strip() for sku in foodContent] 

        # initialize empty list
        uniqueItems = [] 


        for sku in foodContent:           # for each item in foodContent
            if sku not in uniqueItems:    # if not in this list (first iteration will ALWAYS be added)
                uniqueItems.append(sku)   # add item to list


        print("  __________________________\n")
        print("  SKU                  COUNT\n") #SKU = stock keeping unit


        # searches list for unique item names and how many occurences there are then
        # prints and sorts by occurences (ascending)
        resultList = sorted([(sku, foodContent.count(sku)) for sku in uniqueItems], key=lambda y: y[1])  
        for item in resultList:
            print('{:.<25s} {}'.format("  " + item[0].upper(), str(item[1])))


    # catch and throw error if product list will not open
    except:
        print("  __________________________\n")
        print("  SKU                  COUNT\n")                         # SKU = stock keeping unit
        print("\n\n ERROR\n-------> Unable to read productFile.txt !!") # error message
        print("\n\n\nPress any key. . .", end = " ")                    # continue
        input(), "\n"                                                   # accept any input




# ---------------------- CHOICE 2 -- PRODUCT SEARCH FUNCTION
def PyItemSearch(item):
    

    item = item;   # redundant declaration for security
    count = 0;


    print("           SEARCH BY SKU")
    print("           _____________\n\n")

    print("DATE ------------->", end = " "), PyDate() # print date of business
    print("\nITEM ------------->", item.upper())      # item name cast to uppercase
    print("\nSOLD ------------->", end = " ")         # amount sold [DISPLAY ONLY]


    # attempt
    try:

        # below will search the file for the requested item; casefold used to ignore case; returns count to .cpp
        with open(r"productFile.txt") as f: # open file 
            foodContent = f.readlines()     # read lines
    

        # remove spaces at first and last index (if any)
        foodContent = [sku.strip() for sku in foodContent] 


        for x in foodContent:                    # searches foodContent list for all occurences of user input search
            if item.casefold() == x.casefold():  # item is user input, x is element in foodContent list, casefold ignores
                count += 1                       # simple iterator +1 any time a match is found

        return int(count);  # returns occurences of search to .cpp file in option 2 - will return zero if zero results


    # catch and throw error
    except:
        print("\n\n\n\n ERROR\n-------> Unable to read productFile.txt !!") # error message
        print("\n\n\nPress any key . . .", end = " ")                       # continue
        input(), "\n"                                                       # accept any input
        print("\n\n\n RESET\n-------> ... 3... 2... 1...", end = " ")       # amount sold [DISPLAY ONLY]
        return 0


    #needed for screen clear in option 3
def HistogramHeader(): 

     # display information and prompty
    print("    GENERATE PRODUCT HISTOGRAM")
    print("    ---------> ", end = " "), PyDate()
    print("    __________________________\n\n")



# --------------------- CHOICE 3 -- HISTOGRAM
def PyHistogram():

    # display information and prompty
    print("    GENERATE PRODUCT HISTOGRAM")
    print("    ---------> ", end = " "), PyDate()
    print("    __________________________\n\n")

    print("\nPress any key to generate your file . . .", end = " ") # continue
    input(), "\n"                                                   # accept any input


    # create file
    f = None  # declare file variable


    # attempt file creation and create container for writing
    try:
        f = open(r"frequency.dat", "x")                              # create file
        print("\n\n\n SUCCESS\n---------> frequency.dat created !!") # confirmation of success


        # read original file and create container
        with open(r"productFile.txt") as f:

            foodContent = f.readlines()                        # open file, read lines
            foodContent = [sku.strip() for sku in foodContent] # remove spaces at first and last index (if any)
            uniqueItems = []                                   # initialize empty list
        
            for sku in foodContent:          # for each item in foodContent
                if sku not in uniqueItems:   # if not in this list (first iteration will ALWAYS be added)
                    uniqueItems.append(sku)  # add item to list

            
            # sorted container for items and their quantities
            productContainer = sorted([(sku, foodContent.count(sku)) for sku in uniqueItems], key=lambda y: y[1])


        # continue to write file with any input
        print("\n\n\nPress any key to write to to frequency.dat. . .", end = " ")
        input(), "\n"                                                             



        # write attempt 
        try:
            with open(r'frequency.dat', 'w') as f:          # open file; write
                for product in productContainer:            # access tuples; product = any element
                   line = ' '.join(str(x) for x in product) # extract tuple elements and join with whitespace
                   f.write(line + "\n")                     # write string
                  
            f.close() # close file

            # success message
            print("\n\n\n SUCCESS\n---------> frequency.dat written !!") # confirmation of success
            print("\n\n\n\nPress any key to continue . . .", end = " ")  # continue
            input(), "\n"                                                # accept any input


        # catch and throw error if write attempt fails
        except:
            print("\n\n\n ERROR\n------> Unable to write to frequency.dat !!")     # error message
            print("\n\n\n\nPress any key to return to main menu . . .", end = " ") # continue
            input(), "\n"                                                          # accept any input

    # catch and throw error if file creation fails
    except:
        print("\n\n\n ERROR\n-------> Unable to create frequency.dat !!") # error message
        print("\n\n\n\nPress any key to continue . . .", end = " ")       # continue
        input(), "\n"     