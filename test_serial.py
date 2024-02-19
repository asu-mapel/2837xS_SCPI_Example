import serial
ser = serial.Serial('COM5', baudrate=115200)  # open serial port
# ser = serial.Serial('COM5', baudrate=9600)  # open serial port

print(ser.name)         # check which port was really used
ser.write(b'aIDN?a')     # write a string
print(ser.read(100))
ser.close()             # close port