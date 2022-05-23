
# Python3 code to demonstrate
# to generate random number list
# using random.sample()
import random
 
# using random.sample()
# to generate random number list
size = random.randint(900, 1000)
start = random.randint(-1000, 0)
end = random.randint(0, 1000)
res = random.sample(range(start, end), size)
# res = random.sample(range(start, end), size)
 
# printing result
print ("Random number list is : " +  str(res))
print ("Random number list size is : " +  str(size))
