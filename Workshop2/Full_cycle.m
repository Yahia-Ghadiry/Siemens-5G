function [data_rx, BER] = Full_cycle(PN_name, PN_seed, MOD_type, snr)
%FULL_CYCLE Summary of this function goes here
%   Detailed explanation goes here
data = Genrate_PN(PN_name, PN_seed);
scram_data = Scrambler(data);
mod_signal = Modulation(MOD_type, scram_data);
signal_channeled = Tx_Rx(mod_signal, snr);
demod_signal = Demodulation(MOD_type, signal_channeled);
data_rx = Descrambler(demod_signal);
[~ , BER] = biterr(data, data_rx);
 
end

