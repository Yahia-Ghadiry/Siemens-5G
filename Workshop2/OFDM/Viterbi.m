function [decoded_data] = Viterbi(data)
%VITERBI decodes convultioned data

viterbidecoder = comm.ViterbiDecoder(InputFormat='Hard', TracebackDepth=34);

decoded_data = viterbidecoder(data);

end

