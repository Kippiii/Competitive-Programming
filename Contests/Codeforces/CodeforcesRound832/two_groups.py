t = int(input())

for _ in range(t):
    n = int(input())
    ans = abs(sum(map(int, input().split())))
    print(ans)