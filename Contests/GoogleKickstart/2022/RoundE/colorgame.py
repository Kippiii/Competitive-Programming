from math import ceil

t = int(input())

for case_num in range(1, t+1):
    n = int(input())
    ans = ceil(n / 5)
    print(f"Case #{case_num}: {ans}")