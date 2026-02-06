#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
    std::ofstream oldMasterFile("oldmast.dat");

    if (!oldMasterFile.is_open()) {
        std::cerr << "错误: 无法创建 oldmast.dat 文件" << std::endl;
        return 1;
    }

    oldMasterFile << std::fixed << std::setprecision(2);

    oldMasterFile << "100 Alan_Jones 348.17" << std::endl;
    oldMasterFile << "300 Mary_Smith 27.19" << std::endl;
    oldMasterFile << "500 Sam_Sharp 0.00" << std::endl;
    oldMasterFile << "700 Suzy_Green -14.22" << std::endl;

    oldMasterFile.close();
    std::cout << "oldmast.dat 文件已创建并填充数据。" << std::endl;

    std::ofstream transactionFile("trans.dat");

    if (!transactionFile.is_open()) {
        std::cerr << "错误: 无法创建 trans.dat 文件" << std::endl;
        return 1;
    }

    transactionFile << std::fixed << std::setprecision(2);

    transactionFile << "100 27.14" << std::endl;
    transactionFile << "300 62.11" << std::endl;
    transactionFile << "400 100.56" << std::endl;
    transactionFile << "900 82.10" << std::endl;

    transactionFile.close();
    std::cout << "trans.dat 文件已创建并填充数据。" << std::endl;

    return 0;
}