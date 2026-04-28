#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include <windows.h>

// INTERNAL WORKING CONSTANTS
#define MAX_TRANSACTIONS 400
#define FILENAME "budget_tracker_data.txt"
#define TAX_RATE 0.15

// COLOR ESCAPE SEQUENCES (For utilizing max CLI interface)
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"

struct Transaction
{
    char type[10];
    char category[30];
    char description[50];
    float amount;
    char date[12];
};

struct Transaction transactions[MAX_TRANSACTIONS];
int count = 0;
float budgetLimit = 0.0;
float currentBalance = 0.0;

// Function Declarations

// Functions for Input Buffers and Animations
void clearLine();
void processingAnimation(int cycles);
void trimNewline(char *str);
void clearInputBuffer();

// Calculation Functions
float getTotalExpense();
void setBudgetLimit();
void addTransaction();
void viewTransactions();
void categoryAnalysis();
void showSummary();
void searchByDate();
void searchByCategory();
void largestAndSmallestExpense();
void calculateAndShowTax();

// Filing Functions
void saveToFile();
void loadFromFile();

// Main Menu Function

int main()
{
    int choice;
    loadFromFile();

    printf(GREEN "=== Welcome to Budget Tracker ===\n\n" RESET);
    printf(BLUE "INSTRUCTIONS: Data is saved permanently only if you select Option 9 (Save & Exit).\n\n" RESET);
    setBudgetLimit();

    do {
        printf(CYAN "\n========== MAIN MENU ==========\n" RESET);
        printf("1. Add Transaction\n");
        printf("2. View All Transactions\n");
        printf("3. Show Category-wise Analysis\n");
        printf("4. Show Basic Financial Summary (Income vs. Expense)\n");
        printf("5. Search Transaction by Date\n");
        printf("6. Search Transaction by Category\n");
        printf("7. Search Largest & Smallest Expense\n");
        printf("8. Show Summary & Tax Calculation\n");
        printf("9. Save & Exit\n\n");
        printf(YELLOW "Enter Menu Choice: " RESET);
        
        if (scanf("%d", &choice) != 1) {
            choice = 0;
        }
        clearInputBuffer();

        switch (choice)
        {
            case 1:
                addTransaction();
                break;
            
            case 2:
                viewTransactions();
                break;
            
            case 3:
                categoryAnalysis();
                break;
            
            case 4:
                showSummary();
                break;
            
            case 5:
                searchByDate();
                break;
            
            case 6:
                searchByCategory();
                break;
            
            case 7:
                largestAndSmallestExpense();
                break;
            
            case 8:
                calculateAndShowTax();
                break;
            
            case 9:
            	processingAnimation(20);
                saveToFile();
                printf(GREEN "\nData saved successfully. Exiting...\n" RESET);
                break;
            
            default:
                printf(RED "\nInvalid Option, Please try again.\n" RESET);
        }
        
    } while (choice != 9);

    return 0;
}

// Indirect Recursive Functions (For Utility Purposes)

void trimNewline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

float getTotalExpense()
{	
	int i;
    float expense = 0;
    for (i = 0; i < count; i++)
    {
        if (strcasecmp(transactions[i].type, "Expense") == 0)
            expense += transactions[i].amount;
    }
    return expense;
}

void setBudgetLimit()
{
    printf(YELLOW "Enter your initial budget limit (This can be your spending limit OR starting cash): " RESET);
    
    if (scanf("%f", &budgetLimit) != 1)
    {
        budgetLimit = 0.0;
    }
    
    currentBalance = budgetLimit;
    clearInputBuffer();
    printf(GREEN "Starting balance and limit set to %.2f.\n" RESET, currentBalance);

}

// Menu Option's Working Functions

void addTransaction()
{
    if (count >= MAX_TRANSACTIONS)
    {
        printf(RED "\nTransaction list is full!\n" RESET);
        return;
    }

    struct Transaction t;
    
    printf("\nEnter type (Income/Expense): ");
    fgets(t.type, sizeof(t.type), stdin);
    trimNewline(t.type);

    printf("Transaction Categories\nFor Income (e.g:Salary, Bonus, Profits)\nFor Expense(e.g: Food, Rent, Transport, Utilities): ");
    fgets(t.category, sizeof(t.category), stdin);
    trimNewline(t.category);

    printf("Enter description: ");
    fgets(t.description, sizeof(t.description), stdin);
    trimNewline(t.description);

    printf("Enter amount: ");
    if (scanf("%f", &t.amount) != 1) {
        printf(RED "Invalid amount entered. Transaction cancelled.\n" RESET);
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    printf("Enter date (DD/MM/YYYY): ");
    fgets(t.date, sizeof(t.date), stdin);
    trimNewline(t.date);

    transactions[count++] = t;
	
	processingAnimation(20);
	
    if (strcasecmp(t.type, "Income") == 0)
    {
        currentBalance += t.amount;
        printf(GREEN "\nTransaction added successfully! Current Balance: %.2f\n" RESET, currentBalance);
    }
    else if (strcasecmp(t.type, "Expense") == 0)
    {
        currentBalance -= t.amount;
        printf(RED "\nTransaction added successfully! Current Balance: %.2f\n" RESET, currentBalance);
    }
    else
    {
        printf(GREEN "\nTransaction added successfully!\n" RESET);
    }

    float totalExpense = getTotalExpense();
    if (totalExpense > budgetLimit)
    {
        printf(RED "\nALERT!: You have exceeded your overall budget limit of %.2f!\n" RESET, budgetLimit);
    }
}

void viewTransactions()
{
	int i;
	
	processingAnimation(20);
	
    if (count == 0)
    {
        printf(RED "\nNo transactions found!\n" RESET);
        return;
    }

    printf(BLUE "\n%-10s %-12s %-15s %-10s %-12s\n" RESET, "Type", "Category", "Description", "Amount", "Date");
    printf("-------------------------------------------------------------------\n");

    for (i = 0; i < count; i++)
    {
        if (strcasecmp(transactions[i].type, "Income") == 0)
            printf(GREEN);
        else
            printf(RED);

        printf("%-10s %-12s %-15s %-10.2f %-12s\n" RESET,
               transactions[i].type, transactions[i].category,
               transactions[i].description, transactions[i].amount, transactions[i].date);
    }
}

void categoryAnalysis()
{
	int i;
	
	processingAnimation(20);
	
    if (count == 0)
    {
        printf(RED "\nNo data to analyze!\n" RESET);
        return;
    }

    float food = 0, rent = 0, transport = 0, utilities = 0, others = 0;

    for (i = 0; i < count; i++)
    {
        if (strcasecmp(transactions[i].type, "Expense") == 0)
        {
            if (strcasecmp(transactions[i].category, "Food") == 0)
                food += transactions[i].amount;
            else if (strcasecmp(transactions[i].category, "Rent") == 0)
                rent += transactions[i].amount;
            else if (strcasecmp(transactions[i].category, "Transport") == 0)
                transport += transactions[i].amount;
            else if (strcasecmp(transactions[i].category, "Utilities") == 0)
                utilities += transactions[i].amount;
            else
                others += transactions[i].amount;
        }
    }

    printf(MAGENTA "\n=== Category-wise Expense Summary ===\n" RESET);
    printf("Food:        %.2f\n", food);
    printf("Rent:        %.2f\n", rent);
    printf("Transport:   %.2f\n", transport);
    printf("Utilities:   %.2f\n", utilities);
    printf("Others:      %.2f\n", others);
}

void showSummary()
{
	int i;
	
	processingAnimation(20);
	
    float income = 0, expense = 0;

    for (i = 0; i < count; i++)
    {
        if (strcasecmp(transactions[i].type, "Income") == 0)
            income += transactions[i].amount;
        else if (strcasecmp(transactions[i].type, "Expense") == 0)
            expense += transactions[i].amount;
    }

    printf(CYAN "\n=== Basic Financial Summary ===\n" RESET);
    printf("Total Income:  %.2f\n", income);
    printf("Total Expense: %.2f\n", expense);
    printf("Net Balance:   %.2f\n", income - expense);
}

void searchByDate()
{
	int i;
    if (count == 0)
    {
        printf(RED "\nNo records available!\n" RESET);
        return;
    }

    char targetDate[12];
    printf(YELLOW "Enter date to search (DD/MM/YYYY): " RESET);
    
    fgets(targetDate, sizeof(targetDate), stdin);
    trimNewline(targetDate);

	processingAnimation(20);

    int found = 0;
    printf(BLUE "\nResults for date: %s\n" RESET, targetDate);
    printf("%-10s %-12s %-15s %-10s %-12s\n", "Type", "Category", "Description", "Amount", "Date");
    printf("-------------------------------------------------------------------\n");

    for (i = 0; i < count; i++)
    {
        if (strcmp(transactions[i].date, targetDate) == 0)
        {
            found = 1;
            printf("%-10s %-12s %-15s %-10.2f %-12s\n",
                   transactions[i].type, transactions[i].category,
                   transactions[i].description, transactions[i].amount, transactions[i].date);
        }
    }

    if (!found)
    {
        printf(RED "\nNo transactions found on that date.\n" RESET);
    }
}

void searchByCategory()
{
	int i;
    if (count == 0)
    {
        printf(RED "\nNo records available!\n" RESET);
        return;
    }

    char targetCategory[30];
    printf(YELLOW "Enter category to search: " RESET);
    
    fgets(targetCategory, sizeof(targetCategory), stdin);
    trimNewline(targetCategory);
    
    processingAnimation(20);

    int found = 0;
    printf(BLUE "\nResults for category: %s\n" RESET, targetCategory);
    printf("%-10s %-12s %-15s %-10s %-12s\n", "Type", "Category", "Description", "Amount", "Date");
    printf("-------------------------------------------------------------------\n");

    for (i = 0; i < count; i++)
    {
        if (strcasecmp(transactions[i].category, targetCategory) == 0)
        {
            found = 1;
            printf("%-10s %-12s %-15s %-10.2f %-12s\n",
                   transactions[i].type, transactions[i].category,
                   transactions[i].description, transactions[i].amount, transactions[i].date);
        }
    }

    if (!found) printf(RED "\nNo transactions found for that category.\n" RESET);
}

void largestAndSmallestExpense()
{
	int i;
	
	processingAnimation(20);
	
    if (count == 0)
    {
        printf(RED "\nNo transactions recorded!\n" RESET);
        return;
    }

    int largestIndex = -1, smallestIndex = -1;
    float largest = -1, smallest = 1e9;

    for (i = 0; i < count; i++)
    {
        if (strcasecmp(transactions[i].type, "Expense") == 0)
        {
            if (transactions[i].amount > largest)
            {
                largest = transactions[i].amount;
                largestIndex = i;
            }
            if (transactions[i].amount < smallest)
            {
                smallest = transactions[i].amount;
                smallestIndex = i;
            }
        }
    }

    if (largestIndex == -1)
    {
        printf(YELLOW "\nNo expense transactions found.\n" RESET);
        return;
    }

    printf(MAGENTA "\n=== Expense Analysis ===\n" RESET);
    printf(GREEN "\nLargest Expense:\n" RESET);
    printf("%s - %s - %.2f on %s\n",
           transactions[largestIndex].category,
           transactions[largestIndex].description,
           transactions[largestIndex].amount,
           transactions[largestIndex].date);

    printf(RED "\nSmallest Expense:\n" RESET);
    printf("%s - %s - %.2f on %s\n",
           transactions[smallestIndex].category,
           transactions[smallestIndex].description,
           transactions[smallestIndex].amount,
           transactions[smallestIndex].date);
}

void calculateAndShowTax()
{
	int i;
    float income = 0;
    float expense = 0;

    for (i = 0; i < count; i++)
    {
        if (strcasecmp(transactions[i].type, "Income") == 0)
            income += transactions[i].amount;
        else if (strcasecmp(transactions[i].type, "Expense") == 0)
            expense += transactions[i].amount;
    }

    float taxAmount = expense * TAX_RATE;
    float expensePlusTax = expense + taxAmount;
    float netBalance = income - expensePlusTax;
    
    processingAnimation(20);

    printf(CYAN "\n=== Financial Summary & Tax ===\n" RESET);
    printf("Total Income:          %.2f\n", income);
    printf("Total Expense:         %.2f\n", expense);
    printf(YELLOW "TAX (%.0f%% on Expense): " RESET "   %.2f\n", TAX_RATE * 100, taxAmount);
    printf(RED "Total Outflow (Exp + Tax): %.2f\n" RESET, expensePlusTax);
    printf("---------------------------------------\n");

    if (netBalance >= 0)
    {
        printf(GREEN "Net Profit/Loss:       %.2f\n" RESET, netBalance);
    } else {
        printf(RED "Net Profit/Loss:       %.2f (Deficit)\n" RESET, netBalance);
    }
    
    printf(BLUE "Your Running Cash Balance: %.2f\n" RESET, currentBalance);
}

// Local Filing For The User's Convinenece

void saveToFile()
{
	
	int i;
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL)
    {
        printf(RED "Error saving data!\n" RESET);
        return;
    }

    for (i = 0; i < count; i++)
    {
        fprintf(fp, "%s,%s,%s,%.2f,%s\n",
                 transactions[i].type,
                 transactions[i].category,
                 transactions[i].description,
                 transactions[i].amount,
                 transactions[i].date);
    }
    fclose(fp);
}

void loadFromFile()
{
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) return;

    while (fscanf(fp, "%[^,],%[^,],%[^,],%f,%[^\n]\n",
                 transactions[count].type,
                 transactions[count].category,
                 transactions[count].description,
                 &transactions[count].amount,
                 transactions[count].date) == 5)
    {
        count++;
    }

    fclose(fp);
}

// Animations

void clearLine() 
{
    printf("\r\033[K");   // move to start + clear line
}

void processingAnimation(int cycles) 
{
	int i, j;
    for (i = 0; i < cycles; i++) {

        clearLine();
        printf(CYAN "Processing" RESET);

        int dots = i % 4;   // cycles 0,1,2,3

        for ( j = 0; j < dots; j++)
            printf(".");

        fflush(stdout);

        Sleep(300);  // 300 ms
    }

    clearLine();
    printf(GREEN "Done!\n" RESET);
}
