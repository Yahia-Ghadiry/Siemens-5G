function [data_out, rand_int] = Interliver(data_in)
%INTERLIVER Interlives data and return the random int used

    rand_int =  randi(500);
    data_out = randintrlv(data_in, rand_int);

end

