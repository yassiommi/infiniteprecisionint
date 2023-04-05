#include <iostream>
#include <string.h>
#include <regex>

using namespace std;


int extract_sign(string str_value) {
/*
    input: string representing the infinite-precision integer
    output: -1 if input is negative and +1 if positive
*/
    if (str_value[0] == '-') {
        return -1;
    }
    return 1;
}


std::string trim_sign(string str_value) {
/*
    input: string representing the infinite-precision integer
    output: the same string without the sign (if any)
*/
    if (str_value[0] == '-' || str_value[0] == '+') {
        return str_value.substr(1, str_value.length());
    }
    return str_value;
}


std::string trim_lhs_zeros(string str) {
/*
    input: string representing the infinite-precision integer
    output: the same string without left-hand zeroes (if any)
*/
    while (str[0] == '0' && str.length() > 1) {
        str = str.substr(1, str.length());
    }
    return str;
}


int modified_modulo(int val) {
    return val < 0 ? val % 10 + 10 : val % 10;
}

int modified_carry(int val) {
    return val < 0 ? val / 10 - 1 : val / 10;
}

std::string extend_value_with_zero(std::string val, int size) {
/*
    input: string representing the infinite-precision integer
    output: the same string extended with left-hand zeroes so that the two numbers have equal lenghts for easier operations
*/
    int distance = size - val.length();
    string lhs = "";
    for (int i = 0; i < distance; i++) {
        lhs.append("0");
    }
    lhs.append(val);
    return lhs;
}

class InfinitePrecisionInt {
/*
    a class for storing infinite-precision numbers with overloaded operators
    variables:
            value: the string storing the infinite-precision integer
            sign: -1 in case of a negative number and +1 otherwise
*/
    private:
        std::string value;
        int sign;

        InfinitePrecisionInt positive_sum(InfinitePrecisionInt left, InfinitePrecisionInt right) {
/*
    input: two instances of InfinitePrecisionInt
    output: sum of the two inputs, done using an extra "carry" int
*/
            std::string this_value = left.getValue(), right_value = right.getValue(), result = "";
            int carry = 0, this_sign = left.getSign(), right_sign = right.getSign(), this_digit_value, right_digit_value;
            
            int size = std::max(this_value.length(), right_value.length());
            this_value = extend_value_with_zero(this_value, size);
            right_value = extend_value_with_zero(right_value, size);
            
            for (int i = 0; i < size; i++) {
                this_digit_value = this_value[size - i - 1] - '0';
                right_digit_value = right_value[size - i - 1] - '0';
                int sum = this_sign * this_digit_value + right_sign * right_digit_value + carry;
                result.append(std::to_string(modified_modulo(sum)));
                carry = modified_carry(sum);
            }
            result.append(std::to_string(carry));

            std::reverse(result.begin(), result.end());

            result = trim_lhs_zeros(result);

            return InfinitePrecisionInt(result);
        }

        InfinitePrecisionInt recursive_divide(InfinitePrecisionInt left, InfinitePrecisionInt right) {
/*
    input: two instances of InfinitePrecisionInt
    output: the first number divided by the second one
            returns 0 if the dividend is smaller than the divisor
            returns the quotient otherwise
            does the division in a recursive manner
*/
            if (left < right) {
                return (InfinitePrecisionInt) 0;
            }

            InfinitePrecisionInt ten = 10;
            InfinitePrecisionInt right_shifted = right.getValue();

            string zero_string = "";
            
            while (left >= right_shifted * ten) {
                right_shifted = right_shifted * ten;
                zero_string.append("0");
            }

            int counter = 0;

            while (left >= right_shifted) {
                left -= right_shifted;
                counter++;
            }

            zero_string.append(std::to_string(counter));
            std::reverse(zero_string.begin(), zero_string.end());

            return ((InfinitePrecisionInt) zero_string) + recursive_divide(left, right);
        }

        void set_sign_and_value(std::string temp) {
/*
    input: string representing an infinite-precision integer
    output: void
            initializes the value of the variable "sign"
            then removes the sign character from the string (if any)
*/
            sign = extract_sign(temp);
            value = trim_sign(temp);
        }
    
    public:
        InfinitePrecisionInt() {
/*
    default constructor
    initializes the instance with value 0
*/
            value = "0";
            sign = 1;
        }

        InfinitePrecisionInt(int_fast64_t int_value) {
/*
    constructor with int input
    initializes the sign and value variables
*/
            std::string temp = std::to_string(int_value);
            set_sign_and_value(temp);
        }

        InfinitePrecisionInt(string str_value) {
/*             
    constructor with string input
    initializes the sign and value variables
    checks if any ivalid characters are in the input
    
    TO-DO: consider "e" for power
*/
            if (std::regex_match(str_value, std::regex("(\\+|\\-)?[0-9]+"))) {
                set_sign_and_value(str_value);
            }
            else {

                throw std::invalid_argument("String argument is not correctly formatted.");
            }
        }

        std::string getValue() {
/*
    function for accessing the value variable which is private
    returns value
*/
            
            return value;
        }

        int getSign() {
/*
    function for accessing the sign variable which is private
    returns sign
*/
            return sign;
        }

        bool operator==(InfinitePrecisionInt right) {
/*
    overloaded == operator for InfinitePrecisionInt instances
    output: 0 if Flase (not equal) and 1 otherwise
    first checks signs
*/
            if (getSign() != right.getSign()) {
                return 0;
            }
            std::string rightStr = right.getValue();
            if (getValue().compare(rightStr) == 0) {
                return 1;
            }
            return 0;
        }

        bool operator<(InfinitePrecisionInt right) {
/*
    overloaded < oprator for InfinitePrecisionInt instances
    output: 0 if Flase (right not greater) and 1 otherwise
    first checks signs
*/
            if (getSign() < right.getSign()) {
                return 1;
            }
            int has_greater_value = 0;
            if (getValue().length() > right.getValue().length()) {
                has_greater_value = 1;
            }
            else if (getValue().length() < right.getValue().length()) {
                has_greater_value = 0;
            }
            else {
                int i = 0;
                while (getValue()[i] == right.getValue()[i] && i < getValue().length()) {
                    i++;
                }
                if (i == getValue().length()) {
                    return 0;
                }
                if (getValue()[i] < right.getValue()[i]) {
                    has_greater_value = 0;
                }
                else {
                    has_greater_value = 1;
                }
            }
            if (
                (has_greater_value == 1 && getSign() == -1)
                    || (has_greater_value == 0 && getSign() == 1)
            ) {
                return 1;
            }
            return 0;
        }

        bool operator!=(InfinitePrecisionInt right) {
/*
    overloaded != operator for InfinitePrecisionInt instances
    uses the == operator with reverse answer
*/
            return !(*this == right);
        }

        bool operator<=(InfinitePrecisionInt right) {
/*
    overloaded <= operator for InfinitePrecisionInt instances
    uses two other operators < and == to compare them
*/
            return (*this < right) || (*this == right);
        }

        bool operator>(InfinitePrecisionInt right) {
/*
    overloaded < operator for InfinitePrecisionInt instances
    uses two other operators < and != to compare
*/
            return !(*this < right) && (*this != right);
        }

        bool operator>=(InfinitePrecisionInt right) {
/*
    overloaded >= operator for InfinitePrecisionInt instances
    uses the < operator to compare them
*/
            return !(*this < right);
        }

        InfinitePrecisionInt operator-() {
/*
    overloaded - operator (sign) for InfinitePrecisionInt instances
*/
            string signedValue = getSign() == -1 ? "" : "-";
            signedValue.append(getValue());
            return InfinitePrecisionInt(signedValue);
        }

        InfinitePrecisionInt operator+(InfinitePrecisionInt right) {
/*
    overloaded + operator for InfinitePrecisionInt instances
    uses the positive_sum function to perform addition
*/
            if (
                (getSign() == -1 && right.getSign() == -1)
                || (getSign() == -1 && right.getSign() == 1 && -(*this) > right)
                || (getSign() == 1 && right.getSign() == -1 && -right > *this)
            ) {
                return -positive_sum(-(*this), -right);
            }
            return positive_sum(*this, right);
        }

        void operator+=(InfinitePrecisionInt right) {
/*
    overloaded += operator for InfinitePrecisionInt instances
    uses the already overloaded + operator to perform addition
*/
            InfinitePrecisionInt sum = *this + right;
            value = sum.getValue();
            sign = sum.getSign();
        }

        InfinitePrecisionInt operator-(InfinitePrecisionInt right) {
/*
    overloaded - operator for InfinitePrecisionInt instances
    uses the already overloaded + operator with a negative sign
*/
            return *this + (-right);
        }

        void operator-=(InfinitePrecisionInt right) {
/*
    overloaded -= operator for InfinitePrecisionInt instances
    uses the already overloaded - operator with a negative sign
*/
            InfinitePrecisionInt sum = *this - right;
            value = sum.getValue();
            sign = sum.getSign();
        }

        InfinitePrecisionInt operator++() {
/*
    overloaded ++ operator for InfinitePrecisionInt instances
    uses the already overloaded + operator
*/
            InfinitePrecisionInt add = 1;
            InfinitePrecisionInt sum = *this + add;
            value = sum.getValue();
            sign = sum.getSign();
            return *this - add;
        }

        InfinitePrecisionInt operator--() {
/*
    overloaded -- operator for InfinitePrecisionInt instances
    uses the already overloaded - operator
*/
            InfinitePrecisionInt add = 1;
            InfinitePrecisionInt sum = *this - add;
            value = sum.getValue();
            sign = sum.getSign();
            return *this + add;
        }

        InfinitePrecisionInt operator*(InfinitePrecisionInt right) {
/*
    overloaded * operator for InfinitePrecisionInt instances
    uses a carry variable
*/
            InfinitePrecisionInt result = (string) "0";
            int carry = 0, this_digit_value, right_digit_value;
            std::string this_value = getValue(), right_value = right.getValue();

            for (int i = right_value.length() - 1; i >= 0; i--) {
                right_digit_value = right_value[i] - '0';
                string digit_multiply_result = "";

                for (int j = 0; j < right_value.length() - 1 - i; j++) {
                    digit_multiply_result.append("0");
                }

                for (int j = this_value.length() - 1; j >= 0; j--) {
                    this_digit_value = this_value[j] - '0';
                    int turn_multiply = this_digit_value * right_digit_value + carry;
                    digit_multiply_result.append(std::to_string(turn_multiply % 10));
                    carry = turn_multiply / 10;
                }

                digit_multiply_result.append(std::to_string(carry));
                carry = 0;
                std::reverse(digit_multiply_result.begin(), digit_multiply_result.end());
                digit_multiply_result = trim_lhs_zeros(digit_multiply_result);
                InfinitePrecisionInt add = (string) digit_multiply_result;
                result += add;
            }

            if (getSign() * right.getSign() == -1) {
                return -result;
            }
            return result;
        }

        void operator*=(InfinitePrecisionInt right) {
/*
    overloaded *= operator for InfinitePrecisionInt instances
    uses the already overloaded * operator
*/
            InfinitePrecisionInt mult = *this * right;
            value = mult.getValue();
            sign = mult.getSign();
        }

        InfinitePrecisionInt operator/(InfinitePrecisionInt right) {
/*
    overloaded / operator for InfinitePrecisionInt instances
    uses the recursive division function
*/
            InfinitePrecisionInt div = recursive_divide((InfinitePrecisionInt) getValue(), (InfinitePrecisionInt) right.getValue());
            if (getSign() * right.getSign() == -1) {
                return -div;
            }
            return div;
        }

        void operator/=(InfinitePrecisionInt right) {
/*
    overloaded /= operator for InfinitePrecisionInt
    uses the already overloaded / operator
*/
            InfinitePrecisionInt div = *this / right;
            value = div.getValue();
            sign = div.getSign();
        }

        InfinitePrecisionInt operator%(InfinitePrecisionInt right) {
/*
    overloaded % operator for InfinitePrecisionInt instances
    uses the formula: Dividend = (Divisor * Quotient) + Remainder
*/
            InfinitePrecisionInt mod = *this - (*this / right) * right;
            if (mod < 0) {
                return mod + right;
            }
            return mod;
        }

        void operator%=(InfinitePrecisionInt right) {
/*
    overloaded % =operator for InfinitePrecisionInt instances
    uses the already overloaded % operator
*/
            InfinitePrecisionInt mod = *this % right;
            value = mod.getValue();
            sign = mod.getSign();
        }

        char operator[](int i) {
            return getValue()[i];
        }

        friend std::ostream & operator << (ostream &out, InfinitePrecisionInt ipi);
        friend std::istream & operator >> (istream &in,  InfinitePrecisionInt &ipi);
};

std::ostream &operator<<(std::ostream &out, InfinitePrecisionInt ipi) {
/*
    overloaded insertion << operator to print the value
*/
    string signedValue = ipi.getSign() == -1 ? "-" : "";
    signedValue.append(ipi.getValue());
    out << signedValue;
    return out;
}

std::istream &operator>>(std::istream &in, InfinitePrecisionInt &ipi) {
/*
    overloaded insertion >> operator to take the value as input
*/
    in >> ipi.value;
    ipi.set_sign_and_value(ipi.value);
    return in;
}
