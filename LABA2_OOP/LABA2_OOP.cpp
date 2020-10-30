#include <iostream>
#include <conio.h>
using namespace std;

class Point { //создаем класс
public:
	int x, y;// создаем два публичных атрибута
	Point() {//конструктор
		printf("Конструктор по умолчанию\n");//для отладочного вывода
		x = 0;
		y = 0;
	}
	Point(int x, int y) {//конструктор с параметрами
		printf("Конструктор с параметрами: Point(int x, int y)\n");//для отладочного вывода
		this->x = x;//this-указатель на объект текущего класса
		this->y = y;//ему присваивается указанное в параметрах значение
	}
	Point(const Point& p) {//копирующий конструктор значение передается по ссылке
		//const потому что мы ничего не меняем в объекте Point который мы принимаем
		printf("Копирующий конструктор: Point(const Point &p)\n");//для отладочного вывода
		x = p.x;//
		y = p.y;//
	}
	virtual ~Point() {//деструктор
		cout << "Текущее состояние объектов х и у: " << x << " " << y << endl;
		cout << "Point-деструктор" << endl;
	}
	void move(int dx, int dy) {//метод изменения координат после определения
		x = x + dx;
		y = y + dy;
		printf("Метод move\n");
	}
	void reset();
};

void Point::reset() {//реализация метода сразу после определения
	x = 0;
	y = 0;
}

class ColoredPoint :public Point { //создаем класс-потомок
protected: int color;//protected открывает доступ к членам класса дружественным и дочерним классам
public:
	ColoredPoint() :Point() {//конструктор// в нем через :  вызываем конструктор базового класса
		printf("Конструктор Colored по умолчанию\n");//для отладочного вывода
		color = 0;//дополнительно заполняем поле color
	}
	ColoredPoint(int x, int y, int color) :Point(x, y) {//конструктор с параметрами //: вызываем конструктор Point с параметрами
		printf("Конструктор Colored с параметрами: ColoredPoint(int x, int y)\n");//для отладочного вывода
		this->color = color;//
	}
	ColoredPoint(const ColoredPoint& p) {//копирующий конструктор
		printf("Копирующий конструктор: ColoredPoint(const Point &p)\n");//для отладочного вывода
		color = p.color;
		x = p.x;
		y = p.y;
	}
	virtual ~ColoredPoint() {//деструктор
		cout << "Текущее состояние объектов х и у и color: " << x << " " << y << " " << color << endl;
		cout << "ColoredPoint-деструктор" << endl;
	}
	void change_color(int new_color) {//метод изменение цвета
		color = new_color;
	}
};

class Section { //создаем класс Отрезки
protected:
	Point* p1;//указатели на первую и вторую точки отрезка для Section из объекта класса Point
	Point* p2;
public:
	Section() {//конструктор
		printf("Конструктор по умолчанию Section\n");//для отладочного вывода
		p1 = new Point;//создание новых точек для отрезка с помощью констркутора по умолчанию Point
		p2 = new Point;
	}
	Section(int x1, int y1, int x2, int y2) {//конструктор с параметрами
		printf("Конструктор с параметрами: Section(int x1, int y1, int x2, int y2)\n");//для отладочного вывода
		p1 = new Point(x1, y1);
		p2 = new Point(x2, y2);


	}
	Section(const Section& s) {//копирующий конструктор
		printf("Копирующий конструктор: Section(const Section &s)\n");//для отладочного вывода
		p1 = new Point(*(s.p1));//р1-указатель на Point поэтому мы его разыменовываем
								//оператор разыменования позволяет полцчить значение по указанному адресу
								// мы берем тот отрезок который нам передается и создаем точную копию с помощью вызова конструктора копирования
		p2 = new Point(*(s.p2));
	}
	virtual ~Section() {//деструктор
		//cout << "Текущее состояние объектов х и у: " << x << " " << y << endl;
		delete p1;//созданные точки удаляем
		delete p2;
		cout << "Section-деструктор" << endl;
	}
};


int main() {
	setlocale(LC_ALL, "rus");
	printf("\n\nСтатические объекты\n");
	{
		Point p;//создаем объект статически c помощью конструктора
		Point p2(5, 10);//объект с помощтю конструткора с параметрами
		Point p3(p2);//объект с помощью конструктора копирования
		printf("Самовызывающиеся деструкторы:\n");
	}
	printf("\n\nДинамические объекты\n");
	Point* d = new Point;//создаем динамический объект с помощью конструктора
	Point* d2 = new Point(10, 15);//создаем динамический объект с помощью конструктора с параметрами
	Point* d3 = new Point(*d2);//объект с помощью конструктора копирования, р2 разыменовываем(????)

	//Чтобы увидеть работу деструкторов нам надо самим удалить эти динамические объекты, объекты сами удаля.тся только после окончания работы программы
	delete d;
	delete d2;
	delete d3;

	printf("\n\nИспользование метода move\n");
	Point* t = new Point(1, 2);//использование метода move
	t->move(10, 10);
	delete t;

	printf("\n\nИспользование метода reset и move\n");
	Point* t2 = new Point(1, 2);//использование метода reset и move вместе
	t2->reset();
	t2->move(10, 10);
	delete t2;

	printf("\n\nОбъекты класса-наследника\n");
	ColoredPoint* c1 = new ColoredPoint;//объект класса наследника
	delete c1;

	ColoredPoint* c2 = new ColoredPoint(1, 2, 45);//объект класса наслденика
	delete c2;

	printf("\n\nПомещение объектов в перемнные различных типов\n");
	Point* p1 = new ColoredPoint();
	Point* p2 = new ColoredPoint(1, 2, 45);
	delete p1;
	delete p2;

	printf("\n\nКомпозиция: Section\n");
	Section* s1 = new Section;
	Section* s2 = new Section(*s1);
	delete s1;
	delete s2;


	_getch();
	return 0;
}