#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
using namespace std;

//==================== FIO ====================
class fio {
private:
    string surname;
    string name;

public:
    fio(string s = "", string n = "") : surname(s), name(n) {}

    string getSurname() const { return surname; }
    string getName() const { return name; }

    // ВВОД с проверкой
    friend istream& operator>>(istream& in, fio& f) {
        cout << "Фамилия: ";
        in >> f.surname;
        if (f.surname.empty())
            throw runtime_error("Ошибка: пустая фамилия");

        cout << "Имя: ";
        in >> f.name;
        if (f.name.empty())
            throw runtime_error("Ошибка: пустое имя");

        return in;
    }

    // ВЫВОД
    friend ostream& operator<<(ostream& out, const fio& f) {
        out << f.surname << " " << f.name;
        return out;
    }

    bool operator==(const fio& other) const {
        return surname == other.surname && name == other.name;
    }
};

//==================== BANK ====================
class bank {
private:
    fio man;
    double sum;

public:
    bank(double s = 0) : sum(s) {}

    // ВВОД
    friend istream& operator>>(istream& in, bank& b) {
        try {
            in >> b.man;

            cout << "Сумма: ";
            in >> b.sum;

            if (in.fail() || b.sum < 0)
                throw runtime_error("Ошибка: некорректная сумма");

        }
        catch (...) {
            cout << "Ошибка ввода! Повторите.\n";
            in.clear();
            in.ignore(1000, '\n');
            throw; // проброс выше
        }
        return in;
    }

    // ВЫВОД
    friend ostream& operator<<(ostream& out, const bank& b) {
        out << left << setw(20) << b.man
            << setw(15) << b.sum;
        return out;
    }

    // +
    bank operator+(double value) {
        if (value < 0)
            throw runtime_error("Ошибка: нельзя добавить отрицательное значение");

        bank temp = *this;
        temp.sum += value;
        return temp;
    }

    // СРАВНЕНИЕ
    bool operator==(const fio& f) const {
        return man == f;
    }

    double getSum() const { return sum; }
};

//==================== ПОИСК > СУММЫ ====================
bank* findGreater(bank* arr, int n, double value, int& sizeRes) {
    vector<bank> temp;

    for (int i = 0; i < n; i++) {
        if (arr[i].getSum() > value)
            temp.push_back(arr[i]);
    }

    sizeRes = temp.size();

    bank* result = new bank[sizeRes];
    for (int i = 0; i < sizeRes; i++)
        result[i] = temp[i];

    return result;
}

//==================== MAIN ====================
int main() {
    try {
        int n;
        cout << "Количество клиентов: ";
        cin >> n;

        if (n <= 0)
            throw runtime_error("Ошибка: неверный размер массива");

        bank* arr = new bank[n];

        // ВВОД
        cout << "\n--- Ввод ---\n";
        for (int i = 0; i < n; i++) {
            cout << "\nКлиент #" << i + 1 << endl;
            cin >> arr[i];
        }

        // ВЫВОД
        cout << "\n--- Все клиенты ---\n";
        cout << left << setw(20) << "ФИО" << setw(15) << "Сумма" << endl;
        for (int i = 0; i < n; i++)
            cout << arr[i] << endl;

        // ПОИСК клиента
        fio search;
        cout << "\nПоиск клиента:\n";
        cin >> search;

        double addValue;
        cout << "Введите сумму для добавления: ";
        cin >> addValue;

        for (int i = 0; i < n; i++) {
            if (arr[i] == search) {
                arr[i] = arr[i] + addValue;
            }
        }

        // ПОИСК > заданной суммы
        double limit;
        cout << "\nВведите порог: ";
        cin >> limit;

        int sizeRes;
        bank* Rez = findGreater(arr, n, limit, sizeRes);

        // ВЫВОД РЕЗУЛЬТАТА
        cout << "\n--- Результаты (сумма > " << limit << ") ---\n";
        cout << left << setw(20) << "ФИО" << setw(15) << "Сумма" << endl;

        for (int i = 0; i < sizeRes; i++)
            cout << Rez[i] << endl;

        delete[] arr;
        delete[] Rez;
    }
    catch (exception& e) {
        cout << "\nКритическая ошибка: " << e.what() << endl;
    }

    return 0;
}