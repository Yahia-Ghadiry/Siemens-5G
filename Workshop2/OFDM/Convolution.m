function [coded_data] = Convolution(data)
%CONVOLUTION codes data for viterbi

convolutionalencoder = comm.ConvolutionalEncoder;

coded_data = convolutionalencoder(data);

end

