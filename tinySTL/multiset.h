#ifndef TINYSTL_MULTISET_H
#define TINYSTL_MULTISET_H

#include <functional>
#include <initializer_list>
#include <algorithm>
#include <utility>

#include "alloc.h"
#include "utility_move.h"
#include "functional_base.h"
#include "rb_tree.h"
#include "algorithm_base.h"

namespace tinySTL {
    // mltiset 含有 Key 类型对象有序集的容器。不同于 set ，它允许多个关键拥有等价的值。通常其底层实现为红黑树。
    // 接口功能见：https://zh.cppreference.com/w/cpp/container/multiset
    template <class Key, class Compare = tinySTL::less<Key>, class Allocator = tinySTL::allocator<Key>>
    class multiset {
    public:
        using key_type          = Key;
        using value_type        = Key;
        using key_compare       = Compare;
        using value_compare     = Compare;
        using allocator_type    = Allocator;

    private:
        using rb_tree_type = rb_tree<key_type, value_type, tinySTL::identity<value_type>, key_compare, Allocator>;
        rb_tree_type tree_;

    public:
        using size_type                 = typename rb_tree_type::size_type;
        using difference_type           = typename rb_tree_type::difference_type;
        using reference                 = typename rb_tree_type::const_reference;
        using const_reference           = typename rb_tree_type::const_reference;
        using pointer                   = typename rb_tree_type::const_pointer;
        using const_pointer             = typename rb_tree_type::const_pointer;
        using iterator                  = typename rb_tree_type::const_iterator;
        using const_iterator            = typename rb_tree_type::const_iterator;
        using reverse_iterator          = typename rb_tree_type::const_reverse_iterator;
        using const_reverse_iterator    = typename rb_tree_type::const_reverse_iterator;

    public:
        multiset() = default;

        explicit multiset(const Compare& comp) : tree_(comp) {}

        template <class InputIterator>
        multiset(InputIterator first, InputIterator last, const Compare& comp = Compare()) : tree_(comp) {
            tree_.insert_equal(first, last);
        }

        multiset(const multiset& other) : tree_(other.tree_) {}

        multiset(multiset&& other) noexcept : tree_(tinySTL::move(other.tree_)) {}

        multiset(std::initializer_list<value_type> ilist, const Compare& comp = Compare()) : tree_(comp) {
            tree_.insert_equal(ilist.begin(), ilist.end());
        }

        ~multiset() = default;

        multiset& operator=(const multiset& other) {
            tree_ = other.tree_;

            return *this;
        }

        multiset& operator=(multiset&& other) noexcept {
            tree_ = tinySTL::move(other.tree_);

            return *this;
        }

        multiset& operator=(std::initializer_list<value_type> ilist) {
            clear();
            insert(ilist.begin(), ilist.end());

            return *this;
        }

        iterator begin() noexcept {
            return tree_.begin();
        }

        const_iterator begin() const noexcept {
            return tree_.begin();
        }

        const_iterator cbegin() const noexcept {
            return tree_.cbegin();
        }

        iterator end() noexcept {
            return tree_.end();
        }

        const_iterator end() const noexcept {
            return tree_.end();
        }

        const_iterator cend() const noexcept {
            return tree_.cend();
        }

        reverse_iterator rbegin() noexcept {
            return tree_.rbegin();
        }

        const_reverse_iterator rbegin() const noexcept {
            return tree_.rbegin();
        }

        const_reverse_iterator crbegin() const noexcept {
            return tree_.crbegin();
        }

        reverse_iterator rend() noexcept {
            return tree_.rend();
        }

        const_reverse_iterator rend() const noexcept {
            return tree_.rend();
        }

        const_reverse_iterator crend() const noexcept {
            return tree_.crend();
        }

        bool empty() const noexcept {
            return tree_.empty();
        }

        size_type size() const noexcept {
            return tree_.size();
        }

        size_type max_size() const noexcept {
            return tree_.max_size();
        }

        void clear() noexcept {
            tree_.clear();
        }

        iterator insert(const value_type& value) {
            return tree_.insert_equal(value);
        }

        iterator insert(const value_type&& value) {
            return tree_.insert_equal(tinySTL::move(value));
        }

        // 插入 value 到尽可能接近、正好前于 hint 的位置。
        iterator insert(const_iterator hint, const value_type& value) {
            return tree_.insert_equal(hint, value);
        }

        iterator insert(const_iterator hint, const value_type&& value) {
            return tree_.insert_equal(hint, tinySTL::move(value));
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last) {
            tree_.insert_equal(first, last);
        }

        template <class... Args>
        iterator emplace(Args&&... args) {
            return tree_.emplace_equal(tinySTL::forward<Args>(args)...);
        }

        // 插入新元素到尽可能靠近恰在 hint 前的位置。
        // 原位构造元素，即不进行复制或移动操作。
        template <class... Args>
        iterator emplace_hint(const_iterator hint, Args&&... args) {
            return insert(hint, tinySTL::forward<Args>(args)...);
        }

        // 迭代器 pos 必须合法且可解引用。
        // 所以 end() 迭代器（合法，但不可解引用）不能用作 position 所用的值。
        void erase(const_iterator position) {
            tree_.erase(position);
        }

        void erase(const_iterator first, const_iterator last) {
            tree_.erase(first, last);
        }

        size_type erase(const key_type& key) {
            return tree_.erase(key);
        }

        void swap(multiset& other) {
            tree_.swap(other.tree_);
        }

        size_type count(const value_type& key) const {
            return tree_.count(key);
        }

        iterator find(const key_type& key) {
            return tree_.find(key);
        }

        const_iterator find(const key_type& key) const {
            return tree_.find(key);
        }

        tinySTL::pair<iterator, iterator> equal_range(const key_type& key) {
            return tree_.equal_range(key);
        }

        tinySTL::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
            return tree_.equal_range(key);
        }

        iterator lower_bound(const key_type& key) {
            return tree_.lower_bound(key);
        }

        const_iterator lower_bound(const key_type& key) const {
            return tree_.lower_bound(key);
        }

        iterator upper_bound(const key_type& value) {
            return tree_.upper_bound(value);
        }

        const_iterator upper_bound(const key_type& value) const {
            return tree_.upper_bound(value);
        }

        key_compare key_comp() const {
            return tree_.key_comp();
        }

        value_compare value_comp() const {
            return tree_.key_comp();
        }
    }; // class set

    template <class Key, class Compare, class Allocator>
    bool operator==(const multiset<Key, Compare, Allocator>& lhs, const multiset<Key, Compare, Allocator>& rhs) {
        return lhs.size() == rhs.size() && tinySTL::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
    }

    template <class Key, class Compare, class Allocator>
    bool operator!=(const multiset<Key, Compare, Allocator>& lhs, const multiset<Key, Compare, Allocator>& rhs) {
        return !(lhs == rhs);
    }

    template <class Key, class Compare, class Allocator>
    bool operator<(const multiset<Key, Compare, Allocator>& lhs, const multiset<Key, Compare, Allocator>& rhs) {
        return tinySTL::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
    }

    template <class Key, class Compare, class Allocator>
    bool operator<=(const multiset<Key, Compare, Allocator>& lhs, const multiset<Key, Compare, Allocator>& rhs) {
        return !(rhs < lhs);
    }

    template <class Key, class Compare, class Allocator>
    bool operator>(const multiset<Key, Compare, Allocator>& lhs, const multiset<Key, Compare, Allocator>& rhs) {
        return rhs < lhs;
    }

    template <class Key, class Compare, class Allocator>
    bool operator>=(const multiset<Key, Compare, Allocator>& lhs, const multiset<Key, Compare, Allocator>& rhs) {
        return !(rhs > lhs);
    }

    template <class Key, class Compare, class Allocator>
    void swap(const multiset<Key, Compare, Allocator>& lhs, const multiset<Key, Compare, Allocator>& rhs) {
        lhs.swap(rhs);
    }

} // namespace tinySTL


#endif //TINYSTL_MULTISET_H
