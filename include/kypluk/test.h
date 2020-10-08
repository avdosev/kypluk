#pragma once

#include <cstdio>

class test {
    public:
        virtual void run() = 0;

        virtual void assert(bool ok, const char *message, const char *file, unsigned line) {
            if (!ok) printf("File:  %s, Line %d\n%s\n\n",
                    file, line, message);
        }

};

#define IS_TRUE(e) assert((e), "Not true", __FILE__, __LINE__)
#define IS_FALSE(e) assert(!(e), "Not false", __FILE__, __LINE__)
#define EQUAL(l, r) assert((l) == (r), "Not equal", __FILE__, __LINE__)
#define NOT_EQUAL(l, r) assert((l) != (r), "Equal", __FILE__, __LINE__)