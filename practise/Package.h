#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <stdexcept>

class Package {
public:
    Package(const std::string& senderName, const std::string& senderAddress, const std::string& senderCity,
            const std::string& senderState, int senderZip,
            const std::string& recipientName, const std::string& recipientAddress, const std::string& recipientCity,
            const std::string& recipientState, int recipientZip, double weight, double costPerOunce)
        : senderName(senderName), senderAddress(senderAddress), senderCity(senderCity), senderState(senderState),
          senderZip(senderZip), recipientName(recipientName), recipientAddress(recipientAddress),
          recipientCity(recipientCity), recipientState(recipientState), recipientZip(recipientZip),
          weight(weight), costPerOunce(costPerOunce) {
        if (weight <= 0 || costPerOunce <= 0) {
            throw std::invalid_argument("Weight and cost must be positive values");
        }
    }

    virtual ~Package() {}

    virtual double calculateCost() const {
        return weight * costPerOunce;
    }

    std::string senderName;
    std::string recipientName;

protected:
    std::string senderAddress, senderCity, senderState;
    int senderZip;
    std::string recipientAddress, recipientCity, recipientState;
    int recipientZip;
    double weight, costPerOunce;
};

class TwoDayPackage : public Package {
    public:
        TwoDayPackage(const std::string& sName, const std::string& sAddress, 
                      const std::string& sCity, const std::string& sState, int sZIP,
                      const std::string& rName, const std::string& rAddress, 
                      const std::string& rCity, const std::string& rState, int rZIP,
                      double weight, double costPerOunce, double flatFee)
        : Package(sName, sAddress, sCity, sState, sZIP, rName, rAddress, rCity, rState, rZIP, weight, costPerOunce),
          flatFee(flatFee) {}

        virtual double calculateCost() const override {
            return Package::calculateCost() + flatFee;
        }
        
    private:
        double flatFee;
};

class OvernightPackage : public Package {
    public:
        OvernightPackage(const std::string& sName, const std::string& sAddress, 
                         const std::string& sCity, const std::string& sState, int sZIP,
                         const std::string& rName, const std::string& rAddress, 
                         const std::string& rCity, const std::string& rState, int rZIP,
                         double weight, double costPerOunce, double feePerOunce)
        : Package(sName, sAddress, sCity, sState, sZIP, rName, rAddress, rCity, rState, rZIP, weight, costPerOunce),
          additionalFeePerOunce(feePerOunce) {}

        virtual double calculateCost() const override {
            return weight * (costPerOunce + additionalFeePerOunce);
        }
        
    private:
        double additionalFeePerOunce;
};

#endif