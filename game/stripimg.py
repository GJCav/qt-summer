from PIL import Image
from pprint import pprint
from collections.abc import Iterable
import os
import os.path as Path

filePrefix = 'blue-run'
fileSecRange = (1, 9)
fileSuffix = '.png'

filePrefix = input('prefix: ')
st = int(input('range start: '))
ed = int(input('range end: '))
fileSecRange = (st, ed)
fileSuffix = input('suffix: ')

class Point:
    def __init__(self):
        self.x = 0
        self.y = 0
    
    def __init__(self, x, y, *args):
        self.x = x
        self.y = y

def NewRect():
    return [[0, 0], [0, 0]]

def updateRect(rect: list, pos):
    if rect[0][0] == 0: rect[0][0] = pos.x
    if rect[0][1] == 0: rect[0][1] = pos.y
    if rect[1][0] == 0: rect[1][0] = pos.x
    if rect[1][1] == 0: rect[1][1] = pos.y

    if pos.x < rect[0][0]: rect[0][0] = pos.x
    if pos.x > rect[1][0]: rect[1][0] = pos.x
    if pos.y < rect[0][1]: rect[0][1] = pos.y
    if pos.y > rect[1][1]: rect[1][1] = pos.y

def isNullRect(rect):
    for e in rect:
        for v in e:
            if v != 0: return False
    return True

def mergeRect(rectA: list, rectB: list):
    if isNullRect(rectA): return rectB
    if isNullRect(rectB): return rectA
    return [
        [min(rectA[0][0], rectB[0][0]), min(rectA[0][1], rectB[0][1])],
        [max(rectA[1][0], rectB[1][0]), max(rectA[1][1], rectB[1][1])]
    ]

def getImageRect(file):
    img = Image.open(file)
    rect = NewRect()
    for y in range(img.height):
        for x in range(img.width):
            a, *_ = img.getpixel((x, y))
            if a == 0: continue
            updateRect(rect, Point(x, y))

    return rect

def flatten(iter):
    for e in iter:
        if isinstance(e, Iterable):
            yield from flatten(e)
        else:
            yield e


finalRect = NewRect()
for sec in range(*fileSecRange):
    filename = f'{filePrefix}{sec}{fileSuffix}'
    newRect = getImageRect(filename)
    finalRect = mergeRect(finalRect, newRect)

finalRect[1][0] += 1
finalRect[1][1] += 1

if not Path.exists('strip'):
    os.mkdir('strip')

box = tuple(flatten(finalRect))
for sec in range(*fileSecRange):
    filename = f'{filePrefix}{sec}{fileSuffix}'
    newImage = Image.open(filename).crop(box)
    newImage.save(f'./strip/{filePrefix}{sec}{fileSuffix}')
