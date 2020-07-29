function out = ConvertCell2NumArr(inputCell)
%this function converts the output cell array of the sCollectSineData
%function to a usable matrix form
lengthCell = length(inputCell);
out = zeros(lengthCell,2);
for i = 1:lengthCell
    out(i,:) = str2num(inputCell{i});
end
end