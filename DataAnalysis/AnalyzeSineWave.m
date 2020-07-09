%quick data analysis of the output sine wave voltage to test the sine wave
%generation algorithm
%Author: Jake Chung

clc
close all
clear

%load the local data file
load('SineData.mat');
data = acq0001;

%set the first few values to NaN since they are not good
data(1:6,:) = NaN;

freq = detectFreq(data);
disp(freq)

%some plotting
plot(data(:,1),data(:,2), 'o')
grid on
xlabel('Time(s)')
ylabel('Voltage(V)')


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
