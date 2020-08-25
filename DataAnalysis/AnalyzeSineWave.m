%{
Data analysis for determining the transfer function of the platform
Author: Jake Chung
%}

clc
close all
clear

%% load the local data file
loadRaw = load('rawData/BodeData3.mat');
raw = loadRaw.numData; %convert to double type

%% plot the raw data
%create the time index array
time = linspace(0,100,5000);
figure
plot(time, raw(:,1)) %plot the input position
ylabel('Angular position (bit)')
xlabel('Time (s)')
title('Desired position sent to the Platform')
figure
plot(time, raw(:,2)) %plot the respose from the encoder
ylabel('Angular position (pulses)')
xlabel('Time (s)')
title('Response position collected from the encoder')

%% 


