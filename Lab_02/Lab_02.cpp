// Lab_02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

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
    return dv * (mean_1(psi, pdf, 1, start, mid) + mean_1(psi, pdf, 1, mid + 1, end));
}

float mean_2(float const psi[], float const pdf[], float const dv, unsigned size)
{
    float* psi_ = new float[size];
    for (int i = 0; i < size; ++i) {
        psi_[i] = psi[i] * pdf[i];
    }
    int step = 1;
    while (step < size)
        for (int i = 0; i < size; i += 2 * step)
            psi_[i] += psi_[i + step];
    return dv * psi_[0];
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

int main()
{
    std::cout << "Hello World!\n";
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
