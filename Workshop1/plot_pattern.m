function plot_pattern(symbols, symbols2, p, p2)
%plot_pattern plots the symbols based on pattern type
%   No checks are done

    figure(WindowState='maximized');
    hold on;
    %axis equal;
    n_slots = size(symbols, 1);
    slot_time = p/n_slots;
    
    n_slots2 = size(symbols2, 1);
    slot_time2 = p2/n_slots2;
    
    
    for i = 1:(20/(p+p2))
        plot_symbols(symbols, slot_time, ((p+p2)*(i-1)));
    end
    for i = 1:(20/(p+p2))
        plot([((p+p2)*(i-1)), ((p+p2)*(i-1))], [14, 15], 'b');
        text(((p+p2)*(i-1)), 14.5, ' P1 start', Color='blue')
    end
    
    if p2 ~= 0
        for i = 1:(20/(p+p2))
            plot_symbols(symbols2, slot_time2, ((p+p2)*i-p2));
        end
        for i = 1:(20/(p+p2))
            plot([((p+p2)*i-p2), ((p+p2)*i-p2)], [14, 15], 'r');
            text(((p+p2)*i-p2), 14.5, ' P2 start', Color='red')
        end
    end
    
    patches = [patch(NaN, NaN, [0, 0.4470, 0.7410], EdgeColor=[0, 0, 0]), ... 
            patch(NaN, NaN, [0.4660, 0.6740, 0.1880], EdgeColor=[0, 0, 0]), ...
            patch(NaN, NaN, [0.8500, 0.3250, 0.0980], EdgeColor=[0, 0, 0])];
    
    legend(patches,{'Download', 'Flexiable', 'Upload'}, location='northeastoutside')
    yticks([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14])
    xlabel('Time (ms)');
    ylabel('Symbols');

end