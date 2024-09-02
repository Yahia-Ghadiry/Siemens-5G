function [signal_out] = Reciver(signal_in, ofdm_symbols, cp_size, incedent_resopnce)
%RECIVER recives the signal, and makes sure the line of sight is used

%TODO add CP and Gauad band options and lengths

multipaths = width(incedent_resopnce);
[~, line_of_sight] = max(incedent_resopnce);

signal_in = signal_in(line_of_sight:end-multipaths + line_of_sight);

    psk_symbols = length(signal_in);
    size_ofdm_symbol = (psk_symbols / ofdm_symbols) - cp_size;
    signal_in = reshape(signal_in, size_ofdm_symbol + cp_size, ofdm_symbols);
    
    singals_cp_removed = zeros(size_ofdm_symbol, ofdm_symbols);
    singal_out = zeros(size_ofdm_symbol, ofdm_symbols);

    for i = 1:ofdm_symbols

        signals_cp_removed(:, i) = signal_in((cp_size + 1):end, i);

        signal_out(:, i) = fft(signals_cp_removed(:, i));
    
    end

    signal_out = reshape(signal_out, size_ofdm_symbol * ofdm_symbols, 1);
    scatterplot(signal_out);
    
end

