using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
struct Task
{
    int id;
    string description;
    int priority;
    string deadline;
    string category;
    bool completed;

    Task(int id, string desc, int prio, string dead, string cat, bool comp = false)
        : id(id), description(desc), priority(prio), deadline(dead), category(cat), completed(comp) {}
};
struct ComparePriority
{
    bool operator()(const Task& t1, const Task& t2)
    {
        if (t1.priority == t2.priority)
        {
            return t1.deadline > t2.deadline;
        }
        return t1.priority < t2.priority;
    }
};
class TaskManager
{
private:
    vector<Task> tasks;
    const string filename = "tasks_data_v2.csv";
    int nextId;
    int findIndexByDescription(string desc)
    {
        string lowerTarget = desc;
        transform(lowerTarget.begin(), lowerTarget.end(), lowerTarget.begin(), ::tolower);

        for (size_t i = 0; i < tasks.size(); ++i)
        {
            string lowerDesc = tasks[i].description;
            transform(lowerDesc.begin(), lowerDesc.end(), lowerDesc.begin(), ::tolower);

            if (lowerDesc == lowerTarget)
            {
                return i;
            }
        }
        return -1;
    }
    void loadFromFile()
    {
        ifstream file(filename);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string idStr, desc, prioStr, deadStr, catStr, compStr;
            getline(ss, idStr, ',');
            getline(ss, desc, ',');
            getline(ss, prioStr, ',');
            getline(ss, deadStr, ',');
            getline(ss, catStr, ',');
            getline(ss, compStr, ',');
            if (!idStr.empty())
            {
                tasks.push_back(Task(stoi(idStr), desc, stoi(prioStr), deadStr, catStr, stoi(compStr)));
            }
        }
        file.close();
        if (tasks.empty()) nextId = 1;
        else
        {
            int maxId = 0;
            for(const auto& t : tasks)
            {
                if(t.id > maxId) maxId = t.id;
            }
            nextId = maxId + 1;
        }
    }
    void saveToFile()
    {
        ofstream file(filename);
        for (const auto& task : tasks)
        {
            file << task.id << "," << task.description << ","
                 << task.priority << "," << task.deadline << ","
                 << task.category << "," << task.completed << "\n";
        }
        file.close();
    }
public:
    TaskManager()
    {
        nextId = 1;
        loadFromFile();
    }

    ~TaskManager()
    {
        saveToFile();
    }

    void addTask(string desc, int priority, string deadline, string category)
    {
        tasks.push_back(Task(nextId++, desc, priority, deadline, category));
        saveToFile();
        cout << "\nTask added successfully!\n";
    }
    void markTaskCompleted(string desc)
    {
        int index = findIndexByDescription(desc);
        if (index != -1)
        {
            tasks[index].completed = true;
            saveToFile();
            cout << "\nTask \"" << tasks[index].description << "\" marked as completed!\n";
        }
        else
        {
            cout << "\nTask description not found.\n";
        }
    }
    void deleteTask(string desc)
    {
        int index = findIndexByDescription(desc);
        if (index != -1)
        {
            cout << "\nTask \"" << tasks[index].description << "\" successfully deleted.\n";
            tasks.erase(tasks.begin() + index);
            saveToFile();
        }
        else
        {
            cout << "\nTask description not found.\n";
        }
    }
    void editTask(string desc)
    {
        int index = findIndexByDescription(desc);
        if (index == -1)
        {
            cout << "\nTask description not found.\n";
            return;
        }
        cout << "\n--- Editing Task: " << tasks[index].description << " ---\n";
        cout << "1. Edit Description\n2. Edit Category\n3. Edit Priority\n4. Edit Deadline\n";
        cout << "Enter feature choice to modify: ";
        int choice;
        cin >> choice;
        cin.ignore();
        if (choice == 1)
            {
            cout << "Enter new description: ";
            getline(cin, tasks[index].description);
        }
        else if (choice == 2)
        {
            cout << "Enter new category: ";
            getline(cin, tasks[index].category);
        }
        else if (choice == 3)
        {
            cout << "Enter new priority (1-5): ";
            cin >> tasks[index].priority;
        }
        else if (choice == 4)
        {
            cout << "Enter new deadline (YYYY-MM-DD): ";
            cin >> tasks[index].deadline;
        }
        else
        {
            cout << "Invalid choice. No changes made.\n";
            return;
        }
        saveToFile();
        cout << "\nTask adjusted and updated successfully!\n";
    }
    void displayTasksByStatus(bool lookForCompleted)
    {
        bool found = false;
        cout << "\n--- " << (lookForCompleted ? "Completed" : "Pending") << " Tasks ---\n";
        cout << left << setw(5) << "ID" << setw(25) << "Description"
             << setw(12) << "Category" << setw(10) << "Priority" << "Deadline\n";
        cout << "--------------------------------------------------------------------------------\n";
        for (const auto& task : tasks)
        {
            if (task.completed == lookForCompleted)
            {
                cout << left << setw(5) << task.id
                     << setw(25) << task.description
                     << setw(12) << task.category
                     << setw(10) << task.priority
                     << task.deadline << "\n";
                found = true;
            }
        }
        if (!found) cout << "No tasks found matching this criteria.\n";
    }
    void displayAllTasks()
    {
        if (tasks.empty())
        {
            cout << "\nNo tasks found. Your list is empty!\n";
            return;
        }
        cout << "\n--- All Tasks ---\n";
        cout << left << setw(5) << "ID" << setw(25) << "Description"
             << setw(12) << "Category" << setw(10) << "Priority"
             << setw(15) << "Deadline" << "Status\n";
        cout << "--------------------------------------------------------------------------------\n";
        for (const auto& task : tasks)
        {
            cout << left << setw(5) << task.id
                 << setw(25) << task.description
                 << setw(12) << task.category
                 << setw(10) << task.priority
                 << setw(15) << task.deadline
                 << (task.completed ? "[Done]" : "[Pending]") << "\n";
        }
    }
    void displayTasksByCategory(string cat)
    {
        bool found = false;
        cout << "\n--- Tasks in Category: " << cat << " ---\n";
        cout << left << setw(5) << "ID" << setw(25) << "Description"
             << setw(10) << "Priority" << setw(15) << "Deadline" << "Status\n";
        cout << "-----------------------------------------------------------------------\n";
        for (const auto& task : tasks)
        {
            if (task.category == cat)
            {
                cout << left << setw(5) << task.id
                     << setw(25) << task.description
                     << setw(10) << task.priority
                     << setw(15) << task.deadline
                     << (task.completed ? "[Done]" : "[Pending]") << "\n";
                found = true;
            }
        }
        if (!found) cout << "No tasks found matching this category.\n";
    }
    void displayDashboard()
    {
        if (tasks.empty())
        {
            cout << "\nNo data available. Add some tasks first!\n";
            return;
        }
        int totalTasks = tasks.size();
        int completedCount = 0;
        int highPriorityPending = 0;
        for (const auto& task : tasks)
        {
            if (task.completed) completedCount++;
            if (!task.completed && task.priority >= 4) highPriorityPending++;
        }
        double completionRate = ((double)completedCount / totalTasks) * 100;
        cout << "\n====================================\n";
        cout << "        PRODUCTIVITY DASHBOARD      \n";
        cout << "====================================\n";
        cout << " Total Tasks Tracked      : " << totalTasks << "\n";
        cout << " Completed Tasks          : " << completedCount << "\n";
        cout << " Pending Tasks            : " << (totalTasks - completedCount) << "\n";
        cout << " High Priority Overdue    : " << highPriorityPending << " (Priority >= 4)\n";
        cout << " Task Completion Rate     : " << fixed << setprecision(1) << completionRate << "%\n";
        cout << "====================================\n";
    }
    void getNextTaskToDo()
    {
        priority_queue<Task, vector<Task>, ComparePriority> pq;

        for (const auto& task : tasks)
        {
            if (!task.completed) pq.push(task);
        }
        if (pq.empty())
        {
            cout << "\nYou have no pending tasks. Great job!\n";
            return;
        }
        Task topTask = pq.top();
        cout << "\n--- Recommended Next Task (Highest Priority) ---\n";
        cout << "ID: " << topTask.id << " | [" << topTask.category << "] " << topTask.description
             << " | Priority: " << topTask.priority
             << " | Deadline: " << topTask.deadline << "\n";
    }
    void sortTasksByDeadline()
    {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b)
        {
            if (a.completed != b.completed) return !a.completed;
            return a.deadline < b.deadline;
        });
        cout << "\nTasks sorted by deadline.\n";
        displayAllTasks();
    }
    void searchTaskByName(string searchKey)
    {
        if (tasks.empty())
        {
            cout << "\nNo tasks available to search.\n";
            return;
        }
        string lowerKey = searchKey;
        transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), ::tolower);
        bool found = false;
        cout << "\n--- Search Results for \"" << searchKey << "\" ---\n";
        cout << left << setw(5) << "ID" << setw(25) << "Description"
             << setw(12) << "Category" << setw(10) << "Priority"
             << setw(15) << "Deadline" << "Status\n";
        cout << "--------------------------------------------------------------------------------\n";
        for (const auto& task : tasks)
        {
            string lowerDesc = task.description;
            transform(lowerDesc.begin(), lowerDesc.end(), lowerDesc.begin(), ::tolower);
            if (lowerDesc.find(lowerKey) != string::npos)
            {
                cout << left << setw(5) << task.id
                     << setw(25) << task.description
                     << setw(12) << task.category
                     << setw(10) << task.priority
                     << setw(15) << task.deadline
                     << (task.completed ? "[Done]" : "[Pending]") << "\n";
                found = true;
            }
        }
        if (!found) cout << "No tasks found matching your search term.\n";
    }
};
int main()
{
    TaskManager manager;
    int choice;
    do
    {
        cout << "\n=== SMART TASK MANAGER (v1.0) ===\n";
        cout << "1. Add a New Task\n";
        cout << "2. View All Tasks\n";
        cout << "3. What should I do next? (Heap Selection)\n";
        cout << "4. View Tasks Sorted by Deadline\n";
        cout << "5. Filter Tasks by Category\n";
        cout << "6. Filter Tasks by Status (Pending/Completed)\n";
        cout << "7. View Productivity Dashboard (Analytics)\n";
        cout << "8. Mark Task as Completed \n";
        cout << "9. Edit an Existing Task \n";
        cout << "10. Delete a Task \n";
        cout << "11. Search Task by Name / Keyword\n";
        cout << "12. Exit and Save\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (choice == 1)
        {
            string desc, deadline, category;
            int priority;
            cout << "Enter task description: ";
            cin.ignore();
            getline(cin, desc);
            cout << "Enter category (e.g., College, Work, Personal): ";
            getline(cin, category);
            cout << "Enter priority (1=Low, 5=High): ";
            cin >> priority;
            cout << "Enter deadline (YYYY-MM-DD): ";
            cin >> deadline;
            manager.addTask(desc, priority, deadline, category);
        }
        else if (choice == 2)
        {
            manager.displayAllTasks();
        }
        else if (choice == 3)
        {
            manager.getNextTaskToDo();
        }
        else if (choice == 4)
        {
            manager.sortTasksByDeadline();
        }
        else if (choice == 5)
        {
            string category;
            cout << "Enter category name to filter: ";
            cin.ignore();
            getline(cin, category);
            manager.displayTasksByCategory(category);
        }
        else if (choice == 6)
        {
            int subChoice;
            cout << "1. View Pending Tasks\n2. View Completed Tasks\nChoose status choice: ";
            cin >> subChoice;
            manager.displayTasksByStatus(subChoice == 2);
        }
        else if (choice == 7)
        {
            manager.displayDashboard();
        }
        else if (choice == 8)
        {
            string desc;
            cout << "Enter the exact Task Description to mark as completed: ";
            cin.ignore();
            getline(cin, desc);
            manager.markTaskCompleted(desc);
        }
        else if (choice == 9)
        {
            string desc;
            cout << "Enter the exact Task Description you want to edit: ";
            cin.ignore();
            getline(cin, desc);
            manager.editTask(desc);
        }
        else if (choice == 10)
        {
            string desc;
            cout << "Enter the exact Task Description you want to delete: ";
            cin.ignore();
            getline(cin, desc);
            manager.deleteTask(desc);
        }
        else if (choice == 11)
        {
            string name;
            cout << "Enter task name or partial keyword to search: ";
            cin.ignore();
            getline(cin, name);
            manager.searchTaskByName(name);
        }
    }
    while (choice != 12);
    cout << "\nSaving tasks... Data saved safely to 'tasks_data_v2.csv'. Goodbye!\n";
    return 0;
}
