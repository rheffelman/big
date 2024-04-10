#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double getMonthlyPayment(int years, double AIR, double principal);
void displaySummary(double p, double AIR, int years);
void fillMortgageSchedule(vector < vector < double > > &sched, double p, double AIR, int years);
void displayMortgageSchedule(vector < vector < double > > &sched, int startMonth, int endMonth);
int main() {

    //mortgage info
    double principal = 100000.0;
    double annualInterestRate = 12.0;
    int numYears = 30;

    //mortgage schedule
    vector < vector < double > > mortgageSchedule;

    //fill the 2D vector
    fillMortgageSchedule(mortgageSchedule, principal, annualInterestRate, numYears);

    //display the summary
    displaySummary(principal, annualInterestRate, numYears);

    //display the schedule from months 30-60
    int startMonth = 30;
    int endMonth = 60;
    displayMortgageSchedule(mortgageSchedule, startMonth, endMonth);

    //display the schedule from months 300-330
    startMonth = 300;
    endMonth = 330;
    displayMortgageSchedule(mortgageSchedule, startMonth, endMonth);


    return 0;
}
void fillMortgageSchedule(vector < vector < double > > &sched, double p, double r, int years){
    int months = years * 12;
    double monthlyPayment = getMonthlyPayment(years, r, p);
    r *= 0.01;
    r /= 12;
    double remainingP = p;

    sched.resize(months);

    for (int i = 1; i <= months; i++){
    sched[i - 1].push_back(monthlyPayment);
        //amount paid in principal
    sched[i - 1].push_back(monthlyPayment - (r*remainingP));
        //amount paid in interest this month
    sched[i - 1].push_back(r*remainingP);
    remainingP -= monthlyPayment - (r*remainingP);
        //remaining in principal
    sched[i - 1].push_back(remainingP);
    }
}
void displayMortgageSchedule(vector < vector < double > > &sched, int startMonth, int endMonth){
    for (int i = startMonth - 1; i <= endMonth - 1; i++){
        printf("month %d) monthly payment: $%.2f   principal this month: $%.2f   interest this month: $%.2f   remaining in principal: $%.2f", i + 1, sched[i][0], sched[i][1], sched[i][2], sched[i][3]);
        if (i % 12 == 0){
            printf(" year %d\n", i / 12);
        }
        else printf("\n");
    }
}
double getMonthlyPayment(int y, double AIR, double p){
    double r = (AIR/12) / 100.0;
    return p * (r * pow((1 + r), y * 12)) / (pow((1 + r), y * 12) - 1);
}
void displaySummary(double p, double r, int years){
    double monthlyPayment = getMonthlyPayment(years, r, p);
    double amountPaid = monthlyPayment * years * 12;
    double interestPaid = amountPaid - p;
    double paidOverPrincipal = amountPaid / p;

    printf("here's a summary of your loan amount: \n");
    printf("loan amount: $%.2f\n", p);
    printf("annual interest rate: %.1f%\n", r);
    printf("monthly payment: %.2f\n", monthlyPayment);
    printf("total amount paid for the loan: $%.2f\n", amountPaid);
    printf("the amount of interest paid: $%.2f\n", interestPaid);
    printf("ratio of amount paid over principal: %.3f to 1\n\n", paidOverPrincipal);
}
