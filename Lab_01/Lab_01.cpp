// Lab_01.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <string>

int metric(std::pair<int, int> a, std::pair<int, int> b)
{
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

class Particles
{
private:
    int numberOfParticles_;
    int mHeight_, mWidth_;

    std::vector<std::pair<std::pair<int, int>, bool>> coords_;
    std::vector<std::vector<bool>> matrix_;

public:
    Particles(int numberOfParticles, int mHeight, int mWidth)
    {
        this->numberOfParticles_ = numberOfParticles;
        this->mHeight_           = mHeight;
        this->mWidth_            = mWidth;

        this->coords_            = std::vector<std::pair<std::pair<int, int>, bool>>(numberOfParticles);
        this->matrix_            = std::vector<std::vector<bool>>(mHeight, std::vector<bool>(mWidth, false));

        for (int i = 0; i < numberOfParticles; ++i) {
            std::random_device randDev;
            std::mt19937 gen(randDev());
            std::uniform_int_distribution<> distHeight(0, mHeight - 1), 
                                            distWidth(0, mWidth - 1);

            int x = distHeight(gen),
                y = distWidth(gen);

            this->coords_.at(i)       = std::make_pair(std::make_pair(x, y), true);
            this->matrix_.at(x).at(y) = true;
        }
    }

    void updateDead()
    {
        for (auto& particle_i : this->coords_) {
            for (auto& particle_j : this->coords_)
                if (metric(particle_i.first, particle_j.first) == 1)
                    particle_i.second = particle_j.second = false;

            if ((this->mHeight_ == 1 && (particle_i.first.second == 0 || particle_i.first.second == this->mWidth_ - 1)) ||
                (this->mWidth_ == 1  && (particle_i.first.first == 0  || particle_i.first.first == this->mHeight_ - 1)))
                particle_i.second = false;
            else if (particle_i.first.second == 0 || particle_i.first.second == this->mWidth_ - 1 ||
                     particle_i.first.first == 0  || particle_i.first.first == this->mHeight_ - 1)
                particle_i.second = false;
        }
    }

    bool checkDead()
    {
        for (auto particle_i : this->coords_)
            if (particle_i.second)
                return true;
        return false;
    }

    void updateCoords()
    {
        std::random_device randDev;
        std::mt19937 gen(randDev());
        std::uniform_int_distribution<> dist(0, 3);
        for (auto& particle_i : this->coords_)
            if (particle_i.second) {
                int dir = dist(gen);
                if ((dir == 0 && this->mHeight_ != 1) || 
                    (dir == 2 && this->mWidth_ == 1)) {
                    this->matrix_.at(particle_i.first.first--).at(particle_i.first.second) = false;
                    if (this->matrix_.at(particle_i.first.first).at(particle_i.first.second))
                        ++particle_i.first.first;
                    this->matrix_.at(particle_i.first.first).at(particle_i.first.second) = true;
                } else 
                if ((dir == 1 && this->mHeight_ != 1) || 
                    (dir == 3 && this->mWidth_ == 1)) {
                    this->matrix_.at(particle_i.first.first++).at(particle_i.first.second) = false;
                    if (this->matrix_.at(particle_i.first.first).at(particle_i.first.second))
                        --particle_i.first.first;
                    this->matrix_.at(particle_i.first.first).at(particle_i.first.second) = true;
                } else 
                if ((dir == 0 && this->mHeight_ == 1) || 
                    (dir == 2 && this->mWidth_ != 1)) {
                    this->matrix_.at(particle_i.first.first).at(particle_i.first.second--) = false;
                    if (this->matrix_.at(particle_i.first.first).at(particle_i.first.second))
                        ++particle_i.first.second;
                    this->matrix_.at(particle_i.first.first).at(particle_i.first.second) = true;
                } else 
                if ((dir == 1 && this->mHeight_ == 1) || 
                    (dir == 3 && this->mWidth_ != 1)) {
                    this->matrix_.at(particle_i.first.first).at(particle_i.first.second++) = false;
                    if (this->matrix_.at(particle_i.first.first).at(particle_i.first.second))
                        --particle_i.first.second;
                    this->matrix_.at(particle_i.first.first).at(particle_i.first.second) = true;
                }
            }
    }

    void printMatrix()
    {
        for (auto matrix_i : this->matrix_) {
            for (auto matrix_ij : matrix_i)
                std::cout << matrix_ij << ' ';
            std::cout << '\n';
        }
        std::cout << '\n';
    }
};

int main()
{
    /*
    int numberOfParticles = 10, mHeight = 10, mWidth = 10;
    std::cin >> numberOfParticles >> mHeight >> mWidth;
    
    Particles* mParticles = new Particles(numberOfParticles, mHeight, mWidth);
    mParticles->printMatrix();

    while (mParticles->checkDead()) {
        mParticles->updateDead();
        mParticles->updateCoords();
        mParticles->printMatrix();
    }
    */

    // Первое задание
    {
        // Для настройки
        int testNumber = 100, 
            maxHeight = 10, 
            maxWidth = 10;

        std::cout << "1. t(h, w), ns\n";
        std::cout << std::setw(8) << "h \\ w";
        for (int i = 1; i <= maxWidth; ++i)
            std::cout << std::setw(8) << std::to_string(i) + "  ";
        std::cout << '\n';
        int numberOfParticles = 1;
        for (int mHeight = 1; mHeight <= maxHeight; ++mHeight) {
            std::cout << std::setw(8) << std::to_string(mHeight) + "    ";
            for (int mWidth = 1; mWidth <= maxWidth; ++mWidth) {
                auto start = std::chrono::high_resolution_clock::now();
                for (int t = 0; t < testNumber; ++t) {
                    Particles* mParticles = new Particles(numberOfParticles, mHeight, mWidth);
                    while (mParticles->checkDead()) {
                        mParticles->updateDead();
                        mParticles->updateCoords();
                    }
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto nsec = end - start;
                std::cout << std::setw(8) << nsec.count() / testNumber;
            }
            std::cout << '\n';
        }
    }

    // Второе задание
    {
        // Для настройки
        int testNumber = 1000,
            maxHeight = 100,
            maxWidth = 100;

        std::cout << "2. t(n / (h * w)), ns\n";
        std::cout << std::setw(8) << "n / (h * w)" << std::setw(15) << "t     \n";
        while (testNumber--) {
            std::random_device randDev;
            std::mt19937 gen(randDev());
            std::uniform_int_distribution<> distHeight(1, maxHeight), distWidth(1, maxWidth);
            int mHeight = distHeight(gen), mWidth = distWidth(gen);
            std::uniform_int_distribution<> distNumber(1, mHeight * mWidth);
            int numberOfParticles = distNumber(gen);
            auto start = std::chrono::high_resolution_clock::now();
            Particles* mParticles = new Particles(numberOfParticles, mHeight, mWidth);
            while (mParticles->checkDead()) {
                mParticles->updateDead();
                mParticles->updateCoords();
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto nsec = end - start;
            std::cout << std::fixed << std::setw(8) << std::setprecision(5) << static_cast<double>(numberOfParticles) / static_cast<double>(mHeight * mWidth);
            std::cout << std::setw(15) << nsec.count() << '\n';
        }
    }

    // Третье задание
    // График есть 1-ая строка графика из первого задания;
    // Чтобы построить t(n / w) при h = 1, в строке 184 "mHeight = 1".
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
