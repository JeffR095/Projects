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

/*
* This project consisted of calculating the impact of compound interest over a set period of time. 
* The user is asked to place an initial deposit. Optionally, a monthly deposit. The user will choose the interest rate 
* percentage along with defining the time period in years. Afterwards, the program will output the user input followed 
* by the projected growth of the investment without including a monthly deposit in a report called YEAR-END REPORT 
* (NO MONTHLY DEPOSITS). After the YEAR-END REPORT (WITH MONTHLY DEPOSITS) is displayed, the same data from the report 
* above will be displayed if the user previously chose not to add a monthly deposit. Lastly, the MONTHLY BREAKDOWN report 
* shows the growth of the account on a month-by-month basis. My code is easy to follow, and the naming of the members is
* self-explanatory. A third party should be able to comprehend what I am trying to accomplish. I was consistent with my 
* style, and I provided comments which provided insight as to what I was trying to accomplish. I can make my code
* more condensed by re-organizing it in such a way where I include a header file containing the member declarations, 
* while the “.cpp” file includes the definitions. I should have used dynamic memory allocation to improve the efficiency 
* of the program by reutilizing members and deleting the space they occupy once the purpose has been served. I can potentially
* add try/catch to reduce the number of lines I need for validation. Initially, I struggled writing the code for the formula 
* for calculating deposits, because I was not obtaining the output I needed. To correct this, I wrote the calculations by hand,
* this enabled me to visualize what I needed to correct. In my case, I was missing a set of parentheses. The problem-solving
* skills gained from executing this project have taught me that it is important to keep an open mind when it comes to tackling
* a problem because at times the basics are all we need to for overcoming them. Patience is key and asking for help when deemed 
* necessary can help amplify our insight. Finally, following the industry’s best practices, one ensures the success of the program.
*/    
