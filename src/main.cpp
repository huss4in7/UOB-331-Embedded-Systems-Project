#include <Arduino.h>

#include "Lists.h"
#include "CPU.h"

void setup()
{
    // Begin Serial Communication
    Serial.begin(115200);

    // Initialize the processes
    DataStructure::Queue<CPU::Process> processes;

    // Set sample processes
    processes.push(CPU::Process(0, 5, 3));
    processes.push(CPU::Process(3, 10, 4));
    processes.push(CPU::Process(7, 5, 2));
    processes.push(CPU::Process(8, 2, 5));
    processes.push(CPU::Process(9, 4, 1));
    processes.push(CPU::Process(9, 4, 1));

    // Preform the Algorithm and display the results
    CPU::Display::display(CPU::Algorithm::FCFS, processes);
}

void loop()
{
}
