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


data_tx = Genrate_PN(PN_name, sample_size=1024);
scram_data = Scrambler(data_tx);
coded_data = Convolution(scram_data);
mod_signal = Modulation(coded_data, MOD_type);

signal_channeled = Tx_Rx(mod_signal, snr);

demod_signal = Demodulation(signal_channeled, MOD_type);
decoded_data = Viterbi(demod_signal);
data_rx = Descrambler(decoded_data);

BER = Calculate_error(data_tx, data_rx);

end

