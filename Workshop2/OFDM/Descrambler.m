function [descrambeld_frame] = Descrambler(input_frame, seed)
%DESCRAMBLER descrambles the input frame
%   seed is optional
    arguments 
        input_frame double
        seed double = [0 1 0 1]
    end

descamb = comm.Descrambler(CalculationBase=2, InitialConditions=seed);
descrambeld_frame = descamb(input_frame);

end

