#!/usr/bin/python

input = open('./bl1.bin.text', 'r')
output = open('./bl1.bin.padded.text', 'w')

lines = input.readlines()
count = 0

for line in lines:
  output.write(line)
  count = count + 1

while (count < 32768):
  output.write('ffffffff\n')
  count = count + 1

input.close()
output.close()
