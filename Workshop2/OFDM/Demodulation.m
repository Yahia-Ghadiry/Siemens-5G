function [demodulated_signal] = Demodulation(signal, mod_type)
%DEMODULATION Demodulate data
%   mod_type is optional

    arguments 
        signal double
        mod_type char = 'QPSK'
    end

if strcmp(mod_type, 'QPSK')
    demodulated_signal = pskdemod(signal, 4, OutputType='bit');

elseif strcmp(mod_type, 'BPSK')
    demodulated_signal = pskdemod(signal, 2, OutputType='bit');

else

    mod_symbols = mod_type(1:strlength(mod_type)-4);

    try
       mod_symbols = str2double(mod_symbols);
    catch
        error('Modulation use BPSK, QPSK, M-PSK (M is the nouber of PSK Symmbols (need to be power of 2))')
    end

    demodulated_signal = pskdemod(signal, mod_symbols, OutputType='bit');    

end

