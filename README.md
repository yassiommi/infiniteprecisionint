# Infinite Precision Integer

This program contains a c++ class implemented in order to store and perform arithmetic on infinite-precision integers.

Part of:
CSE 701:
Foundations of Modern Scientific Programming
McMaster University, Fall 2022
By: Prof. Barak Shoshany

## Utility Functions

- ```extract_sign``` is a function which checks the first character of the string and returns -1 if it's negative and +1 otherwise.
- ```trim_sign``` is a function which removes the first character of the string of it's a sign (- or +).
- ```trim_lhs_zeros``` is a function to remove additional left-hand zeroes of the input if any.
- ```extend_value_with_zero``` is a function to use when you want to make two strings have the same length as the larger one. 

## InfinitePrecisionInt Class

### (Private) Variables:
- ```value``` is a string storing the value. It van be accessed using the ```getValue()``` function. 
- ```sign``` is an integer with values -1 in case the number is negative and +1 otherwise. It can accessed using the ```getSign()``` function.

### Functions:

-  ```positive_sum``` 
```positive_sum``` is  the implemented private function to sum two instances of the InfinitePrecisionInt class, using a ```carry```  integer variable. 
#### Example:
```
int main(){
InfinitePrecisionInt a, b;
cout << "Enter two numbers: ";
cin >> a >> b;
cout << "a + b = " << (a+b) << endl;
}
```
Output:
```
Enter two numbers: 7946587346159873465874659746198376598734659836475962345
13784658713465619384756394685762408734875964398751630485601384765831746598731465983465
a + b = 13784658713465619384756394685770355322222124272217505145347583142430481258567941945810
Program ended with exit code: 0
```
- ```recursive_divide``` 
```recursive_divide``` is the implemented private function to perform division on two instances of the InfinitePrecisionInt class. It returns 0 if the dividend is smaller than the divisor, and returns the quotient otherwise. *(Can take some time for very large numbers...)*

#### Example:
```
int main(){
InfinitePrecisionInt a, b;
cout << "Enter two numbers: ";
cin >> a >> b;
cout << "a / b = " << (a/b) << endl;   
}
```
Output:
```
Enter two numbers: 2489756987364598726478163495876439875623948756
1378946598734659871346598713659873465871364598173465813475
a / b = 0
Program ended with exit code: 0
```
- ```set_sign_and_value```
```set_sign_and_value``` is a private function that initializes the value of the variable ```sign```, then removes the sign character from the string (if any). 

### Constructors 
The class has three constructors. A default one, which makes an instance of the class with value 0, and two other constructors working with ```int``` and ```string```.

### Overloaded Operators
A complete list of operators has been overloaded for the InfinitePrecisionInt class: ```==```, ```!=```, ```<```, ```<=```,```>```,```>=```,```+```,```-```,```+=```,```-+```,```++```,```--```,```*```,```*=```,```/```,```/=```,```%```,```%=```,```[]```,```<<``` and ```>>```.
### Example
Here's an example of the operators working on instances of the InfinitePrecisionInt class.
```
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
```
Output:
```
Please enter your first number: 5716354763157613547234876324765
Please enter your second number: -1273954673159734657834657345756345
Please enter your third number: 9876543678765645435657687689756345
a - b = 1279671027922892271381892222081110
a - b - c = -8596872650842753164275795467675235
a + b = -1268238318396577044287422469431580
a + b + c = 8608305360369068391370265220324765
a * b = -7282376863963549986182472053436327528230297063620075182779383925
a * b * c = -71924713182168384245100319382688405529031750418343982501764199391140519317840783749596272459754125
a+=b : -1268238318396577044287422469431580
a-=b :5716354763157613547234876324765
a - c + b = -11144781997162222479945110159187925
a == b : False
a == a : True
a < a : False
a < b : True
a > b : False
a  < a : False
a <= b : True
a <= a : True
a != b : True
a != a : False
a >= b : False
a / b = -0
b / a = -222
a % b = 5716354763157613547234876324765
--a =5716354763157613547234876324765
++a =5716354763157613547234876324764
Program ended with exit code: 0
```
