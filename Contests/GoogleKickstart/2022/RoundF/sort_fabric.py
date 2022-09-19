t = int(input())
for case in range(1, t+1):
    n = int(input())
    full_data = [input().split() for _ in range(n)]

    ada = [(x[0], int(x[2])) for x in full_data]
    charles = [(int(x[1]), int(x[2])) for x in full_data]
    ada.sort()
    charles.sort()

    matches = sum([1 if ada[i][1] == charles[i][1] else 0 for i in range(n)])
    print(f"Case #{case}: {matches}")