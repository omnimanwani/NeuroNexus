#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Task
{
    string task_disc;
    bool completed;

    Task(const string &disc) : task_disc(disc), completed(false) {}
};

class tdl
{
private:
    vector<Task> list_of_tasks;
    string filename;

public:
    tdl(const string &user) : filename(user + "_todo_list.txt")
    {
        load_tasks();
    }

    void load_tasks()
    {
        ifstream file(filename);
        if (file.is_open())
        {
            Task task("");
            while (getline(file, task.task_disc))
            {
                file >> task.completed;
                list_of_tasks.push_back(task);
                file.ignore();
            }
            file.close();
        }
    }

    void save_tasks()
    {
        ofstream file(filename);
        if (file.is_open())
        {
            for (const auto &task : list_of_tasks)
            {
                file << task.task_disc << endl;
                file << task.completed << endl;
            }
            file.close();
        }
    }

    void add_task(const string &task_disc)
    {
        list_of_tasks.push_back(Task(task_disc));
        cout << "Task added! "<<endl;
        save_tasks();
    }

    void view_tasks()
    {
        if (list_of_tasks.empty())
            cout << "wohoo!! No task pending." << endl;
        else
        {
            cout << "List of Tasks: " << endl;
            for (int i = 0; i < list_of_tasks.size(); ++i)
            {
                if (!list_of_tasks[i].completed)
                    cout << i + 1 << ". [ ] " << list_of_tasks[i].task_disc << endl;
            }
            for (int i = 0; i < list_of_tasks.size(); ++i)
            {
                if (list_of_tasks[i].completed)
                    cout << i + 1 << ". [X] " << list_of_tasks[i].task_disc << endl;
            }
        }
    }

    void complete_tasks(int index)
    {
        if (list_of_tasks.empty())
            cout << "No tasks to mark as completed. Add tasks first." << endl;
        else if (index >= 1 && index <= list_of_tasks.size())
        {
            list_of_tasks[index - 1].completed = true;
            cout << "Task marked as completed: " << list_of_tasks[index - 1].task_disc << endl;
            save_tasks();
        }
        else
            cout << "Invalid task index." << endl;
    }

    void mark_complete(int index)
    {
        if (list_of_tasks.empty())
            cout << "No tasks to mark as incomplete. Add tasks first." << endl;
        else if (index >= 1 && index <= list_of_tasks.size())
        {
            if (list_of_tasks[index - 1].completed)
            {
                list_of_tasks[index - 1].completed = false;
                cout << "Task marked as incomplete: " << list_of_tasks[index - 1].task_disc << endl;
                save_tasks();
            }
            else
                cout << "Task is already incomplete." << endl;
        }
        else
            cout << "Invalid task index." << endl;
    }

    void remove_tasks(int index)
    {
        if (list_of_tasks.empty())
            cout << "No tasks to remove. Add tasks first." << endl;
        else if (index >= 1 && index <= list_of_tasks.size())
        {
            cout << "Task removed: " << list_of_tasks[index - 1].task_disc << endl;
            list_of_tasks.erase(list_of_tasks.begin() + index - 1);
            save_tasks();
        }
        else
            cout << "Task does not exist." << endl;
    }
};

int main()
{
    string username;
    cout << "Enter your name: ";
    cin >> username;

    tdl to_do_lists(username);

    int ch;

    do
    {
        cout << endl
             << "-------To-Do List -------\n"
             << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Mark Task as Complete" << endl;
        cout << "4. Mark Task as Incomplete" << endl;
        cout << "5. Remove Task" << endl;
        cout << endl
             << "Enter 0 to Exit.\n"
             << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        cout << endl;

        switch (ch)
        {
        case 0:
            cout << "Exiting the program. Goodbye!\n";
            break;
        case 1:
        {
            string task_description;
            cout << "Enter task: ";
            cin.ignore();
            getline(cin, task_description);
            to_do_lists.add_task(task_description);
            break;
        }
        case 2:
            to_do_lists.view_tasks();
            break;
        case 3:
        {
            int task_index;
            cout << "Enter the task index to mark as completed: ";
            cin >> task_index;
            to_do_lists.complete_tasks(task_index);
            break;
        }
        case 4:
        {
            int task_index;
            cout << "Enter the task index to mark as incomplete: ";
            cin >> task_index;
            to_do_lists.mark_complete(task_index);
            break;
        }
        case 5:
        {
            int task_index;
            cout << "Enter the task index to remove: ";
            cin >> task_index;
            to_do_lists.remove_tasks(task_index);
            break;
        }

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (ch != 0);

    return 0;
}
