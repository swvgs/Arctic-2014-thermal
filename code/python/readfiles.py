#!/usr/bin/env python
import glob
import csv

file_length = 0

filenames = glob.glob('*.txt')
print filenames

filenames_length = len(filenames)

for fnames in filenames:
	print fnames
	read_file = open(fnames)
	for line in read_file:
		file_length += 1
		#if file_length > 1:
		#	print file_length,':',line
	       	a=line.split(';')
		print a
		if file_length > 1:
			time = a[1].split(',')
			time2 = [float(col) for col in time]
			amb = a[2].split(',')
			amb2 = [float(col) for col in amb]
			tempir = a[3].rstrip('\n')
			ir = tempir.split(',')
			ir2 = [float(col) for col in ir]
		mark = a[0]
		print mark
		if file_length >1:
			avg_time = sum(time2)/float(len(time2))
			avg_amb = sum(amb2)/float(len(amb2))
			avg_ir = sum(ir2)/float(len(ir2))
#			print time2
			print avg_time
#			print amb2
			print avg_amb
#			print ir2
			print avg_ir
	print "\nFile length is %d lines." %file_length
	file_length = 0



