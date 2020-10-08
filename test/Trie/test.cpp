#include <kypluk/test.h>
#include <kypluk/trie.h>


class test_trie final : public test  {
public:
    void check_insert() {
        TrieSet trie;

        trie.insert("test");
        trie.insert("baba");
        trie.insert("kakaha");
        trie.insert("test2");

        IS_TRUE(trie.contains("test"));
        IS_TRUE(trie.contains("baba"));
        IS_TRUE(trie.contains("kakaha"));
        IS_TRUE(trie.contains("test2"));

        IS_FALSE(trie.contains("tes"));
        IS_FALSE(trie.contains("bab"));
        IS_FALSE(trie.contains("kakah"));
        IS_FALSE(trie.contains("test1"));
    }

    void run() override {
        check_insert();
    }
};

int main() {
    test_trie().run();
}