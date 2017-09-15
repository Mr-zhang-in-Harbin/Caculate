#include "Butto.h"
#include <Windows.h>

void selectFont(int size, int charset, const char* face)
{
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

void drawString(const char* str) //屏幕显示字体  
{
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) {
		isFirstCall = 0;
		// 申请MAX_CHAR个连续的显示列表编号  
		lists = glGenLists(128);
		// 把每个字符的绘制命令都装到对应的显示列表中  
		wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符  
	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
}
//上面两个函数具体原理我也不懂,知识因为要在OpenGL上显示字符串所以在网上找的

Button::Button(int x_l, int  x_r, int y_u, int  y_d, Color MyColor, char data)
{
	this->MyColor = MyColor;
	this->x_l = x_l;
	this->x_r = x_r;
	this->y_d = y_d;
	this->y_u = y_u;
	this->data = data;
	this->next = NULL;
}

bool Button::ifclick(int x, int y)
{
	if (x >= x_l&&x <= x_r&&y >= y_d&&y <= y_u)
		return true;
	else return false;
}

void Button::display()
{
	switch (MyColor)
	{
	case orange:glColor3f(1.0, 0.3789, 0.0); break;
	case white:glColor3f(1.0, 1.0, 1.0); break;
	}
	glRectf(x_l, y_u, x_r, y_d);
	selectFont(48, CHINESEBIG5_CHARSET, "Comic Sans MS");
	glColor3f(0, 0, 0); //设置字体颜色  
	glRasterPos2i(x_l + 25, y_d + 30);  //起始位置  
	char *temp = &data;
	drawString(temp);   //输出的字符串  
	if (next != NULL)
		next->display();
}

void Button_System::NewButton(int x_l, int  x_r, int y_d, int  y_u, Color MyColor, char data)
{
	Button *p = new Button(x_l, x_r, y_u, y_d, MyColor, data);
	Button *q = first;
	while (q->next != NULL)
		q = q->next;
	q->next = p;
	return;
}

Button_System::Button_System()
{
	this->first = new Button(0, 0, 0, 0, white, 0);
	NewButton(0, 160, 0, 84, white, '0');
	NewButton(160, 240, 0, 84, white, '.');
	NewButton(240, 320, 0, 84, orange, '=');
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			NewButton(80 * i, 80 * i + 80, 84 * j + 84, 84 * j + 2 * 84, white, '1' + 3 * j + i);
			printf("%d  %d  %c\n", 80 * i, 84 * j, '1' + 3 * j + i);
		}
	NewButton(240, 320, 84 * 1, 84 * 2, orange, '+');
	NewButton(240, 320, 84 * 2, 84 * 3, orange, '-');
	NewButton(240, 320, 84 * 3, 84 * 4, orange, '*');
	NewButton(240, 320, 84 * 4, 84 * 5, orange, '/');
	NewButton(0, 80, 84 * 4, 84 * 5, white, 'C');
	NewButton(80, 160, 84 * 4, 84 * 5, white, '(');
	NewButton(160, 240, 84 * 4, 84 * 5, white, ')');
}

char Button_System::myMouse(int x, int y, string &temp)
{
	Button *p = first;
	while (p != NULL)
	{
		if (p->ifclick(x, y))
		{
			if (p->data != '=')
			{
				temp += p->data;
				printf("p.data: %c\n", p->data);
				return p->data;
			}
			else if (p->data == 'C')
				return 'C';
			else
			{
				temp += '#';
				return '#';
			}
		}
		p = p->next;
	}
	return NULL;
}
