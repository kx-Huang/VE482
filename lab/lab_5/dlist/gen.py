with open("input/rand_int.txt", 'w') as f:
    for i in range(10000):
        f.write("{0}={1}\n".format(i, 10000-i))
