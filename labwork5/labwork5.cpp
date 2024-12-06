#include <iostream>
#include <fstream>

using namespace std;

// Структура для дроби
struct Fraction {
    int a; // Числитель
    int b; // Знаменатель
};

// Функция для сложения двух дробей
Fraction addFractions(const Fraction& f1, const Fraction& f2) {
    Fraction result;
    result.a = f1.a * f2.b + f2.a * f1.b; // Общий числитель
    result.b = f1.b * f2.b;               // Общий знаменатель
    return result;
}

// Функция для вычитания двух дробей
Fraction subtractFractions(const Fraction& f1, const Fraction& f2) {
    Fraction result;
    result.a = f1.a * f2.b - f2.a * f1.b; // Общий числитель
    result.b = f1.b * f2.b;               // Общий знаменатель
    return result;
}

// Функция для сокращения дроби
void simplifyFraction(Fraction& frac) {
    int gcd = [](int x, int y) {
        while (y != 0) {
            int temp = y;
            y = x % y;
            x = temp;
        }
        return x;
        }(abs(frac.a), abs(frac.b));

    frac.a /= gcd;
    frac.b /= gcd;

    // Корректируем знак знаменателя
    if (frac.b < 0) {
        frac.a = -frac.a;
        frac.b = -frac.b;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    Fraction f1, f2, sum, difference;

    // Ввод данных
    cout << "Введите первую дробь (числитель и знаменатель): ";
    cin >> f1.a >> f1.b;
    cout << "Введите вторую дробь (числитель и знаменатель): ";
    cin >> f2.a >> f2.b;

    // Проверяем на нулевой знаменатель
    if (f1.b == 0 || f2.b == 0) {
        cerr << "Ошибка: знаменатель не может быть равен 0." << endl;
        return 1;
    }

    // Выполняем арифметические операции
    sum = addFractions(f1, f2);
    difference = subtractFractions(f1, f2);

    // Сокращаем дроби
    simplifyFraction(sum);
    simplifyFraction(difference);

    // Открываем файл для записи
    ofstream outFile("results.txt");
    if (!outFile) {
        cerr << "Ошибка: не удалось открыть файл для записи." << endl;
        return 1;
    }

    // Записываем результаты в файл
    outFile << f1.a << "/" << f1.b << " + " << f2.a << "/" << f2.b
        << " = " << sum.a << "/" << sum.b << endl;
    outFile << f1.a << "/" << f1.b << " - " << f2.a << "/" << f2.b
        << " = " << difference.a << "/" << difference.b << endl;

    outFile.close();

    // Выводим результат в консоль
    cout << "Результаты записаны в файл 'results.txt'." << endl;

    return 0;
}