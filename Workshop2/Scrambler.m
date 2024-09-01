function [scrambeld_frame] = Scrambler(input_frame, seed)
%SCRAMBLER Scrambles the input_frame
%  seed is optional
    
    arguments 
        input_frame double
        seed double = [0 1 0 1]
    end

scramb = comm.Scrambler(CalculationBase=2, InitialConditions=seed);
scrambeld_frame = scramb(input_frame);

end

