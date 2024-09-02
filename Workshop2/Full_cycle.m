function [BER] = Full_cycle(snr, options)
%FULL_CYCLE genrate full cycle using given parameters
%   Most parameters are optional
    arguments
        snr double = 40
        options.PN_type char = 'PN11'
        options.PN_seed double = ones(11)
        options.MOD_type char = 'QPSK'
        options.incedent_responce double = [1]
        options.symbol_size double =  1024
        options.number_symbols double = 14
        options.cp_size double = 64
    end


data_tx = Genrate_PN(options.number_symbols, options.symbol_size, options.PN_type, options.PN_seed);
scram_data = Scrambler(data_tx);
coded_data = Convolution(scram_data);
mod_signal = Modulation(coded_data, options.MOD_type);

signal_tx = Transmmiter(mod_signal, options.number_symbols, options.cp_size);
signal_channel = Channel(signal_tx, options.incedent_responce, snr);
signal_rx = Reciver(signal_channel, options.number_symbols, options.cp_size, options.incedent_responce);

demod_signal = Demodulation(signal_rx, options.MOD_type);
decoded_data = Viterbi(demod_signal);
data_rx = Descrambler(decoded_data);

BER = Calculate_error(data_tx, data_rx);

end

