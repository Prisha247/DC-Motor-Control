import serial
import time

ser = serial.Serial('COM13', 9600)
ser.close()
ser.open()

start = time.time()
with open('data.csv', 'w') as f:
    f.write('left,right,speed\n')
    while(True):
        lineOfData = ser.readline().decode()
        if len(lineOfData)>0:
            left_sensor, right_sensor, motor_speed = [x for x in lineOfData.split(' ')]
            f.write(f'{left_sensor},{right_sensor},{motor_speed}')
        if time.time() >= 30 + start:
            f.close()
            break


