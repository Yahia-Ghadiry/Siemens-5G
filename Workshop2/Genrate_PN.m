function [pn_frame] = Genrate_PN(PN_name, seed, sample_size)
%GENRATE_PN creates a PN sequance using PN_Sequance name and seed
%   seed size needs to be compatibale with PN_Name

    arguments
        PN_name char = 'PN11'
        seed double = ones(11)
        sample_size double = 1024
    end

if strcmp(PN_name, 'PN11')
    if width(seed ~= 11)
        seed = ones(1, 11);
    end
    poly = 'z^11 + z^2 + 1';

elseif strcmp(PN_name, 'PN15')
    if width(seed ~= 15)
        seed = ones(1, 15);
    end
    poly = 'z^15 + z^14 + 1';

elseif strcmp(PN_name, 'PN23')
    if width(seed ~= 23)
        seed = ones(1, 23);
    end
    poly = 'z^23 + z^5 + 1';

else
    error('PN sequance not supported')
end

pn_Seq = comm.PNSequence(Polynomial=poly, InitialConditions=seed, SamplesPerFrame=sample_size);
pn_frame = pn_Seq();


end

