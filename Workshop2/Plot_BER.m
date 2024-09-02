function Plot_BER(snrs, psks)
%PLOT_BER Summary genrates plots for each psks with snrs accuracy

hold on

for psk = psks
    bers = zeros(1, width(snrs));
    disp(psk)
    for i = 1:width(snrs)
        bers(i) = Full_cycle(snrs(i), MOD_type=psk);
    end
    
    semilogy(snrs, bers);

end
hold off

xlabel('Signal to Noise Ration in db');
ylabel('Bit Error Rate');
title('Bit Error Rate vs Signal to Noise Ratio for M-PSKs comparison');
legend ('BPSK','QPSK','16-PSK', '256-PSK')
end

