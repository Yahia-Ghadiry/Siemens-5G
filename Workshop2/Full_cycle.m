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
        options.SCRAM_seed double = [0 1 0 1]
        options.draw_Contelation char = 'no'
    end


data_tx = Genrate_PN(options.number_symbols, options.symbol_size, options.PN_type, options.PN_seed);
scram_data = Scrambler(data_tx, options.SCRAM_seed);
coded_data = Convolution(scram_data);
[interlived_data, interliver_rand] = Interliver(coded_data);
mod_signal = Modulation(interlived_data, options.MOD_type);

signal_tx = Transmmiter(mod_signal, options.number_symbols, options.cp_size);
signal_channel = Channel(signal_tx, options.incedent_responce, snr);
signal_rx = Reciver(signal_channel, options.number_symbols, options.cp_size, options.incedent_responce, options.draw_Contelation);

demod_signal = Demodulation(signal_rx, options.MOD_type);
deinterlived_data = Deinterliver(demod_signal, interliver_rand);
decoded_data = Viterbi(deinterlived_data);
data_rx = Descrambler(decoded_data, options.SCRAM_seed);


BER = Calculate_error(data_tx, data_rx);

end

