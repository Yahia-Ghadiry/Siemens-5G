function [scrambeld_frame] = Scrambler(input_frame)
%SCRAMBLER Summary of this function goes here
%   Detailed explanation goes here
scramb = comm.Scrambler(CalculationBase=2, InitialConditions=[0 1 0 1]);
scrambeld_frame = scramb(input_frame);

end

