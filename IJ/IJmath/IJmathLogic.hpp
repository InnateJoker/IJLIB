#ifndef IJMATHLOGIC_HPP
#define IJMATHLOGIC_HPP

namespace ij {
    template <typename t_and>
    bool And(t_and &one, t_and &two) {
        return one != 0 && two != 0;
    }
    template <typename T_and>
    bool And(T_and &&one, T_and &&two) {
        return one != 0 && two != 0;
    }

    template <typename t_or>
    bool Or(t_or &one, t_or &two) {
        return one != 0 || two != 0;
    }
    template <typename T_or>
    bool Or(T_or &&one, T_or &&two) {
        return one != 0 || two != 0;
    }

    template <typename t_not>
    bool Not(t_not &one) {
        return one == 0;
    }
    template <typename T_not>
    bool Not(T_not &&one) {
        return one == 0;
    }
}

#endif // IJMATHLOGIC_HPP