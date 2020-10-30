#include <iostream>
#include <conio.h>
using namespace std;

class Point { //������� �����
public:
	int x, y;// ������� ��� ��������� ��������
	Point() {//�����������
		printf("����������� �� ���������\n");//��� ����������� ������
		x = 0;
		y = 0;
	}
	Point(int x, int y) {//����������� � �����������
		printf("����������� � �����������: Point(int x, int y)\n");//��� ����������� ������
		this->x = x;//this-��������� �� ������ �������� ������
		this->y = y;//��� ������������� ��������� � ���������� ��������
	}
	Point(const Point& p) {//���������� ����������� �������� ���������� �� ������
		//const ������ ��� �� ������ �� ������ � ������� Point ������� �� ���������
		printf("���������� �����������: Point(const Point &p)\n");//��� ����������� ������
		x = p.x;//
		y = p.y;//
	}
	virtual ~Point() {//����������
		cout << "������� ��������� �������� � � �: " << x << " " << y << endl;
		cout << "Point-����������" << endl;
	}
	void move(int dx, int dy) {//����� ��������� ��������� ����� �����������
		x = x + dx;
		y = y + dy;
		printf("����� move\n");
	}
	void reset();
};

void Point::reset() {//���������� ������ ����� ����� �����������
	x = 0;
	y = 0;
}

class ColoredPoint :public Point { //������� �����-�������
protected: int color;//protected ��������� ������ � ������ ������ ������������� � �������� �������
public:
	ColoredPoint() :Point() {//�����������// � ��� ����� :  �������� ����������� �������� ������
		printf("����������� Colored �� ���������\n");//��� ����������� ������
		color = 0;//������������� ��������� ���� color
	}
	ColoredPoint(int x, int y, int color) :Point(x, y) {//����������� � ����������� //: �������� ����������� Point � �����������
		printf("����������� Colored � �����������: ColoredPoint(int x, int y)\n");//��� ����������� ������
		this->color = color;//
	}
	ColoredPoint(const ColoredPoint& p) {//���������� �����������
		printf("���������� �����������: ColoredPoint(const Point &p)\n");//��� ����������� ������
		color = p.color;
		x = p.x;
		y = p.y;
	}
	virtual ~ColoredPoint() {//����������
		cout << "������� ��������� �������� � � � � color: " << x << " " << y << " " << color << endl;
		cout << "ColoredPoint-����������" << endl;
	}
	void change_color(int new_color) {//����� ��������� �����
		color = new_color;
	}
};

class Section { //������� ����� �������
protected:
	Point* p1;//��������� �� ������ � ������ ����� ������� ��� Section �� ������� ������ Point
	Point* p2;
public:
	Section() {//�����������
		printf("����������� �� ��������� Section\n");//��� ����������� ������
		p1 = new Point;//�������� ����� ����� ��� ������� � ������� ������������ �� ��������� Point
		p2 = new Point;
	}
	Section(int x1, int y1, int x2, int y2) {//����������� � �����������
		printf("����������� � �����������: Section(int x1, int y1, int x2, int y2)\n");//��� ����������� ������
		p1 = new Point(x1, y1);
		p2 = new Point(x2, y2);


	}
	Section(const Section& s) {//���������� �����������
		printf("���������� �����������: Section(const Section &s)\n");//��� ����������� ������
		p1 = new Point(*(s.p1));//�1-��������� �� Point ������� �� ��� ��������������
								//�������� ������������� ��������� �������� �������� �� ���������� ������
								// �� ����� ��� ������� ������� ��� ���������� � ������� ������ ����� � ������� ������ ������������ �����������
		p2 = new Point(*(s.p2));
	}
	virtual ~Section() {//����������
		//cout << "������� ��������� �������� � � �: " << x << " " << y << endl;
		delete p1;//��������� ����� �������
		delete p2;
		cout << "Section-����������" << endl;
	}
};


int main() {
	setlocale(LC_ALL, "rus");
	printf("\n\n����������� �������\n");
	{
		Point p;//������� ������ ���������� c ������� ������������
		Point p2(5, 10);//������ � ������� ������������ � �����������
		Point p3(p2);//������ � ������� ������������ �����������
		printf("���������������� �����������:\n");
	}
	printf("\n\n������������ �������\n");
	Point* d = new Point;//������� ������������ ������ � ������� ������������
	Point* d2 = new Point(10, 15);//������� ������������ ������ � ������� ������������ � �����������
	Point* d3 = new Point(*d2);//������ � ������� ������������ �����������, �2 ��������������(????)

	//����� ������� ������ ������������ ��� ���� ����� ������� ��� ������������ �������, ������� ���� �����.��� ������ ����� ��������� ������ ���������
	delete d;
	delete d2;
	delete d3;

	printf("\n\n������������� ������ move\n");
	Point* t = new Point(1, 2);//������������� ������ move
	t->move(10, 10);
	delete t;

	printf("\n\n������������� ������ reset � move\n");
	Point* t2 = new Point(1, 2);//������������� ������ reset � move ������
	t2->reset();
	t2->move(10, 10);
	delete t2;

	printf("\n\n������� ������-����������\n");
	ColoredPoint* c1 = new ColoredPoint;//������ ������ ����������
	delete c1;

	ColoredPoint* c2 = new ColoredPoint(1, 2, 45);//������ ������ ����������
	delete c2;

	printf("\n\n��������� �������� � ��������� ��������� �����\n");
	Point* p1 = new ColoredPoint();
	Point* p2 = new ColoredPoint(1, 2, 45);
	delete p1;
	delete p2;

	printf("\n\n����������: Section\n");
	Section* s1 = new Section;
	Section* s2 = new Section(*s1);
	delete s1;
	delete s2;


	_getch();
	return 0;
}