function [BER] = Calculate_error(data_tx, data_rx, using_viterbi)
%CALCULATE_ERROR calculates BER
    arguments   
        data_tx double
        data_rx double
        using_viterbi char = 'true'
    end

    if strcmp(using_viterbi, 'true')
        error = comm.ErrorRate(ComputationDelay=3,ReceiveDelay=34);
        BER = error(data_tx, data_rx);
        BER = BER(1);
        
    else
        error = comm.ErrorRate();
        BER = error(data_tx, data_rx);
        BER = BER(1);
    end

end

