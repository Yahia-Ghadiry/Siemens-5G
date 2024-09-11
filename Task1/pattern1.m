function pattern1(scs, p, d_slots, u_slots, d_symbols, u_symbols)
%pattern1 Applies pattern1 and plots there symbols
%   All checks are done
    if mod(20, p) ~= 0
        error("P must divide 20")
    end
    
    n_slots = get_n_slots(scs, p);
    slots = config_slots(n_slots, d_slots, u_slots);
    symbols = expand_symbols(slots, d_symbols, u_symbols);
    
    plot_pattern(symbols, '', p, 0)

end