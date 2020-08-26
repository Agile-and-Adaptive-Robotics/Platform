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
title('Response position collected from the encoder')
figure
plot(time, raw(:,2)) %plot the respose from the encoder
ylabel('Angular position (pulses)')
xlabel('Time (s)')
title('Desired position sent to the Platform')

%% detect -99 and break the raw data up to individual discrete frequency

index99 = find(raw(:,1) == -99); %index of -99 values
index99 = [1;index99]; %add the index 1 for the loop
%split the raw data to a 3D array [time, position, frequency]
%create holder 3D array
encoderData = ones(length(index99)-1,501); %502 is the maximum number of elements in each frequency
for i = 1:length(index99)-1
    encoderData(i,index99(i)-index99(i)+1:index99(i+1)-index99(i)) = raw(index99(i):index99(i+1),1)'; %seperate the frequency array based on the -99 index
end


