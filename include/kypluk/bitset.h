#pragma once

#include "typedef.h"

namespace kypluk {

class Bits {
    private:
        size_t byte;
        static const size_t _size = sizeof(size_t) * 8;

        class Bit {
            private:
                int index;
                Bits * parent;
            public:
                Bit(int i, Bits * p) {
                    index = i;
                    parent = p;
                }

                Bit& operator = (bool value) {
                    parent->set(index, value);
                    return *this;
                }

                Bit& operator = (const Bit& copy) {
                    parent->set(index, copy);
                    return *this;
                }

                operator bool () const {
                    return parent->at(index);
                }

        };
    public:
        Bits (size_t bits) {
            byte = bits;
        }


        bool at (size_t i) const {
            if (i > _size) throw 0;
            int index = 1 << i;
            return (byte & index) != 0;
        }


        void flip(size_t i) {
            if (i >= _size) throw 0;

            byte ^= 1 << i;
        }


        void set(size_t i, bool value) {
            if (i >= _size) throw 0;
            int index = 1 << i;
            int val = value ? (~0) : 0;
            byte = (index & val) | (byte & ~index);
        }

        void flip() {
            byte = ~byte ;
        }

        static size_t size() {
            return _size;
        }

        Bit operator [] (int index) {
            return Bit(index, this);
        }
};

}
