#include <stdio.h>

double calculateRepayment(double loan, double interestRate, int years, double installment, double extraPayment)
{

    if (loan <= 0 || years == 0)
    {
        return 0;
    }

    double payment = installment + extraPayment;
    loan -= payment;

    if (loan > 0)
    {
        loan *= (1 + interestRate);
    }

    printf("Year %d: Remaining loan = %.2f\n", years, loan);

    return payment + calculateRepayment(loan, interestRate, years - 1, installment, extraPayment);
}

int main()
{
    double loan;
    double interestRate;
    int years;
    double installment;
    double extraPayment;
    printf("Enter loan amount: ");
    scanf("%lf", &loan);
    printf("Enter annual interest rate (as a decimal): ");
    scanf("%lf", &interestRate);
    printf("Enter number of years for repayment: ");
    scanf("%d", &years);
    printf("Enter annual installment amount: ");
    scanf("%lf", &installment);
    printf("Enter extra payment amount (if any): ");
    scanf("%lf", &extraPayment);

    printf("Repayment Schedule:\n");
    double totalRepayment = calculateRepayment(loan, interestRate, years, installment, extraPayment);

    printf("\nTotal repayment over %d years = %.2f\n", years, totalRepayment);

    return 0;
}