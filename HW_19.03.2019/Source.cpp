#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include<math.h>
#include<ctime>
#include<cstring>
#include<fstream>
#include<Windows.h>

using namespace std;

// Описать структуру Rabotnik(Фамилия, должность, дата поступления на работу).
// Создать массив из 10 работников.
// Предусмотреть:
//- Заполнение массива из 10 элементов;
//- Вывод информации о достижении пенсионного возраста работниками с указанием фамилии, возраста и должности.
//- Вывод информации о стаже работы сотрудников на указанный год в порядке убывания.

struct Date {
	int day, month, year;

	void print() {
		cout << day << "/" << month << "/" << year << endl;
	}
};
struct Rabotnik {
	char surname[30];
	char position[50];
	Date hiring;
	int age;

	void print() {
		_strupr_s(surname);
		cout << surname << " " << position << " " << age << " лет" << endl;
	}
};
void retired(Rabotnik *r) {
	int k = 0;
	cout << endl << "Работники, достигшие пенсионного возраста:" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (r[i].age >= 63)
		{
			r[i].print();
			k++;
		}
	}
	if (k == 0)
		cout << "Нет пенсионеров" << endl;
}
void experience(Rabotnik *r) {
	cout << endl << "Enter a year (curent or another):";
	int y, x[10];
	cin >> y;

	for (int i = 0; i < 10; i++)
		x[i] = y - r[i].hiring.year;

	for (int i = 0; i < 10 - 1; i++)
	{
		for (int j = 0; j < 10 - 1; j++)
		{
			if (x[j] < x[j + 1])
			{
				swap(r[j], r[j + 1]);
				swap(x[j], x[j + 1]);
			}
		}
	}

	for (int i = 0; i < 10; i++)
		if(x[i]>0)
			cout << r[i].surname << ", стаж работы на указанный год: " << x[i] << endl;
}

int main()
{
	srand(time(NULL));

	setlocale(LC_ALL, "Rus");

	Rabotnik r[10];
	ifstream in_file("in.txt");
	char c;
	int i = 0;
	if (!in_file)
		cerr << "File open error" << endl;
	else
	{
		for(int i=0; i<10; i++)
		{
			in_file >> r[i].surname;
			in_file.ignore();
			in_file.getline(r[i].position, 50, '#');
			in_file >> r[i].hiring.day >> c >> r[i].hiring.month >> c >> r[i].hiring.year >> r[i].age;
		}
	}

	/*for (int i = 0; i < 10; i++)
		r[i].print();*/
	retired(r);
	experience(r);

	system("pause");
	return 0;
}