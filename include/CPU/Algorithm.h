
// Fist Come First Served Scheduling Algorithm
void CPU::Algorithm::FCFS(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table)
{
    int time = 0;

    while (processes.notEmpty())
    {
        CPU::Process process = CPU::Process();

        while (time < processes.front().arrival_time)
            time++, process.temp_burst_time++;

        if (process.temp_burst_time > 0)
        {
            process.id = -1, process.completion_time = time;

            gantt->push(process);
        }

        process = processes.pop();

        process.set_response_time(time);

        while (process.burst_time_left > 0)
        {
            process.temp_burst_time++;
            process.burst_time_left--;
            time++;
        }

        process.set_completion_time(time);

        // Update the Gantt Chart
        gantt->push(process);

        process.temp_burst_time = 0;

        // Update the completion time to the queue
        table->push(process);
    }
}

// Shortest Job First Scheduling Algorithm
void CPU::Algorithm::SJF_P(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table)
{
    int clock = 0;

    CPU::Process process;

    while (!processes.empty())
    {
        while (clock < processes.front().arrival_time)
        {
            process.temp_burst_time++;
            clock++;
        }

        if (process.temp_burst_time > 0)
        {
            process.id = -1;
            process.completion_time = clock;
            gantt->push(process);
        }

        process = CPU::Process::pop_index(&processes, CPU::Process::min_BT_index(processes, clock));

        if (process.arrival_time == process.initial_arrival_time)
            process.set_response_time(clock);

        while (process.burst_time_left > 0 && (processes.empty() || clock < processes.front().arrival_time || process.burst_time_left <= CPU::Process::min_BT(processes, clock)))
        {
            process.burst_time_left--;
            process.temp_burst_time++;
            clock++;
        }

        if (process.burst_time_left == 0)
        {
            process.arrival_time = process.initial_arrival_time;
            process.set_completion_time(clock);
            gantt->push(process);
            process.temp_burst_time = 0;
            table->push(process);
        }
        else
        {
            process.arrival_time = clock;
            process.completion_time = clock;
            gantt->push(process);
            process.temp_burst_time = 0;
            processes.push(process);
        }
    }
}

// Shortest Job First (Non-Preemptive) Scheduling Algorithm
void CPU::Algorithm::SJF_NP(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table)
{
    int clock = 0;

    CPU::Process process;

    while (!processes.empty())
    {
        while (clock < processes.front().arrival_time)
        {
            process.temp_burst_time++;
            clock++;
        }
        if (process.temp_burst_time > 0)
        {
            process.id = -1;
            process.completion_time = clock;
            gantt->push(process);
        }

        process = CPU::Process::pop_index(&processes, CPU::Process::min_BT_index(processes, clock));
        process.set_response_time(clock);
        while (process.burst_time_left > 0)
        {
            process.temp_burst_time++;
            process.burst_time_left--;
            clock++;
        }
        process.set_completion_time(clock);
        gantt->push(process);
        process.temp_burst_time = 0;
        table->push(process);
    }
}

// Longest Job First Scheduling Algorithm
void CPU::Algorithm::LJF_P(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table)
{
    int clock = 0;

    CPU::Process process;

    while (!processes.empty())
    {
        while (clock < processes.front().arrival_time)
        {
            process.temp_burst_time++;
            clock++;
        }
        if (process.temp_burst_time > 0)
        {
            process.id = -1;
            process.completion_time = clock;
            gantt->push(process);
        }
        process = CPU::Process::pop_index(&processes, CPU::Process::max_BT_index(processes, clock));
        if (process.arrival_time == process.initial_arrival_time)
            process.set_response_time(clock);

        while (process.burst_time_left > 0 && (processes.empty() || clock < processes.front().arrival_time || process.burst_time_left >= CPU::Process::max_BT(processes, clock)))
        {
            process.temp_burst_time++;
            process.burst_time_left--;
            clock++;
        }
        if (process.burst_time_left == 0)
        {
            process.arrival_time = process.initial_arrival_time;
            process.set_completion_time(clock);
            gantt->push(process);
            process.temp_burst_time = 0;
            table->push(process);
        }
        else
        {
            process.arrival_time = clock;
            process.completion_time = clock;
            gantt->push(process);
            process.temp_burst_time = 0;
            processes.push(process);
        }
    }
}

// Longest Job First (Non-Preemptive) Scheduling Algorithm
void CPU::Algorithm::LJF_NP(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table)
{
    int clock = 0;
    CPU::Process process;

    while (!processes.empty())
    {
        while (clock < processes.front().arrival_time)
        {
            process.temp_burst_time++;
            clock++;
        }
        if (process.temp_burst_time > 0)
        {
            process.id = -1;
            process.set_completion_time(clock);
            gantt->push(process);
        }
        process = CPU::Process::pop_index(&processes, CPU::Process::max_BT_index(processes, clock));
        process.set_response_time(clock);
        while (process.burst_time_left > 0)
        {
            process.temp_burst_time++;
            process.burst_time_left--;
            clock++;
        }
        process.set_completion_time(clock);
        gantt->push(process);
        process.temp_burst_time = 0;
        table->push(process);
    }
}

// Round Robin Scheduling Algorithm
void CPU::Algorithm::RR(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table)
{
    RR(processes, gantt, table, 2);
}

void CPU::Algorithm::RR(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table, int rr_time_slice)
{
    int clock = 0;

    CPU::Process process;

    while (processes.notEmpty())
    {
        while (clock < processes.front().arrival_time)
        {
            process.temp_burst_time++;
            clock++;
        }
        if (process.temp_burst_time > 0)
        {
            process.id = -1;
            process.completion_time = clock;
            gantt->push(process);
        }
        process = processes.pop();

        if (process.arrival_time == process.initial_arrival_time)
            process.set_response_time(clock);

        while (process.burst_time_left > 0 && (process.temp_burst_time < rr_time_slice || processes.empty() || clock < processes.front().arrival_time))
        {
            process.temp_burst_time++;
            process.burst_time_left--;
            clock++;
        }

        if (process.burst_time_left == 0)
        {
            process.arrival_time = process.initial_arrival_time;
            process.set_completion_time(clock);
            gantt->push(process);

            process.temp_burst_time = 0;
            table->push(process);
        }
        else
        {
            process.arrival_time = clock;
            process.completion_time = clock;
            gantt->push(process);

            process.temp_burst_time = 0;
            processes.push(process);
        }
    }
}

// Priority Preemptive Scheduling Algorithm
void CPU::Algorithm::P_P(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table)
{
    P_P(processes, gantt, table, false);
}

void CPU::Algorithm::P_P(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table, bool high)
{
    int clock = 0;

    CPU::Process process;

    if (high == 1)
    {
        while (!processes.empty())
        {
            while (clock < processes.front().arrival_time)
            {
                process.temp_burst_time++;
                clock++;
            }
            if (process.temp_burst_time > 0)
            {
                process.id = -1;
                process.completion_time = clock;
                gantt->push(process);
            }
            process = CPU::Process::pop_index(&processes, CPU::Process::max_priority_index(processes, clock, high));
            if (process.arrival_time == process.initial_arrival_time)
                process.set_response_time(clock);
            while (process.burst_time_left > 0 && (processes.empty() || clock < processes.front().arrival_time || process.priority >= CPU::Process::max_priority(processes, clock, high)))
            {
                process.temp_burst_time++;
                process.burst_time_left--;
                clock++;
            }
            if (process.burst_time_left == 0)
            {
                process.arrival_time = process.initial_arrival_time;
                process.set_completion_time(clock);
                gantt->push(process);
                process.temp_burst_time = 0;
                table->push(process);
            }
            else
            {
                process.arrival_time = clock;
                process.completion_time = clock;
                gantt->push(process);
                process.temp_burst_time = 0;
                processes.push(process);
            }
        }
    }
    else
    {
        while (!processes.empty())
        {
            while (clock < processes.front().arrival_time)
            {
                process.temp_burst_time++;
                clock++;
            }
            if (process.temp_burst_time > 0)
            {
                process.id = -1;
                process.completion_time = clock;
                gantt->push(process);
            }
            process = CPU::Process::pop_index(&processes, CPU::Process::max_priority_index(processes, clock, high));

            if (process.arrival_time == process.initial_arrival_time)
                process.set_response_time(clock);

            while (process.burst_time_left > 0 && (processes.empty() || clock < processes.front().arrival_time || process.priority <= CPU::Process::max_priority(processes, clock, high)))
            {
                process.temp_burst_time++;
                process.burst_time_left--;
                clock++;
            }
            if (process.burst_time_left == 0)
            {
                process.arrival_time = process.initial_arrival_time;
                process.set_completion_time(clock);
                gantt->push(process);
                process.temp_burst_time = 0;
                table->push(process);
            }
            else
            {
                process.arrival_time = clock;
                process.completion_time = clock;
                gantt->push(process);
                process.temp_burst_time = 0;
                processes.push(process);
            }
        }
    }

    // return table;
}

// Priority Non-Preemptive Scheduling Algorithm
void CPU::Algorithm::P_NP(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table)
{
    P_NP(processes, gantt, table, false);
}

void CPU::Algorithm::P_NP(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table, bool high)
{
    int clock = 0;

    CPU::Process process;

    if (high == 1)
    {
        while (!processes.empty())
        {
            while (clock < processes.front().arrival_time)
            {
                process.temp_burst_time++;
                clock++;
            }
            if (process.temp_burst_time > 0)
            {
                process.id = -1;
                process.completion_time = clock;
                gantt->push(process);
            }
            process = CPU::Process::pop_index(&processes, CPU::Process::max_priority_index(processes, clock, high));
            process.set_response_time(clock);

            while (process.burst_time_left > 0)
            {
                process.temp_burst_time++;
                process.burst_time_left--;
                clock++;
            }
            process.set_completion_time(clock);
            gantt->push(process);
            process.temp_burst_time = 0;

            table->push(process);
        }
    }
    else
    {
        while (!processes.empty())
        {
            while (clock < processes.front().arrival_time)
            {
                process.temp_burst_time++;
                clock++;
            }
            if (process.temp_burst_time > 0)
            {
                process.id = -1;
                process.completion_time = clock;
                gantt->push(process);
            }
            process = CPU::Process::pop_index(&processes, CPU::Process::max_priority_index(processes, clock, high));
            process.set_response_time(clock);

            while (process.burst_time_left > 0)
            {
                process.temp_burst_time++;
                process.burst_time_left--;
                clock++;
            }
            process.set_completion_time(clock);
            gantt->push(process);
            process.temp_burst_time = 0;

            table->push(process);
        }
    }
}

// Highest Response Ratio Next Scheduling Algorithm
void CPU::Algorithm::HRRN(Lists::Queue<CPU::Process> processes, Lists::Queue<CPU::Process> *gantt, Lists::Queue<CPU::Process> *table)
{
    int clock = 0;

    CPU::Process process;

    while (!processes.empty())
    {
        while (clock < processes.front().arrival_time)
        {
            process.temp_burst_time++;
            clock++;
        }
        if (process.temp_burst_time > 0)
        {
            process.id = -1;
            process.completion_time = clock;
            gantt->push(process);
        }
        process = CPU::Process::pop_index(&processes, CPU::Process::max_response_ratio_index(processes, clock));
        process.set_response_time(clock);

        while (process.burst_time_left > 0)
        {
            process.temp_burst_time++;
            process.burst_time_left--;
            clock++;
        }
        process.set_completion_time(clock);
        gantt->push(process);
        process.temp_burst_time = 0;

        table->push(process);
    }
}

// Get total completion time of the processes
double CPU::Algorithm::get_total_completion_time(Lists::Queue<CPU::Process> processes)
{
    double total = 0;

    while (processes.notEmpty())
        total += processes.pop().completion_time;

    return total;
}

// Get total waiting time of the processes
double CPU::Algorithm::get_total_waiting_time(Lists::Queue<CPU::Process> processes)
{
    double total = 0;

    while (processes.notEmpty())
        total += processes.pop().waiting_time;

    return total;
}

// Get total turnaround time of the processes
double CPU::Algorithm::get_total_turnaround_time(Lists::Queue<CPU::Process> processes)
{
    double total = 0;

    while (processes.notEmpty())
        total += processes.pop().turnaround_time;

    return total;
}

// Get total response time of the processes
double CPU::Algorithm::get_total_reponse_time(Lists::Queue<CPU::Process> processes)
{
    double total = 0;

    while (processes.notEmpty())
        total += processes.pop().response_time;

    return total;
}
