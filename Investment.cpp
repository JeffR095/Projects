/*
 * Jeffrey Rivera
 * CS-210
 * Project 2
 */


#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Investment {
public:
    void gatherInput();
    void displayInvestmentSummary();
    void generateReports();
    void calculateWithoutDeposit();
    void calculateWithDeposit();
    void displayReport(string title, vector<int> years, vector<double> balances, vector<double> interests);
    void displayMonthlyBreakdown();

private:
    double initialInvestment = 0.0;
    double monthlyDeposit = 0.0;
    double annualInterest = 0.0;
    int years = 0;

    //The following vectors will be useful for storing info we need to create our reports
    vector<int> yearsWithoutDeposit;
    vector<double> balancesWithoutDeposit;
    vector<double> interestsWithoutDeposit;

    vector<int> yearsWithDeposit;
    vector<double> balancesWithDeposit;
    vector<double> interestsWithDeposit;

    vector<vector<double>> monthlyDetails;
};

//User input will be used in the functions that follow
void Investment::gatherInput() {
    cout << "Enter Initial Investment Amount: $";
    cin >> initialInvestment;
    cout << "Enter Monthly Deposit: $";
    cin >> monthlyDeposit;
    cout << "Enter Annual Interest : %";
    cin >> annualInterest;
    cout << "Enter Number of Years: ";
    cin >> years;
    cin.ignore();
}

//Displays user input
void Investment::displayInvestmentSummary() {
    cout << "\n==========================\n";
    cout << "=======DATA INPUT\n";
    cout << "==========================\n";
    cout << fixed << setprecision(2); //Restrict output to 2 decimal places
    cout << "Initial Investment Amount: $" << initialInvestment << "\n";
    cout << "Monthly Deposit: $" << monthlyDeposit << "\n";
    cout << "Annual Interest: %" << annualInterest << "\n";
    cout << "Number of Years: " << years << "\n";
}


void Investment::generateReports() {
    calculateWithoutDeposit();
    calculateWithDeposit();
    displayReport("Year-End Report (No Monthly Deposits)", yearsWithoutDeposit, balancesWithoutDeposit, interestsWithoutDeposit);
    displayReport("Year-End Report (With Monthly Deposits)", yearsWithDeposit, balancesWithDeposit, interestsWithDeposit);
    displayMonthlyBreakdown();
}

void Investment::calculateWithoutDeposit() {
    double balance = initialInvestment;

    for (int year = 1; year <= years; ++year) {
        for (int month = 0; month < 12; ++month) {
            double interest = balance * ((annualInterest / 100) / 12); // Monthly interest
            balance += interest; // Update balance with interest
        }

        yearsWithoutDeposit.push_back(year); //place new values at end by appending same applies for line below
        balancesWithoutDeposit.push_back(balance);
        interestsWithoutDeposit.push_back(balance - initialInvestment); // Total interest earned
    }
}

void Investment::calculateWithDeposit() {
    double balance = initialInvestment;

    for (int month = 1; month <= years * 12; ++month) {
        double openingAmount = balance; // Current balance before deposit
        double interest = (openingAmount + monthlyDeposit) * ((annualInterest / 100) / 12); // Calculate interest
        double total = openingAmount + monthlyDeposit; // Total for this month

        // Update balance with interest and deposit
        balance += interest + monthlyDeposit;

        // Store monthly details
        monthlyDetails.push_back({ static_cast<double>(month), openingAmount, monthlyDeposit, total, interest, balance });
    }

    // Calculate year-end balances and interests for reporting
    for (int year = 1; year <= years; ++year) {
        double totalDeposited = initialInvestment + (monthlyDeposit * 12 * year);
        int lastMonthIndex = year * 12 - 1; //must subtract 1 since 0 is counted
        double yearEndBalance = monthlyDetails[lastMonthIndex].back();
        yearsWithDeposit.push_back(year);
        balancesWithDeposit.push_back(yearEndBalance);
        interestsWithDeposit.push_back(yearEndBalance - totalDeposited); // Total interest earned
    }
}

void Investment::displayReport(string title, vector<int> years, vector<double> balances, vector<double> interests) {
    cout << "\n==========================\n";
    cout << "   " << title << "\n";
    cout << "==========================\n";
    cout << "| Year | Year-End Balance | Year-End Earned Interest |\n";
    for (size_t i = 0; i < years.size(); ++i) {
        //size_t to avoid non-positive numbers
        //display values stored in vectors
        cout << "| " << setw(4) << years[i]
            << " | $" << setw(16) << balances[i]
            << " | $" << setw(24) << interests[i] << " |\n";
    }
}

void Investment::displayMonthlyBreakdown() {
    cout << "\n==========================\n";
    cout << "   Monthly Breakdown\n";
    cout << "==========================\n";
    cout << "| Month | Opening Amount | Deposited Amount |   Total   |  Interest  | Closing Balance |\n";
    //the info above was gathered by our previous reports and calculations performed
    for (const vector<double>& detail : monthlyDetails) {
        cout << "| " << setw(5) << static_cast<int>(detail[0])
            << " | $" << setw(14) << detail[1]
            << " | $" << setw(15) << detail[2]
            << " | $" << setw(9) << detail[3]
            << " | $" << setw(10) << detail[4]
            << " | $" << setw(15) << detail[5] << " |\n";
    }
}

int main() {
    cout << "==========================\n";
    cout << "   AIRGEAD BANKING\n";
    cout << "==========================\n";

    Investment investment;
    investment.gatherInput();
    investment.displayInvestmentSummary();

    cout << "\nPress enter to continue...";
    cin.get(); // Wait for Enter

    investment.generateReports();

    return 0;
}
