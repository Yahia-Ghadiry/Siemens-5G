function [rx_signal] = Tx_Rx(signal, snr)
%TX_RX Summary of this function goes here
%   Detailed explanation goes here

tx_signal = ifft(signal);
tx_signal_noise = awgn(tx_signal, snr);
rx_signal= fft(tx_signal_noise);

end

