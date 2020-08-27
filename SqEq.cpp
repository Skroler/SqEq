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


int find_d (double a, double b, double c) //discriminant finder
{
    return (b*b - 4*a*c);
}

int find_quantity_sol (double a, double b, double c,
                       double* x1, double* x2)
{
    assert (std::isfinite (a)); //�� �������� ��� cmath � assert ������?
    assert (std::isfinite (b));
    assert (std::isfinite (c));

    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (a == 0)
    {
        if (b == 0)
        {
            return (c == 0) ? -1 : 0;
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

void print_name_date()
{
    printf ("# quadratic equation solver\n"
            "# (c) Yafarov Vladimir, 2020\n\n");

    printf ("# enter a, b, c: ");
}

int main()
{
    print_name_date();

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
    return 0;
}