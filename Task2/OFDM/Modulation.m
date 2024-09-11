function [modulated_signal] = Modulation(data, mod_type)
%MODULATION Modulate data
%   mod_type is optional and is checked

    arguments 
        data double
        mod_type char = 'QPSK'
    end

if strcmp(mod_type, 'QPSK')
    modulated_signal = pskmod(data, 4, inputType='bit');

elseif strcmp(mod_type, 'BPSK')
    modulated_signal = pskmod(data, 2, inputType='bit');

else

    mod_symbols = mod_type(1:strlength(mod_type)-4);

    try
       mod_symbols = str2double(mod_symbols);
    catch
        error('Modulation use BPSK, QPSK, M-PSK (M is the nouber of PSK Symmbols (need to be power of 2))')
    end

    modulated_signal = pskmod(data, mod_symbols, inputType='bit');    

end

