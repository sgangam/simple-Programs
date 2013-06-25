#!/usr/bin/python
"""
Author: Sriharsha Gangam
The Quick Select method.
"""
import random

# kth smallest element #cannot handle duplicates.
def quickSelect(inputList, k):
    pivotIndex = random.randint(0, len(inputList) - 1) 
   
    smallList = []
    largeList = []
    for n in inputList:
        if n < inputList[pivotIndex]:
            smallList.append(n)
        elif n > inputList[pivotIndex]:
            largeList.append(n)

    if k <= len(smallList):
        return quickSelect(smallList, k)
    elif k > 1 + len(smallList):
        return quickSelect(largeList, k - len(smallList) - 1 )
    else:
        return inputList[pivotIndex]


if __name__ == '__main__':
    inputList = range(10) 
    #print inputList, quickSelect(inputList, 5), quickSelect(inputList, 5) == 4
    assert quickSelect(inputList, 5) == 4
    assert quickSelect(inputList, 1) == 0
    assert quickSelect(inputList, 2) == 1
    assert quickSelect(inputList, 9) == 8
    assert quickSelect(inputList, 10) == 9


    inputList = [23, 33, 53, 54, 98 ]
    assert quickSelect(inputList, 3) == 53
