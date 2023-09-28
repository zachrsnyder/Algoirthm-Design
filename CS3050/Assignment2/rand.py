#Used to create txt files with an inorder sequence of numbers in any range.
f = open("0-256000.txt","w")
for num in range(0,256000):
    f.write(str(num))
    f.write(", ")
