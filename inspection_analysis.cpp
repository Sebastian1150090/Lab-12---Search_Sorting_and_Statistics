/*
 * Course: COEN 2210 - Introduction to Programming
 * Name: [Sebastian A. Feliciano]
 * Lab: 12 - Search, Sorting and Statistics
 * Description: []
 * Due Date: [11/9/26]
 */
#include <iostream> // Provides console input and output
#include <iomanip> // Provides table and decimal formatting
#include <string> // Provides string and getline
using namespace std;
 
struct Inspection {
    int id = 0;
    string area;
    double vibration = 0.0;
    bool isEmpty = true;
};
 
int findInspectionById(const Inspection inspections[], int capacity, int targetId);
int displayInspectionsByArea(const Inspection inspections[], int capacity, string targetArea);
int copyVibrations(const Inspection inspections[], int capacity, double values[]);
void selectionSort(double values[], int count);
double calculateMean(const double values[], int count);
double calculateMedian(const double sortedValues[], int count);
void displayModes(const double sortedValues[], int count);
void displayInspection(Inspection inspection);
 
int main() {
    const int CAPACITY = 6;
    Inspection inspections[CAPACITY] = {
        {101, "Assembly", 0.30, false},
        {104, "Power", 0.15, false},
        {109, "Assembly", 0.30, false},
        {115, "Thermal", 0.45, false},
        {118, "Power", 0.10, false},
        {123, "Assembly", 0.15, false}
    };
    double sortedVibrations[CAPACITY] = {};
    int menuChoice = 0;
 
    cout << fixed << setprecision(2);
    do {
        cout << "\nInspection Analysis\n";
        cout << "1. Find inspection by ID\n";
        cout << "2. List inspections by area\n";
        cout << "3. Analyze vibration readings\n";
        cout << "4. Exit\n";
        cout << "Enter option number: ";
        cin >> menuChoice;
 
        if (menuChoice == 1) {
            int targetId = 0;
            cout << "Enter inspection ID: ";
            cin >> targetId;
            int foundIndex = findInspectionById(inspections, CAPACITY, targetId);
            if (foundIndex == -1) {
                cout << "Inspection not found." << endl;
            } else {
                displayInspection(inspections[foundIndex]);
            }
        } else if (menuChoice == 2) {
            string targetArea;
            cout << "Enter area: ";
            getline(cin >> ws, targetArea);
            int matchCount = displayInspectionsByArea(inspections, CAPACITY, targetArea);
            cout << "Matches: " << matchCount << endl;
        } else if (menuChoice == 3) {
            int valueCount = copyVibrations(inspections, CAPACITY, sortedVibrations);
            if (valueCount == 0) {
                cout << "No readings available for statistics." << endl;
            } else {
                selectionSort(sortedVibrations, valueCount);
                cout << "Values used: " << valueCount << endl;
                cout << "Mean: " << calculateMean(sortedVibrations, valueCount) << endl;
                cout << "Median: " << calculateMedian(sortedVibrations, valueCount) << endl;
                cout << "Mode: ";
                displayModes(sortedVibrations, valueCount);
            }
        } else if (menuChoice != 4) {
            cout << "Invalid option." << endl;
        }
    } while (menuChoice != 4);
 
    return 0;
}
 
void displayInspection(Inspection inspection) {
    cout << "ID: " << inspection.id
         << " | Area: " << inspection.area
         << " | Vibration: " << inspection.vibration << endl;
}
 
int findInspectionById(const Inspection inspections[], int capacity, int targetId) {
    // TODO: Traverse every position. Ignore empty slots and return the index of the matching ID.
    for (int index = 0; index < capacity; index++) {
        if (!inspections[index].isEmpty && inspections[index].id == targetId) {
            return index;
        }
    }
    // TODO: Return -1 only after the complete search finds no occupied match.
    return -1;
}
 
int displayInspectionsByArea(const Inspection inspections[], int capacity, string targetArea) {
    int matchCount = 0;
    // TODO: Traverse every position, display every occupied inspection in targetArea, and update matchCount.
    for (int index = 0; index < capacity; index++) {
        if (!inspections[index].isEmpty && inspections[index].area == targetArea) {
            displayInspection(inspections[index]);
            matchCount++;
        }
    }
    return matchCount;
}
 
int copyVibrations(const Inspection inspections[], int capacity, double values[]) {
    int valueCount = 0;
    // TODO: Copy the vibration from each occupied inspection into the next position of values.
    for (int index = 0; index < capacity; index++) {
        if (!inspections[index].isEmpty) {
            values[valueCount] = inspections[index].vibration;
            valueCount++;
        }
    }
    // TODO: Return the number of copied values, not capacity.
    return valueCount;
}
 
void selectionSort(double values[], int count) {
    // TODO: Complete selection sort in ascending order for the used positions only.
    for (int position = 0; position < count - 1; position++) {
        int minIndex = position;
        for (int index = position + 1; index < count; index++) {
            if (values[index] < values[minIndex]) {
                minIndex = index;
            }
        }
        if (minIndex != position) {
            double temp = values[position];
            values[position] = values[minIndex];
            values[minIndex] = temp;
        }
    }
}
 
double calculateMean(const double values[], int count) {
    double total = 0.0;
    // TODO: Accumulate the used values and return total divided by count.
    for (int index = 0; index < count; index++) {
        total += values[index];
    }
    return total / count;
}
 
double calculateMedian(const double sortedValues[], int count) {
    // TODO: Use the middle value for odd counts or average the two middle values for even counts.
    if (count % 2 == 1) {
        return sortedValues[count / 2];
    }
    double average = (sortedValues[count / 2 - 1] + sortedValues[count / 2]) / 2.0;
    // Round half up to two decimals; the tiny tolerance offsets binary floating-point error (0.225 is stored slightly low).
    int hundredths = static_cast<int>(average * 100.0 + 0.5 + 0.000001);
    return hundredths / 100.0;
}
 
void displayModes(const double sortedValues[], int count) {
    // TODO: Find the maximum repeated frequency, then display every value tied at that frequency.
    int maxFrequency = 0;
    int index = 0;
    while (index < count) {
        int runEnd = index;
        while (runEnd < count && sortedValues[runEnd] == sortedValues[index]) {
            runEnd++;
        }
        int frequency = runEnd - index;
        if (frequency > maxFrequency) {
            maxFrequency = frequency;
        }
        index = runEnd;
    }
 
    // TODO: Display N/A when no value repeats.
    if (maxFrequency == 1) {
        cout << "N/A" << endl;
        return;
    }
 
    bool isFirst = true;
    index = 0;
    while (index < count) {
        int runEnd = index;
        while (runEnd < count && sortedValues[runEnd] == sortedValues[index]) {
            runEnd++;
        }
        if (runEnd - index == maxFrequency) {
            if (!isFirst) {
                cout << ", ";
            }
            cout << sortedValues[index];
            isFirst = false;
        }
        index = runEnd;
    }
    cout << endl;
}

/*
 * Test Cases:
 * 1. Inputs: 1, then 109
 *    Expected: Shows the Assembly inspection with vibration 0.30.
 *    Observed: ID: 109 | Area: Assembly | Vibration: 0.30
 * 2. Inputs: 1, then 999
 *    Expected: Shows Inspection not found.
 *    Observed: Inspection not found.
 * 3. Inputs: 2, then Assembly
 *    Expected: Shows three inspections and reports Matches: 3.
 *    Observed: Lists IDs 101, 109 and 123; Matches: 3.
 * 4. Inputs: 3
 *    Expected: Mean 0.24, median 0.23, modes 0.15 and 0.30.
 *    Observed: Values used: 6; Mean: 0.24; Median: 0.23; Mode: 0.15, 0.30.
 */

 /*
 * Analysis:
 * 1. Why does findInspectionById return an index instead of the ID?
 *    Answer: The index gives access to the whole record, not just its ID.
 * 2. Why must displayInspectionsByArea continue after its first match?
 *    Answer: An area can have several inspections, and stopping early would undercount them.
 * 3. Why does copyVibrations use valueCount separately from index?
 *    Answer: valueCount fills values without gaps, while index also counts empty slots.
 * 4. Why is selectionSort applied to sortedVibrations instead of inspections?
 *    Answer: Sorting the original records would break the link between each ID and its vibration.
 * 5. Which two values determine the median when six readings are sorted?
 *    Answer: The third and fourth values, 0.15 and 0.30.
 */