function [demodulated_signal] = Demodulation(mod_type,signal)
%DEMODULATION Summary of this function goes here
%   Detailed explanation goes here

if strcmp(mod_type, 'QPSK')
    modulator = comm.QPSKDemodulator(BitOutput=true);
    
demodulated_signal = modulator(signal);

end

