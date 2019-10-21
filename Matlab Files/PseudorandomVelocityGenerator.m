%This script generates a pseudorandom ternary sequence, as outlined by
%Robert Peterka in "Sensorimotor Integration in Human Postural Control". It
%used a shift register to generate an output, which is calculated by a
%modulo 3 addition of the last 3 register positions at the time step.

clear
close all
clc

VelGain = 0.3;  

%Reg = [2 0 2 0 2];             %The given initial sequence from the paper
Reg = [0 1 2 0 1];

TimeStep = 0.25;

Position(1) = 0;

%Pseudorandom sequence has a period of i = 243
for i = 1:243
    %Calculate output with modulo 3 addition
    Output(i) = mod(Reg(3)-Reg(4)-Reg(5), 3);

    %shift Register values
    Reg(2:5) = Reg(1:4);
    Reg(1) = Output(i);
    
    %Convert the Ouput into a velocity profile
    if Output(i) == 0
        Vel(i) = 0;
    elseif Output(i) == 1
        Vel(i) = VelGain;
    else
        Vel(i) = -VelGain;
    end
    
    %Integrate velocity for a position profile
    if i == 1
        Position(i) = 0;
    else
        Position(i) = Position(i-1) + Vel(i-1)*TimeStep;
    end
    
    time(i) = TimeStep*(i-1);
end

figure
stairs(Vel)
ylim([-VelGain*1.2 VelGain*1.2])

figure
plot(time, Position)