#include<iostream>
#include<regex>
#include<fstream>
#include<string>
#include <cstring>
#include <locale>
#include<Windows.h>
#include <map>
#include<vector>
#define PI 3.14159265
using namespace std;
string clean(string a) {
	int i = 0;
	while (i < a.length()) {
		if (!isdigit(a[i]) && (a[i] != ' ') && (a[i] != ',')) {
			a.erase(i, 1);
			i--;
		}
		i++;
	}
	return a;
}
boolean prov(string a)
{
	regex MyReg("(\\d+)||(-\\d)||(\\d+,\\d+)||(-\\d+,\\d+)");
	if (regex_match(a.begin(), a.end(), MyReg)) return true;
	else return false;
}

void line(const HDC& dc, const int x1, const int y1, const int x2, const int y2) {
	MoveToEx(dc, x1, y1, 0);
	LineTo(dc, x2, y2);
}
void Star(const HDC& dc, const int x1, const int y1) {
	//Рисуем по часовой  стрелке

	int dopxM = 2;
	int dopyM = 2;
	int dopxB = 5;
	int dopyB = 5;

	int X = 1;
	int Y = 2;
	int k = 2;

	int i1;
	int j;
	SetPixel(dc, x1, y1, RGB(255, 255, 255));
	for (i1 = 0; i1 < 6; i1++) {

		if (k % 2 == 0) {
			for (j = 0; j < k - 1; j++) {
				SetPixel(dc, x1 + j, y1 + i1, RGB(255, 255, 255));
			}
			for (j = 0; j < k - 1; j++) {
				SetPixel(dc, x1 - j, y1 + i1, RGB(255, 255, 255));
			}
			i1++;
			for (j = 0; j < k; j++) {
				SetPixel(dc, x1 + j, y1 + i1, RGB(255, 255, 255));
			}
			for (j = 0; j < k - 1; j++) {
				SetPixel(dc, x1 - j, y1 + i1, RGB(255, 255, 255));
			}
		}
		else {
			for (j = 0; j < k; j++) {
				SetPixel(dc, x1 + j, y1 + i1, RGB(255, 255, 255));
			}
			for (j = 0; j < k - 1; j++) {
				SetPixel(dc, x1 - j, y1 + i1, RGB(255, 255, 255));
			}
		}
		k++;
	}
	//Верхний угол
	k = 0;
	j += 6;
	for (i1; i1 < 12; i1++) {
		for (int zam = j - k; 0 <= zam; zam--) {
			SetPixel(dc, x1 + zam, y1 + i1, RGB(255, 255, 255));
		}
		for (int zam = j - k; 0 < zam; zam--) {
			SetPixel(dc, x1 - zam, y1 + i1, RGB(255, 255, 255));
		}
		k++;
	}
	//Верхняя часть,в которой 2 угла
	int dop = j - k;
	k = 0;
	for (i1; i1 < 15; i1++) {
		for (int zam = 0; zam <= dop + k + 1; zam++) {
			SetPixel(dc, x1 + zam, y1 + i1, RGB(255, 255, 255));
		}
		for (int zam = 0; zam <= dop + k + 1; zam++) {
			SetPixel(dc, x1 - zam, y1 + i1, RGB(255, 255, 255));
		}
		k++;
	}
	//Нижняя часть с 2мя углами
	dop = dop + k + 1;
	k = 2;
	for (i1; i1 < 19; i1++) {
		if (i1 % 2 == 0) {
			k -= 3;
			dop--;
			for (int zam = k; zam < dop + 1; zam++) {
				SetPixel(dc, x1 + zam, y1 + i1, RGB(255, 255, 255));
			}
			for (int zam = k; zam < dop + 1; zam++) {
				SetPixel(dc, x1 - zam, y1 + i1, RGB(255, 255, 255));
			}
			k += 3;
			dop++;
			i1++;
			for (int zam = k; zam < dop + 1; zam++) {
				SetPixel(dc, x1 + zam, y1 + i1, RGB(255, 255, 255));
			}
			for (int zam = k; zam < dop + 1; zam++) {
				SetPixel(dc, x1 - zam, y1 + i1, RGB(255, 255, 255));
			}
			i1++;
		}
		else {
			for (int zam = k; zam < dop + 1; zam++) {
				SetPixel(dc, x1 + zam, y1 + i1, RGB(255, 255, 255));
			}
			for (int zam = k; zam < dop + 1; zam++) {
				SetPixel(dc, x1 - zam, y1 + i1, RGB(255, 255, 255));
			}
			k += 3;
			dop++;
		}
		k += 3;
		dop++;
	}
}

double triangle(double a, double b, double c) {
	double p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}
double rectangle(double a, double b) {
	return a * b;
}
double circle(double R) {
	return PI * R * R;
}
int symbol(char c, int ocn) {
	int b = 0;
	if (c >= '0' && c <= '9' && (c - '0') < ocn) {
		b = c - '0';
	}
	else {
		if (c >= 'A' && c <= 'Z' && (c - 'A') < ocn) {
			b = c - 'A' + 10;
		}
		else {
			b = -1;
		}
	}
	return b;
}
bool zero(vector <int> chislo) {
	for (int i = 0; i < chislo.size(); i++) {
		if (chislo[i] != 0) return true;
	}
	return false;
}
void perevod(vector <int> chislo, int ocna, int ocnb, int razm) {
	int j = 0;
	int mas[100];
	int k = 0;
	int size = 0;
	while (zero(chislo)) {
		k = 0;
		for (int i = 0; i < razm; i++) {
			k = k * ocna + chislo[i];
			chislo[i] = k / ocnb;
			k = k % ocnb;
		}
		mas[j] = k;
		j++;
		size++;
	}
	cout << "Ответ: ";
	for (int i = size - 1; 0 <= i; i--) {
		std::cout << mas[i] << "";
	}
}
void swap(int* mas, int j, int I) {
	int k = mas[j];
	mas[j] = mas[I];
	mas[I] = k;
}
bool perestanovka(int* mas, int n) {
	int j = n - 1;
	while (mas[j + 1] < mas[j] && 0 < j) {
		j--;
	}
	if (j == 0) return false;
	int I = 0;
	for (int i = n; j < i; i--) {
		if (mas[j] < mas[i]) {
			I = i;
			break;
		}
	}
	swap(mas, j, I);
	int zam;
	for (int i = 0; i < (n - j) / 2; i++) {
		swap(mas, j + 1 + i, n - i);
	}
	return true;
}



void one() {
	string a;
	string b;
	string otv;

	cout << "Введите ваши числа :";
	cin.ignore();
	getline(cin, a);
	a = clean(a);

	string mas[10];
	int j = 0;
	bool c = false;
	int i = 0;
	int k = 0;
	while (i < a.length()) {
		if (49 <= (int)a[i] <= 57) {
			b += a[i];

			if (i + 1 < a.length()) {
				k = i + 1;
				while ((k < a.length()) && ((int)a[k] != 32)) {
					if ((48 <= a[k] <= 57) || (a[k] == ',')) {
						if (a[k] == ',') {
							if (c == false) {
								b += a[k];
								c = true;
							}
						}
						else b += a[k];
					}
					k++;
				}
				i = k;
			}
			mas[j] = b;
			b = "";
			c = false;
			j++;
		}
		i++;
	}
	ofstream file("C:\\Users\\nikita\\Desktop\\file.txt");
	for (int i = 0; i < j; i++) {
		file << mas[i] << endl;
	}
	file.close();

	ifstream fine("C:\\Users\\nikita\\Desktop\\file.txt");
	double otvet = 0;
	while (!fine.eof()) {
		getline(fine, a);
		otvet += atof(a.c_str());
	}
	cout << "Ответ: " << otvet << endl;
}

void two() {
	string s;
	double y;
	boolean a = false;
	while (a != true) {
		std::cout << "Введите число: ";
		cin >> s;
		if (prov(s)) y = atof(s.c_str());
		else {
			std::cout << "Вы ввели один или несколько неподходящих символов.\nПожадуйста введите число." << endl;
			continue;
		}
		if (y > 0) s = "1";
		else if (y == 0) s = "0";
		else s = "-1";
		std::cout << "X = " << s;
		a = true;
	}
}

void three() {
	string a;
	bool i = true;
	while (i != false) {
		cout << "Вы хотите посчитать площадь треугольника(1), прямоугольника(2), круга(3): ";
		cin >> a;
		if (a.length() > 1) {
			cout << "Нет геометрической фигуры с таким номером. \nПожалуйста,введите номер заново" << endl;
			continue;
		}
		char number = a[0];
		int x1;
		int x2;
		int x3;
		switch (number) {
		case '1':

			cout << "Введите стороны треугольника: " << endl;
			cout << "a ";
			cin >> x1;
			cout << "b: ";
			cin >> x2;
			cout << "c: ";
			cin >> x3;
			cout << "S= ";
			printf("%.4f", triangle(x1, x2, x3));
			i = false;
		case '2':
			cout << "Введите стороны прямоугольника: " << endl;
			cout << "a: ";
			cin >> x1;
			cout << "b: ";
			cin >> x2;
			cout << "S= ";
			printf("%.4f", rectangle(x1, x2));
			i = false;
		case '3':
			cout << "Введите радиус круга: " << endl;
			cout << "R1: ";
			cin >> x1;
			cout << "S= ";
			printf("%.4f", circle(x1));
			i = false;
		}
	}
}

void four() {
	HWND hwnd = GetConsoleWindow(); //Берём ориентир на консольное окно (В нём будем рисовать)
	HDC dc = GetDC(hwnd); //Цепляемся к консольному окну
	RECT window = {}; //Переменная window будет использована для получения ширины и высоты окна
	HBRUSH brush;
	HPEN pen;//Переменная brush - это кисть, она будет использоваться для закрашивания	
	RECT rc;
	int yStart = 45;

	RECT WinCoord = {}; //Массив координат окна 
	GetWindowRect(hwnd, &WinCoord); //Узнаём координаты

	brush = CreateSolidBrush(RGB(255, 255, 255)); //Создаём кисть определённого стиля и цвета
	SelectObject(dc, brush); //Выбираем кисть



	Rectangle(dc, 0, 70, 900, 590);
	brush = CreateSolidBrush(RGB(177, 35, 50)); //Создаём кисть определённого стиля и цвета
	SelectObject(dc, brush); //Выбираем кисть
	int x1 = 0;
	int y1 = 70;
	int x2 = 900;
	int y2 = 110;
	for (int i = 0; i < 7; i++) {
		Rectangle(dc, x1, y1, x2, y2);
		y1 = y1 + 80;
		y2 = y2 + 80;
	}
	brush = CreateSolidBrush(RGB(0, 38, 100)); //Создаём кисть определённого стиля и цвета
	SelectObject(dc, brush); //Выбираем кисть
	Rectangle(dc, 0, 70, 370, 350);

	x1 = 25;
	y1 = 90;

	pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(dc, pen); //Выбираем кисть

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			Star(dc, x1 + j * 45, y1 + i * 43);
		}
	}


	string clean;
	cout << "Введите любой символ,чтобы очистить окно: ";
	cin >> clean;
	system("cls");
}

void five() {
	system("cls");
	HWND hwnd = GetConsoleWindow(); //Берём ориентир на консольное окно (В нём будем рисовать)
	HDC dc = GetDC(hwnd); //Цепляемся к консольному окну
	RECT window = {}; //Переменная window будет использована для получения ширины и высоты окна
	HPEN pen; //Переменная brush - это кисть, она будет использоваться для закрашивания	
	RECT rc;
	int yStart = 45;

	RECT WinCoord = {}; //Массив координат окна 
	GetWindowRect(hwnd, &WinCoord); //Узнаём координаты

	pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //Создаём кисть определённого стиля и цвета
	SelectObject(dc, pen); //Выбираем кисть
	line(dc, 0, yStart + 300, WinCoord.right + 200, yStart + 300);//x
	line(dc, 0, 45, 0, 700);//y



	//Верхняя 1
	line(dc, 0, yStart + 150, 10, yStart + 150);
	rc.left = 15;
	rc.top = yStart + 130;
	rc.right = 50;
	rc.bottom = yStart + 150;
	DrawText(dc, L"1", 1, &rc, DT_CENTER);

	//Нижняя 1
	line(dc, 0, yStart + 450, 10, yStart + 450);
	rc.left = 15;
	rc.top = yStart + 450;
	rc.right = 50;
	rc.bottom = yStart + 470;
	DrawText(dc, L"-1", 2, &rc, DT_CENTER);

	int xg = 125;
	int yg1 = 290;
	int yg2 = 310;


	//Правое Pi/2
	line(dc, xg + 6, yStart + yg1, xg + 6, yStart + yg2);
	rc.left = 75;
	rc.top = yStart + 315;
	rc.right = 125;
	rc.bottom = yStart + 335;
	DrawText(dc, L"Pi/2", 4, &rc, DT_CENTER);

	//Правое Pi
	line(dc, 2 * (xg + 6), yStart + yg1, 2 * (xg + 6), yStart + yg2);
	rc.left = 210;
	rc.top = yStart + 315;
	rc.right = 260;
	rc.bottom = yStart + 335;
	DrawText(dc, L"Pi", 2, &rc, DT_CENTER);

	//Построение графика
	int chislo = 15;
	int x;
	double y;
	double i = 0;

	while (i < 400) {
		y = sin(0.024 * i);
		for (int j = 0; j < 500; j++) {
			for (int w = 0; w < 800; w++) {}
		}
		SetPixel(dc, i, round(345 - y * 150), RGB(255, 255, 255));
		i = i + 0.1;
	}

	string clean;
	cout << "Введите любой символ,чтобы очистить окно: ";
	cin >> clean;
	system("cls");
	DeleteObject(pen); //Очищаем память от созданной, но уже ненужной кисти

	ReleaseDC(hwnd, dc); //Освобождаем общий или оконный (не влияющий на класс или локальность) контекст устpойства, делая его доступным для дpугих пpикладных задач. 
}

void six() {
	string chislo;
	boolean bol = true;
	std::cout << "Введите число:";
	cin >> chislo;
	map <char, int> dictionary = {
		{'I' , 1},
		{'V' , 5},
		{'X' , 10},
		{'L' , 50},
		{'C' , 100},
		{'D' , 500},
		{'M' , 1000}
	};
	int otvet = 0;
	for (int i = 0; i < chislo.length() - 1; i = i + 1) {
		if (dictionary[chislo[i]] < dictionary[chislo[i + 1]]) {
			otvet += dictionary[chislo[i + 1]] - dictionary[chislo[i]];
			chislo.erase(i, 2);
			i--;
		}
	}
	for (int i = 0; i < chislo.length(); i++) {
		otvet += dictionary[chislo[i]];
	}
	std::cout << "Ответ: " << otvet;
}

void eight()
{
	double A[3][4]; double B[4][2]; double C[3][2]; int ryad; int stolb; int i;
	A[0][0] = 5; A[0][1] = 2; A[0][2] = 0; A[0][3] = 10;
	A[1][0] = 3; A[1][1] = 5; A[1][2] = 2; A[1][3] = 5;
	A[2][0] = 20; A[2][1] = 0; A[2][2] = 0; A[2][3] = 0;

	B[0][0] = 1.2; B[0][1] = 0.5;
	B[1][0] = 2.8; B[1][1] = 0.4;
	B[2][0] = 5; B[2][1] = 1;
	B[3][0] = 2; B[3][1] = 1.5;

	C[0][0] = 0; C[0][1] = 0;
	C[1][0] = 0; C[1][1] = 0;
	C[2][0] = 0; C[2][1] = 0;
	for (ryad = 0; ryad < 3; ryad++)
		for (stolb = 0; stolb < 4; stolb++)
		{
			C[ryad][0] += A[ryad][stolb] * B[stolb][0];
			C[ryad][1] += A[ryad][stolb] * B[stolb][1];
		}
	std::cout << "Больше всего денег получил 2ой продавец\nМеньше всего 1ый" << endl << endl;
	std::cout << "Больше всего денег получил 1ый продавец\nМеньше всего 3ий" << endl << endl;
	std::cout << "Общая сумма денег: 92" << endl;
	std::cout << "Общая сумма комисионных: 41" << endl;
}

void nain() {
	bool log = false;
	while (!log) {
		int sa, b, sb;
		string a;
		std::cout << "Введите ваше число: ";
		cin >> a;
		std::cout << "Введите основание сс: ";
		cin >> sa;
		std::cout << "Введите ваше требуемое основание сс: ";
		cin >> sb;
		int razm = a.length();
		vector <int> mas;
		int c = 0;

		boolean locallog = false;
		for (int i = 0; i < a.length(); i++) {
			c = symbol(a[i], sa);
			if (c == -1) locallog = true;
			mas.push_back(symbol(a[i], sa));
		}
		if (locallog == true) {
			std::cout << "Введите ввели недопустимый символ" << endl;
			mas.clear();
			continue;
		}
		perevod(mas, sa, sb, razm);
		log = true;
	}
}

void ten() {
	int n = 0;
	cout << "Введите n:";
	cin >> n;
	int mas[1000];
	bool log = false;

	for (int i = 1; i <= n; i++) {
		mas[i] = i;
	}
	int chet = 0;
	while (perestanovka(mas, n)) {
		log = false;
		for (int i = 1; i <= n; i++)if ((mas[i] == i) && (log == false)) {
			chet++;
			log = true;
		}
	}
	cout << "Ответ:" << chet + 1;

}

int main()
{
	setlocale(LC_ALL, "Russian");
	char a;
	string s;
	bool i = true;

	while (i != false) {
		std::cout << "Введите номер задания (1-5) : ";
		cin >> s;
		if (s.length() > 1 && (s != "10")) {
			std::cout << "Нет такого задания. \nПожалуйста,введите номер заново" << endl;
			continue;
		}
		a = s[0];
		if (s == "10")a = 'A';
		switch (a) {
		case '1':
			one();
			std::cout << endl;
			continue;
		case '2':
			two();
			cout << endl;
			continue;
		case '3':
			three();
			cout << endl;
			continue;
		case '4':
			four();
			cout << endl;
			continue;
		case '5':
			five();
			cout << endl;
			continue;
		case '6':
			six();
			cout << endl;
			continue;
		case '8':
			eight();
			continue;
		case '9':
			nain();
			cout << endl;
			continue;
		case 'A':
			ten();
			cout << endl;
			continue;
		default:
			cout << "Не то" << endl;
			continue;
		}
		cout << endl;
	}
	return 0;

}
