c = int(input())
queries = [input().split() for _ in range(c)]

index = 0
topping_map = {}
for k in range(len(queries)):
    if queries[k][0] != "if":
        if queries[k][0] not in topping_map:
            topping_map[queries[k][0]] = index
            index += 1
        queries[k][0] = topping_map[queries[k][0]]
    else:
        for i in range(len(queries[k])):
            if queries[k][i] != "if" and queries[k][i] != "and" and queries[k][i] != "or" and queries[k][i] != "then":
                if queries[k][i] not in topping_map:
                    topping_map[queries[k][i]] = index
                    index += 1
                queries[k][i] = topping_map[queries[k][i]]

ans = [False for _ in range(index)]
evaluated = [False for _ in range(c)]
changes = True
while changes:
    changes = False
    for i in range(len(queries)):
        q = queries[i]
        if evaluated[i]:
            continue
        else:
            if len(q) == 1:
                ans[q[0]] = True
                evaluated[i] = True
                changes = True
            elif len(q) == 4:
                if ans[q[1]]:
                    ans[q[3]] = True
                    evaluated[i] = True
                    changes = True
            else:
                if q[2] == "and":
                    is_true = True
                    for j in range(1, len(q) - 1, 2):
                        if not ans[q[j]]:
                            is_true = False
                            break
                    if is_true:
                        evaluated[i] = True
                        changes = True
                        ans[q[-1]] = True
                else:
                    is_true = False
                    for j in range(1, len(q) - 1, 2):
                        if ans[q[j]]:
                            is_true = True
                            break
                    if is_true:
                        evaluated[i] = True
                        changes = True
                        ans[q[-1]] = True

topping_count = 0
for b in ans:
    if b:
        topping_count += 1
print(topping_count)
