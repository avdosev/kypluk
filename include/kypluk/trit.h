#pragma once

#include "typedef.h"

namespace kypluk {

    class trit {
        public:
            enum class logical : uint8_t {
                True  = 0b10,
                False = 0b01,
                None  = 0b00
            };

            constexpr trit() = default;
            constexpr trit(const trit&) = default;
            constexpr trit(logical val) : value(uint8_t(val)) {}
            constexpr trit(bool val) : trit(from_bool(val)) {}


            constexpr bool is(logical logic) const {
                return value == uint8_t(logic);
            }

            constexpr static trit from_bool(bool val) {
                return trit(val ? logical::True : logical::False);
            }

            constexpr bool to_bool() const {
                return static_cast<bool>(value >> 1);
            }

            constexpr logical to_logical() const {
                return logical(value);
            }

            constexpr operator bool() const {
                return this->to_bool();
            }

            constexpr bool operator == (logical logic) const {
                return this->is(logic);
            }

            constexpr bool operator == (const trit& val) const {
                return this->value == val.value;
            }

            constexpr trit& operator = (const trit& val) = default;

        private:
            uint8_t value = uint8_t(logical::None);
    };

}