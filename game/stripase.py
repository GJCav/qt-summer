from genericpath import isfile
from PIL import Image
import json as Json
import os
import os.path as Path
import sys

fileList = os.listdir()
fileList = [f for f in fileList if Path.isfile(f) and f.lower().endswith('.json')]

def selectFromArr(arr):
    for i, e in enumerate(arr):
        print(f'{i}: {e}')
    slt = int(input('select: '))
    return arr[slt]

jsonFile = selectFromArr(fileList)
with open(jsonFile, 'r', encoding='utf-8') as f:
    json = Json.load(f)

bottom = 0
for frame in json['frames']:
    bottom = max(bottom, frame['frame']['y'] + frame['frame']['h'])

print(f'total height: {bottom}')
yes = input('Sure?: y/n')
if yes != 'y':
    sys.exit(0)

imgFiles = [f for f in os.listdir() if Path.isfile(f) and f.lower().endswith('.png')]
imgFile = selectFromArr(imgFiles)

src = Image.open(imgFile)
dst = src.crop((0, 0, src.width, bottom))

if not Path.exists('strip'):
    os.mkdir('strip')

dst.save(f'strip/{imgFile}')