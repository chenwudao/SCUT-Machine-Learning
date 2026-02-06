#include <iostream>
#include <fstream>   
#include <string>    
#include <iomanip>   
#include <limits>    
#include <cstring>

const int MAX_RECORDS = 100;
const int EMPTY_QUANTITY = 0;

struct Tool {
    char toolName[50];
    int quantity;
    double cost;

    Tool() : quantity(EMPTY_QUANTITY), cost(0.0) {
        toolName[0] = '\0';
    }

    Tool(const char* name, int qty, double cst) : quantity(qty), cost(cst) {
        strncpy(toolName, name, sizeof(toolName) - 1);
        toolName[sizeof(toolName) - 1] = '\0'; 
    }
};

void displayMenu();
void initializeFile(std::fstream& file, const std::string& filename);
void addTool(std::fstream& file); 
void listAllTools(std::fstream& file); 
void updateTool(std::fstream& file); 
void deleteTool(std::fstream& file); 
Tool readToolRecord(std::fstream& file, int recordNum); 
void writeToolRecord(std::fstream& file, int recordNum, const Tool& tool); 
int getValidatedRecordNumber(); 
void clearInputBuffer(); 

int main() {
    std::fstream hardwareFile("hardware.dat", std::ios::in | std::ios::out | std::ios::binary);

    if (!hardwareFile.is_open()) {
        std::cerr << "文件 'hardware.dat' 未找到或无法打开。尝试创建并初始化..." << std::endl;
        hardwareFile.open("hardware.dat", std::ios::out | std::ios::binary | std::ios::trunc);
        hardwareFile.close(); 
        hardwareFile.open("hardware.dat", std::ios::in | std::ios::out | std::ios::binary); 

        if (!hardwareFile.is_open()) {
            std::cerr << "致命错误: 无法打开/创建 hardware.dat。程序退出。" << std::endl;
            return 1;
        }
        initializeFile(hardwareFile, "hardware.dat"); 
    } else {
        std::cout << "硬件库存文件成功打开。" << std::endl;
    }

    int choice;
    do {
        displayMenu();
        std::cout << "请输入你的选择: ";
        std::cin >> choice;
        clearInputBuffer(); 

        switch (choice) {
            case 1:
                initializeFile(hardwareFile, "hardware.dat"); 
                break;
            case 2:
                addTool(hardwareFile);
                break;
            case 3:
                listAllTools(hardwareFile);
                break;
            case 4:
                updateTool(hardwareFile);
                break;
            case 5:
                deleteTool(hardwareFile);
                break;
            case 6:
                std::cout << "程序退出。再见！" << std::endl;
                break;
            default:
                std::cout << "无效的选择。请重试。" << std::endl;
                break;
        }
        std::cout << std::endl; 
    } while (choice != 6);

    hardwareFile.close(); 
    return 0;
}

void displayMenu() {
    std::cout << "--- 硬件库存管理菜单 ---" << std::endl;
    std::cout << "1. 初始化/重置库存文件" << std::endl;
    std::cout << "2. 添加新工具" << std::endl;
    std::cout << "3. 列出所有工具" << std::endl;
    std::cout << "4. 更新工具信息" << std::endl;
    std::cout << "5. 删除工具记录" << std::endl;
    std::cout << "6. 退出" << std::endl;
}

void initializeFile(std::fstream& file, const std::string& filename) {
    file.close();
    file.open(filename, std::ios::out | std::ios::binary | std::ios::trunc); 
    if (!file.is_open()) {
        std::cerr << "错误: 无法截断并重新打开文件进行初始化。" << std::endl;
        return;
    }

    Tool emptyTool;
    for (int i = 0; i < MAX_RECORDS; ++i) {
        file.write(reinterpret_cast<const char*>(&emptyTool), sizeof(Tool));
    }
    std::cout << MAX_RECORDS << " 条空记录已初始化。" << std::endl;

    file.close();
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "错误: 初始化后无法以读/写模式重新打开文件。" << std::endl;
        return;
    }

    writeToolRecord(file, 3, Tool{"Electric sander", 7, 57.98});
    writeToolRecord(file, 17, Tool{"Hammer", 76, 11.99});
    writeToolRecord(file, 24, Tool{"Jig saw", 21, 11.00});
    writeToolRecord(file, 39, Tool{"Lawn mower", 3, 79.50});
    writeToolRecord(file, 56, Tool{"Power saw", 18, 99.99});
    writeToolRecord(file, 68, Tool{"Screwdriver", 106, 6.99});
    writeToolRecord(file, 77, Tool{"Sledge hammer", 11, 21.50});
    writeToolRecord(file, 83, Tool{"Wrench", 34, 7.50});

    std::cout << "初始工具数据已加载到文件。" << std::endl;
}

void addTool(std::fstream& file) {
    int recordNum = getValidatedRecordNumber();
    if (recordNum == -1) return; 

    Tool tool = readToolRecord(file, recordNum);

    if (tool.quantity != EMPTY_QUANTITY) {
        std::cout << "记录 " << recordNum << " 已被占用，工具为: "
                  << tool.toolName << ", 数量: " << tool.quantity
                  << ", 成本: " << std::fixed << std::setprecision(2) << tool.cost << std::endl;
        std::cout << "如果要更改，请使用“更新工具”选项，或选择一个空闲记录。" << std::endl;
        return;
    }

    std::cout << "请输入工具名称 (最多49个字符): ";
    std::cin.getline(tool.toolName, sizeof(tool.toolName)); 

    std::cout << "请输入数量: ";
    while (!(std::cin >> tool.quantity) || tool.quantity < 0) {
        std::cout << "无效的数量。请输入非负整数: ";
        clearInputBuffer();
    }
    clearInputBuffer();

    std::cout << "请输入成本: ";
    while (!(std::cin >> tool.cost) || tool.cost < 0.0) {
        std::cout << "无效的成本。请输入非负数字: ";
        clearInputBuffer();
    }
    clearInputBuffer(); 

    writeToolRecord(file, recordNum, tool);
    std::cout << "工具已成功添加到记录 " << recordNum << "。" << std::endl;
}

void listAllTools(std::fstream& file) {
    std::cout << std::left << std::setw(10) << "记录号"
              << std::setw(50) << "工具名称"
              << std::setw(10) << "数量"
              << std::setw(10) << "成本" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (int i = 1; i <= MAX_RECORDS; ++i) {
        Tool tool = readToolRecord(file, i);
        if (tool.quantity != EMPTY_QUANTITY) { 
            std::cout << std::left << std::setw(10) << i
                      << std::setw(50) << tool.toolName
                      << std::setw(10) << tool.quantity
                      << std::setw(10) << std::fixed << std::setprecision(2) << tool.cost << std::endl;
        }
    }
    std::cout << std::string(80, '-') << std::endl;
}

void updateTool(std::fstream& file) {
    int recordNum = getValidatedRecordNumber();
    if (recordNum == -1) return;

    Tool tool = readToolRecord(file, recordNum);

    if (tool.quantity == EMPTY_QUANTITY) {
        std::cout << "记录 " << recordNum << " 为空。没有工具可以更新。" << std::endl;
        return;
    }

    std::cout << "当前工具: " << tool.toolName << ", 数量: " << tool.quantity
              << ", 成本: " << std::fixed << std::setprecision(2) << tool.cost << std::endl;

    std::cout << "请输入新工具名称 (最多49个字符，按Enter键保持当前): ";
    std::string newName;
    std::getline(std::cin, newName);
    if (!newName.empty()) {
        strncpy(tool.toolName, newName.c_str(), sizeof(tool.toolName) - 1);
        tool.toolName[sizeof(tool.toolName) - 1] = '\0';
    }

    std::cout << "请输入新数量 (按Enter键保持当前, 当前: " << tool.quantity << "): ";
    std::string qtyInput;
    std::getline(std::cin, qtyInput);
    if (!qtyInput.empty()) {
        try {
            int newQuantity = std::stoi(qtyInput);
            if (newQuantity >= 0) {
                tool.quantity = newQuantity;
            } else {
                std::cout << "数量无效。保持当前数量。" << std::endl;
            }
        } catch (const std::invalid_argument& ia) {
            std::cout << "数量格式无效。保持当前数量。" << std::endl;
        }
    }

    std::cout << "请输入新成本 (按Enter键保持当前, 当前: " << std::fixed << std::setprecision(2) << tool.cost << "): ";
    std::string costInput;
    std::getline(std::cin, costInput);
    if (!costInput.empty()) {
        try {
            double newCost = std::stod(costInput);
            if (newCost >= 0.0) {
                tool.cost = newCost;
            } else {
                std::cout << "成本无效。保持当前成本。" << std::endl;
            }
        } catch (const std::invalid_argument& ia) {
            std::cout << "成本格式无效。保持当前成本。" << std::endl;
        }
    }

    writeToolRecord(file, recordNum, tool);
    std::cout << "记录 " << recordNum << " 的工具信息已成功更新。" << std::endl;
}

void deleteTool(std::fstream& file) {
    int recordNum = getValidatedRecordNumber();
    if (recordNum == -1) return;

    Tool tool = readToolRecord(file, recordNum);

    if (tool.quantity == EMPTY_QUANTITY) {
        std::cout << "记录 " << recordNum << " 已经为空。没有工具可以删除。" << std::endl;
        return;
    }

    std::cout << "正在删除记录 " << recordNum << ": " << tool.toolName << ", 数量: " << tool.quantity << std::endl;
    Tool emptyTool; 
    writeToolRecord(file, recordNum, emptyTool);
    std::cout << "记录 " << recordNum << " 已成功删除。" << std::endl;
}

Tool readToolRecord(std::fstream& file, int recordNum) {
    Tool tool;
    long long offset = static_cast<long long>(recordNum - 1) * sizeof(Tool);

    file.seekg(offset, std::ios::beg);

    file.read(reinterpret_cast<char*>(&tool), sizeof(Tool));

    file.clear();

    return tool;
}

void writeToolRecord(std::fstream& file, int recordNum, const Tool& tool) {
    long long offset = static_cast<long long>(recordNum - 1) * sizeof(Tool);

    file.seekp(offset, std::ios::beg);

    file.write(reinterpret_cast<const char*>(&tool), sizeof(Tool));

    file.flush();
}

int getValidatedRecordNumber() {
    int recordNum;
    std::cout << "请输入记录号 (1-" << MAX_RECORDS << "): ";
    while (!(std::cin >> recordNum) || recordNum < 1 || recordNum > MAX_RECORDS) {
        std::cout << "记录号无效。请输入 1 到 " << MAX_RECORDS << "之间的数字: ";
        clearInputBuffer();
    }
    clearInputBuffer(); 
    return recordNum;
}

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}