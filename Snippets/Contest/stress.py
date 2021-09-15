import subprocess
from random import randint as rng

#-------------------------------------

def solve(): # Stupid solution
    pass

#-------------------------------------

def gen(): # Gen test
    pass
#-------------------------------------

def outTo(file): # Write test to file
    pass

#-------------------------------------

def chk(ans, res):
    return ans == res

#-------------------------------------
# VARIABLES
#-------------------------------------

subprocess.run("g++ -o main main.cpp -std=c++17 -fmodules", shell=True)
subprocess.run("g++ -o stupid stupid.cpp -std=c++17 -fmodules", shell=True)
for test in range(10000):
    gen()

    with open("input.txt", "w") as out:
        outTo(out)

    print("GEN", test + 1, "FINISHED")
    res = subprocess.run("./main", capture_output=True, check=True).stdout.decode()
    ans = subprocess.run("./stupid", capture_output=True, check=True).stdout.decode()
    #ans = solve()

    if not chk(ans, res):
        print("TEST", test + 1, "FAILED")
        print("Code output:\n" + str(res) + "but real answer is:\n" + ans)
        exit(-1)

    print("TEST", test + 1, "PASSED")

