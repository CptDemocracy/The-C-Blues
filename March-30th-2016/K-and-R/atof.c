#include <ctype.h>
#include <math.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)

 Extend atof to handle scientific notation of the form
 123.45e-6
 where a floating-point number may be followed by e or E 
 and an optionally signed exponent. 
*/

double Atof(const char* s) {
    
    if (!s) return 0.0;
    
    while (isspace(*s)) ++s;

    int sign = 1;
    double frac = 1.0;
    double result = 0.0;

    if (*s == '-') {
        sign = -1;
        ++s;
    }
    else if (*s == '+') {
        ++s;
    }
    while (isdigit(*s)) {
        result = result * 10.0 + (*s - '0');
        ++s;
    }
    if (*s == '.') {
        ++s;
        while (isdigit(*s)) {
            result = result * 10.0 + (double)(*s - '0');
            frac *= 10;
            ++s;
        }

        if (*s == 'E' || *s == 'e') {
            ++s;
        
            double exp = 0.0;
            int fracsign = 1;

            if (*s == '-') {
                fracsign = -1;
                ++s;
            }
            else if (*s == '+') {
                fracsign = 1;
                ++s;
            }
            
            while (isdigit(*s)) {
                exp = exp * 10.0 + (*s - '0');
                ++s;
            }
            exp *= fracsign;
        
            return sign * result / frac * pow(10.0, exp);
        }

        return sign * result / frac;
    }
    else if (*s == 'E' || *s == 'e') {
        ++s;
        
        double exp = 0.0;
        int fracsign = 1;

        if (*s == '-') {
            fracsign = -1;
        }
        else if (*s == '+') {
            fracsign = 1;
        }

        ++s;

        while (isdigit(*s)) {
            exp = exp * 10.0 + (*s - '0');
            ++s;
        }
        exp *= fracsign;
        
        return sign * result * pow(10.0, exp);
    }
    
    return result;
}
