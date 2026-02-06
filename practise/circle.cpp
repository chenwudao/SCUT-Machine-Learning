#include <iostream>
#include <iomanip>

class circle{
    public:
        circle(double r) : radius(r) {}
        virtual double area(){
            return pi * radius * radius;
        }
        virtual double volumn(){
            return 0;
        }
        double pi = 3.14;

    protected:
        double radius;
};

class sphere : public circle {
    public:
        sphere(double r) : circle(r) {}
        double area() override {
            return 4 * pi * radius * radius;
        }
        double volumn() override {
            return (4.0 / 3.0) * pi * radius * radius * radius;
        }
};

class cylinder : public circle{
    public:
        cylinder(double r, double h) : circle(r), height(h) {}

        double area() override{
            return 2 * pi * radius * (radius + height);
        }
        double volumn() override{
            return pi * radius * radius * height;
        }

    private:
        double height;
};

int main(){
    double r1, r2, h;
    std::cout << std::fixed << std::setprecision(2); 
    
    while(std::cin >> r1 >> r2 >> h) {
        sphere s(r1);
        cylinder cy(r2, h);

        std::cout << "sphere: area:"  << s.area() << " volume:" << s.volumn() << std::endl;
        std::cout << "column: area:"  << cy.area() << " volume:" << cy.volumn() << std::endl;
    }
    return 0;
}
