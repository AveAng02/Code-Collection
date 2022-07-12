import math

pi = 3.1415926535897932384626433832795

accuracy = int(input("Enter the number accuracy after decimal: "))

radius = 10.0 ** accuracy  #radius of the circle

peri_ex = 8 * radius

peri_in = (radius / math.sqrt(2)) * 8

print(peri_ex)
print(peri_in)

while ((int(peri_ex) + int(peri_in)) / (4 * radius)) - pi > (10 ** ((-1) * accuracy)):
    peri_ex = 2 * peri_ex * peri_in / (peri_ex + peri_in)
    peri_in = math.sqrt(peri_in * peri_ex)

  #  if ((int(peri_ex) + int(peri_in)) / (4 * radius)) - pi < (10 ** ((-1) * accuracy)):
  #      break

    print((int(peri_ex) + int(peri_in)) / (4 * radius))


print((int(peri_ex) + int(peri_in)) / (4 * radius))







