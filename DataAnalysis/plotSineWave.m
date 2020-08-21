%Author: Jake Chung
%Aug-5-2020
%Plot the data output from the platform to comepare the sine wave output

clc
close all
clear

%load in the data
dir1 = 'rawData\BodeRawData2.mat';
data1 = load(dir1, 'data');
data1 = data1.data; %convert to double type

dir2 = 'rawData\BodeRawData_motorNotRunning.mat';
data2 = load(dir2, 'data');
data2 = data2.data; %convert to double type

%plot the data
index = linspace(1,100,5000);
figure(1)
plot(index, data1(:,2))
hold on
plot(index, data2(:,2))
ylabel('Position in Binary')
xlabel('Time (s)')

