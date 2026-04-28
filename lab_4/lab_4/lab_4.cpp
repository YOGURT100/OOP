#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

//==================== КЛАСС man ====================
class man {
private:
    string surname;
    string name;
public:
    man(string s = "", string n = "") : surname(s), name(n) {}

    string getSurname() const { return surname; }
    string getName() const { return name; }

    friend istream& operator>>(istream& in, man& m) {
        cout << "Фамилия: ";
        in >> m.surname;
        cout << "Имя: ";
        in >> m.name;
        return in;
    }

    friend ostream& operator<<(ostream& out, const man& m) {
        out << m.surname << " " << m.name;
        return out;
    }

    bool operator==(const man& other) const {
        return surname == other.surname && name == other.name;
    }
};

//==================== БАЗОВЫЙ КЛАСС ====================
class common {
protected:
    man client;

public:
    virtual void input() = 0;
    virtual void output() const = 0;
    virtual void add(double value) = 0;

    bool operator==(const man& m) const {
        return client == m;
    }

    virtual ~common() {}
};

//==================== DEPOSIT ====================
class deposit : public common {
private:
    double balance; // сумма на счете

public:
    deposit(double b = 0) : balance(b) {}

    void input() override {
        cin >> client;
        cout << "Сумма вклада: ";
        cin >> balance;
    }

    void output() const override {
        cout << left << setw(15) << client
            << setw(15) << "Deposit"
            << setw(15) << balance << endl;
    }

    void add(double value) override {
        balance += value;
    }

    friend istream& operator>>(istream& in, deposit& d) {
        d.input();
        return in;
    }

    friend ostream& operator<<(ostream& out, const deposit& d) {
        d.output();
        return out;
    }
};

//==================== CREDIT ====================
class credit : public common {
private:
    int cardNumber;
    double creditSum;
    double percent;

public:
    credit(int c = 0, double s = 0, double p = 0)
        : cardNumber(c), creditSum(s), percent(p) {
    }

    void input() override {
        cin >> client;
        cout << "Номер карты: ";
        cin >> cardNumber;
        cout << "Сумма кредита: ";
        cin >> creditSum;
        cout << "Процент: ";
        cin >> percent;
    }

    void output() const override {
        cout << left << setw(15) << client
            << setw(15) << "Credit"
            << setw(10) << cardNumber
            << setw(10) << creditSum
            << setw(10) << percent << endl;
    }

    void add(double value) override {
        creditSum += value;
    }

    friend istream& operator>>(istream& in, credit& c) {
        c.input();
        return in;
    }

    friend ostream& operator<<(ostream& out, const credit& c) {
        c.output();
        return out;
    }
};

//==================== MAIN ====================
int main() {
    int n, m;

    cout << "Количество вкладов: ";
    cin >> n;
    deposit* dep = new deposit[n];

    cout << "Количество кредитов: ";
    cin >> m;
    credit* cred = new credit[m];

    // Ввод
    cout << "\n--- Ввод вкладов ---\n";
    for (int i = 0; i < n; i++) {
        cout << "\nВклад #" << i + 1 << endl;
        cin >> dep[i];
    }

    cout << "\n--- Ввод кредитов ---\n";
    for (int i = 0; i < m; i++) {
        cout << "\nКредит #" << i + 1 << endl;
        cin >> cred[i];
    }

    // Поиск
    man search;
    cout << "\nВведите клиента для поиска:\n";
    cin >> search;

    vector<common*> Result;

    for (int i = 0; i < n; i++) {
        if (dep[i] == search)
            Result.push_back(&dep[i]);
    }

    for (int i = 0; i < m; i++) {
        if (cred[i] == search)
            Result.push_back(&cred[i]);
    }

    // Добавление суммы
    double addValue;
    cout << "\nВведите сумму для добавления: ";
    cin >> addValue;

    for (auto obj : Result) {
        obj->add(addValue);
    }

    // Вывод
    cout << "\n--- Результаты ---\n";
    cout << left << setw(15) << "Клиент"
        << setw(15) << "Тип"
        << setw(10) << "Карта"
        << setw(10) << "Сумма"
        << setw(10) << "Процент" << endl;

    for (auto obj : Result) {
        obj->output();
    }

    delete[] dep;
    delete[] cred;

    return 0;
}