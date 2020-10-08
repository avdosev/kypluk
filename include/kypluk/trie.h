#ifndef KYPLUK_TRIE_H
#define KYPLUK_TRIE_H

#include <memory>
#include <unordered_map>
#include <string_view>

template <typename CharT = char, typename TraitsT = std::char_traits<CharT>>
class TrieSet {
public:
    using string_view_type = std::basic_string_view<CharT, TraitsT>;

private:
    struct node {
        bool has_end = false;
        std::unordered_map<CharT, node> children;
    };

public:
    void insert(string_view_type str) {
        node* ins = &head;

        for (auto ch : str) {
            auto &postfix = ins->children;

            auto it = postfix.find(ch);
            if (it == postfix.end()) {
                it = postfix.insert({ch, node()}).first;
            }

            ins = &it->second;
        }

        ins->has_end = true;
    }

    bool contains(string_view_type str) {
        node* ins = &head;

        for (auto ch : str) {
            auto &postfix = ins->children;
            auto &it = postfix.find(ch);

            if (it == postfix.end()) {
                return false;
            }

            ins = &it->second;
        }

        return ins->has_end;
    }

private:
    node head;
};

#endif //KYPLUK_TRIE_H
