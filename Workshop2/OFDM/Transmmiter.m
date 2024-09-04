function [signal_out] = Transmmiter(signal_in, ofdm_symbols, cp_size)
%TRANSMMITER Transimts the signal by converting it to time domain 
% and addes the CP or guard band

    arguments 
        signal_in double
        ofdm_symbols double
        cp_size double
    
    end

%TODO add CP and Gauad band options and lengths

    psk_symbols = length(signal_in);
    size_ofdm_symbol = psk_symbols / ofdm_symbols;
    signal_in = reshape(signal_in, size_ofdm_symbol, ofdm_symbols);
    
    signal_cp = zeros(cp_size+size_ofdm_symbol, ofdm_symbols);  
    for i = 1:ofdm_symbols
        
        current_ofdm_symbol = ifft(signal_in(:, i));
        signal_cp(:, i) = [current_ofdm_symbol((end - cp_size + 1):end); current_ofdm_symbol];
    end

    signal_out = reshape(signal_cp, (cp_size+size_ofdm_symbol) * ofdm_symbols, 1);        


end

