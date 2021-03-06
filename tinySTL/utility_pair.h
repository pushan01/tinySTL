#ifndef TINYSTL_UTILITY_PAIR_H
#define TINYSTL_UTILITY_PAIR_H

#include <algorithm>
#include <utility>
#include <tuple>

#include "type_traits.h"
#include "utility_move.h"
#include "algorithm_base.h"

namespace tinySTL {
    // 接口功能见：https://zh.cppreference.com/w/cpp/utility/pair
    template <class T1, class T2>
    struct pair {
        using first_type    = T1;
        using second_type   = T2;

        T1 first;
        T2 second;

        pair() : first(), second() {}

        pair(const T1& x, const T2& y) : first(x), second(y) {}

        template <class U1, class U2>
        pair(U1&& x, U2&& y) : first(tinySTL::forward<U1>(x)), second(tinySTL::forward<U2>(y)) {}

        template <class U1, class U2>
        explicit pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

        // 万能引用结合完美转发。
        template <class U1, class U2>
        explicit pair(pair<U1, U2>&& p) : first(tinySTL::forward<U1>(p.first)), second(tinySTL::forward<U2>(p.second)) {}

        template <class U1, class U2>
        explicit pair(const pair& p) : first(p.first), second(p.second) {}

        template <class U1, class U2>
        explicit pair(pair&& p) : first(tinySTL::move(p.first)), second(tinySTL::move(p.second)) {}

        pair& operator=(const pair& other) {
            first = other.first;
            second = other.second;

            return *this;
        }

        template <class U1, class U2>
        pair& operator=(const pair<U1, U2>& other) {
            first = other.first;
            second = other.second;

            return *this;
        }

        pair& operator=(pair&& other) noexcept {
            first = tinySTL::move(other.first);
            second = tinySTL::move(other.second);

            return *this;
        }

        template <class U1, class U2>
        pair& operator=(pair<U1, U2>&& other) { // 万能引用（引用折叠）
            first = tinySTL::forward<U1>(other.first);
            second = tinySTL::forward<T2>(other.second);

            return *this;
        }

        void swap(pair& other) noexcept {
            using tinySTL::swap;
            // 如果存在对应类型版本的 swap() 函数，
            // 则调用该特定版本。
            // 因为如果实参类的命名空间中存在该实参类型版本的 swap() 函数，
            // 则它被查找的优先级比 using 声明的优先级搞。
            // 见《C++ Primer》第五版 P706
            swap(first, other.first);
            swap(second, other.second);
        }
    }; // struct pair

    // 类型 T 退化（隐式转换，移除 cv 限定符：const 和 volatile）：
    // - 左值 -> 右值
    // - 数组 -> 指针
    // - 函数 -> 指针
    template<class T1, class T2>
    pair<typename std::decay<T1>::type, typename std::decay<T2>::type> make_pair(T1&& first, T2&& second) {
        return pair<typename std::decay<T1>::type, typename std::decay<T2>::type>
               (tinySTL::forward<T1>(first), tinySTL::forward<T2>(second));
    }

    template <typename T1, typename T2>
    bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <typename T1, typename T2>
    bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return !(lhs == rhs);
    }

    // 先比较首元素，然后仅若它们相等，再比较第二元素。

    template <typename T1, typename T2>
    bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        if (lhs.first < rhs.first) {
            return true;
        } else if (rhs.first > lhs.first) {
            return true;
        } else { // lhs.first == rhs.first
            return lhs.second < rhs.second;
        }
    }

    template <typename T1, typename T2>
    bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return !(rhs < lhs);
    }

    template <typename T1, typename T2>
    bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return rhs < lhs;
    }

    template <typename T1, typename T2>
    bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return !(lhs < rhs);
    }

    template<class T1, class T2>
    void swap(pair<T1, T2>& x, pair<T1, T2>& y) {
        x.swap(y);
    }

    namespace detail {
        template <size_t I>
        struct get_pair;

        template <>
        struct get_pair<0> {
            template <class T1, class T2>
            T1& get(tinySTL::pair<T1, T2>& p) {
                return p.first;
            }

            template <class T1, class T2>
            const T1& get(const tinySTL::pair<T1, T2>& p) {
                return p.first;
            }

            template <class T1, class T2>
            T1&& get(tinySTL::pair<T1, T2>&& p) {
                return tinySTL::forward<T1>(p.first);
            }

            template <class T1, class T2>
            const T1&& get(const tinySTL::pair<T1, T2>&& p) {
                return tinySTL::forward<const T1>(p.first);
            }
        };

        template <>
        struct get_pair<1> {
            template <class T1, class T2>
            T1& get(tinySTL::pair<T1, T2>& p) {
                return p.second;
            }

            template <class T1, class T2>
            const T1& get(const tinySTL::pair<T1, T2>& p) {
                return p.second;
            }

            template <class T1, class T2>
            T1&& get(tinySTL::pair<T1, T2>&& p) {
                return tinySTL::forward<T1>(p.second);
            }

            template <class T1, class T2>
            const T1&& get(const tinySTL::pair<T1, T2>&& p) {
                return tinySTL::forward<const T1>(p.second);
            }
        };
    }

    // I 为 0 或 1。
    // 详细用法见：https://zh.cppreference.com/w/cpp/utility/pair/get
    template <size_t I, class T1, class T2>
    typename std::tuple_element<I, tinySTL::pair<T1, T2>>::type& get(tinySTL::pair<T1, T2>& p) noexcept {
        return detail::get_pair<I>::get(p);
    }

    template <size_t I, class T1, class T2>
    const typename std::tuple_element<I, tinySTL::pair<T1, T2>>::type& get(const tinySTL::pair<T1, T2>& p) noexcept {
        return detail::get_pair<I>::get(p);
    }

    template <size_t I, class T1, class T2>
    typename std::tuple_element<I, tinySTL::pair<T1, T2>>::type&& get(tinySTL::pair<T1, T2>&& p) noexcept {
        return detail::get_pair<I>::get(tinySTL::move(p));
    }
} // namespace tinySTl

#endif //TINYSTL_UTILITY_PAIR_H
