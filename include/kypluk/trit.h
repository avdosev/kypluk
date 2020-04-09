#pragma once

#include "typedef.h"

namespace kypluk {

    class trit {
        public:
            using value_t = uint8_t;
            enum class logical {
                True  = 0b10,
                False = 0b01,
                None  = 0b00
            };


            constexpr trit() noexcept = default;
            constexpr trit(const trit&) noexcept = default;
            constexpr trit(logical val) noexcept : value(static_cast<value_t>(val))  {}
            constexpr trit(bool val) noexcept : trit(from_bool(val)) {}
            ~trit() = default;

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
                return trit((orig.value ^ 3u) % 3u);
            }

            friend constexpr trit operator && (trit lft, trit rgh) {
                value_t A = lft.value, B = rgh.value;
                return trit(((A | B) & 1u) | (A & B));
            }

            friend constexpr trit operator || (trit lft, trit rgh) {
                value_t A = lft.value, B = rgh.value;
                return trit(((A | B) & 2u) | (A & B));
            }

            static const trit none;
        private:
            constexpr trit(uint val) : value(val) {}

            value_t value = value_t(logical::None);
    };

    constexpr trit operator && (bool left, trit right) {
        return right && trit::from_bool(left);
    }

    constexpr trit operator && (trit left, bool right) {
        return left && trit::from_bool(right);
    }

    constexpr trit operator || (bool left, trit right) {
        return right || trit::from_bool(left);
    }

    constexpr trit operator || (trit left, bool right) {
        return left || trit::from_bool(right);
    }

    namespace trit_const {
        constexpr static const trit none = trit::logical::None;
        constexpr static const trit _true = trit::logical::True;
        constexpr static const trit _false = trit::logical::False;
    }

}