def solution(K, A):
    mydict = {}
    for i, value in enumerate(A):
        key = K - value
        mydict[key] = 1 + mydict.get(key, 0)

    totalCount = 0
    for i, value in enumerate(A):
        count = mydict.get(value, 0)
        totalCount += count

    return totalCount


A = [1, 8, -3, 0, 1, 3, -2, 4, 5]
A = [1, 8, -3, 0, 1, 3, -2, 4, 5, 3]
A = [1, 8, -3, 0, 1, 3, -2, 4, 5, 3, 3]
K = 6
print solution(K,A)
