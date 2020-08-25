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


%% function to calculate the frequency of the sinewave data
function freq = detectFreq(data)
[~, idx] = max(data(:,2))
freqArr = zeros(1,length(idx)-1)
for i=1:length(idx)-1
    T = max(i+1,1)-max(i,1);
    freqArr(i) = 1/T;
end
freq = mean(freqArr);
end
