
from bitarray.util import int2ba

# preconditions of scene
iterations = 4
numberOfRows = 2**iterations
numberOfColumns = 2**iterations
numberOfCells = numberOfRows * numberOfColumns
width = 800
height = 800
dx = width / numberOfRows
dy = height / numberOfColumns

# taking coordinates 
xCoord = float(input("Enter x coordinate: "))
yCoord = float(input("Enter y coordinate: "))

# generating bitarrays
rowNumOfCoord = int(xCoord // dx)
colNumOfCoord = int(yCoord // dy)

xarray = list(int2ba(rowNumOfCoord))
yarray = list(int2ba(colNumOfCoord))

# padding the lists
length = int(iterations) - len(xarray)
pad = []

if length > 0:
    pad = [0] * length

xarray = pad + xarray

length = int(iterations) - len(yarray)
pad = []

if length > 0:
    pad = [0] * length

yarray = pad + yarray

morton = []

# generating morton code
for i in range(int(iterations)):
    morton.append(yarray[i])
    morton.append(xarray[i])

print(morton)

