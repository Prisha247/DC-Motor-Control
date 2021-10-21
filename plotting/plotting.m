Array=csvread('raw_data.csv');
l_ir = Array(:, 1); %left IR sensor
r_ir = Array(:, 2); %right IR sensor
l_motorspeed = Array(:, 3); %left motor speed
r_motorspeed = Array(:, 4); %right motor speed
time = Array(:, 5); %time


yyaxis left
plot(time, l_motorspeed)
hold on;
plot(time, r_motorspeed)
title('Sensor Values and Motor Speed Over Time')
xlabel('Time (as calculated by millis function)')
ylabel('Motor Speed')

yyaxis right
hold on;
plot(time, l_ir)
hold on;
plot(time, r_ir)
ylabel('IR Sensor Value')
legend('Left IR Sensor Value', 'Right IR Sensor Value', 'Left Motor Speed', 'Right Motor Speed')

hold off

