function [symbols] = expand_symbols(slots,d_symbols,u_symbols)
%expand_symbols expands symbols for all slots
%   All checks are done
    d_slots = count(slots, 'D');
    s_slots = count(slots, 'S');
    u_slots = count(slots, 'U');
    n_slots = strlength(slots);
    
    if d_symbols + u_symbols > s_slots*14
        error("Not enough Special slots")
    end
    
    d_slots = d_slots + floorDiv(d_symbols, 14);
    u_slots = u_slots + floorDiv(u_symbols, 14);
    s_slots = s_slots - floorDiv(d_symbols, 14) - floorDiv(u_symbols, 14);
    d_symbols = mod(d_symbols, 14);
    u_symbols = mod(u_symbols, 14);
    
    symbols = char(zeros(n_slots, 14));
    symbols(1:d_slots, :) = 'D';
    symbols((d_slots+1):(n_slots-u_slots), :) = 'F';
    symbols((1+n_slots - u_slots):n_slots, :) = 'U';
    
    if s_slots > 0
        symbols((d_slots+1), 1:d_symbols) = 'D';
        symbols((n_slots - u_slots), (14-u_symbols+1):14) = 'U';
    end
        
end