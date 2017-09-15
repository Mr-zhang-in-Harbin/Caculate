#ifndef Button_h
#define Button_h

#include <string>
#include <gl/glut.h>
#include <stdio.h>

using namespace std;

const int Windows_x = 320;
const int Windows_y = 580;

enum Color { orange, white };

void selectFont(int size, int charset, const char* face);
void drawString(const char* str);

class Button
{
private:
	int x_l, x_r, y_u, y_d;
	Color MyColor;
public:
	Button(int x_l, int  x_r, int y_d, int  y_u, Color MyColor, char data);
	char data;
	Button *next;
	bool ifclick(int x, int y);
	void display();
};

class Button_System
{
public:
	Button *first;
	void NewButton(int x_l, int  x_r, int y_u, int  y_d, Color MyColor, char data);
	Button_System();//在构造函数里把按钮都给定义好
	char myMouse(int x, int y, string &temp);
};

#endif // !Button_h
