function [n_slots] = get_n_slots(scs,p)
%slots_csc gives number of slots when giving sub carrier spacing and period p
%   All checks are done

    meo = (scs/15000 -1);
    
    if mod(meo, 1) ~= 0 || meo < 0
        error("slots_scs must by multiple of 15000")
    end
    
    n_slots = p.*2^(meo);
    
    if mod(n_slots, 1) ~= 0
        error("P and SCS (meo) do not match")
    end
    
end