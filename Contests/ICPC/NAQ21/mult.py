n = int(input())
first = 0
first_set = False
for i in range(n):
    tmp = int(input())
    if not first_set:
        first = tmp
        first_set = True
    else:
        if tmp % first == 0:
            print(tmp)
            first_set = False
