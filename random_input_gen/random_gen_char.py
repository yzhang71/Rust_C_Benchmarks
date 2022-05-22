# Python3 code to demonstrate
# to generate random number string
import random
import string

# printing lowercase
size = random.randint(50, 100)
letters = string.ascii_lowercase
print ("Random string is : " + ''.join(random.choice(letters) for i in range(size)))
print ("Random string size is : " +  str(size))