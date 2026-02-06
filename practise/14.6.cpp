#include <iostream> 
#include <fstream>
#include <string> 
#include <iomanip>
#include <limits>

bool readMasterRecord(std::ifstream& file, int& account, std::string& name, double& balance) {
    if (file >> account) { 
        file >> name >> balance; 
        return true;
    }
    return false; 
}

bool readTransactionRecord(std::ifstream& file, int& account, double& amount) {
    if (file >> account) { 
        file >> amount;    
        return true;
    }
    return false; 
}

void writeMasterRecord(std::ofstream& file, int account, const std::string& name, double balance) {
    file << account << " " << name << " " << std::fixed << std::setprecision(2) << balance << std::endl;
}

int main() {
    const std::string OLD_MASTER_FILE = "oldmast.dat";
    const std::string TRANSACTION_FILE = "trans.dat";
    const std::string NEW_MASTER_FILE = "newmast.dat";

    std::ifstream oldMaster(OLD_MASTER_FILE);
    std::ifstream transaction(TRANSACTION_FILE);
    std::ofstream newMaster(NEW_MASTER_FILE);

    if (!oldMaster.is_open()) {
        std::cerr << "错误: 无法打开文件 " << OLD_MASTER_FILE << std::endl;
        return 1; 
    }
    if (!transaction.is_open()) {
        std::cerr << "错误: 无法打开文件 " << TRANSACTION_FILE << std::endl;
        oldMaster.close();
        return 1;
    }
    if (!newMaster.is_open()) {
        std::cerr << "错误: 无法创建/打开文件 " << NEW_MASTER_FILE << std::endl;
        oldMaster.close();
        transaction.close();
        return 1;
    }

    std::cout << "文件匹配程序开始运行..." << std::endl;

    int oldMasterAccount = 0;
    std::string oldMasterName = "";
    double oldMasterBalance = 0.0;
    bool hasOldMasterRecord = readMasterRecord(oldMaster, oldMasterAccount, oldMasterName, oldMasterBalance);

    int transactionAccount = 0;
    double transactionAmount = 0.0;
    bool hasTransactionRecord = readTransactionRecord(transaction, transactionAccount, transactionAmount);

    while (hasOldMasterRecord || hasTransactionRecord) {
        if (hasOldMasterRecord && hasTransactionRecord) {
            if (oldMasterAccount < transactionAccount) {
                writeMasterRecord(newMaster, oldMasterAccount, oldMasterName, oldMasterBalance);
                hasOldMasterRecord = readMasterRecord(oldMaster, oldMasterAccount, oldMasterName, oldMasterBalance);
            } else if (oldMasterAccount > transactionAccount) {
                std::cerr << "错误: Unmatched transaction record for account number " << transactionAccount << std::endl;
                hasTransactionRecord = readTransactionRecord(transaction, transactionAccount, transactionAmount);
            } else { 
                oldMasterBalance += transactionAmount;
                writeMasterRecord(newMaster, oldMasterAccount, oldMasterName, oldMasterBalance);

                hasOldMasterRecord = readMasterRecord(oldMaster, oldMasterAccount, oldMasterName, oldMasterBalance);
                hasTransactionRecord = readTransactionRecord(transaction, transactionAccount, transactionAmount);
            }
        } else if (hasOldMasterRecord) {
            writeMasterRecord(newMaster, oldMasterAccount, oldMasterName, oldMasterBalance);
            hasOldMasterRecord = readMasterRecord(oldMaster, oldMasterAccount, oldMasterName, oldMasterBalance);
        } else { 
            std::cerr << "错误: Unmatched transaction record for account number " << transactionAccount << std::endl;
            hasTransactionRecord = readTransactionRecord(transaction, transactionAccount, transactionAmount);
        }
    }

    std::cout << "文件匹配程序执行完毕。" << std::endl;

    oldMaster.close();
    transaction.close();
    newMaster.close();

    return 0;
}