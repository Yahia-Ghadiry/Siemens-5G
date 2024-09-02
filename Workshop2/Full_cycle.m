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


data_tx = Genrate_PN(14, 1024);
scram_data = Scrambler(data_tx);
coded_data = Convolution(scram_data);
mod_signal = Modulation(coded_data, MOD_type);

signal_tx = Transmmiter(mod_signal, 14, 128);
length(signal_tx) / 14
length(signal_tx)
signal_tx = conv(signal_tx, [2 2.5 1.5])/3;
length(signal_tx)
%tx_signal_noise = awgn(tx_signal, snr);
% signal_channeled = Tx_Rx(mod_signal, snr);

signal_rx = Reciver(signal_tx, 14, 128, [2 2.5 1.5]);



demod_signal = Demodulation(signal_rx, MOD_type);
decoded_data = Viterbi(demod_signal);
data_rx = Descrambler(decoded_data);

BER = Calculate_error(data_tx, data_rx);

end

