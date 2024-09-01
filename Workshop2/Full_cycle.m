function [BER] = Full_cycle(snr, PN_name, MOD_type, Cyclic_Guarde, Cyclic_Guarde_size)
%FULL_CYCLE genrate full cycle using given parameters
%   Most parameters are optional
    arguments
        snr double
        PN_name char = 'PN11'
        MOD_type char = 'QPSK'
        Cyclic_Guarde char = 'Cyclic'
        Cyclic_Guarde_size double = 0
    end

data = Genrate_PN(PN_name);
scram_data = Scrambler(data);
mod_signal = Modulation(scram_data, MOD_type);

signal_channeled = Tx_Rx(mod_signal, snr);

demod_signal = Demodulation(MOD_type, signal_channeled);
data_rx = Descrambler(demod_signal);
BER = biterr(data, data_rx);
 
end

