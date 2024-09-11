function pattern2(scs, p, d_slots, u_slots, d_symbols, u_symbols, p2, d_slots2, u_slots2, d_symbols2, u_symbols2)
%pattern1 Applies pattern1 and plots there symbols
%   All checks are done
    if mod(20, p+p2) ~= 0
        error("P + P2 must divide 20")
    end
    n_slots = get_n_slots(scs, p);
    slots = config_slots(n_slots, d_slots, u_slots);
    symbols = expand_symbols(slots, d_symbols, u_symbols);
    
    n_slots2 = get_n_slots(scs, p2);
    slots2 = config_slots(n_slots2, d_slots2, u_slots2);
    symbols2 = expand_symbols(slots2, d_symbols2, u_symbols2);
    
    plot_pattern(symbols, symbols2, p, p2)

end