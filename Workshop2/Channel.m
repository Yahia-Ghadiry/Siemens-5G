function [signal_out] = Channel(signal_in, incedent_responce, snr)
%CHANNEL Simulate channel
%   only multipath and awgn noise are implemented

% TODO add more 
    arguments 
        signal_in double
        incedent_responce double = 1
        snr double = 40
    end

signal_in = conv(signal_in, incedent_responce)/width(incedent_responce);
signal_out = awgn(signal_in, snr);

end

