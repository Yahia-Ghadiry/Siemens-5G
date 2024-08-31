function [pn_frame] = Genrate_PN(PN_name, seed)
%GENRATE_PN Summary of this function goes here
%   Detailed explanation goes here

if strcmp(PN_name, 'PN11')
    if width(seed ~= 11)
        %TODO
        disp('seed size is incompatiable')
        seed = ones(1, 11);
    end
    poly = 'z^11 + z^2 + 1';
elseif strcmp(PN_name, 'PN15')
    if width(seed ~= 15)
        %TODO
        disp('seed size is incompatiable')
        seed = ones(1, 15);
    end
    poly = 'z^15 + z^14 + 1';
elseif strcmp(PN_name, 'PN23')
    if width(seed ~= 23)
        %TODO
        disp('seed size is incompatiable')
        seed = ones(1, 23);
    end
    poly = 'z^23 + z^5 + 1';o
else
    error('PN sequance not supported')
end

pn_Seq = comm.PNSequence(Polynomial=poly, InitialConditions=seed, SamplesPerFrame=1024);
pn_frame = pn_Seq();


end

