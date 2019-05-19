#include <iostream>

using namespace std;

enum Kind_transport {
    car, SUV, tank
};

// Вспомогательный класс, описывающий средство передвижения
class Transport {

    friend class Ingeneer;     // Инженеры шарят в транспорте

    Kind_transport kind;  //вид транспорта

    int complexity;   // Сложность дела



public:

    const char *description;    // Краткое описание транспорта

    Transport(Kind_transport choice, int hard, const char *description) : kind(choice), description(description),
                                                                          complexity(hard) {}

};

//Абстрактный класс инженера который шарит
class Ingeneer {

protected:

    int Skills;      // навыки у инженера от 1 до 10

    Ingeneer *next;    // более шарящий инженер, который всё разрулит синей изолентой

    virtual void Breakbuild(const char *description) {}    // инженер построил

public:

    Ingeneer(int skills) : Skills(skills) {}

    virtual ~Ingeneer() {
        if (next) {
            delete next;
        }
    }

    //Добавляет в цепочку ответственности более шарящего инженера,если этот невывозит
    Ingeneer *setNext(Ingeneer *ingeneer) {
        next = ingeneer;
        return next;
    }

    //Инженер начинает строить, если тяжело передаёт более опытному колеге
    void Build(Transport *transport) {
        if (Skills < transport->complexity) {
            if (next) {
                next->Build(transport);
            } else {
                std::cout << "Тут не поможет даже синяя изолента." << std::endl;
            }
        } else {
            Breakbuild(transport->description);
        }
    }
};

//Работающие инженеры на заводе
class Vasya : public Ingeneer {

protected:

    void Breakbuild(const char *description) {
        cout << description << "-сделано Васькой с ваc пузырь беленькой" << endl;
    }

public:

    Vasya(int Skills) : Ingeneer(Skills) {}
};

class Petrovich : public Ingeneer {

protected:

    void Breakbuild(const char *description) {
        cout << description << "-сделано Петровичем с ваc яшик беленькой" << endl;
    }

public:

    Petrovich(int Skills) : Ingeneer(Skills) {}
};

class Mihalich : public Ingeneer {

protected:

    void Breakbuild(const char *description) {
        cout << description << "-сделано Михалычем с вас трубопровод от ликёроводочного!" << endl;
    }

public:

    Mihalich(int Skills) : Ingeneer(Skills) {}
};


int main() {
    Ingeneer *ingeneer = new Vasya(3);
    ingeneer->setNext(new Petrovich(5))->setNext(new Mihalich(10));// добавляем ему двух опытных коллег

    ingeneer->Build(new Transport(car,11, "Копейка, чтобы хотя бы ездила"));
    ingeneer->Build(new Transport(SUV,9, "Внедорожник попсовый, чтобы дворниками девочонок соскребать можно было"));
    ingeneer->Build(new Transport(tank,10, "Танк,чтобы пробок и российских дорог не боятся"));

    return 0;
}