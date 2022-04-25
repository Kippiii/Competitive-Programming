
def sevens_unique(arr):
    while len(arr) > 0:
        if not all_unique(arr[:min(7, len(arr))]):
            return False
        arr = arr[min(7, len(arr)):]
    return True

def all_unique(arr):
    if len(list(set(arr))) == len(arr):
        return True
    return False

def check_index(arr, i):
    if all_unique(arr[:i]) and sevens_unique(arr[i:]):
        return True
    return False

t = int(input())
for _ in range(t):
    s = input().strip()
    answer = False
    for i in range(7):
        if check_index(s, i):
            answer = True
    if answer:
        print(1)
    else:
        print(0)
