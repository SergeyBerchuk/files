//Берчук Сергей Утс/б 22-2-о вариант 1
/*
 * 1. Реализовать чтение заголовков файлов форматов. Проверить работоспособность
можно по примерам.
a. ICO: ICONDIR и ICONDIRENTRY
*/

#include <iostream>
#include <fstream>

typedef short int WORD;
typedef char SHWORD;
typedef int LWORD;


#pragma pack(push, 2)

struct ICONDIR {
    WORD Reserved;
    WORD Type;
    WORD Count;
};

struct ICONDIRENTRY {
    SHWORD Width;
    SHWORD Height;
    SHWORD ColorCount;
    SHWORD Reserved;
    WORD Planes;
    WORD BitCount;
    LWORD BytesInRes;
    LWORD ImageOffset;
};

#pragma pack(pop)

int main() {


    std::ifstream file("rotation.ico", std::ios::binary);
    ICONDIR icon_dir;
    file.read((char*)&icon_dir, sizeof(icon_dir));
    std::cout << "\t--ICONDIR--" << std::endl;
    std::cout << "\tReserved: " << icon_dir.Reserved << std::endl;
    std::cout << "\tType: " << icon_dir.Type << std::endl;
    std::cout << "\tCount: " << icon_dir.Count << std::endl << std::endl;

    ICONDIRENTRY dir_entry;
    file.read((char*)&dir_entry, sizeof(dir_entry));
    file.close();

    std::cout << "\t--ICONDIRENTRY--" << std::endl;
    std::cout << "\tWidth: " << (short)(dir_entry.Width) << std::endl;
    std::cout << "\tHeight: " << (short)(dir_entry.Height) << std::endl;
    std::cout << "\tColorCount: " << (short)(dir_entry.ColorCount) << std::endl;
    std::cout << "\tPlanes: " << dir_entry.Planes << std::endl;
    std::cout << "\tBitCount: " << dir_entry.BitCount << std::endl;
    std::cout << "\tBytesInRes: " << dir_entry.BytesInRes << std::endl;
    std::cout << "\tImageOffset: " << dir_entry.ImageOffset << std::endl;

    return 0;
}
/*
 * 3. Протабулировать функцию. Начальную и финальную точки, шаг, параметр Ч
считывать из файла in.txt. Результат записывать в текстовый файл out.txt. Формат
записи данных:
x0, y(x0)
x1, y(x1)
x2, y(x2)
и т.д.
a. 𝑦 = 𝑥 + 2𝑥 + 3𝑥 + ⋯ + Ч𝑥
*/

#include <iostream>
#include <fstream>
#include <cmath>

int main() {
    double x0, x1, step, C; // параметр Ч - это C
    std::ifstream f("in.txt");
    f >> x0 >> x1 >> step >> C;
    f.close();

    std::ofstream fout("out.txt");
    for (double x = x0; x <= x1; x += step) {
        double y = 0;
        for (int i = 1; i <= C; i++) {
            y += i * x;
        }
        fout << x << ", " << y << std::endl;
    }
    fout.close();

    std::cout << "Tabulling be save in out.txt" << std::endl;

    return 0;
}
/*
 * 4. Разработать программу для считывания данных о студентах из файла в следующем
формате: 1 строка Фамилия, 2 строка Средняя оценка, 3 строка Курс. Остальные
строки повторяют тройками эти данные для других студентов. Организовать
считывание данных из файла в массив структур. Организовать переменные для
хранения информации.
*/

#include <iostream>
#include <fstream>
#include <string>
#include<array>

const int N = 10;
struct Student {
    std::string lastName;
    double averageGrade;
    int course;
};

void showInfo(Student& student)
{
    std::cout << student.lastName << std::endl;
    std::cout << student.averageGrade << std::endl;
    std::cout << student.course << std::endl;
    std::cout << std::endl;
}
int main() {
    std::array<Student, N> students;
    std::ifstream fin("D:/data_samples/students.txt");

    int count = 0;
    while (!fin.eof() && count < N) {
        std::getline(fin, students[count].lastName);
        fin >> students[count].averageGrade;
        fin >> students[count].course;
        fin.ignore();
        count++;
    }

    fin.close();

    std::cout << "Read " << count << " students from file." << std::endl;

    for (int i = 0; i < count; i++)
        showInfo(students[i]);

    return 0;
}