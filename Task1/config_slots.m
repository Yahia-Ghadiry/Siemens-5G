function [slots] = config_slots(n_slots, d_slots, u_slots)
%config_slots Configures Slots using number of download and upload slots
%   All checks are done

if d_slots + u_slots > n_slots
    error("Number of slots isn't enough")
end
slots = "";
for s = 1:n_slots
    if s <= d_slots
        slots = slots + "D";
    elseif s <= n_slots - u_slots
        slots = slots + "S";
    else
        slots = slots + "U";
    end
end
end