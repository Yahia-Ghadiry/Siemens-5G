function [pn_frames] = Genrate_PN(n_frames, sample_size, sequance_type, seed)
%GENRATE_PN creates a PN sequance using PN_Sequance name and seed
%   seed size needs to be compatibale with PN_Name

    arguments
        n_frames double = 1
        sample_size double = 1024
        sequance_type char = 'PN11'
        seed double = ones(11)
    end

if strcmp(sequance_type, 'PN11')
    if width(seed ~= 11)
        seed = ones(1, 11);
    end
    poly = 'z^11 + z^2 + 1';

elseif strcmp(sequance_type, 'PN15')
    if width(seed ~= 15)
        seed = ones(1, 15);
    end
    poly = 'z^15 + z^14 + 1';

elseif strcmp(sequance_type, 'PN23')
    if width(seed ~= 23)
        seed = ones(1, 23);
    end
    poly = 'z^23 + z^5 + 1';

else
    error('PN sequance not supported')
end

pn_Seq = comm.PNSequence(Polynomial=poly, InitialConditions=seed, SamplesPerFrame=sample_size);

pn_frames = zeros(sample_size, n_frames);

for i = 1:n_frames

    pn_frames(:, i) = pn_Seq();
end

pn_frames = reshape(pn_frames, sample_size * n_frames, 1);

end

