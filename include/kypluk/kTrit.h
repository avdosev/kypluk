#pragma once

#include "utility.h"

namespace kypluk {

class Trit {
    public:
        enum class Logical {
            True  = 0b10,
            False = 0b01,
            None  = 0b00
        };
    private:
        uint8_t value = uint8_t(Logical::None);
    public:
        enum class Logical {
            True = 0b11,
            False = 0b10,
            None = 0
        };

        Trit(Logical val) : value(uint8_t(val)) {

        }

        Trit(bool val) : value(uint8_t(val ? Logical::True : Logical::False)) {

        }

        bool to_bool() const {
            return this->value >> 1;
        }

        explicit operator bool() const {
            return this->to_bool();
        }

};

}