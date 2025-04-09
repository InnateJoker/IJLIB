#ifndef IJMATH_HPP
#define IJMATH_HPP

#include <cmath>
#include "IJint.hpp"

namespace ij {
    typedef IJint IJint;

    // lowpow

    template <typename t_lowpow>
    t_lowpow lowpow(t_lowpow &one, t_lowpow &two) {
        t_lowpow res = 1;
        while (two > 0) {
            if (two % 2 == 1) {
                res *= one;
            }
            one *= one;
            two /= 2;
        }
        return res;
    }
    template <typename T_lowpow_>
    T_lowpow_ lowpow(T_lowpow_ &&one, T_lowpow_ &&two) {
        T_lowpow_ res = 1;
        while (two > 0) {
            if (two % 2 == 1) {
                res *= one;
            }
            one *= one;
            two /= 2;
        }
        return res;
    }
    template <typename T_lowpow>
    T_lowpow lowpow(T_lowpow &one, T_lowpow &two, T_lowpow &mod) {
        T_lowpow res = 1;
        while (two > 0) {
            if (two % 2 == 1) {
                res = (res * one) % mod;
            }
            one = (one * one) % mod;
            two /= 2;
        }
        return res;
    }
    template <typename T_lowpow_>
    T_lowpow_ lowpow(T_lowpow_ &&one, T_lowpow_ &&two, T_lowpow_ &&mod) {
        T_lowpow_ res = 1;
        while (two > 0) {
            if (two % 2 == 1) {
                res = (res * one) % mod;
            }
            one = (one * one) % mod;
            two /= 2;
        }
        return res;
    }

    // gcd and lcm

    template <typename t_gcd>
    t_gcd gcd(t_gcd &one, t_gcd &two) {
        while (two != 0) {
            t_gcd t = one;
            two = one % two;
            one = t;
        }
        return one;
    }
    template <typename T_gcd>
    T_gcd gcd(T_gcd &&one, T_gcd &&two) {
        while (two != 0) {
            T_gcd t = one;
            two = one % two;
            one = t;
        }
        return one;
    }

    template <typename t_lcm>
    t_lcm lcm(t_lcm &one, t_lcm &two) {
        return one / gcd(one, two) * two;
    }
    template <typename T_lcm>
    T_lcm lcm(T_lcm &&one, T_lcm &&two) {
        return one / gcd(one, two) * two;
    }

    // max and min

    template <typename t_max>
    t_max max(t_max &one) {
        return one;
    }
    template <typename T_max, typename ...T_maxs>
    T_max max(T_max &one, T_maxs &...two) {
        return one > max(two...) ? one : max(two...);
    }
    template <typename t_max_>
    t_max_ max(t_max_ &&one) {
        return one;
    }
    template <typename T_max_, typename ...T_maxs_>
    T_max_ max(T_max_ &&one, T_maxs_ &&...two) {
        return one > max(two...) ? one : max(two...);
    }

    template <typename t_min>
    t_min min(t_min &one) {
        return one;
    }
    template <typename T_min, typename ...T_mins>
    T_min min(T_min &one, T_mins &...two) {
        return one < min(two...) ? one : min(two...);
    }
    template <typename t_min_>
    t_min_ min(t_min_ &&one) {
        return one;
    }
    template <typename T_min_, typename ...T_mins_>
    T_min_ min(T_min_ &&one, T_mins_ &&...two) {
        return one < min(two...) ? one : min(two...);
    }

    // abs and sqrt

    template <typename t_abs>
    t_abs abs(t_abs &one) {
        return one < 0 ? -one : one;
    }
    template <typename T_abs>
    T_abs abs(T_abs &&one) {
        return one < 0 ? -one : one;
    }

    template <typename t_sqrt>
    t_sqrt sqrt(t_sqrt &one) {
        if constexpr (std::is_floating_point<t_sqrt>::value) {
            t_sqrt x = one;
            t_sqrt prev = 0;
            while (abs(x - prev) > 1e-6) {
                prev = x;
                x = (x + one / x) / 2;
            }
            return x;
        } else {
            t_sqrt left = 0, right = one, mid, ans = 0;
            while (left <= right) {
                mid = left + (right - left) / 2;
                if (mid * mid <= one) {
                    ans = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            return ans;
        }
    }
    template <typename T_sqrt>
    T_sqrt sqrt(T_sqrt &&one) {
        if constexpr (std::is_floating_point<T_sqrt>::value) {
            T_sqrt x = one;
            T_sqrt prev = 0;
            while (abs(x - prev) > 1e-6) {
                prev = x;
                x = (x + one / x) / 2;
            }
            return x;
        } else {
            T_sqrt left = 0, right = one, mid, ans = 0;
            while (left <= right) {
                mid = left + (right - left) / 2;
                if (mid * mid <= one) {
                    ans = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            return ans;
        }
    }
    template <typename t_sqrtn>
    t_sqrtn sqrt(t_sqrtn &one, t_sqrtn &n) {
        t_sqrtn left = 0, right = one, mid, ans = 0;
        auto power = [&](t_sqrtn base, t_sqrtn exp) {
            t_sqrtn result = 1;
            for (int i = 0; i < static_cast<int>(exp); ++i) {
                result *= base;
                if (result > one) {
                    return result;
                }
            }
            return result;
        };

        if constexpr (std::is_floating_point<t_sqrtn>::value) {
            while (right - left > 1e-6) {
                mid = left + (right - left) / 2;
                if (std::pow(mid, n) <= one) {
                    ans = mid;
                    left = mid;
                } else {
                    right = mid;
                }
            }
        } else {
            while (left <= right) {
                mid = left + (right - left) / 2;
                t_sqrtn p = power(mid, n);
                if (p <= one) {
                    ans = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return ans;
    }
    template <typename T_sqrtn>
    T_sqrtn sqrt(T_sqrtn &&one, T_sqrtn &&n) {
        T_sqrtn left = 0, right = one, mid, ans = 0;
        auto power = [&](T_sqrtn base, T_sqrtn exp) {
            T_sqrtn result = 1;
            for (int i = 0; i < static_cast<int>(exp); ++i) {
                result *= base;
                if (result > one) {
                    return result;
                }
            }
            return result;
        };

        if constexpr (std::is_floating_point<T_sqrtn>::value) {
            while (right - left > 1e-6) {
                mid = left + (right - left) / 2;
                if (std::pow(mid, n) <= one) {
                    ans = mid;
                    left = mid;
                } else {
                    right = mid;
                }
            }
        } else {
            while (left <= right) {
                mid = left + (right - left) / 2;
                T_sqrtn p = power(mid, n);
                if (p <= one) {
                    ans = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return ans;
    }
}
#endif // IJMATH_HPP