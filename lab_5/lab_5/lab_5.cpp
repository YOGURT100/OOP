#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;

//==================== CLASS man ====================
class man {
private:
    string surname;
    string name;
public:
    man(string s = "", string n = "") : surname(s), name(n) {}

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

//==================== BASE CLASS ====================
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
    double balance;
public:
    void input() override {
        cin >> client;
        cout << "Сумма вклада: ";
        cin >> balance;
    }

    void output() const override {
        cout << left << setw(15) << client
            << setw(10) << "Deposit"
            << setw(10) << balance << endl;
    }

    void add(double value) override {
        balance += value;
    }
};

//==================== CREDIT ====================
class credit : public common {
private:
    int card;
    double sum;
    double percent;
public:
    void input() override {
        cin >> client;
        cout << "Номер карты: ";
        cin >> card;
        cout << "Сумма кредита: ";
        cin >> sum;
        cout << "Процент: ";
        cin >> percent;
    }

    void output() const override {
        cout << left << setw(15) << client
            << setw(10) << "Credit"
            << setw(10) << sum
            << setw(10) << percent << endl;
    }

    void add(double value) override {
        sum += value;
    }
};

//==================== TEMPLATE FUNCTIONS ====================

// Инициализация
template <class T>
void init(T* arr, int n, T minVal = -50, T maxVal = 50) {
    for (int i = 0; i < n; i++)
        arr[i] = minVal + rand() % (int)(maxVal - minVal + 1);
}

// Перегрузка для char
void init(char* arr, int n, char minVal, char maxVal) {
    for (int i = 0; i < n; i++)
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
}

// Поиск минимума
template <class T>
void findMin(T* arr, int n, T& minVal, int& index) {
    minVal = arr[0];
    index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
            index = i;
        }
    }
}

// Вывод
template <class T>
void print(T* arr, int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

//==================== TEMPLATE CLASS ====================
template <class T>
class Array {
private:
    int n;
    T* Bp;
    T* Tp;

public:
    Array(int size) {
        n = size;
        Bp = new T[n];
        Tp = Bp;

        for (int i = 0; i < n; i++)
            Bp[i] = rand() % 100 - 50;
    }

    ~Array() {
        delete[] Bp;
    }

    void print() {
        for (int i = 0; i < n; i++)
            cout << Bp[i] << "\t";
        cout << endl;
    }

    void sortDesc() {
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (Bp[i] < Bp[j])
                    swap(Bp[i], Bp[j]);
    }
};

//==================== MAIN ====================
int main() {
    srand(time(0));

    // ===== БАНК =====
    int n, m;
    cout << "Количество вкладов: ";
    cin >> n;
    cout << "Количество кредитов: ";
    cin >> m;

    deposit* dep = new deposit[n];
    credit* cred = new credit[m];

    cout << "\n--- Ввод вкладов ---\n";
    for (int i = 0; i < n; i++) dep[i].input();

    cout << "\n--- Ввод кредитов ---\n";
    for (int i = 0; i < m; i++) cred[i].input();

    man search;
    cout << "\nПоиск клиента:\n";
    cin >> search;

    vector<common*> Result;

    for (int i = 0; i < n; i++)
        if (dep[i] == search) Result.push_back(&dep[i]);

    for (int i = 0; i < m; i++)
        if (cred[i] == search) Result.push_back(&cred[i]);

    double addValue;
    cout << "Добавить сумму: ";
    cin >> addValue;

    for (auto x : Result)
        x->add(addValue);

    cout << "\n--- Результат ---\n";
    for (auto x : Result)
        x->output();

    delete[] dep;
    delete[] cred;

    // ===== ШАБЛОНЫ =====
    int size = 10;

    int* a = new int[size];
    double* b = new double[size];
    char* c = new char[size];

    init(a, size);
    init(b, size);
    init(c, size, 'A', 'Z');

    cout << "\nINT:\n"; print(a, size);
    cout << "DOUBLE:\n"; print(b, size);
    cout << "CHAR:\n"; print(c, size);

    int minI, idxI;
    findMin(a, size, minI, idxI);

    double minD; int idxD;
    findMin(b, size, minD, idxD);

    char minC; int idxC;
    findMin(c, size, minC, idxC);

    cout << "\nMin int: " << minI << " index " << idxI << endl;
    cout << "Min double: " << minD << " index " << idxD << endl;
    cout << "Min char: " << minC << " index " << idxC << endl;

    delete[] a;
    delete[] b;
    delete[] c;

    // ===== КЛАСС =====
    cout << "\n--- TEMPLATE CLASS ---\n";

    Array<int> ai(10);
    ai.print();
    ai.sortDesc();
    ai.print();

    Array<double> ad(10);
    ad.print();
    ad.sortDesc();
    ad.print();

    return 0;
}