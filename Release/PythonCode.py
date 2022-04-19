import re
import string


file_name = 'InputFile.txt'  # sets the file name to whichever file is being read

word_list = []
word_dict = {}

f = open(file_name, 'r')  # opens the list of purchased items and splits it into a list, each line being an item
file = f.read()
word_list = file.split('\n')
f.close()

for word in word_list:
    test = word_list.count(word)  # counts how many times the word appear in the document
    word_dict[word] = test  # creates a dictonary element with the item name and how many times it appears


def printsomething():  # prints a hello message, only used for troubleshooting to test if python is working
    print("Hello from python!")


def printFullList():
    for word in word_dict:
        print("{} - {}".format(word, word_dict[word]))  # prints each item in the word dictonary and the number associated with it
        
            
def printItem(word):
    print("")
   
    try:
        print("{} - {}".format(word, word_dict[word]))  # prints the specific word given and its frequency
    except:
        print("Item does not exist, please enter another")  # if item is not on the list, display an error message

    return 0


def histogram():
    f = open("frequency.dat", 'w')  # opens the frequency file and writes each item in the word dictonary into it
    for word in word_dict:
        f.writelines("{} {} \n".format(word, word_dict[word])) 
    f.close()