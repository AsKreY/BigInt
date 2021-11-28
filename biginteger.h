#pragma once
#ifndef BIGINTEGER_LIBRARY_H
#define BIGINTEGER_LIBRARY_H

#include <iostream>
#include <vector>
#include <string>

const int base = 1000000000;

class BigInteger {
 private:
  std::vector<long long> num;

  bool is_negative = false;

 public:
  BigInteger() = default;

  ~BigInteger() = default;

  BigInteger(const BigInteger &a) = default;

  BigInteger &operator=(const BigInteger &a) = default;

  BigInteger(int num_);

  explicit BigInteger(const std::string &num_);

  void zero_fix() {
    size_t i = num.size() - 1;
    while (true) {
      if (!num[i] && i) {
        num.pop_back();
      } else {
        break;
      }
      --i;
    }
    if (num.size() == 1 && !num[0]) is_negative = false;
  }

  bool get_sign() const {
    return is_negative;
  }

  BigInteger &operator+=(const BigInteger &arg);

  BigInteger &operator-=(const BigInteger &arg);

  BigInteger &operator*=(const BigInteger &arg);

  BigInteger &operator/=(const BigInteger &arg);

  BigInteger &operator%=(const BigInteger &arg);

  BigInteger operator-();

  BigInteger &operator++();

  BigInteger operator++(int);

  friend std::ostream &operator<<(std::ostream &os, const BigInteger &a);

  friend std::istream &operator>>(std::istream &os, BigInteger &a);

  std::string toString() const;

  explicit operator bool() const;

  friend bool operator<(const BigInteger &a, const BigInteger &b);
};

BigInteger::BigInteger(const std::string &num_) {
  int end = 0;
  if (num_[0] == '-') {
    is_negative = true;
    end = 1;
  }
  for (char i: num_) {
    if (i != '0') {
      break;
    }
    ++end;
  }
  for (long long i = num_.length(); i > end; i -= 9) {
    if (i < 9 + end) {
      num.push_back(std::stoi(num_.substr(end, (is_negative) ? i - 1 : i)));
    } else {
      num.push_back(std::stoi(num_.substr(i - 9, 9)));
    }
  }
  num.push_back(0);
  zero_fix();
}

BigInteger::BigInteger(int num_) : is_negative(num_ < 0) {
  if (is_negative) num_ *= -1;
  do {
    num.push_back(num_ % base);
    num_ /= base;
  } while (num_);
}

BigInteger::operator bool() const {
  return (num.size() > 1 || num[0] != 0);
}

std::string BigInteger::toString() const {
  std::string ans;
  std::string cur_str;
  if (is_negative) {
    ans += '-';
  }
  size_t i = num.size() - 1;
  while (true) {
    cur_str = std::to_string(num[i]);
    if (i != num.size() - 1) {
      ans += std::string(9 - cur_str.length(), '0');
    }
    ans += cur_str;
    if (!i) {
      break;
    }
    --i;
  }
  return ans;
}

std::ostream &operator<<(std::ostream &os, const BigInteger &a) {
  std::string cur_str;
  if (a.is_negative) {
    os << '-';
  }
  size_t i = a.num.size() - 1;
  while (true) {
    cur_str = std::to_string(a.num[i]);
    if (i != a.num.size() - 1) {
      os << std::string(9 - cur_str.length(), '0');
    }
    os << cur_str;
    if (!i) {
      break;
    }
    --i;
  }
  return os;
}

std::istream &operator>>(std::istream &os, BigInteger &a) {
  std::string b;
  os >> b;
  a = BigInteger(b);
  a.zero_fix();
  return os;
}

bool operator<(const BigInteger &a, const BigInteger &b) {
  if (!a.is_negative && b.is_negative) {
    return false;
  }
  if (!b.is_negative && a.is_negative) {
    return true;
  }
  if (((a.num.size() < b.num.size()) && (!a.is_negative)) || ((a.num.size() > b.num.size()) && (a.is_negative))) {
    return true;
  }
  if (((a.num.size() < b.num.size()) && (a.is_negative)) || ((a.num.size() > b.num.size()) && (!a.is_negative))) {
    return false;
  }
  size_t i = a.num.size() - 1;
  while (true) {
    if (((a.num[i] > b.num[i]) && (!a.is_negative)) || ((a.num[i] < b.num[i]) && (a.is_negative))) {
      return false;
    }
    if (((a.num[i] < b.num[i]) && (!a.is_negative)) || ((a.num[i] > b.num[i]) && (a.is_negative))) {
      return true;
    }
    if (!i) {
      break;
    }
    --i;
  }
  return false;
}

bool operator>(const BigInteger &a, const BigInteger &b) {
  return b < a;
}

bool operator==(const BigInteger &a, const BigInteger &b) {
  return !(b < a || a < b);
}

bool operator!=(const BigInteger &a, const BigInteger &b) {
  return !(a == b);
}

bool operator<=(const BigInteger &a, const BigInteger &b) {
  return !(a > b);
}

bool operator>=(const BigInteger &a, const BigInteger &b) {
  return !(a < b);
}

BigInteger BigInteger::operator-() {
  BigInteger copy = *this;
  copy.is_negative = !copy.is_negative;
  copy.zero_fix();
  return copy;
}

BigInteger &BigInteger::operator+=(const BigInteger &arg) {
  zero_fix();
  size_t end = std::max(num.size(), arg.num.size());
  int carry = 0;
  if (is_negative == arg.is_negative) {
    if (num.size() < end) {
      num.resize(end, 0);
    }
    for (size_t i = 0; i < end; ++i) {
      if (i < arg.num.size()) {
        num[i] += arg.num[i];
      }
      num[i] += carry;
      carry = static_cast<int>(num[i]) / base;
      num[i] %= base;
    }
    if (!carry) {
      num.push_back(carry);
    }
    zero_fix();
    return *this;
  }
  bool is_negative_this = is_negative;
  bool is_first_more_abs;
  is_negative = arg.is_negative;
  if ((is_negative && *this < arg) || (!is_negative && *this >= arg)) {
    is_first_more_abs = true;
  } else {
    is_first_more_abs = false;
  }
  if (num.size() < end) {
    num.resize(end, 0);
  }
  for (size_t i = 0; i < end; ++i) {
    if (i < arg.num.size()) {
      num[i] = is_first_more_abs ? num[i] - arg.num[i] : arg.num[i] - num[i];
    }
    num[i] -= carry;
    carry = 0;
    if (num[i] < 0) {
      num[i] += base;
      ++carry;
    }
  }
  is_negative = is_first_more_abs == is_negative_this;
  zero_fix();
  return *this;
}

BigInteger &BigInteger::operator-=(const BigInteger &arg) {
  zero_fix();
  is_negative = !is_negative;
  *this += arg;
  *this = -*this;
  zero_fix();
  return *this;
}

BigInteger &BigInteger::operator*=(const BigInteger &arg) {
  zero_fix();
  size_t i = num.size() - 1;
  num.resize(num.size() + arg.num.size());
  while (true) {
    size_t j = arg.num.size() - 1;
    while (true) {
      if (i + j == i) {
        num[i] *= arg.num[j];
      } else {
        num[i + j] += num[i] * arg.num[j];
      }
      if (num[i + j] >= base) {
        if (i + j + 1 >= num.size()) {
          num.push_back(0);
        }
        num[i + j + 1] += num[i + j] / base;
        num[i + j] %= base;
        if (num[i + j + 1] >= base) {
          if (i + j + 2 >= num.size()) {
            num.push_back(0);
          }
          num[i + j + 2] += num[i + j + 1] / base;
          num[i + j + 1] %= base;
        }
      }
      if (!j) {
        break;
      }
      --j;
    }
    if (i == 0) {
      break;
    }
    --i;
  }
  long long carry = 0;
  for (long long &j: num) {
    j = j + carry;
    carry = j / base;
    j %= base;
  }
  if (carry) {
    num.push_back(carry);
  }
  is_negative = is_negative != arg.is_negative;
  zero_fix();
  return *this;
}

BigInteger operator*(const BigInteger &a, const BigInteger &b) {
  BigInteger result = a;
  result *= b;
  return result;
}
BigInteger operator/(const BigInteger &a, const BigInteger &b) {
  BigInteger result = a;
  result /= b;
  return result;
}
BigInteger operator-(const BigInteger &a, const BigInteger &b) {
  BigInteger result = a;
  result -= b;
  return result;
}

BigInteger &BigInteger::operator/=(const BigInteger &arg) {
  zero_fix();
  bool is_negative_end = is_negative != arg.is_negative;
  is_negative = false;
  BigInteger result;
  BigInteger current;
  BigInteger second = arg;
  result.num.resize(num.size());
  second.is_negative = false;
  size_t i = num.size() - 1;
  while (true) {
    int l = 0;
    int r = base;
    int mid;
    while (l + 1 < r) {
      mid = (l + r) >> 1;
      result.num[i] = mid;
      current = result * second;
      if (current > *this) {
        r = mid;
      } else {
        l = mid;
      }
      result.num[i] = l;
    }
    if (!i) {
      break;
    }
    --i;
  }
  *this = result;
  is_negative = is_negative_end;
  zero_fix();
  return *this;
}

BigInteger &BigInteger::operator%=(const BigInteger &arg) {
  zero_fix();
  *this = *this - (*this / arg) * arg;
  zero_fix();
  return *this;
}

BigInteger &BigInteger::operator++() {
  *this += 1;
  zero_fix();
  return *this;
}

BigInteger BigInteger::operator++(int) {
  zero_fix();
  BigInteger copy = *this;
  ++*this;
  zero_fix();
  return copy;
}

BigInteger operator+(const BigInteger &a, const BigInteger &b) {
  BigInteger result = a;
  result += b;
  return result;
}
BigInteger operator%(const BigInteger &a, const BigInteger &b) {
  BigInteger result = a;
  result %= b;
  return result;
}

BigInteger gcd(const BigInteger &a, const BigInteger &b) {
  if (!b) return a;
  return gcd(b, a % b);
}

BigInteger lcm(const BigInteger &a, const BigInteger &b) {
  return a / gcd(a, b) * b;
}

BigInteger ten_degree(size_t degree) {
  BigInteger a = 1;
  for (; degree > 8; degree -= 9) {
    a *= base;
  }
  for (; degree > 0; --degree) {
    a *= 10;
  }
  return a;
}
class Rational {
 private:

  BigInteger numerator;
  BigInteger denominator = 1;
  bool is_negative = false;

 public:
  Rational() = default;
  ~Rational() = default;
  Rational(const BigInteger &a) : numerator(a) {
    sign_fix();
  }
  Rational(const int a) : numerator(a) {
    sign_fix();
  }
  void to_irreducible();
  void sign_fix();
  Rational &operator+=(const Rational &arg);
  Rational &operator-=(const Rational &arg);
  Rational &operator*=(const Rational &arg);
  Rational &operator/=(const Rational &arg);
  Rational &operator-() {
    is_negative = !is_negative;
    return *this;
  }
  BigInteger get_numerator() const {
    return numerator;
  }
  BigInteger get_denominator() const {
    return denominator;
  }
  bool get_sign() const {
    return is_negative;
  }
  std::string toString() const;
  std::string asDecimal(size_t precision) const;
  explicit operator double() const;
};

void Rational::sign_fix() {
  bool negative = false;
  if (numerator < 0) {
    negative = true;
    numerator = -numerator;
  }
  if (denominator < 0) {
    negative = !negative;
    denominator = -denominator;
  }
  is_negative = is_negative != negative;
}

void Rational::to_irreducible() {
  sign_fix();
  if (!numerator) {
    denominator = 1;
    is_negative = false;
    return;
  }
  BigInteger gcd_ = gcd(numerator, denominator);
  numerator /= gcd_;
  denominator /= gcd_;
}

Rational &Rational::operator+=(const Rational &arg) {
  BigInteger lcm_ = lcm(denominator, arg.denominator);
  numerator = ((is_negative) ? -1 : 1) * numerator * (lcm_ / denominator)
      + ((arg.is_negative) ? -1 : 1) * arg.numerator * (lcm_ / arg.denominator);
  denominator = lcm_;
  is_negative = numerator.get_sign();
  if (numerator < 0) numerator = -numerator;
  to_irreducible();
  return *this;
}

Rational &Rational::operator-=(const Rational &arg) {
  is_negative = !is_negative;
  *this += arg;
  is_negative = !is_negative;
  to_irreducible();
  return *this;
}

Rational &Rational::operator*=(const Rational &arg) {
  is_negative = is_negative != arg.is_negative;
  numerator *= arg.numerator;
  denominator *= arg.denominator;
  to_irreducible();
  return *this;
}

Rational &Rational::operator/=(const Rational &arg) {
  is_negative = is_negative != arg.is_negative;
  numerator *= arg.denominator;
  denominator *= arg.numerator;
  to_irreducible();
  return *this;
}

Rational operator+(const Rational &a, const Rational &b) {
  Rational copy = a;
  copy += b;
  return copy;
}

Rational operator-(const Rational &a, const Rational &b) {
  Rational copy = a;
  copy -= b;
  return copy;
}

Rational operator*(const Rational &a, const Rational &b) {
  Rational copy = a;
  copy *= b;
  return copy;
}

Rational operator/(const Rational &a, const Rational &b) {
  Rational copy = a;
  copy /= b;
  return copy;
}

bool operator<(const Rational &a, const Rational &b) {
  if (!a.get_sign() && b.get_sign()) {
    return false;
  }
  if (a.get_sign() && !b.get_sign()) {
    return true;
  }
  if ((a - b).get_sign()) {
    return true;
  }
  return false;
}

bool operator>(const Rational &a, const Rational &b) {
  return b < a;
}

bool operator==(const Rational &a, const Rational &b) {
  return !(b < a || a < b);
}

bool operator!=(const Rational &a, const Rational &b) {
  return !(a == b);
}

bool operator<=(const Rational &a, const Rational &b) {
  return !(a > b);
}

bool operator>=(const Rational &a, const Rational &b) {
  return !(a < b);
}

std::string Rational::toString() const {
  std::string ans;
  if (is_negative) {
    ans += '-';
  }
  if (denominator == 1) {
    return ans + numerator.toString();
  }
  ans += numerator.toString() + '/' + denominator.toString();
  return ans;
}

std::string Rational::asDecimal(size_t precision) const {
  std::string ans;
  if (is_negative) {
    ans = "-";
  }
  std::string num = ((numerator * ten_degree(precision)) / denominator).toString();
  ans += (num.length() > precision) ? num.substr(0, num.length() - precision) + '.'
      + num.substr(num.length() - precision, precision) : "0." + std::string(precision - num.length(), '0') + num;
  return ans;
}

Rational::operator double() const {
  std::string a = asDecimal(15);
  if (is_negative) {
    return -1 * std::strtod(a.substr(1, a.length() - 1).c_str(), nullptr);
  }
  return std::strtod(a.c_str(), nullptr);
}
#endif //BIGINTEGER_LIBRARY_H
