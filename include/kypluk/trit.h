#pragma once

#include "typedef.h"

namespace kypluk {

    class trit {
        public:
            using value_t = uint8_t;
            enum class logical : value_t {
                True  = 0b10,
                False = 0b01,
                None  = 0b00
            };

            constexpr trit() = default;
            constexpr trit(const trit&) = default;
            constexpr trit(logical val) : value(value_t(val)) {}
            constexpr trit(bool val) : trit(from_bool(val)) {}


            constexpr bool is(logical logic) const {
                return value == value_t(logic);
            }

            constexpr static trit from_bool(bool val) {
                return trit(val ? logical::True : logical::False);
            }

            constexpr bool to_bool() const {
                return static_cast<bool>(value >> 1u);
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

            friend constexpr trit operator ! (trit orig) {
                return trit((orig.value ^ 3u) / 3u);
            }

            friend constexpr trit operator && (trit lft, trit rgh) {
                value_t A = lft.value, B = rgh.value;
                return trit(((A | B) & 1u) | (A&B));
            }

            friend constexpr trit operator || (trit lft, trit rgh) {
                value_t A = lft.value, B = rgh.value;
                return trit(((A | B) & 2u) | (A & B));
            }

        private:
            constexpr trit(uint val) : value(val) {}

            value_t value = value_t(logical::None);
    };

}