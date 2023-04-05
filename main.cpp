#include <iostream>
#include "infinite_int.hpp"

int main() {
    InfinitePrecisionInt a, b, c;

    cout << "Please enter your first number: ";
    cin >> a;
    
    cout << "Please enter your second number: ";
    cin >> b;
    
    cout << "Please enter your third number: ";
    cin >> c;
    
    cout << "a - b = " << (a-b) << endl;
    
    cout << "a - b - c = " << (a-b-c) << endl;
    
    cout << "a + b = " << (a+b) << endl;
    
    cout << "a + b + c = " << (a+b+c) << endl;
    
    cout << "a * b = " << (a*b) << endl;
    
    cout << "a * b * c = " << (a*b*c) << endl;
    
    a+=b;
    cout << "a+=b : " << (a) << endl;
    
    a-=b;
    cout << "a-=b :" << (a) << endl;
    
//    cout << "[a] =" << ([a]) << endl;
    
    cout << "a - c + b = " << (a-c+b) << endl;
    
    cout << "a == b : ";
    (a==b) ? (cout << "True") : (cout << "False");
    cout << endl;
    
    cout << "a == a : ";
    (a==a) ? (cout << "True") : (cout << "False");
    cout << endl;

    cout << "a < a : ";
    (a<a) ? (cout << "True") : (cout << "False");
    cout << endl;
    
    cout << "a < b : ";
    (a<b) ? (cout << "True") : (cout << "False");
    cout << endl;

    cout << "a > b : ";
    (a>b) ? (cout << "True") : (cout << "False");
    cout << endl;

    cout << "a  < a : ";
    (a<a) ? (cout << "True") : (cout << "False");
    cout << endl;
    
    cout << "a <= b : ";
    (a<=b) ? (cout << "True") : (cout << "False");
    cout << endl;
    
    cout << "a <= a : ";
    (a<=a) ? (cout << "True") : (cout << "False");
    cout << endl;

    cout << "a != b : ";
    (a!=b) ? (cout << "True") : (cout << "False");
    cout << endl;

    cout << "a != a : ";
    (a!=a) ? (cout << "True") : (cout << "False");
    cout << endl;

    cout << "a >= b : ";
    (a>=b) ? (cout << "True") : (cout << "False");
    cout << endl;
    
    cout << "a / b = " << (a/b) << endl;
    
    cout << "b / a = " << (b/a) << endl;
    
    cout << "a % b = " << (a%b) << endl;
    
    cout << "--a =" << (--a) << endl;
    
    cout << "++a =" << (++a) << endl;
    
    return 0;
}

