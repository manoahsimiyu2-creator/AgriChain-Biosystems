#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h> // For Sleep() to make the "Loading" feel real

using namespace std;

class AgriChainSystem {
private:
    string batchID;
    float moisture;
    int approvedCount;
    int rejectedCount;
    int totalChecks;

public:
    AgriChainSystem(string id, float startMoisture) {
        batchID = id;
        moisture = startMoisture;
        approvedCount = 0;
        rejectedCount = 0;
        totalChecks = 0;
    }

    void showInitialization() {
        cout << ">> SYSTEM BOOT: AGRI-CHAIN BIOSYSTEMS v2.0" << endl;
        cout << ">> MAPPING REAL-WORLD SENSORS TO COMPUTATIONAL STATE..." << endl;
        Sleep(500);
        cout << ">> [OK] Mapping 'Soil Moisture' -> float moisture" << endl;
        cout << ">> [OK] Mapping 'Batch Identity' -> string batchID" << endl;
        cout << ">> [OK] Mapping 'Quality Logic' -> Encapsulated Class Methods" << endl;
        cout << ">> INITIALIZATION COMPLETE. STANDING BY.\n" << endl;
    }

    void runSimulation(int cycles) {
        cout << "--- STARTING QUALITY EVALUATION FOR: " << batchID << " ---\n" << endl;
        for (int i = 1; i <= cycles; i++) {
            totalChecks++;
            cout << "Cycle #" << i << " | Current Sensor Reading: " << fixed << setprecision(2) << moisture << "%" << endl;
            
            // Standard Quality Logic (Threshold 20% to 60%)
            if (moisture >= 20.0 && moisture <= 60.0) {
                cout << " >> STATUS: [APPROVED] - Product meets export standards." << endl;
                approvedCount++;
            } else {
                cout << " >> STATUS: [REJECTED] - Quality out of bounds. Adjusting..." << endl;
                rejectedCount++;
                // Simulated Bio-feedback loop
                if (moisture < 20.0) moisture += 12.5; 
                else moisture -= 8.5;
            }
            moisture -= 2.15; // Natural daily depletion simulation
            cout << "--------------------------------------------------------" << endl;
            Sleep(300); // Slows down the text so it looks professional
        }
    }

    void displayFinalDashboard() {
        float rate = (totalChecks > 0) ? ((float)approvedCount / totalChecks * 100) : 0;
        
        cout << "\n========================================================" << endl;
        cout << "             FINAL QUALITY REPORT SUMMARY               " << endl;
        cout << "========================================================" << endl;
        cout << "  BATCH IDENTIFIER : " << batchID << endl;
        cout << "  TOTAL INSPECTIONS: " << totalChecks << endl;
        cout << "  BATCHES APPROVED : " << approvedCount << " [GREEN LIGHT]" << endl;
        cout << "  BATCHES REJECTED : " << rejectedCount << " [HOLD]" << endl;
        cout << "  FINAL APPROVAL % : " << fixed << setprecision(1) << rate << "%" << endl;
        cout << "========================================================" << endl;
        cout << "  SYSTEM STATUS: " << (rate > 60 ? "STABLE" : "ACTION REQUIRED") << endl;
        cout << "========================================================\n" << endl;
    }
};

int main() {
    float startVal;
    cout << "ENTER INITIAL BIOSENSOR READING (Juja Farm Site A): ";
    cin >> startVal;
    cout << endl;

    AgriChainSystem mySystem("JUJA-WHEAT-001", startVal);

    mySystem.showInitialization();
    mySystem.runSimulation(6); // Running 6 cycles to match your dashboard
    mySystem.displayFinalDashboard();

    system("pause");
    return 0;
}
