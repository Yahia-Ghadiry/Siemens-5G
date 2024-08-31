function [modulated_signal] = Modulation(mod_type,data)
%MODULATION Summary of this function goes here
%   Detailed explanation goes here

if strcmp(mod_type, 'QPSK')
    modulator = comm.QPSKModulator(BitInput=true);
    
modulated_signal = modulator(data);

end

