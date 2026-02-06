#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;

class Animal{
  public:
      Animal(){};
      virtual void sound(){
          cout << "~";    
      }
      ~Animal(){};
};

class Cat : public Animal{
    public:
        Cat(){};
        void sound() override{
            cout << "meow";
        }
        ~Cat(){};
};

class Dog : public Animal{
    public:
        Dog(){};
        void sound() override{
            cout << "wang";
        }
        ~Dog(){};
};

class Tiger : public Animal{
    public:
        Tiger(){};
        void sound() override{
            cout << "howl";
        }
        ~Tiger(){};
};

int main(){
    Animal* ptr = nullptr;
    Cat cat;
    Dog dog;
    Tiger tiger;
    string inputanimal;
    vector<string> inputanimals;

    while (true) {
        getline(cin, inputanimal);
        if (inputanimal.empty()) break; 
        if (inputanimal == "cat" || inputanimal == "dog" || inputanimal == "tiger") {
            inputanimals.push_back(inputanimal);
        }
    }

    for(int i = 0; i < inputanimals.size(); ++i){
        if(inputanimals[i] == "cat"){
            ptr = &cat;
        }else if(inputanimals[i] == "dog"){
            ptr = &dog;
        }else if(inputanimals[i] == "tiger"){
            ptr = &tiger;
        }
        ptr->sound();
        cout << endl;
    }
    return 0;
}