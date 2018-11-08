/*
Zaprojektowac hierarchie klas Zwierzatko, Kotek, Piesek. Kazda ma miec metode daj_glos().

Tu pytam jak defniujemy interfejs w C++ (klasa czysto abstrakcyjna itp, co daje virtual, czy potrzebny destuktor).

Zdefiniowac vector wskaznikow na zwierzatka, wrzucic tam pare kotkow i pieskow.
Dalej przechodzimy po wektorze wykonujac polimorficzny call i zwierzatka daja glos (wypas :P).
Najlepszy foreach z boost::bind, potem jakis ptr_fun, potem iteratory (czy beda const? :P) a potem zwykly for (ostatecznie).
*/
#include <iostream>
#include <limits>
#include <vector>
#include <memory>

using namespace std;

void pressEnterToContinue()
{
    cout << "press ENTER to continue" << endl;
//    cin.sync();
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getchar();
}

class Animal
{
public:
    Animal() {
        m_id = m_count++;
        cout << "Animal created, count: " << m_id << endl;
    };
    virtual ~Animal() = default;
    virtual void giveSound() const = 0;

    static int m_count;
    int m_id = 0;
};

int Animal::m_count = 0;

class Cat : public Animal
{
public:
    Cat() = default;
    void giveSound() const override {
        cout << m_id << " Cat says Miauuu" << endl;
    }
};

class Dog : public Animal
{
public:
    Dog() = default;
    void giveSound() const override {
        cout << m_id << " Dog says Hau Hau" << endl;
    }
};

int main()
{
    Dog dog;
    dog.giveSound();

    unique_ptr<Dog> dogU {new Dog()};
    dogU->giveSound();

    vector<unique_ptr<Animal>> animals;
    
    animals.emplace_back(new Dog{});
    animals.emplace_back(new Dog{});
    animals.emplace_back(new Cat{});
    animals.emplace_back(new Dog{});
    animals.emplace_back(new Cat{});

    for (const auto& animal : animals) {
        animal->giveSound();
    }

    pressEnterToContinue();

    return 0;
}

