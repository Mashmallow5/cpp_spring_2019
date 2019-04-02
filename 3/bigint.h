#pragma once

#include <iostream>
#include <iomanip>
#include "list.h"

class BigInt {
    friend std::ostream &operator<<(std::ostream &os, const BigInt &number);

private:
    const int64_t base = 1000000000;
    LinkedList _string;
    bool _sign;

    void remove_zeroes() {
        while (_string.get_length() > 1 && _string[_string.get_length() - 1] == 0) {
            _string.pop();
        }
        if (_string.get_length() == 1 && _string[0] == 0)
            _sign = true;
    }

public:
    BigInt(std::string str = "") {
        if (str.length() == 0)
            this->_sign = true;
        else {
            if (str[0] == '-') {
                str = str.substr(1);
                this->_sign = false;
            } else
                this->_sign = true;
            this->_string = LinkedList();
            for (long long i = str.length(); i > 0; i -= 9) {
                if (i < 9) {
                    _string.add(atoi(str.substr(0, i).c_str()));
                } else
                    _string.add(atoi(str.substr(i - 9, 9).c_str()));
            }
        }
        remove_zeroes();
    }

    BigInt &operator=(int64_t __int) {
        _string.~LinkedList();
        if (__int < 0) {
            this->_sign = false;
            __int = -__int;
        }
        else this->_sign = true;
        do {
            this->_string.add(__int % base);
            __int /= base;
        } while (__int != 0);
        return *this;
    }

    BigInt(int64_t __int) {
        if (__int < 0) {
            this->_sign = false;
            __int = -__int;
        }
        else this->_sign = true;
        do {
            this->_string.add(__int % base);
            __int /= base;
        } while (__int != 0);
    }

    BigInt(const BigInt &number) {
        _sign = number._sign;
        for (size_t i = 0; i < number._string.get_length(); i++)
            _string.add(number._string[i]);
    }

    BigInt &operator=(const BigInt &number) {
        if (this == &number)
            return *this;
        this->_string.~LinkedList();
        for (size_t i = 0; i < number._string.get_length(); i++)
            _string.add(number._string[i]);
        _sign = number._sign;
        return *this;
    }

    BigInt operator-() const {
        BigInt tmp = BigInt(*this);
        if (!(_string.get_length() && _string[0] == 0))
            tmp._sign = !(this->_sign);
        return tmp;
    }

    BigInt operator+(const BigInt &number) const {
        if (_sign == number._sign) {
            BigInt tmp;
            if (this->_string.get_length() < number._string.get_length())
                tmp = BigInt(number);
            else
                tmp = BigInt(*this);

            for (size_t i = 0; i < number._string.get_length() - 1; i++) {
                tmp._string[i] += number._string[i];
                if (tmp._string[i] >= base) {
                    tmp._string[i] = tmp._string[i] % base;
                    tmp._string[i + 1] += 1;
                }
            }
            size_t i = number._string.get_length() - 1;
            tmp._string[i] += number._string[i];
            while (tmp._string[i] >= base) {
                tmp._string[i] = tmp._string[i] % base;
                i += 1;
                if (i == tmp._string.get_length())
                    tmp._string.add(1);
            }
            return tmp;
        } else {
            if (_sign)
                return (*this - (-number));
            else return (number - (-(*this)));
        }
    }

    BigInt operator-(const BigInt &number) const {
        if (!(number._sign))
            return *this + (-number);
        else if (!(this->_sign))
            return -(-(*this) + number);
        else if (*this < number)
            return -(number - (*this));
        BigInt tmp = BigInt(*this);
        for (size_t i = 0; i < tmp._string.get_length(); i++) {
            tmp._string[i] -= (i < number._string.get_length() ? number._string[i] : 0);
            if (tmp._string[i] < 0) {
                tmp._string[i] += base;
                tmp._string[i + 1] -= 1;
            }
        }
        tmp.remove_zeroes();
        return tmp;
    }

    bool operator==(const BigInt &number) const {
        if (this->_string.get_length() != number._string.get_length())
            return false;
        if (this->_sign != number._sign)
            return false;
        if (this->_string.get_length() == 0)
            return true;
        size_t i;
        for (i = 0; i < this->_string.get_length(); i++)
            if (number._string[i] != this->_string[i])
                return false;
        return true;
    }

    bool operator!=(const BigInt &number) const {
        return !(*this == number);
    }

    bool operator<(const BigInt &number) const {
        if (number._sign != this->_sign)
            return !_sign;
        if (number._string.get_length() < this->_string.get_length())
            return !_sign;
        if (number._string.get_length() > this->_string.get_length())
            return _sign;
        for (long long i = number._string.get_length() - 1; i >= 0; i--)
            if (number._string[i] != this->_string[i])
                if (this->_string[i] > number._string[i])
                    return !_sign;
                else return _sign;
        return false;
    }

    bool operator>(const BigInt &number) const {
        if (*this == number)
            return false;
        return !(*this < number);
    }

    bool operator<=(const BigInt &number) const {
        return !(*this > number);
    }

    bool operator>=(const BigInt &number) const {
        return !(*this < number);
    }

};

std::ostream &operator<<(std::ostream &os, const BigInt &number) {
    if (number._string.get_length() == 0)
        os << 0;
    else {
        if (!(number._sign))
            os << '-';
        os << number._string[number._string.get_length() - 1];
        char old_fill = os.fill('0');
        for (long long i = static_cast<long long>(number._string.get_length()) - 2; i >= 0; i--) {
            os << std::setw(9) << number._string[i];
        }
    }
    return os;
}

