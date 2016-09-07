#pragma once

#ifdef DEBUG
#include <iostream>
#endif

#include <mapbox/geometry/wagyu/active_bound_list.hpp>
#include <mapbox/geometry/wagyu/bound.hpp>

namespace mapbox {
namespace geometry {
namespace wagyu {

template <typename T>
struct sorting_bound {

    active_bound_list_itr<T> bound;
    std::size_t index;

    sorting_bound(active_bound_list_itr<T> bound_, std::size_t index_)
        : bound(bound_), index(index_) {
    }
};

template <typename T>
using sorting_bound_list = std::list<sorting_bound<T>>;

template <typename T>
using sorting_bound_list_itr = typename sorting_bound_list<T>::iterator;

template <typename T>
struct sorting_bound_sorter {
    inline bool operator()(sorting_bound<T> const& bound1, sorting_bound<T> const& bound2) {
        return bound2.index > bound1.index;
    }
};

template <typename T>
inline void swap_positions_in_SBL(sorting_bound_list_itr<T>& bnd1,
                                  sorting_bound_list_itr<T>& bnd2,
                                  sorting_bound_list<T>& sorting_bounds) {
    if (std::next(bnd2) == bnd1) {
        sorting_bounds.splice(bnd2, sorting_bounds, bnd1);
    } else if (std::next(bnd1) == bnd2) {
        sorting_bounds.splice(bnd1, sorting_bounds, bnd2);
    } else {
        auto next_bnd1 = std::next(bnd1);
        auto next_bnd2 = std::next(bnd2);
        sorting_bounds.splice(next_bnd1, sorting_bounds, bnd2);
        sorting_bounds.splice(next_bnd2, sorting_bounds, bnd1);
    }
}

#ifdef DEBUG

template <class charT, class traits, typename T>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& out,
                                                     const sorting_bound<T>& s) {
    out << "    index: " << s.index << std::endl;
    out << *(*(s.bound)) << std::endl;
    return out;
}

template <class charT, class traits, typename T>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& out,
                                                     const sorting_bound_list<T>& bnds) {
    for (auto const& bnd : bnds) {
        out << bnd;
    }
    return out;
}

#endif
}
}
}