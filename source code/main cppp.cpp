// ============================================================
//  ICS 2276: Computer Programming II
//  Agricultural Supply Chain System
//  Milestone 1: Computational Foundations
// ============================================================

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// ============================================================
//  SYSTEM STATE VARIABLES (Real-world to variable mapping)
// ============================================================

// --- Product Information ---
string productName;
int    productID;
string productCategory;   // e.g., "Grain", "Vegetable", "Fruit"
double unitPrice;         // price per unit (KES)

// --- Inventory / Warehouse ---
int    quantityInStock;   // current units available
int    warehouseCapacity; // max units warehouse can hold
int    reorderLevel;      // minimum stock before reorder is triggered

// --- Supplier Information ---
string supplierName;
string supplierLocation;

// --- Computed / Derived Variables ---
double totalInventoryValue;   // quantityInStock * unitPrice
double stockPercentage;       // (quantityInStock / warehouseCapacity) * 100
bool   reorderNeeded;         // true if quantityInStock <= reorderLevel


// ============================================================
//  FUNCTION DECLARATIONS
// ============================================================
void  displayWelcomeBanner();
void  initializeSystem();
void  computeMetrics();
void  displayDashboard();
void  runSimulation();
void  displayMenu();


// ============================================================
//  MAIN ENTRY POINT
// ============================================================
int main() {
    displayWelcomeBanner();
    initializeSystem();
    computeMetrics();
    displayDashboard();
    runSimulation();

    cout << "\n[SYSTEM] Shutting down Agricultural Supply Chain System. Goodbye!\n";
    return 0;
}


// ============================================================
//  WELCOME BANNER
// ============================================================
void displayWelcomeBanner() {
    cout << "============================================================\n";
    cout << "     AGRICULTURAL SUPPLY CHAIN SYSTEM v1.0\n";
    cout << "     ICS 2276 | Milestone 1: Computational Foundations\n";
    cout << "============================================================\n\n";
}


// ============================================================
//  SYSTEM INITIALIZATION
//  Hardcoded initial state to simulate a real farm product
// ============================================================
void initializeSystem() {
    cout << "[INIT] Initializing system with default product data...\n\n";

    // Product
    productName      = "Maize";
    productID        = 1001;
    productCategory  = "Grain";
    unitPrice        = 45.50;   // KES per kg

    // Inventory
    quantityInStock  = 320;     // kg
    warehouseCapacity= 1000;    // kg
    reorderLevel     = 100;     // kg

    // Supplier
    supplierName     = "Rift Valley Farms Ltd";
    supplierLocation = "Nakuru, Kenya";
}


// ============================================================
//  COMPUTE METRICS
//  Basic arithmetic computations on system state
// ============================================================
void computeMetrics() {
    totalInventoryValue = quantityInStock * unitPrice;
    stockPercentage     = (static_cast<double>(quantityInStock) / warehouseCapacity) * 100.0;
    reorderNeeded       = (quantityInStock <= reorderLevel);
}


// ============================================================
//  DISPLAY DASHBOARD
//  Shows current system snapshot
// ============================================================
void displayDashboard() {
    cout << fixed << setprecision(2);

    cout << "============================================================\n";
    cout << "                   SYSTEM DASHBOARD\n";
    cout << "============================================================\n";

    cout << "\n  [PRODUCT]\n";
    cout << "    ID       : " << productID        << "\n";
    cout << "    Name     : " << productName      << "\n";
    cout << "    Category : " << productCategory  << "\n";
    cout << "    Unit Price: KES " << unitPrice   << " / kg\n";

    cout << "\n  [SUPPLIER]\n";
    cout << "    Name     : " << supplierName     << "\n";
    cout << "    Location : " << supplierLocation << "\n";

    cout << "\n  [WAREHOUSE / INVENTORY]\n";
    cout << "    Capacity         : " << warehouseCapacity << " kg\n";
    cout << "    Current Stock    : " << quantityInStock   << " kg\n";
    cout << "    Reorder Level    : " << reorderLevel      << " kg\n";
    cout << "    Stock Level      : " << stockPercentage   << "%\n";
    cout << "    Inventory Value  : KES " << totalInventoryValue << "\n";

    cout << "\n  [ALERTS]\n";
    if (reorderNeeded) {
        cout << "    *** REORDER ALERT: Stock is at or below reorder level! ***\n";
    } else {
        cout << "    Stock levels are sufficient. No reorder needed.\n";
    }

    cout << "============================================================\n\n";
}


// ============================================================
//  MENU
// ============================================================
void displayMenu() {
    cout << "\n---- MAIN MENU ----------------------------------------\n";
    cout << "  1. Add stock (receive new shipment)\n";
    cout << "  2. Dispatch stock (fulfill an order)\n";
    cout << "  3. Update unit price\n";
    cout << "  4. View dashboard\n";
    cout << "  5. Exit\n";
    cout << "-------------------------------------------------------\n";
    cout << "  Enter choice: ";
}


// ============================================================
//  SIMULATION LOOP
//  Simple control flow: conditionals and loops
// ============================================================
void runSimulation() {
    int    choice;
    int    quantity;
    double newPrice;
    bool   running = true;

    cout << "[SIM] Supply Chain Simulation Started.\n";

    while (running) {
        displayMenu();
        cin >> choice;

        // Input guard
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [ERROR] Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            // --- Add Stock ---
            cout << "  Enter quantity to add (kg): ";
            cin >> quantity;

            if (quantity <= 0) {
                cout << "  [ERROR] Quantity must be positive.\n";
            } else if (quantityInStock + quantity > warehouseCapacity) {
                cout << "  [WARNING] Addition exceeds warehouse capacity!\n";
                cout << "  Available space: " << (warehouseCapacity - quantityInStock) << " kg\n";
            } else {
                quantityInStock += quantity;
                computeMetrics();
                cout << "  [OK] Stock updated. New stock: " << quantityInStock << " kg\n";
            }

        } else if (choice == 2) {
            // --- Dispatch Stock ---
            cout << "  Enter quantity to dispatch (kg): ";
            cin >> quantity;

            if (quantity <= 0) {
                cout << "  [ERROR] Quantity must be positive.\n";
            } else if (quantity > quantityInStock) {
                cout << "  [ERROR] Insufficient stock! Available: " << quantityInStock << " kg\n";
            } else {
                quantityInStock -= quantity;
                computeMetrics();
                cout << "  [OK] Dispatched " << quantity << " kg. Remaining: " << quantityInStock << " kg\n";
                if (reorderNeeded) {
                    cout << "  *** REORDER ALERT: Stock has dropped to reorder level! ***\n";
                }
            }

        } else if (choice == 3) {
            // --- Update Price ---
            cout << "  Enter new unit price (KES): ";
            cin >> newPrice;

            if (newPrice <= 0) {
                cout << "  [ERROR] Price must be positive.\n";
            } else {
                unitPrice = newPrice;
                computeMetrics();
                cout << "  [OK] Unit price updated to KES " << fixed << setprecision(2) << unitPrice << "\n";
            }

        } else if (choice == 4) {
            // --- View Dashboard ---
            displayDashboard();

        } else if (choice == 5) {
            // --- Exit ---
            running = false;

        } else {
            cout << "  [ERROR] Invalid choice. Please select 1-5.\n";
        }
    }
}
