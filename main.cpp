#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
// Structure for Staff (Doctors/Nurses)
struct Staff {
int id;
string name;
string role; // Doctor or Nurse
int shiftStart; // 0-23 hour format
int shiftEnd;
};
// Structure for Patient
struct Patient {
string name;
int urgency; // 1 for Critical, 0 for Normal
string assignedDoctor;
};
// Custom Comparator for Priority Queue (Critical patients first)
struct CompareUrgency {
bool operator()(Patient const& p1, Patient const& p2) {
return p1.urgency < p2.urgency;
}
};
class HospitalSystem {
vector<Staff> staffList;
priority_queue<Patient, vector<Patient>, CompareUrgency> patientQueue;
public:
// 1. Record Staff Data to File
void addStaff(int id, string name, string role, int startHour) {
Staff s;
s.id = id;
s.name = name;
s.role = role;
s.shiftStart = startHour;
s.shiftEnd = (startHour + 8) % 24; // 8-hour shift logic
staffList.push_back(s);
ofstream outFile("staff_records.txt", ios::app);outFile << id << " " << name << " " << role << " " << s.shiftStart << " " << s.shiftEnd <<
endl;
outFile.close();
cout << role << " added and rostered successfully!\n";
} //
2. Schedule & Show Roster
void showRoster() {
cout << "\n--- 24-Hour Duty Roster ---\n";
for (const auto& s : staffList) {
cout << s.role << ": " << s.name << " | Shift: "
<< s.shiftStart << ":00 to " << s.shiftEnd << ":00\n";
}
} //
3 & 5. Manage Patient Priority Queue
void addPatient(string name, int urgency) {
Patient p = {name, urgency, "Pending"};
patientQueue.push(p);
ofstream outFile("patient_history.txt", ios::app);
outFile << name << " Priority:" << (urgency ? "Critical" : "Normal") << endl;
outFile.close();
} //
4. Assign Doctors Efficiently
void treatPatient(int currentHour) {
if (patientQueue.empty()) {
cout << "No patients in queue.\n";
return;
} P
atient p = patientQueue.top();
patientQueue.pop();
string assignedDoc = "No Doctor Available";
for (const auto& s : staffList) {
if (s.role == "Doctor") {
// Check if doctor is within their 8-hour shift
bool inShift = false;
if (s.shiftStart < s.shiftEnd)
inShift = (currentHour >= s.shiftStart && currentHour < s.shiftEnd);
else // Over-night shift logic
inShift = (currentHour >= s.shiftStart || currentHour < s.shiftEnd);
if (inShift) {
assignedDoc = s.name;
break;}
}
} c
out << "Treating Patient: " << p.name << " [" << (p.urgency ? "CRITICAL" : "Normal")
<< "] assigned to Dr. " << assignedDoc << " at hour " << currentHour << endl;
}
};
int main() {
HospitalSystem hms;
// Adding Staff (ID, Name, Role, Start Hour)
hms.addStaff(101, "Ali", "Doctor", 8); // 08:00 to 16:00
hms.addStaff(102, "Sara", "Nurse", 16); // 16:00 to 00:00
hms.addStaff(103, "Zayn", "Doctor", 0); // 00:00 to 08:00
// Adding Patients (Name, Urgency: 1=High, 0=Low)
hms.addPatient("Patient_A", 0);
hms.addPatient("Patient_B", 1); // Critical
hms.showRoster();
// Simulating treatment at 10:00 AM
cout << "\n--- Current Patient Processing ---\n";
hms.treatPatient(10);
hms.treatPatient(10);
return 0;
}
