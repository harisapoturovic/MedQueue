#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Patient {
    int id;
    int interarrival_time;
    int arrival_time;
    int service_time;
    int service_start_time;
    int service_end_time;
    int waiting_time;
    int time_spent_in_system;
    int priority;
};

class SingleServerQueueSimulation {
private:
    int num_patients;
    vector<Patient> patients;

    int getRandomInterarrivalTime();
    int getRandomServiceTime();
    int getRandomPriority();

public:
    SingleServerQueueSimulation(int num_patients);
    void simulate();
    void printSimulationTable();
};

SingleServerQueueSimulation::SingleServerQueueSimulation(int num_patients) : num_patients(num_patients) {
    patients.resize(num_patients);

    for (int i = 0; i < num_patients; ++i) {
        patients[i].id = i + 1;
        patients[i].interarrival_time = (i == 0) ? 0 : getRandomInterarrivalTime();
        patients[i].arrival_time = (i == 0) ? 0 : patients[i - 1].arrival_time + patients[i].interarrival_time;
        patients[i].service_time = getRandomServiceTime();
        patients[i].priority = getRandomPriority();
    }
}

void SingleServerQueueSimulation::simulate() {
    for (int i = 0; i < patients.size(); ++i) {
        int service_start_time = (i == 0) ? patients[i].arrival_time : max(patients[i].arrival_time, patients[i].arrival_time + patients[i - 1].service_time);

        patients[i].service_start_time = service_start_time;
        patients[i].service_end_time = service_start_time + patients[i].service_time;
        patients[i].waiting_time = patients[i].service_start_time - patients[i].arrival_time;
        patients[i].time_spent_in_system = patients[i].service_end_time - patients[i].arrival_time;
    }

    sort(patients.begin(), patients.end(), [](const Patient& a, const Patient& b) {
        if (a.priority != b.priority) {
            return a.priority > b.priority;
        }
        return a.id < b.id;
        });
}

void SingleServerQueueSimulation::printSimulationTable() {
    std::cout << "ID\tPriority\tInterarrival Time\tArrival Time\tService Time\tService Start Time\tService End Time\tWaiting Time\tTime Spent in System\n";

    for (const auto& patient : patients) {
        cout << patient.id << "\t" << patient.priority << "\t" << patient.interarrival_time << "\t" << patient.arrival_time << "\t"
            << patient.service_time << "\t" << patient.service_start_time << "\t" << patient.service_end_time << "\t"
            << patient.waiting_time << "\t" << patient.time_spent_in_system << "\n";
    }
}

int SingleServerQueueSimulation::getRandomInterarrivalTime() {
    return rand() % 8 + 1; //doktor 1
}

int SingleServerQueueSimulation::getRandomServiceTime() {
    return rand() % 5 + 5; //doktor 1
}

int SingleServerQueueSimulation::getRandomPriority() {
    return rand() % 3 + 1;
}

int main() {
    const int num_patients_to_simulate = 35;
    SingleServerQueueSimulation simulation(num_patients_to_simulate);
    simulation.simulate();
    simulation.printSimulationTable();

    return 0;
}
