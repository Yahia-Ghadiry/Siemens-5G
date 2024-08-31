function [descrambeld_frame] = Descrambler(input_frame)
%DESCRAMBLER Summary of this function goes here
%   Detailed explanation goes here
descamb = comm.Descrambler(CalculationBase=2, InitialConditions=[0 1 0 1]);
descrambeld_frame = descamb(input_frame);

end

