import random

def main():
    f = open("512k.txt", "w")
    for i in range(0,512001):
        f.write(str(round(random.uniform(0.0,1024000.0),6)))
        f.write(", ")

main()