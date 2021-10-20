import serial

# Setting Arduino parameters
arduinoComPort="/dev/cu.usbmodem101" # fill out later
baudRate = 9600
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

with open('data.csv', 'a') as f:
    f.write('left,right\n')
    while(True):
        lineOfData = serialPort.readline().decode()
        if len(lineOfData)>0:
            try:    
                left, right = [x for x in lineOfData.split(' ')]
                f.write(f'{left},{right}')
            except:
                f.close()
                break
