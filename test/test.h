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

#define EQUAL(l, r) assert((l) == (r), "Not equal", __FILE__, __LINE__);