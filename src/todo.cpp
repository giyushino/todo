#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <map>

void getTasks(const char* file_path, std::map<std::string, std::vector<std::string>> &tasks) {
    std::string tempLine;
    std::fstream taskFile(file_path);
    std::string lastTaskLevel;
    
    while (getline (taskFile, tempLine)) {
        if (tempLine == "urgent" || tempLine == "important" || tempLine == "medium" || tempLine == "low") {
            lastTaskLevel = tempLine;
        } else {
            tasks[lastTaskLevel].push_back(tempLine);
        }
    }
}
 
void printColoredBox(const std::string &level, const std::string &color, const std::vector<std::string> &box) {
    int width = level.length() + 2;
    
    const std::string RESET = "\033[0m";
    std::cout << color;
    // Top border
    std::cout << box[0];
    for (int i = 0; i < width; i++) {
        std::cout << box[5];
    }
    std::cout << box[1] << std::endl;
    
    // Middle with text
    std::cout << box[4] << " " << level << " " << box[4] << std::endl;
    
    // Bottom border
    std::cout << box[2];
    for (int i = 0; i < width; i++) {
        std::cout << box[5];
    }
    std::cout << box[3] << RESET << std::endl;
}

// Usage:

void printTasks(std::map<std::string, std::vector<std::string>> &tasks, const std::vector<std::string> &taskLevels, 
                const std::vector<std::string> &styles, const std::vector<std::string> &colors, const std::vector<std::string> &box) {
    for (std::string level: taskLevels) {
        const std::string RESET = "\033[0m";
        
        if (level == "urgent") {
            printColoredBox(level, colors[1], box);
            for (std::string task: tasks[level]) {
                std::cout << colors[1] << " • " <<  task << std::endl; 
            }
        } else if (level == "important") {
            printColoredBox(level, colors[2], box);
            for (std::string task: tasks[level]) {
                std::cout << colors[2] << " • "<< task << std::endl; 
            }
        } else if (level == "medium") {
            printColoredBox(level, colors[4], box);
            for (std::string task: tasks[level]) {
                std::cout << colors[4] << " • "<< task << std::endl; 
            }
        } else {
            printColoredBox(level, colors[3], box);
            for (std::string task: tasks[level]) {
                std::cout << colors[3] << " • " << task << std::endl; 
            }
        }

        std::cout << RESET << std::endl;
    }
}

void writeToFile(const char* file_path, std::map<std::string, std::vector<std::string>> &tasks, const std::vector<std::string> &taskLevels) {
    std::ofstream taskFile(file_path);
    for (std::string level: taskLevels) {
        taskFile << level << std::endl; 
        for (std::string task: tasks[level]) {
            taskFile << task << std::endl; 
        }
    }
    taskFile.close();
}

int changeTasks(std::map<std::string, std::vector<std::string>> &tasks, const std::vector<std::string> &taskLevels, 
                const std::vector<std::string> &styles, const std::vector<std::string> &colors, const std::vector<std::string> &box) {
    std::string userInput;
    std::map<std::string, std::string> urgencyNumbers;
    urgencyNumbers["1"] = "urgent";
    urgencyNumbers["2"] = "important";
    urgencyNumbers["3"] = "medium";
    urgencyNumbers["4"] = "low";

    
    while (userInput != "3") {
        printTasks(tasks, taskLevels, styles, colors, box);
        std::cout << "Do you want to (1) add a task or (2) remove a task? To exit, press (3)" << std::endl << "Enter: ";
        std::getline(std::cin, userInput);

        if (userInput == "1") {
            std::cout << "Task Urgency" << std::endl;
            std::cout << box[0];
            for (int i = 0; i < 50; i++) {
                std::cout << box[5];
            }
            std::cout << box[1] << std::endl;
            std::cout << box[4] << " 1: Urgent || 2: Important || 3: Medium || 4: Low " << box[4] << std::endl;
            std::cout << box[2];
            for (int i = 0; i < 50; i++) {
                std::cout << box[5];
            }
            std::cout << box[3] << std::endl;
             
            std::string taskUrgency, newTask;
            std::cout << "Task Urgency: ";
            std::getline(std::cin, taskUrgency);
            std::cout << "Task: ";
            std::getline(std::cin, newTask);

            try {
                tasks[urgencyNumbers[taskUrgency]].push_back(newTask); 
            } catch (...) {
                std::cout << "You didn't enter either 1, 2, 3, or 4"<< std::endl;
            }
        } else if (userInput == "2") {
            std::string taskUrgency, newTask;
            std::cout << "Task Urgency" << std::endl;
            std::cout << box[0];
            for (int i = 0; i < 50; i++) {
                std::cout << box[5];
            }
            std::cout << box[1] << std::endl;
            std::cout << box[4] << " 1: Urgent || 2: Important || 3: Medium || 4: Low " << box[4] << std::endl;
            std::cout << box[2];
            for (int i = 0; i < 50; i++) {
                std::cout << box[5];
            }
            std::cout << box[3] << std::endl;
            std::cout << "Level to remove task from: ";
            std::getline(std::cin, taskUrgency);

            int count = 0; 
            if (taskUrgency == "1" || taskUrgency == "2" || taskUrgency == "3" || taskUrgency == "4") {
                for (std::string task: tasks[urgencyNumbers[taskUrgency]]) {
                    count++;
                    std::cout << "Task "<< count << ": " << task << std::endl;
                }
            }
            std::cout << "Task to remove: "; std::getline(std::cin, newTask);
            try {
                int index = std::stoi(newTask);
                tasks[urgencyNumbers[taskUrgency]].erase(tasks[urgencyNumbers[taskUrgency]].begin() + index - 1);
            } catch (...) {
                std::cout << "something went wrong"; // most descriptive error message!
            }
        }
    }
    return 0;  
}


int main(int argc, char *argv[]) {
    const std::vector<std::string> taskLevels = {"urgent", "important", "medium", "low"};
    const std::vector<std::string> box = {"╭", "╮", "╰", "╯", "│", "─"};
    std::map<std::string, std::vector<std::string>> tasks;
    std::string userInput;
    tasks["urgent"] = {};
    tasks["important"] = {};
    tasks["medium"] = {};
    tasks["low"] = {};

    // no file inputted
    if (argc == 1) {
        std::cout << "No file path provided";
        return 0;
    }

    // otherwise try to read the file into the vector     
    try {
        getTasks(argv[1], tasks);
    }
    catch (...) {
        std::cout << "No valid file path was passed through";
        return 0;
    }
    
    // text colors
    const std::vector<std::string> colors = {
        "\033[30m", "\033[31m", "\033[32m", "\033[33m",
        "\033[34m", "\033[35m", "\033[36m", "\033[37m",
        "\033[90m", "\033[91m", "\033[92m", "\033[93m",
        "\033[94m", "\033[95m", "\033[96m", "\033[97m"
    };

    // text colors
    const std::vector<std::string> styles = {
        "\033[1m",  // bold
        "\033[2m",  // dim
        "\033[3m",  // italic
        "\033[4m",  // underline
        "\033[5m",  // blink
        "\033[7m",  // reverse
        "\033[9m"   // strikethrough
    };

    std::string todoApp = R"(
    ████████╗ ██████╗         ██████╗  ██████╗      █████╗ ██████╗ ██████╗ 
    ╚══██╔══╝██╔═══██╗        ██╔══██╗██╔═══██╗    ██╔══██╗██╔══██╗██╔══██╗
       ██║   ██║   ██║        ██║  ██║██║   ██║    ███████║██████╔╝██████╔╝
       ██║   ██║   ██║        ██║  ██║██║   ██║    ██╔══██║██╔═══╝ ██╔═══╝ 
       ██║   ╚██████╔╝        ██████╔╝╚██████╔╝    ██║  ██║██║     ██║     
       ╚═╝    ╚═════╝         ╚═════╝  ╚═════╝     ╚═╝  ╚═╝╚═╝     ╚═╝     
    )";
    std::cout << todoApp << std::endl; 
    //printTasks(tasks, taskLevels, styles, colors, box);
    changeTasks(tasks, taskLevels, styles, colors, box);
    writeToFile(argv[1], tasks, taskLevels);
    return 0;
}
