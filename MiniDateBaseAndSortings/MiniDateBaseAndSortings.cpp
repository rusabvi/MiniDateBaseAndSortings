#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Service
{
	string kind;
	string responsible;
	double price;
	double discount;
};

void Print(Service service)
{
	cout <<		"Вид СТО                   : " << service.kind <<
		endl << "Ответственный             : " << service.responsible <<
		endl << "Стоимость работ           : " << service.price <<
		endl << "Скидка постоянным клиентам: " << service.discount << endl;
}

void PrintAll(Service services[], int size)
{
	if (size == 0)
	{
		cout << "Массив пуст";
		return;
	}

	cout << "================================" << endl;
	for (int i = 0; i < size; i++)
	{
		Print(services[i]);
		cout << "================================" << endl;
	}
}

void ShowInfo()
{
	cout << "Выберите действие:" << endl <<
		"1) Добавить СТО." << endl <<
		"2) Прочитать весь массив." << endl <<
		"3) Найти СТО по полю 'ответственный'." << endl <<
		"4) Выполнить сортировку по полю 'цена'." << endl <<
		"5) Сохранить в файл." << endl <<
		"6) Прочитать массив из файла." << endl <<
		"7) Выйти из программы." << endl;
}

void Add(Service services[], int &size)
{
	cout << "Введите тип СТО: ";
	getline(cin, services[size].kind);
	cout << "Введите ответственного: ";
	getline(cin, services[size].responsible);
	cout << "Введите стоимость работ: ";
	cin >> services[size].price;
	cin.ignore();
	cout << "Введите скидку постоянным клиентам: ";
	cin >> services[size].discount;
	cin.ignore();
	size++;
}

void Find(Service services[], int size)
{
	bool isFound = false;
	string responsible;
	cout << "Введите ответственного для поиска: ";
	getline(cin, responsible);

	for (int i = 0; i < size; i++)
	{
		if (services[i].responsible == responsible)
		{
			cout << "================================" << endl;
			Print(services[i]);
			isFound = true;
		}
	}

	if (!isFound)
		cout << "СТО с таким ответственным отсутствует." << endl;
	else
		cout << "================================" << endl;
}

void ShowSortingInfo()
{
	cout << "Выберите тип сортировки:" << endl <<
		"1) Выбором." << endl <<
		"2) Пузырьком." << endl <<
		"3) Шелла." << endl <<
		"4) Вставками." << endl <<
		"5) Быстрая (Хоара)." << endl <<
		"6) Отмена." << endl;
}

void SelectionSort(Service services[], int size)
{
	Service temp;

	for (int i = 0; i < size; i++)
	{
		int k = i;
		temp = services[i];
		for (int j = i + 1; j < size; j++)
			if (services[j].price < temp.price)
				k = j;

		temp = services[k];
		services[k] = services[i];
		services[i] = temp;
	}
}

void BubbleSort(Service services[], int size)
{
	Service temp;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1; j++)
			if (services[j].price > services[j + 1].price)
			{
				temp = services[j];
				services[j] = services[j + 1];
				services[j + 1] = temp;
			}
}

void ShellSort(Service services[], const int size)
{
	Service temp;
	for (int step = size / 2; step > 1; step /= 2)
		for (int i = step; i < size; i++)
			for (int j = i - step; j > 0 && services[j - 1].price > services[j].price; j -= step)
			{
				temp = services[j];
				services[j] = services[j + step];
				services[j + step] = temp;
			}

	for (int i = 1; i < size; i++)
		for (int j = i; j > 0 && services[j - 1].price > services[j].price; j--)
		{
			temp = services[j - 1];
			services[j - 1] = services[j];
			services[j] = temp;
		}
}

void InsertionSort(Service services[], int size)
{
	Service temp;

	for (int i = 1; i < size; i++)
		for (int j = i; j > 0 && services[j - 1].price > services[j].price; j--)
		{
			temp = services[j - 1];
			services[j - 1] = services[j];
			services[j] = temp;
		}
}

void QuickSort(Service services[], int first, int last)
{
	Service temp;

	int f = first, l = last;

	double middle = services[(first + last) / 2].price;
	do {
		while (services[f].price > middle)
			f++;

		while (services[l].price < middle)
			l--;

		if (f >= l)
		{
			if (f > l)
			{
				temp = services[f];
				services[f] = services[l];
				services[l] = temp;
			}

			f++;
			l--;
		}

	} while (f >= l);

	if (f < last)
		QuickSort(services, f, last);

	if (first < l)
		QuickSort(services, first, l);
}

void Sort(Service services[], int size)
{
	string act;
	bool noSort = size < 2;

	if (noSort)
	{
		cout << "Сортировка не нужна";
		return;
	}
	do
	{
		ShowSortingInfo();
		cout << "Ваш выбор: ";
		getline(cin, act);

		if (act == "1")
			SelectionSort(services, size);

		else if (act == "2")
			BubbleSort(services, size);

		else if (act == "3")
			ShellSort(services, size);

		else if (act == "4")
			InsertionSort(services, size);

		else if (act == "5")
			QuickSort(services, 0, size - 1);

		else if (act == "6")
			noSort = true;

		else
			cout << "Неверный ввод" << endl << endl << endl;

	} while (act != "1" && act != "2" &&
		act != "3" && act != "4" &&
		act != "5" && act != "6");

	if (!noSort)
		cout << "Сортировка выполнена." << endl;
	else
		cout << "Сортировка отменена." << endl;
}

void Save(Service services[], int size)
{
	ifstream fileStreamIn;
	int fileSize = fileStreamIn.tellg();

	ofstream fileStreamOut;
	fileStreamOut.open("Sto.txt", ios::app);

	if (fileStreamOut.is_open())
	{
		if (fileSize != 0)
		{
			fileStreamOut << endl << endl;
		}

		for (int i = 0; i < size; i++)
		{
			fileStreamOut << services[i].kind << endl <<
				services[i].responsible << endl <<
				services[i].price << endl <<
				services[i].discount;

			if (i != size - 1)
				fileStreamOut << endl << endl;
		}

		cout << "Файл сохранён." << endl;
	}

	else
		cout << "Ошибка открытия файла" << endl;
}

void Open(Service services[], int& size)
{
	ifstream fileStreamIn;
	bool endOfFile = false;
	string lastString;
	string randomText = "EQ. Here can be everything, yo";
	fileStreamIn.open("Sto.txt", ios::out);
	if (fileStreamIn.is_open())
	{
		int i;
		for (i = 0; !endOfFile; i++)
		{
			string kind = randomText, responsible = randomText;
			double price, discount;
			getline(fileStreamIn, services[i].kind);
			getline(fileStreamIn, services[i].responsible);
			fileStreamIn >> services[i].price;
			fileStreamIn >> services[i].discount;

			lastString = randomText;
			fileStreamIn.ignore();
			getline(fileStreamIn, lastString);

			if (lastString == randomText)
				endOfFile = true;
		}

		size = i;
		fileStreamIn.close();
		cout << "Данные с файла прочитаны." << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	int size = 0;
	string act;
	Service services[1000];

	for (bool exit = false; !exit; )
	{
		ShowInfo();
		cout << "Ваше действие: ";
		getline(cin, act);
		cout << endl;

		if (act == "1")
			Add(services, size);

		else if (act == "2")
			PrintAll(services, size);

		else if (act == "3")
			Find(services, size);

		else if (act == "4")
			Sort(services, size);

		else if (act == "5")
			Save(services, size);

		else if (act == "6")
			Open(services, size);

		else if (act == "7")
			exit = true;

		else
			cout << "Неверный ввод.";

		cout << endl << endl << endl;
	}
}