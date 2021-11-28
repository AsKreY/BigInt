#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "biginteger.h"

int main() {
    BigInteger b, k;
    b = 0, k = 1234567;
    std::ostringstream oss;
    oss << b << ' ' << k;
    if (oss.str() != "0 1234567") {
         std::cerr<<("Assignment from int, or stream output failed.\n");
    }

    BigInteger a = b;
    a = -a;
    std::string testString = a.toString() + " " + (-k).toString();
    if (testString != "0 -1234567") {
         std::cerr<<("Unary minus or toString method failed.\n");
    }

    a = 999, b = 1000;
    a = a += a;
    testString = a.toString();
    if (testString != "1998") {
         std::cerr<<("Operator = or += failed.\n");
    }
    ++a %= a /= a *= a -= b++;
    std::ostringstream oss2;
    oss2 << 5+a << ' ' << 1-b; // 5 -1000
    if (oss2.str() != "5 -1000") {
         std::cerr<<oss2.str();
    }
  
  std::ostringstream oss3;
    oss3 << (a = (bool(a) ? -1 : -2));
    if (oss3.str() != "-2") {
         std::cerr<<("BigIntegerests failed.\n");
    }

    std::istringstream iss("26 5");
    iss >> a >> b;
    std::ostringstream oss4;
    oss4 << b << ' ' << a << ' ';
    if (oss4.str() != "5 26 ") {
         std::cerr<<("Stream input or output failed.\n");
    }

    oss4 << a+b << ' ' << a-b << ' ' << a*b << ' ' << a/b << ' ' << a%b << '\n';
    oss4 << b+a << ' ' << b-a << ' ' << b*a << ' ' << b/a << ' ' << b%a;
    if (oss4.str() != "5 26 31 21 130 5 1\n31 -21 130 0 5") {
         std::cerr<<("Arithmetic operations failed.\n");
    }

    std::vector<BigInteger> v;
    for (size_t i = 0; i < 1000; ++i) {
        v.push_back(1000 - i);
    }
    std::sort(v.begin(), v.end());

    std::ostringstream oss5;
    oss5 << v[0] << ' ' << v[500] << ' ' << v[999] << ' ';

    oss5 << (a != b) << ' ' << (a < b) << ' ' << (a > b) << ' ';
       oss5 << (a <= b) << ' ' << (a >= b);
    if (oss5.str() != "1 501 1000 1 0 1 0 1") {
         std::cerr<<("Rationalelation operations failed.\n");
    }
    std::istringstream iss2("1000000000000000000000000000000000 -1000000");
    iss2 >> a >> b;
    std::ostringstream oss6;
    oss6 << b << a;
    if (oss6.str() != "-10000001000000000000000000000000000000000") {
         std::cerr<<("Stream input or output failed.\n");
    }

    std::istringstream iss3("453234523460009834520987234598234502345987029345436345634563 "
                             "234523452034623049872345234520983475325345234232578");
    BigInteger c, d;
    iss3 >> c >> d;

    std::istringstream iss4("-23534576554950000000000000009999990000999900000 "
                             "8888888888884444444444433333333333332222222222222111112222777777777");
    BigInteger e, f;
    iss4 >> e >> f;

      std::ostringstream oss7;

      oss7 << a+b << ' ' << c+d << ' ' << e+f;
      if (oss7.str() != "999999999999999999999999999000000 "
                   "453234523694533286555610284470579736866970504670781579867141 "
                "8888888888884444444420898756778383332222222222212111122221777877777") {
     std::cerr<<("Operatori + failed.\n");
      }
    
    std::ostringstream oss8;
    oss8 << a-b << ' ' << c-d << ' ' << e-f;
    if (oss8.str() != "1000000000000000000000000001000000 "
                    "453234523225486382486364184725889267825003554020091111401985 "
                    "-8888888888884444444467967909888283332222222222232111102223777677777") {
         std::cerr<<("Operator - failed.\n");
    }

    std::ostringstream oss9;
       oss9 << a*b << ' ' << c*d << ' ' << e*f;
    if (oss9.str() != "-1000000000000000000000000000000000000000 "
                    "106294125023108851855435239407742287054686671354449187194200406809777590661604024572718537860109672117737393414 "
                    "-209196236043895401881977738593593744982694026094492829962212043149123345328234038901116544451103777729999222300000") {
         std::cerr<<("Operator * failed.\n");
    }

std::ostringstream oss10;
    oss10 << a/b << ' ' << c/d << ' ' << e/f;
    if (oss10.str() != "-1000000000000000000000000000 1932576548 0") {
        std::cerr<<("Operator / failed.\n");
    }
    std::ostringstream oss11;
    oss11 << a%b << ' ' << c%d << ' ' << e%f;
    if (oss11.str() != "0 101894444317458440603421824036688159663989325253819 "
                       "-23534576554950000000000000009999990000999900000") {}

    Rational r;
    r = 5;
    r += 3;
    r *= 7; 
    b = 15;
    (r /= 8) -= b;
    if (-r != 8)
        std::cerr<<("BigIntegerest 1 failed.\n");

    Rational s, t;
    s = Rational(85)/37, t = Rational(29)/BigInteger(-163);
    s += t;
    t = 1;
    for (int i = 0; i < 15; ++i)
        t *= s;
    if ((1/t).toString() != "507972178875842800075597772950831264898404875587494819951"
            "/39717526884730183825748150063721595142668632339785349901549568")
        std::cerr<<("BigIntegerest 2 failed.\n");
    s = 4*3*7*13*19*41*43*11; // 2^2×3×7×13×19×41×43×11
    t = -17*13*23*79;
    s *= s*s, t *= t*t;
  Rational q = s/t;
    if (q.toString() != "-29650611427828166204352/29472131485369")
        std::cerr<<("BigIntegerest 3 failed.\n");
    if (q/1000000000 >= 1)
        std::cerr<<("BigIntegerest 4 failed.\n");
    if (0/q != 0)
        std::cerr<<("BigIntegerest 5 failed.\n");
    q *= t/s;
    if (q != 1 || q.toString() != "1")
        std::cerr<<("BigIntegerest 6 failed.\n");
    s = 4*3*7*13*19*41*43*11;
    t = s - 25; // t=402365939
    s = 1000000007;
    s *= 1000000009;
    s *= 2147483647;
    if ((s/t).asDecimal(10) != "5337140829307966068.3989202202")
        std::cerr<<("BigIntegerest 7 failed.\n");
    t = -t;
    if ((t/s).asDecimal(25) != "-0.0000000000000000001873662")
        std::cerr<<("BigIntegerest 8 failed.\n");
    

}
