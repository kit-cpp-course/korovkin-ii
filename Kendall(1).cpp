#include <iostream>

using namespace std;

class Table {
	struct Node {
		double X; // первая величина
		double Y; // вторая величина
	};

	Node *values; // массив значений
	int *rangs; // массив рангов
	int n; // количество значений

	void SortByX(); // ортировка по X
	void SortByY(); // ортировка по Y

public:
	Table(int n); // создание таблицы из количества элементов

	void Read(); // ввод значений X и Y
	void Print(); // вывод значений

	double Calculate(); // вычисление коэффициента

	~Table();
};

// создание таблицы из количества элементов
Table::Table(int n) {
	this->n = n;

	values = new Node[n]; // выделяем память под массив значений
	rangs = new int[n]; // выделяем память под массив рангов
}

// сортировка по X
void Table::SortByX() {
	bool isSorted = false;

	while (!isSorted) {
		isSorted = true;

		for (int i = 0; i < n - 1; i++) {
			if (values[i].X > values[i + 1].X) {
				Node tmp = values[i];
				values[i] = values[i + 1];
				values[i + 1] = tmp;
				isSorted = false;
			}
		}
	}
}

// сортировка по Y
void Table::SortByY() {
	bool isSorted = false;

	while (!isSorted) {
		isSorted = true;

		for (int i = 0; i < n - 1; i++) {
			if (values[i].Y > values[i + 1].Y) {
				Node tmp = values[i];
				values[i] = values[i + 1];
				values[i + 1] = tmp;
				swap(rangs[i], rangs[i + 1]);

				isSorted = false;
			}
		}
	}
}

// ввод значений X и Y
void Table::Read() {
	for (int i = 0; i < n; i++) {
		cout << "Enter Y, X(use space between values): ";
		cin >> values[i].Y >> values[i].X;
	}
}

// вывод значений
void Table::Print() {
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << (i + 1) << "\t" << values[i].X << "\t" << values[i].Y << endl;
	}
}

double Table::Calculate() {
	SortByX(); // сортируем по Х

	// проставляем ранги
	for (int i = 0; i < n; i++)
		rangs[i] = i + 1;

	SortByY(); // сортируем по У вместе с рангами

	int *Pp = new int[n]; // выделяем память под массив совпадений
	int P = 0; // обнуляем сумму

	Pp[0] = 0;
	Pp[n - 1] = 0;

	// расчитываем значения P(p)
	for (int i = 1; i < n - 1; i++) {
		if (values[i].X > values[i + 1].X) {
			Pp[i] = 0;
		}
		else {
			Pp[i] = rangs[i + 1] - rangs[i];
		}

		P += Pp[i]; // наращиваем сумму
	}

	int Pq = n * (n - 1) / 2 - P; // рассчитываем P(q)

	cout << endl << "P(p): ";
	for (int i = 0; i < n; i++)
		cout << Pp[i] << " ";

	cout << endl << "Sum P(p) = " << P << endl; // выводим сумму
	cout << endl << "P(q) = " << Pq << endl; // выводим P(q)

	delete[] Pp; // очищаем память от временного массива

	return 4.0 * P / (n * (n - 1)) - 1; // возвращаем коэффициент 4P / (N*(N-1)) - 1
}

// деструктор (очистка памяти)
Table::~Table() {
	delete[] values; // очищаем память от массива значений
	delete[] rangs; // очищаем память от массива рангов
}

int main() {
	int n;

	cout << "Enter n: ";
	cin >> n; // считываем размер

	Table table(n); // создаём таблицу

	table.Read(); // считываем параметры

	cout << "Readed table: " << endl;
	table.Print(); // выводим введённую таблицу

	double t = table.Calculate(); // вычисляем коэффициент

	cout << "t = " << t << endl; // выводим коэффициент
    system("pause");
}
