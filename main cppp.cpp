// ============================================================
//  ICS 2276: Computer Programming II
//  Agricultural Supply Chain System
//  Milestone 2: Control Logic & Object Introduction
//
//  CHANGES FROM MILESTONE 1:
//  - Global variables encapsulated into Product, Supplier,
//    and Warehouse classes (OOP introduction)
//  - Order class added to model supply chain decisions
//  - Decision-making system: order approval logic
//  - Loop-based simulation cycle with structured menu
//  - Robust input validation on all user inputs
//  - Multiple products now supported via class instances
// ============================================================

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


// ============================================================
//  CLASS: Product
//  Encapsulates all product state and behaviour
// ============================================================
class Product {
private:
    int    productID;
    string name;
    string category;
    double unitPrice;      // KES per kg
    int    quantityInStock;
    int    reorderLevel;

public:
    // --- Constructor ---
    Product(int id, string n, string cat, double price, int qty, int reorder)
        : productID(id), name(n), category(cat),
          unitPrice(price), quantityInStock(qty), reorderLevel(reorder) {}

    // --- Getters ---
    int    getID()           const { return productID; }
    string getName()         const { return name; }
    string getCategory()     const { return category; }
    double getUnitPrice()    const { return unitPrice; }
    int    getQuantity()     const { return quantityInStock; }
    int    getReorderLevel() const { return reorderLevel; }

    // --- Setters ---
    void setUnitPrice(double price) { unitPrice = price; }

    // --- Computed Metrics ---
    double getTotalValue()     const { return quantityInStock * unitPrice; }
    bool   isReorderNeeded()   const { return quantityInStock <= reorderLevel; }

    // --- Stock Operations ---
    bool addStock(int qty) {
        if (qty <= 0) return false;
        quantityInStock += qty;
        return true;
    }

    bool dispatchStock(int qty) {
        if (qty <= 0 || qty > quantityInStock) return false;
        quantityInStock -= qty;
        return true;
    }

    // --- Display ---
    void display() const {
        cout << fixed << setprecision(2);
        cout << "    ID           : " << productID       << "\n";
        cout << "    Name         : " << name            << "\n";
        cout << "    Category     : " << category        << "\n";
        cout << "    Unit Price   : KES " << unitPrice   << " / kg\n";
        cout << "    In Stock     : " << quantityInStock << " kg\n";
        cout << "    Reorder Level: " << reorderLevel    << " kg\n";
        cout << "    Total Value  : KES " << getTotalValue() << "\n";
        cout << "    Reorder Alert: " << (isReorderNeeded() ? "*** YES ***" : "No") << "\n";
    }
};


// ============================================================
//  CLASS: Supplier
//  Encapsulates supplier information
// ============================================================
class Supplier {
private:
    int    supplierID;
    string name;
    string location;
    string contact;
    double reliabilityRating;  // 0.0 - 10.0

public:
    // --- Constructor ---
    Supplier(int id, string n, string loc, string con, double rating)
        : supplierID(id), name(n), location(loc),
          contact(con), reliabilityRating(rating) {}

    // --- Getters ---
    int    getID()     const { return supplierID; }
    string getName()   const { return name; }
    string getLocation() const { return location; }
    double getRating() const { return reliabilityRating; }

    // --- Decision: Is supplier reliable enough to place order? ---
    bool isReliable() const { return reliabilityRating >= 7.0; }

    // --- Display ---
    void display() const {
        cout << "    ID         : " << supplierID        << "\n";
        cout << "    Name       : " << name              << "\n";
        cout << "    Location   : " << location          << "\n";
        cout << "    Contact    : " << contact           << "\n";
        cout << "    Reliability: " << reliabilityRating << "/10 "
             << (isReliable() ? "[APPROVED]" : "[UNRELIABLE]") << "\n";
    }
};


// ============================================================
//  CLASS: Warehouse
//  Encapsulates warehouse capacity management
// ============================================================
class Warehouse {
private:
    int    warehouseID;
    string location;
    int    capacity;     // max kg

public:
    // --- Constructor ---
    Warehouse(int id, string loc, int cap)
        : warehouseID(id), location(loc), capacity(cap) {}

    // --- Getters ---
    int    getID()       const { return warehouseID; }
    string getLocation() const { return location; }
    int    getCapacity() const { return capacity; }

    // --- Decision Logic ---
    bool canAccommodate(int currentStock, int incoming) const {
        return (currentStock + incoming) <= capacity;
    }

    int availableSpace(int currentStock) const {
        return capacity - currentStock;
    }

    double getUsagePercentage(int currentStock) const {
        return (static_cast<double>(currentStock) / capacity) * 100.0;
    }

    // --- Display ---
    void display(int currentStock) const {
        cout << fixed << setprecision(2);
        cout << "    ID         : " << warehouseID << "\n";
        cout << "    Location   : " << location    << "\n";
        cout << "    Capacity   : " << capacity    << " kg\n";
        cout << "    In Use     : " << currentStock << " kg ("
             << getUsagePercentage(currentStock) << "%)\n";
        cout << "    Free Space : " << availableSpace(currentStock) << " kg\n";
    }
};


// ============================================================
//  CLASS: Order
//  Models a supply chain order with approval decision logic
// ============================================================
class Order {
public:
    // Order status as named constants
    static const int PENDING  = 0;
    static const int APPROVED = 1;
    static const int REJECTED = 2;

private:
    int    orderID;
    int    productID;
    int    quantity;
    double totalCost;
    int    status;        // PENDING / APPROVED / REJECTED
    string reason;        // reason for rejection if any

public:
    // --- Constructor ---
    Order(int oid, int pid, int qty, double unitPrice)
        : orderID(oid), productID(pid), quantity(qty),
          totalCost(qty * unitPrice), status(PENDING), reason("") {}

    // --- Getters ---
    int    getID()        const { return orderID; }
    int    getQuantity()  const { return quantity; }
    double getTotalCost() const { return totalCost; }
    int    getStatus()    const { return status; }
    string getReason()    const { return reason; }

    string getStatusLabel() const {
        if (status == APPROVED) return "APPROVED";
        if (status == REJECTED) return "REJECTED";
        return "PENDING";
    }

    // --- Decision Logic: Approve or Reject order ---
    void evaluate(const Supplier& supplier, const Warehouse& warehouse, int currentStock) {
        // Rule 1: Supplier must be reliable
        if (!supplier.isReliable()) {
            status = REJECTED;
            reason = "Supplier reliability rating below threshold (7.0)";
            return;
        }
        // Rule 2: Warehouse must have enough space
        if (!warehouse.canAccommodate(currentStock, quantity)) {
            status = REJECTED;
            reason = "Insufficient warehouse space for this order";
            return;
        }
        // Rule 3: Quantity must be positive
        if (quantity <= 0) {
            status = REJECTED;
            reason = "Order quantity must be greater than zero";
            return;
        }
        // All checks passed
        status = APPROVED;
        reason = "All checks passed";
    }

    // --- Display ---
    void display() const {
        cout << fixed << setprecision(2);
        cout << "    Order ID   : " << orderID          << "\n";
        cout << "    Product ID : " << productID        << "\n";
        cout << "    Quantity   : " << quantity         << " kg\n";
        cout << "    Total Cost : KES " << totalCost    << "\n";
        cout << "    Status     : " << getStatusLabel() << "\n";
        cout << "    Reason     : " << reason           << "\n";
    }
};


// ============================================================
//  INPUT VALIDATION HELPERS
// ============================================================
int getValidInt(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < minVal || value > maxVal) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [ERROR] Please enter a number between "
                 << minVal << " and " << maxVal << ".\n";
        } else {
            cin.ignore(1000, '\n');
            return value;
        }
    }
}

double getValidDouble(const string& prompt, double minVal) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < minVal) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [ERROR] Please enter a valid number >= " << minVal << ".\n";
        } else {
            cin.ignore(1000, '\n');
            return value;
        }
    }
}


// ============================================================
//  DISPLAY HELPERS
// ============================================================
void displayBanner() {
    cout << "============================================================\n";
    cout << "     AGRICULTURAL SUPPLY CHAIN SYSTEM v2.0\n";
    cout << "     ICS 2276 | Milestone 2: Control Logic & OOP\n";
    cout << "============================================================\n\n";
}

void displayDashboard(const Product& p, const Supplier& s, const Warehouse& w) {
    cout << "\n============================================================\n";
    cout << "                    SYSTEM DASHBOARD\n";
    cout << "============================================================\n";

    cout << "\n  [PRODUCT]\n";
    p.display();

    cout << "\n  [SUPPLIER]\n";
    s.display();

    cout << "\n  [WAREHOUSE]\n";
    w.display(p.getQuantity());

    cout << "============================================================\n";
}

void displayMenu() {
    cout << "\n---- MAIN MENU ----------------------------------------\n";
    cout << "  1. Add stock (receive shipment)\n";
    cout << "  2. Dispatch stock (fulfill order)\n";
    cout << "  3. Place a new supply order\n";
    cout << "  4. Update unit price\n";
    cout << "  5. View dashboard\n";
    cout << "  6. Exit\n";
    cout << "-------------------------------------------------------\n";
}


// ============================================================
//  SIMULATION LOOP
// ============================================================
void runSimulation(Product& product, Supplier& supplier, Warehouse& warehouse) {
    bool running  = true;
    int  orderCounter = 2001;  // auto-incrementing order IDs

    cout << "\n[SIM] Simulation cycle started. Awaiting user input...\n";

    while (running) {
        displayMenu();
        int choice = getValidInt("  Enter choice: ", 1, 6);

        if (choice == 1) {
            // ---- Add Stock ----
            int qty = getValidInt("  Enter quantity to add (kg): ", 1, 99999);

            if (!warehouse.canAccommodate(product.getQuantity(), qty)) {
                cout << "  [WARNING] Cannot add " << qty << " kg — exceeds warehouse capacity.\n";
                cout << "  Available space: " << warehouse.availableSpace(product.getQuantity()) << " kg\n";
            } else {
                product.addStock(qty);
                cout << "  [OK] Added " << qty << " kg. New stock: " << product.getQuantity() << " kg\n";
            }

        } else if (choice == 2) {
            // ---- Dispatch Stock ----
            int qty = getValidInt("  Enter quantity to dispatch (kg): ", 1, 99999);

            if (!product.dispatchStock(qty)) {
                cout << "  [ERROR] Insufficient stock! Available: " << product.getQuantity() << " kg\n";
            } else {
                cout << "  [OK] Dispatched " << qty << " kg. Remaining: " << product.getQuantity() << " kg\n";
                if (product.isReorderNeeded()) {
                    cout << "  *** REORDER ALERT: Stock has dropped to reorder level! ***\n";
                    cout << "  Consider placing a new order (option 3).\n";
                }
            }

        } else if (choice == 3) {
            // ---- Place New Supply Order ----
            cout << "\n  [ORDER] Creating new supply order...\n";
            int qty = getValidInt("  Enter order quantity (kg): ", 1, 99999);

            Order order(orderCounter++, product.getID(), qty, product.getUnitPrice());

            // Decision logic: evaluate order
            order.evaluate(supplier, warehouse, product.getQuantity());

            cout << "\n  [ORDER RESULT]\n";
            order.display();

            // If approved, add stock automatically
            if (order.getStatus() == Order::APPROVED) {
                product.addStock(qty);
                cout << "  [OK] Stock updated after approved order. New stock: "
                     << product.getQuantity() << " kg\n";
            }

        } else if (choice == 4) {
            // ---- Update Unit Price ----
            double newPrice = getValidDouble("  Enter new unit price (KES): ", 0.01);
            product.setUnitPrice(newPrice);
            cout << "  [OK] Unit price updated to KES " << fixed << setprecision(2) << newPrice << "\n";

        } else if (choice == 5) {
            // ---- Dashboard ----
            displayDashboard(product, supplier, warehouse);

        } else if (choice == 6) {
            // ---- Exit ----
            running = false;
        }
    }
}


// ============================================================
//  MAIN ENTRY POINT
// ============================================================
int main() {
    displayBanner();

    // --- Initialize objects (evolved from M1 global variables) ---
    Product   product(1001, "Maize", "Grain", 45.50, 320, 100);
    Supplier  supplier(501, "Rift Valley Farms Ltd", "Nakuru, Kenya", "+254700000001", 8.5);
    Warehouse warehouse(301, "Nakuru Central Store", 1000);

    cout << "[INIT] System initialized with Product, Supplier, and Warehouse objects.\n";

    // --- Show initial dashboard ---
    displayDashboard(product, supplier, warehouse);

    // --- Run simulation loop ---
    runSimulation(product, supplier, warehouse);

    cout << "\n[SYSTEM] Shutting down Agricultural Supply Chain System. Goodbye!\n";
    return 0;
}
