#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

class AgriChainManager {
private:
    string batchID;
    string cropType;
    int quantity;        // kg
    string status;       // Farm, Warehouse, or Delivered
    bool qualityPassed;

public:
    AgriChainManager(string id, string crop, int qty) {
        batchID = id;
        cropType = crop;
        quantity = qty;
        status = "FARM (Production)";
        qualityPassed = false;
    }

    // STAGE 1: Production (Your requested features)
    void runProduction() {
        cout << "\n[1/3] PRODUCTION PHASE STARTING..." << endl;
        cout << ">> Preparing land and planting " << quantity << " seeds..." << endl;
        Sleep(1000);
        cout << ">> Irrigation and weeding cycles complete." << endl;
        status = "HARVESTED (Processing)";
        cout << "[OK] Batch harvested and moved to processing site." << endl;
    }

    // STAGE 2: Quality Control (Supply Chain Essential)
    void qualityCheck() {
        if (status == "FARM (Production)") {
            cout << "[ERROR] Cannot check quality before harvest!" << endl;
            return;
        }
        cout << "\n[2/3] QUALITY ASSURANCE CHECK..." << endl;
        Sleep(1000);
        qualityPassed = true; 
        status = "WAREHOUSE (Storage)";
        cout << "[OK] Grade A Quality confirmed. Logged in Digital Ledger." << endl;
    }

    // STAGE 3: Distribution (The "Supply Chain" Part)
    void distribute(string destination) {
        if (!qualityPassed) {
            cout << "[ERROR] Quality check failed or not performed!" << endl;
            return;
        }
        cout << "\n[3/3] DISTRIBUTION & LOGISTICS..." << endl;
        cout << ">> Loading trucks for " << destination << "..." << endl;
        Sleep(1000);
        status = "DELIVERED to " + destination;
        cout << "[SUCCESS] Batch " << batchID << " has reached the buyer." << endl;
    }

    void showGlobalDashboard() {
        cout << "\n==========================================" << endl;
        cout << "      AGRI-CHAIN SCM TRACKER v3.0" << endl;
        cout << "==========================================" << endl;
        cout << " BATCH ID   : " << batchID << endl;
        cout << " CROP TYPE  : " << cropType << endl;
        cout << " QUANTITY   : " << quantity << " kg" << endl;
        cout << " CURRENT LOC: " << status << endl;
        cout << " QC STATUS  : " << (qualityPassed ? "CERTIFIED" : "PENDING") << endl;
        cout << "==========================================" << endl;
    }
};

int main() {
    AgriChainManager myBatch("BATCH-2026-NAK", "Maize", 5000);

    int choice;
    string buyer;

    while (true) {
        myBatch.showGlobalDashboard();
        cout << "\nSelect Supply Chain Action:" << endl;
        cout << "1. Run Farm Production (Land/Irrigation/Harvest)" << endl;
        cout << "2. Perform Quality Check (Logistics Prep)" << endl;
        cout << "3. Dispatch to Buyer (Distribution)" << endl;
        cout << "4. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        if (choice == 4) break;

        switch (choice) {
            case 1: myBatch.runProduction(); break;
            case 2: myBatch.qualityCheck(); break;
            case 3: 
                cout << "Enter Buyer Name (e.g. Juja-Millers): ";
                cin >> buyer;
                myBatch.distribute(buyer); 
                break;
            default: cout << "Invalid Selection!" << endl;
        }
        cout << "\nPress any key to continue...";
        system("pause > nul");
        system("cls");
    }

    return 0;
}
