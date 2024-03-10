import sys
print(sys.version)
print(sys.path)

import time
import csv
import serial
import time
import os
    
path = "C:\\Users\\haofg\\Documents\\Arduino\\Data"
file_name = 'dataset_test'
counter = 1
file_path = ''

try:
    arduino = serial.Serial("COM9", 115200)
    print('Established communication to the Arduino, COM9, 115200')
except:
    print('Error establishing a communication with the Arduino')
    print('Exiting')
    exit()

# Creating a new data file path + data + first_free_number
while True:
    file_path = path + '\\' + file_name + str(counter) + '.csv'
    if os.path.exists(file_path) == False:
        print('Creating new dataset file: ' + file_path)
        f = open(file_path, 'w')
        f.close()
        break
    else:
        counter += 1

print('Starting to record the data')
with open(file_path, 'a', newline = '') as csv_file:
    csv_writer = csv.writer(csv_file)
    tare = time.perf_counter()
    csv_writer.writerow(["time", "pressure"])
    while True:
        time_ = float(time.perf_counter()) - tare
        data_point = float(arduino.readline())
        csv_writer.writerow([str(time_), str(data_point)])