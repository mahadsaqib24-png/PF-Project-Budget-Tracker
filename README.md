# Budget Tracker

A personal finance management console application built in **C** as a Programming Fundamentals final project. The program lets users log income and expense transactions, analyse spending by category, calculate tax, and persist data between sessions — all through a coloured terminal interface.

---

## Features

- Add income and expense transactions with category, description, amount, and date
- View all transactions in a formatted, colour-coded table
- Category-wise expense breakdown (Food, Rent, Transport, Utilities, Others)
- Basic financial summary — total income vs. total expense vs. net balance
- Search transactions by date or by category
- Find the largest and smallest expense
- Tax calculation (15% on total expenses) with full financial summary
- Budget limit alert — warns when total spending exceeds the set limit
- Persistent file storage — data saved to `budget_tracker_data.txt` on exit and reloaded on the next run

---

## How to Compile and Run

### Windows (Dev-C++ / MinGW)

Open the `.c` file in Dev-C++ and press **F11** to compile and run, or from the terminal:

```bash
gcc budget_tracker.c -o budget_tracker.exe
budget_tracker.exe
```

### Linux / Mac

```bash
gcc budget_tracker.c -o budget_tracker
./budget_tracker
```

> **Note for Linux/Mac:** The code uses `<windows.h>` for `Sleep()` and `<strings.h>` for `strcasecmp()`. On Linux, remove `#include <windows.h>` and replace `Sleep(300)` with `usleep(300000)`. `strcasecmp()` is available natively on Linux via `<strings.h>`.

---

## Usage

On launch, you will be asked to set a **budget limit** — this is your starting cash or spending cap. The main menu then gives you 9 options:

```
========== MAIN MENU ==========
1. Add Transaction
2. View All Transactions
3. Show Category-wise Analysis
4. Show Basic Financial Summary (Income vs. Expense)
5. Search Transaction by Date
6. Search Transaction by Category
7. Search Largest & Smallest Expense
8. Show Summary & Tax Calculation
9. Save & Exit
```

> Data is only written to disk when you select **Option 9 (Save & Exit)**. Closing the window without saving will lose any unsaved transactions.

---

## Data Storage

Transactions are saved to `budget_tracker_data.txt` in the same directory as the executable. The format is one transaction per line, comma-separated:

```
Expense,Food,Groceries,45.50,12/04/2025
Income,Salary,Monthly pay,50000.00,01/04/2025
```

The file is loaded automatically every time the program starts.

---

## Tax Calculation

```
Tax Amount     =  Total Expenses × 15%
Total Outflow  =  Total Expenses + Tax Amount
Net Balance    =  Total Income - Total Outflow
```

A positive net balance is shown in green. A deficit is shown in red.

---

## Project Structure

```
├── budget_tracker.c              Single-file C source
└── budget_tracker_data.txt       Auto-created on first Save & Exit
```

---

## Authors

**Mahad Saqib** — 25K-0509  
**Arsalan Ahmed** — 25K-0754  

Programming Fundamentals Final Project — FAST-NUCES Karachi
