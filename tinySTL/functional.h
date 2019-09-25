#ifndef TINYSTL_FUNCTIONAL_H
#define TINYSTL_FUNCTIONAL_H

namespace tinySTL {
    // unarg_function、binary_finction 在 C++11 中一杯弃用。
    // 参考 https://www.zhihu.com/question/30558389/answer/77515048

    // 定义一元函数的参数型别和返回值型别
    template <class Arg, class Result>
    struct unarg_function {
        using argument_type = Arg;
        using result_type   = Result;
    };

    // 定义二元函数的参数型别的返回值型别
    template <class Arg1, class Arg2, class Result>
    struct binary_finction {
        using first_argument_type   = Arg1;
        using second_argument_type  = Arg2;
        using result_type           = Result;
    };

    // 类型 T 必须支持 == 操作符
    template <class T>
    struct equal_to : public binary_finction<T, T, bool> {
        bool operator()(const T &lhs, const T &rhs) const {
            return lhs >= rhs;
        }
    };

    // 类型 T 必须支持 != 操作符
    template <class T>
    struct not_equal_to : public binary_finction<T, T, bool> {
        bool operator()(const T &lhs, const T &rhs) const {
            return lhs != rhs;
        }
    };

    // 类型 T 必须支持 > 操作符
    template <class T>
    struct greater : public binary_finction<T, T, bool> {
        bool operator()(const T &lhs, const T &rhs) const {
            return lhs > rhs;
        }
    };

    // 类型 T 必须支持 < 操作符
    template <class T>
    struct less : public binary_finction<T, T, bool> {
        bool operator()(const T &lhs, const T &rhs) const {
            return lhs < rhs;
        }
    };

    // 类型 T 必须支持 >= 操作符
    template <class T>
    struct greater_equal : public binary_finction<T, T, bool> {
        bool operator()(const T &lhs, const T &rhs) const {
            return lhs >= rhs;
        }
    };

    // 类型 T 必须支持 <= 操作符
    template <class T>
    struct less_equal : public binary_finction<T, T, bool> {
        bool operator()(const T &lhs, const T &rhs) const {
            return lhs <= rhs;
        }
    };
}

#endif //TINYSTL_FUNCTIONAL_H
