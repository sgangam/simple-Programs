#!/usr/bin/python
"""
Using recursing to perform permutations and combinations on a list of items.
"""

def permute(someList, startIndex):
    if len(someList) - 1 == startIndex:
        print someList
    else:
        newList = [i for i in someList]
        permute(someList, startIndex + 1)
        i = startIndex + 1
        while i < len(someList):
            someList = newList
            first = someList[startIndex]
            someList[startIndex] = someList[i]
            someList[i] = first
            permute(someList, startIndex + 1)
            i += 1

def combine(someList, startIndex):
    if len(someList)  == startIndex:
        print someList
    else:
        newList = [i for i in someList]
        combine(someList, startIndex + 1)
        someList = newList
        someList.pop(startIndex)
        combine(someList, startIndex)

someList = ['a', 'b', 'c', 'd']
permute(someList, 0)
print "************************"
combine(someList, 0)
