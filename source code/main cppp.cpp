#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h> // For Sleep() to simulate the flow of time

using namespace std;

// ============================================================
// STAGE 1: THE UPSTREAM (Production & Environment)
// Focus: Milestone 1 Requirements (State variables & Math)
// ============================================================
class FarmProduction {
private:
    string cropType;
    float temperature;
    float soilMoisture;
    bool landReady;
    bool inputsApplied; // Fertilizer/Pesticides

public:
    FarmProduction(string crop, float temp) 
        : cropType(crop), temperature(temp), soilMoisture(10.0), landReady(false), inputsApplied(false) {}

    void prepareLand() {
        cout << "\n[1. PRODUCTION] Preparing land plots for " << cropType << "..." << endl;
        Sleep(1000); landReady = true;
        cout << " >> Status: Land is Tilled and Ready." << endl;
    }

    void applyInputs() {
        if (!landReady) return;
        cout << "[2. INPUTS] Applying Fertilizer and seeds..." << endl;
        Sleep(1000); inputsApplied = true;
    }

    // Decision Logic: Irrigation based on Temperature (Milestone 2)
    void runClimateControl() {
        cout << "[3. CLIMATE] Monitoring Juja Sensors... Temp: " << temperature << "C" << endl;
        if (temperature > 29.0) {
            cout << " >> Action: High Heat! Automated Irrigation ACTIVE." << endl;
            soilMoisture = 85.0;
        } else {
            cout << " >> Action: Moderate Climate. Standard Irrigation applied." << endl;
            soilMoisture = 45.0;
        }
    }

    int harvest() {
        cout << "[4. HARVEST] Harvesting " << cropType << "..." << endl;
        Sleep(1500);
        // Math logic: Yield depends on moisture levels
        return (soilMoisture > 50) ? 2500 : 1200; 
    }
};

// ============================================================
// STAGE 2: THE DOWNSTREAM (Logistics & Distribution)
// Focus: Milestone 2 Requirements (Classes & Decision Systems)
// ============================================================
class SupplyChainLogistics {
private:
    int warehouseStock;
    double unitPrice;

public:
    SupplyChainLogistics(double price) : warehouseStock(0), unitPrice(price) {}

    // The "Flow" Point: Receiving the harvest
    void receiveShipment(int amount) {
        cout << "\n[5. LOGISTICS] Receiving truck from farm..." << endl;
        Sleep(1000);
        warehouseStock += amount;
        cout << " >> Inventory Updated: +" << amount << "kg." << endl;
    }

    // Decision System: Approve or Reject Orders
    void fulfillOrder(int requested) {
        cout << "\n[6. DISTRIBUTION] Evaluating Order for " << requested << "kg..." << endl;
        if (requested <= warehouseStock) {
            warehouseStock -= requested;
            cout << " >> Status: [ORDER APPROVED]. Dispatching to market." << endl;
        } else {
            cout << " >> Status: [REJECTED]. Reason: Insufficient Stock." << endl;
        }
    }

    void displayReport() {
        cout << "\n==========================================" << endl;
        cout << "      FINAL AGRI-CHAIN STATUS REPORT" << endl;
        cout << "==========================================" << endl;
        cout << " Warehouse Stock: " << warehouseStock << " kg" << endl;
        cout << " Current Value  : KES " << fixed << setprecision(2) << (warehouseStock * unitPrice) << endl;
        cout << "==========================================" << endl;
    }
};

// ============================================================
// MAIN: The Master Flow Controller
// ============================================================
int main() {
    cout << "--- AGRICULTURAL SUPPLY CHAIN SYSTEM START ---" << endl;

    // 1. Setup Phase
    FarmProduction jujaFarm("Maize", 32.5); // Warm climate
    SupplyChainLogistics nakuruHub(45.50); // Market pricing

    // 2. The Flow: Stage 1 (Production)
    jujaFarm.prepareLand();
    jujaFarm.applyInputs();
    jujaFarm.runClimateControl();
    int cropYield = jujaFarm.harvest();

    // 3. The Flow: Stage 2 (Logistics transition)
    nakuruHub.receiveShipment(cropYield);
    nakuruHub.displayReport();

    // 4. The Flow: Stage 3 (Market Distribution)
    int buyerDemand;
    cout << "\nEnter Buyer Order Quantity (kg): ";
    cin >> buyerDemand;
    nakuruHub.fulfillOrder(buyerDemand);
    
    nakuruHub.displayReport();

    cout << "\n[SYSTEM] Flow complete. Press any key to terminate simulation." << endl;
    system("pause > nul");
    return 0;
}
