// Lab_02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <numbers>
#include <iomanip>

float mean(float const psi[], float const pdf[], float const dv, unsigned size)
{
    float sum = 0.f;
    for (int i = 0; i < size; ++i)
        sum += pdf[i] * psi[i];
    return dv * sum;
}

float mean_1(float const psi[], float const pdf[], float const dv, unsigned start, unsigned end)
{
    if (start == end)
        return psi[start] * pdf[start] * dv;
    float mid = (start + end) / 2;
    return mean_1(psi, pdf, dv, start, mid) + mean_1(psi, pdf, dv, mid + 1, end);
}

float mean_2(float const psi[], float const pdf[], float const dv, unsigned size)
{
    float* psi_ = new float[size];
    for (int i = 0; i < size; ++i) {
        psi_[i] = psi[i] * pdf[i] * dv;
    }
    int step = 1;
    while (step < size) {
        for (int i = 0; i < size - step; i += 2 * step)
            psi_[i] += psi_[i + step];
        step *= 2;
    }
    return psi_[0];
}

float mean_3(float const psi[], float const pdf[], float const dv, unsigned size)
{
    float sum = 0.f;
    float c = 0.f;
    for (int i = 0; i < size; ++i) {
        float y = psi[i] * pdf[i] - c;
        float t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum * dv;
}

float mean_4(float const psi[], float const pdf[], float const dv, unsigned size)
{
    float sum = 0.f;
    for (int i = 0; i < size; ++i)
        sum = fma(psi[i], pdf[i], sum);
    return dv * sum;
}

double mean_5(float const psi[], float const pdf[], float const dv, unsigned size)
{
    double sum = 0.0;
    for (int i = 0; i < size; ++i)
        sum += static_cast<double>(psi[i]) * static_cast<double>(pdf[i]);
    return static_cast<double>(dv) * sum;
}

void MaxwellDistributionTest(double T)
{
    const double dv = 1e-3;
    const int size = 1e7;
    float* psi = new float[size], * psi_2 = new float[size], * pdf = new float[size];
    double nu = -(size / 2) * dv;
    for (int i = 0; i < size; ++i) {
        psi[i] = 1;
        psi_2[i] = abs(nu);
        pdf[i] = 1.0 / sqrt(T * std::numbers::pi) * exp(-(nu) * (nu) / T);
        nu += dv;
    }
    std::cout << "Maxwell distribution (expected res = 1.0000000000)\n";
    std::cout << "mean:   " << std::fixed << std::setprecision(10) << mean(psi, pdf, dv, size) << ' ' << abs(mean(psi, pdf, dv, size) - 1.0) << '\n';
    std::cout << "mean_1: " << std::fixed << std::setprecision(10) << mean_1(psi, pdf, dv, 0, size - 1) << ' ' << abs(mean_1(psi, pdf, dv, 0, size - 1) - 1.0) << '\n';
    std::cout << "mean_2: " << std::fixed << std::setprecision(10) << mean_2(psi, pdf, dv, size) << ' ' << abs(mean_2(psi, pdf, dv, size) - 1.0) << '\n';
    std::cout << "mean_3: " << std::fixed << std::setprecision(10) << mean_3(psi, pdf, dv, size) << ' ' << abs(mean_3(psi, pdf, dv, size) - 1.0) << '\n';
    std::cout << "mean_4: " << std::fixed << std::setprecision(10) << mean_4(psi, pdf, dv, size) << ' ' << abs(mean_4(psi, pdf, dv, size) - 1.0) << '\n';
    std::cout << "mean_5: " << std::fixed << std::setprecision(10) << mean_5(psi, pdf, dv, size) << ' ' << abs(mean_5(psi, pdf, dv, size) - 1.0) << '\n';
    std::cout << "\nNon-trivial average (expected res = " << std::setprecision(10) << sqrt(T / std::numbers::pi) << ")\n";
    std::cout << "mean:   " << std::fixed << std::setprecision(10) << mean(psi_2, pdf, dv, size) << ' ' << abs(mean(psi_2, pdf, dv, size) - sqrt(T / std::numbers::pi)) << '\n';
    std::cout << "mean_1: " << std::fixed << std::setprecision(10) << mean_1(psi_2, pdf, dv, 0, size - 1) << ' ' << abs(mean_1(psi_2, pdf, dv, 0, size - 1) - sqrt(T / std::numbers::pi)) << '\n';
    std::cout << "mean_2: " << std::fixed << std::setprecision(10) << mean_2(psi_2, pdf, dv, size) << ' ' << abs(mean_2(psi_2, pdf, dv, size) - sqrt(T / std::numbers::pi)) << '\n';
    std::cout << "mean_3: " << std::fixed << std::setprecision(10) << mean_3(psi_2, pdf, dv, size) << ' ' << abs(mean_3(psi_2, pdf, dv, size) - sqrt(T / std::numbers::pi)) << '\n';
    std::cout << "mean_4: " << std::fixed << std::setprecision(10) << mean_4(psi_2, pdf, dv, size) << ' ' << abs(mean_4(psi_2, pdf, dv, size) - sqrt(T / std::numbers::pi)) << '\n';
    std::cout << "mean_5: " << std::fixed << std::setprecision(10) << mean_5(psi_2, pdf, dv, size) << ' ' << abs(mean_5(psi_2, pdf, dv, size) - sqrt(T / std::numbers::pi)) << '\n';
}

int main()
{
    while (true) {
        double T;
        std::cout << "Maxwell Distribution Test for T = ";
        std::cin >> T;
        MaxwellDistributionTest(T);
        std::cout << '\n';
    }
    /*
    std::cout << "Maxwell Distribution Test for T = " << 1.0 << ":\n";
    MaxwellDistributionTest(1.0);
    std::cout << "\nMaxwell Distribution Test for T = " << 10.0 << ":\n";
    MaxwellDistributionTest(10.0);
    std::cout << "\nMaxwell Distribution Test for T = " << 100.0 << ":\n";
    MaxwellDistributionTest(100.0);
    */
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
