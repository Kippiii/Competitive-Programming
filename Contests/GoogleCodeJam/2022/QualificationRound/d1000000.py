t = int(input())

for case_num in range(1, t+1):
    n = int(input())
    s = list(map(int, input().split()))
    s.sort()
    num = 1
    counter = 0
    for i in range(n):
        if s[i] >= num:
            counter += 1
            num += 1
    print(f'Case #{case_num}: {counter}')
