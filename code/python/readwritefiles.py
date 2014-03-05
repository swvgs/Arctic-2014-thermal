#!/usr/bin/env python
import glob #import global vars for the computer so we can get the directory list

#import sys
#import time
#import numarray
#print sys.version
#time.sleep(5.5)

file_length = 0 #var to count lines in the file

filenames = glob.glob('*.TXT') #make an array that has all the .TXT files in the directly listed in it
print filenames #print the file names

filenames_length = len(filenames) #count the number of file names

# This function will find the median. Used this for the time since the array is not sorted. Since the array is 30, it will always output a half number.
def getMedian(numericValues):
	theValues = sorted(numericValues)
	if len(theValues) % 2 == 1:
		return theValues[(len(theValues)+1)/2-1]
	else:
		lower = theValues[len(theValues)/2-1]
		upper = theValues[len(theValues)/2]
		return (float(lower + upper)) / 2
def getStdev(valueArray,avgVal):
	counter = 0 #initilize the counter
	varArr = [] #make an empty array to save values to
	for num in valueArray:
		varArr.append ( (valueArray[counter] - avgVal)**2) #add the new element to the array 
		counter += 1 #incriment the counter
	innards = sum(varArr)/len(varArr)
	stdev = innards**0.5
	return stdev



for fnames in filenames: #loop through all the files found above
	print fnames #print the current file name
	read_file = open(fnames) #open and read the data from the current file
	line_count = 1
	outfile = open(fnames+'-'+line_count+'.csv','w')
	outfile.write('Mark,'+' Time,'+' AmbTemp,'+' AmbStdv,'+ ' IR Temp,'+' IR Stdv\n') 
	for line in read_file: #loop through all the lines in the file
		file_length += 1 #incriment our number of lines counter
		print file_length #print the file length
		#if file_length > 1:
		#	print file_length,':',line
#		print line
		if 'Data collection stopped.' in line: #check to see if we stopped collecting data or not
			outfile.close()
			line_count += 1
			outfile = open(fnames+'-'line_count+'.csv','w')
#			print 'End of data stream.' #print a happy message letting us know we found the end of the file			
#			break #exit the loop
	       	a=line.split(';') #split the line at all the semicolons
#		print a
		if file_length > 0: #this will let us disreguard the array header if needed
			time = a[1].split(',') #split the time into an array
			time2 = [float(col) for col in time] #convert time from strings to floats
			amb = a[2].split(',') #split the ambient temperatures into an array
			amb2 = [float(col) for col in amb] #convert the ambient temperatures from strings to floats
			tempir = a[3].rstrip('\r\n') #get rid of the line end for the IR last item
			ir = tempir.split(',') #break the IR temperatures into an array
			ir2 = [float(col) for col in ir] #convert the IR temperatures from strings to floats
		mark = a[0] #put the marks into its own little special variable
		outfile.write(mark) #print the mark
		if file_length >0:#check to skip the header again if needed (probably can combine this loop)
			avg_time = sum(time2)/float(len(time2)) #average the time
			avg_time = getMedian(time2) #find the median time (overwrites the above line)
			avg_amb = sum(amb2)/float(len(amb2)) #average the ambient temperatures
			stdevamb = getStdev(amb2,avg_amb)
			avg_ir = sum(ir2)/float(len(ir2)) #average the IR temperatures
			stdevir = getStdev(ir2,avg_ir)

#			print avg_time
#			print avg_amb
#			print stdevamb
#			print avg_ir
#			print stdevir


			str_avgtime = str(avg_time)
			str_avgamb = str(avg_amb)
			str_stdevamb = str(stdevamb)
			str_avgir = str(avg_ir)
			str_stdevir = str(stdevir)

			
			outfile.write(','+str_avgtime+','+str_avgamb+','+str_stdevamb+','+str_avgir+','+str_stdevir+'\n')

#			print '------------------' #print a line so we can see the breaks easier
	outfile.close()
	print "\nFile length is %d lines." %file_length #tell us how many lines are in the file
	file_length = 0 #reset the variable for the next file.



