#include <stdio.h>
#include <math.h>
#include <cmath>
#include <assert.h>

//-------------------------------------------------------------
//! Solves a square equation ax2 + bx + c = 0
//!
//! @param [in] a a-coeff
//! @param [in] b b-coeff
//! @param [in] c c-coeff
//! @param [out] x1 Solution to the 1st root
//! @param [out] x2 Solution to the 1st root
//!
//! @return Number of roots
//!
//! @note In case of infinite number of roots,
//!       returns "-1".
//-------------------------------------------------------------

bool IsZero (double value);

int find_d (double a, double b, double c); //discriminant finder


int find_quantity_sol (double a, double b, double c,
                       double* x1, double* x2);

void print_name_date();

void Test_IsZero();



//-------------------------------------------------------------
//Main Function
//-------------------------------------------------------------

int main()
    {
    print_name_date();

    printf ("# enter a, b, c: ");

    double a = 0, b = 0, c = 0;

    scanf ("%lg %lg %lg", &a, &b, &c);

    double x1 = 0, x2 = 0;

    int quantity_sol = find_quantity_sol(a, b, c, &x1, &x2);

    switch (quantity_sol)
    {
        case 0: printf ("No solutions\n");
                break;

        case 1: printf ("x = %lg \n", x1);
                break;

        case 2: printf ("x1 = %lg, x2 = %lg \n", x1, x2);
                break;

        case -1: printf("Any num");
                break;

        default: printf("main(): ERROR: quantity_sol = %d\n",
                         quantity_sol);
                 return 1;
    }
    Test_IsZero();
    return 0;
    }



//-------------------------------------------------------------
//Other functions
//-------------------------------------------------------------

bool IsZero (double value)
    {
    return (fabs (value) <= 1e-5); // enter error size
    }

int find_quantity_sol (double a, double b, double c,
                       double* x1, double* x2)
    {
    assert (std::isfinite (a)); //не работает без cmath и assert почему?
    assert (std::isfinite (b));
    assert (std::isfinite (c));

    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (IsZero(a))
    {
        if (IsZero(b))
        {
            return (IsZero(c)) ? -1 : 0;
        }
        else // if b != 0
        {
            *x1 = -c / b;
            return 1;
        }
    }

    else // if a != 0
    {
        double d = find_d(a,b,c);

        if (d < 0) return 0;

        else if (d == 0)
        {
            *x1 = *x2 = -b / 2*a;
            return 1;
        }

        else // if d >= 0
        {
            double sqrt_d = sqrt(d);

            *x1 = (-b - sqrt_d) / (2*a);
            *x2 = (-b + sqrt_d) / (2*a);

            return 2;
        }
    }
}

int find_d (double a, double b, double c) //discriminant finder
    {
    return (b*b - 4*a*c);
}

void print_name_date()
    {
    printf ("# quadratic equation solver\n"
            "# (c) Yafarov Vladimir, 2020\n\n");
}



//-------------------------------------------------------------
// Unit Test
//-------------------------------------------------------------

void Test_IsZero()
    {

    double val = 0;
    int    res = IsZero (val);
    int    exp = 1;

    #define DO_TEST                                                                                            \
        if (res == exp) {printf ("Test #%d Ok\n", __LINE__);}                                                  \
        else            {printf ("Test #%d BAD: IsZero (%g) == %d, should be %d\n", __LINE__, val, res, exp);} \

    DO_TEST

           val = 1;
           res = IsZero (val);
           exp = 0;

    DO_TEST

           val = 1e-5;
           res = IsZero (val);
           exp = 1;

    DO_TEST

    #undef DO_TEST
    }
