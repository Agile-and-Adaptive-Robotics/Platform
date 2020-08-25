%Author: Jake Chung
%Aug-5-2020
%Plot the data output from the platform to comepare the sine wave output

clc
close all
clear

%load in the data
dir1 = 'rawData\BodeData3.mat';
data1 = load(dir1, 'numData');
data1 = data1.numData; %convert to double type

% dir2 = 'rawData\BodeRawData_motorNotRunning.mat';
% data2 = load(dir2, 'data');
% data2 = data2.data; %convert to double type

%scale encoder data 
encAngle = 360/8192 * data1(:,1);
encBit = 4096/10*encAngle;

%plot the data
index = linspace(1,100,5000);
figure(1)
plot(index, data1(:,2)-2048)
%plot(index, data2(:,2))
ylabel('Position in Binary')
xlabel('Time (s)')
hold on
plot(index, encBit)
ylabel('Angular position (Encoder pulse)')
xlabel('Time (s)')
