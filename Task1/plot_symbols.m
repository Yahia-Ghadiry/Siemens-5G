function plot_symbols(symbols, slot_time, offset)
%plot_symbols plots the given symbols
%   No checks needed
    
    symbol_colors = containers.Map({'D', 'F', 'U'}, {[0, 0.4470, 0.7410], [0.4660, 0.6740, 0.1880], [0.8500, 0.3250, 0.0980]});

    [rows , columns] = size(symbols);
    for r = 1:rows
        for c = 1:columns
            rectangle(Position=[((r-1)*slot_time+offset), (c-1), slot_time 1], FaceColor=symbol_colors(symbols(r, c)), EdgeColor=[0, 0, 0]);
            %TODO make lines in between p1 and p2 and
        end
    end
end

