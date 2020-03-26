#pragma once

#include <stdexcept>

#include "define.h"
#include "vector.h"

#include "utility.h"

namespace kypluk {

    class BigInt {
        private:
            using base_t = uint8_t;
            using container_t = Vector<base_t>;

            static constexpr base_t base = 10;
            // true - is_negative
            // false - is_not_negative
            bool _is_negative = false;
            container_t arr;

            void remove_leading_zeros() {
                while (!arr.empty() and arr.back() == 0)
                    arr.pop_back();
                if (arr.empty()) {
                    arr.push_back(0);
                    _is_negative = false;
                }
            }

            friend void swap(BigInt& lf, BigInt& rh);

        public:
            class division_by_zero : public std::runtime_error{
            public:
                explicit division_by_zero(const char* string) : runtime_error(string) {}
            };

            BigInt() {
                _is_negative = false;
                arr.push_back(0);
            }

            BigInt(llint other) {
                _is_negative = other < 0;
                if (_is_negative) other = -other;
                arr.push_back(other%10);
                while ((other/=10) != 0) {
                    arr.push_back(other%10);
                }
            }

            BigInt(const BigInt & other) = default;
            BigInt(BigInt&& other) noexcept {
                swap(*this, other);
            };


            ~BigInt() {
                arr.clear();
            }

            BigInt& add (const BigInt& other) {
                if (this->negative()) {
                    if (other.negative()) return this->neg().add(-other).neg();
                    else return *this = other - this->neg();
                }
                else if (other.negative()) return this->sub(-other);

                if (this->length() < other.length()) {
                    size_t bufSize = other.length() - this->length();
                    //arr.reserve(arr.size()+bufSize+1);
                    for (size_t i = 0; i < bufSize; i++)
                        arr.push_back(0);
                }

                base_t carry = 0;
                auto j = other.arr.begin();
                for (auto& item : this->arr) {
                    item = item + carry + (j == other.arr.end() ? 0 : *j );

                    carry = static_cast<base_t>(item >= base);
                    if (carry) {
                        item -= base; // i % base
                    }

                    if (j != other.arr.end()) ++j;
                }

                if (carry)
                    arr.push_back(1);

                return *this;
            }

            BigInt& sub (const BigInt& other) {

                if (other.negative()) return this->add(-other);
                else if (this->negative()) return this->neg().add(other).neg();
                else if (*this < other) return *this = -(other - *this);

                bool carry = false;

                auto i = this->arr.begin();
                for (auto j = other.arr.begin(); j != other.arr.end() || carry != 0; ++i) {
                    *i -= carry + (j != other.arr.end() ? *j : 0);
                    carry = *i > base;
                    if (carry) *i += base;
                    if (j != other.arr.end()) ++j;
                }

                this->remove_leading_zeros();

                return *this;
            }

            BigInt& mult10(size_t other = 1) {
                if (!this->zero()) {
                    container_t temp(other, 0);
                    arr.resize(arr.size()+other);
                    for (size_t i = arr.size() - other; i > 0; i--) {
                        arr[i-1+other] = arr[i-1];
                    }
                    for (size_t i = 0; i < other; i++) {
                        arr[i] = 0;
                    }
                }
                return *this;
            }


            BigInt& mult0to9 (base_t other) {
                if (other == 0) (*this) = 0;
                else {
                    base_t carry = 0;
                    for (base_t& item : this->arr) {
                        item = item * other + carry;
                        carry = item / base;
                        item %= base;
                    }
                    if (carry) this->arr.push_back(carry);
                }
                return *this;
            }

            BigInt& mult (BigInt other) {
                BigInt buffer = std::move(*this);
                bool thisNegative = this->_is_negative;
                buffer._is_negative = false;
                (*this) = 0;

                Vector<BigInt> mult_temp;
                for (base_t i = 0; i < base; i++) {
                    mult_temp.emplace_back(BigInt(buffer).mult0to9(i));
                }

                std::array<size_t, base> first_size{};
                for (base_t i = 0; i < base; i++) {
                    first_size[i] = mult_temp[i].length();
                }

                size_t j = 0;
                for (auto i = other.arr.begin(); i != other.arr.end(); ++i, ++j)
                {
                    (*this) += mult_temp[*i].mult10(j-(mult_temp[*i].arr.size()-first_size[*i]));
                }

                //boolean xor
                this->_is_negative = (!other._is_negative && thisNegative) || (other._is_negative && !thisNegative);

                return *this;
            }


            Pair<BigInt, BigInt> divmod(const BigInt &b1) const {
                if (b1 == 0) throw division_by_zero("division by zero");

                base_t norm = base / (b1.arr.back() + 1);
                BigInt a = this->abs() * norm;
                BigInt b = b1.abs() * norm;
                BigInt q, r;
                //q.arr.resize(arr.arr.size());
                q.arr = container_t(a.arr.size());

                for (auto i = --a.arr.end(), j = --q.arr.end(); i < a.arr.end(); --i, --j) {
                    r *= base;
                    r += *i;
                    base_t s1 = r.arr.size() <= b.arr.size() ? 0 : r.arr.at(b.arr.size());
                    base_t s2 = r.arr.size() <= b.arr.size() - 1 ? 0 : r.arr.at(b.arr.size() - 1);
                    int d = ( base * s1 + s2) / b.arr.back();
                    r -= b * d;
                    while (r < 0) {
                        r += b;
                        --d;
                    }
                    *j = d;
                }

                q._is_negative = this->_is_negative || b1._is_negative;
                r._is_negative = this->_is_negative;

                q.remove_leading_zeros();
                r.remove_leading_zeros();

                return Pair<BigInt, BigInt>({q, r.divbase(norm)});
            }

            BigInt divbase(int8_t v) const {
                BigInt copy = *this;
                if (v < 0) {
                    copy._is_negative = true;
                    v = -v;
                }
                base_t rem = 0;
                for (auto i = copy.arr.end()-1; i < copy.arr.end(); --i) {
                    base_t cur = *i + rem * base;
                    *i = cur / v;
                    rem = cur % v;
                }
                copy.remove_leading_zeros();
                return copy;
            }

            //--------
            //dispensable methods
            //--------

            int sign() const {
                if (this->negative())
                    return -1;
                return (*this) == 0 ? 0 : 1;
            }

            BigInt abs() const {
                BigInt other(*this);
                other._is_negative = false;
                return other;
            }

            bool odd() const {
                return this->arr.front() & 1;
            }

            bool even() const {
                return !this->odd();
            }

            bool negative() const {
                return this->_is_negative;
            }

            BigInt& neg() {
                this->_is_negative = !(this->_is_negative);
                return *this;
            }

            bool zero() const {
                return arr.size() == 1 && arr.back() == 0;
            }

            size_t length() const {
                return arr.size();
            }

            //---------
            //static function
            //---------

            friend std::string to_string(const BigInt& number);

            static BigInt from_string(const char * value) {
                BigInt res;
                bool is_ngt = false;
                if (*value) {
                    if (*value == '-') {
                        is_ngt = true;
                        value++;
                    }
                    res = *value - '0';
                    value++;
                }
                while (*value) {
                    res.mult10(1).add(*value - '0');
                    value++;
                }
                res._is_negative = is_ngt;
                return res;
            }

            static int compare(const BigInt& raz, const BigInt& dva) {
                if (raz._is_negative != dva._is_negative)
                    return dva._is_negative - raz._is_negative;

                if (raz.length() != dva.length())
                    return raz.length() > dva.length() ? 1 : -1;

                for (auto i = --raz.arr.end(), j = --dva.arr.end(); i < raz.arr.end() and j < dva.arr.end(); --i, --j)
                {
                    if (*i != *j)
                        return (*i - *j) * (raz._is_negative ? -1 : 1);
                }

                return 0;
            }

            //---------
            //operators
            //---------

            BigInt& operator ++ () {
                if (++(*arr.begin()) > 9) {
                    *arr.begin() -= 10;
                    add(BigInt(10));
                }

                return *this;
            }

            BigInt& operator = (const BigInt& other) {
                arr = other.arr;
                _is_negative = other._is_negative;
                return *this;
            }

            BigInt& operator = (BigInt&& other) noexcept {
                swap(*this, other);
                return *this;
            }

            BigInt& operator += (const BigInt &other) {
                return add(other);
            }

            BigInt& operator -= (const BigInt &other) {
                return sub(other);
            }

            BigInt& operator *= (const BigInt& other) {
                return mult(other);
            }

            BigInt& operator /= (const BigInt& other) {
                return *this = this->divmod(other).first;
            }

            friend const BigInt operator + (const BigInt& raz, const BigInt& dvas) {
                BigInt other = raz;
                return other.add(dvas);
            }

            friend const BigInt operator - (const BigInt& raz, const BigInt& dvas) {
                BigInt other = raz;
                return other.sub(dvas);
            }

            friend const BigInt operator * (const BigInt& raz, const BigInt& dvas) {
                BigInt other = raz;
                return other.mult(dvas);
            }

            friend const BigInt operator / (const BigInt& raz, const BigInt& dvas) {
                return raz.divmod(dvas).first;
            }

            friend const BigInt operator % (const BigInt& raz, const BigInt& dvas) {
                return raz.divmod(dvas).second;
            }

            BigInt operator +() const {
                return BigInt(*this);
            }

            BigInt operator -() const {
                BigInt temp(*this);
                temp.neg();
                return temp;
            }

            bool operator != (const BigInt& other) const{
                return compare(*this, other) != 0;
            }

            bool operator >= (const BigInt& other) const {
                return compare(*this, other) >= 0;
            }

            bool operator <= (const BigInt& other) const {
                return compare(*this, other) <= 0;
            }

            bool operator > (const BigInt& other) const {
                return compare(*this, other) > 0;
            }

            bool operator < (const BigInt& other) const {
                return compare(*this, other) < 0;
            }

            bool operator == (const BigInt& other) const{
                return compare(*this, other) == 0;
            }
    };


    std::string to_string(const BigInt& number) {
        std::string buf;
        buf.resize(number.length()+number._is_negative);
        if (number._is_negative) buf.front() = '-';
        auto it = buf.rbegin();
        for (auto item : number.arr) {
            *it = item+'0';
            ++it;
        }
        return buf;
    }

    void swap(BigInt& lf, BigInt& rh) {
        swap(lf._is_negative, rh._is_negative);
        swap(lf.arr, rh.arr);
    }

/*
fast factor
http://www.luschny.de/math/factorial/binarysplitfact.html
*/ 

} // end namespace kypluk
