#pragma once
#include <vector>
#include <functional>

template <bool prefix_tree = true, class dtype = int, class itype = int, class Opt = std::function<dtype(dtype, dtype)>>
struct fenwick_tree {
    static const std::function<itype(itype)> gnext;
    static const std::function<itype(itype)> unext;

    const itype max_val;
    std::unordered_map<itype, dtype> data;
    Opt get_opt, inc_opt, dec_opt;
    
    fenwick_tree(const itype& max_val_,
                const Opt& get_opt_ = std::plus<dtype>(),
                const Opt& inc_opt_ = std::plus<dtype>(),
                const Opt& dec_opt_ = std::minus<dtype>())
              : max_val(max_val),
                get_opt(get_opt),
                inc_opt(inc_opt),
                dec_opt(dec_opt) {}
    
    dtype get(const itype& pos) {
        dtype res(0);
        for (itype i = pos + 1; i > (itype)0 && i <= max_val; i = get_next(i)) {
            res = get_opt(res, data[i]);
        }
        return res;
    }
    template <bool inc = true>
    void inc(const itype& pos, const dtype& val) {
        for (itype i = pos + 1; i > (itype)0 && i <= max_val; i = update_next(i)) {
            data[i] = (inc ? inc_opt : dec_opt)(data[i], val);
        }
    }
};

template <bool prefix_tree, class dtype, class itype, class Opt>
const std::function<itype(itype)> fenwick_tree<prefix_tree, dtype, itype, Opt>::gnext
        = [] (const itype& x) {return x + (prefix_tree ? -1 : 1) * (x & -x);};

template <bool prefix_tree, class dtype, class itype, class Opt>
const std::function<itype(itype)> fenwick_tree<prefix_tree, dtype, itype, Opt>::unext
        = [] (const itype& x) {return x - (prefix_tree ? -1 : 1) * (x & -x);};
