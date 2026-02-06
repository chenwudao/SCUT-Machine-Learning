#include <iostream>
#include <vector>

class Complex{
private:
    double rel,img;

public:
    Complex(double r=0,double i=0);
    Complex operator + (const Complex &a)const;
    Complex operator - (const Complex &a)const;
    Complex operator * (const Complex &a)const;
    friend std :: ostream & operator <<(std :: ostream &os, const Complex &a);
};

Complex :: Complex(double r,double i){
    rel = r;
    img = i;
}

Complex Complex :: operator + (const Complex &a)const{
    return Complex(rel + a.rel,img + a.img);
}

Complex Complex :: operator - (const Complex &a)const{
    return Complex(rel - a.rel,img - a.img);
}

Complex Complex :: operator * (const Complex &a)const{
    return Complex(rel * a.rel - img * a.img,rel * a.img + img * a.rel);
}

std::ostream & operator <<(std::ostream &os, const Complex &a){
    if(a.rel == 0 && a.img == 0) os << 0;
    
    else if(a.rel == 0) os << a.img << "i";

    else if(a.img == 0) os << a.rel;

    else if(a.img > 0) os << a.rel << "+" << a.img << "i"; 

    else os << a.rel << a.img << "i";

    return os;
}

int main() {
    double a, b, c, d;
    std::vector<Complex> v;

    while (std::cin >> a >> b >> c >> d) {
        Complex x(a, b), y(c, d);
        v.push_back(x + y);
        v.push_back(x - y);
        v.push_back(x * y);
    }

    for (const auto& complex : v) {
        std::cout << complex << std::endl;
    }
    
    return 0;
}