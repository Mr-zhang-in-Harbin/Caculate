#include <iostream>   
#include <gl/glut.h>
#include "Butto.h"
#include "stack.h"


using namespace std;

Button_System *System = new Button_System();//��ťϵͳ
string temp;//�ݴ�����,���޸���Ϻ�ͳһ���д���
char output[100];//����һ�����

bool ifanswer = false;//������ʾ�����������ݴ������

//ǰ���˻�����
void 	MyInit();
void myMouse(int button, int state, int x, int y);
void onKeyboard(unsigned char key, int x1, int y1);
void onUpdate();
void onDisplay();

//����߼�ʵ��
int calculate(string s);
int priority(char x);
bool isnumber(char x);

int main(int argc, char*  argv[])
{
	temp += '#';
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(Windows_x, Windows_y);
	glutCreateWindow("Caculate");
	glutDisplayFunc(&onDisplay);
	glutIdleFunc(onUpdate);
	//glutKeyboardFunc(onKeyboard);
	glutMouseFunc(myMouse);
	MyInit();
	glutMainLoop();
	return 0;
}


void onDisplay()
{

}

void onUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT);
	System->first->display();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(Windows_x / 4.0 * 1, 420);
	glVertex2f(Windows_x / 4.0 * 1, 84);
	glVertex2f(Windows_x / 4.0 * 2, 420);
	glVertex2f(Windows_x / 4.0 * 2, 0);
	glVertex2f(Windows_x / 4.0 * 3, 420);
	glVertex2f(Windows_x / 4.0 * 3, 0);
	for (int i = 1; i < 5; i++)
	{
		glVertex2f(0, i * 84);
		glVertex2f(Windows_x, i * 84);
	}
	glEnd();
	if (!ifanswer)
	{
		int len = temp.length();
		for (int i = 1; i < len; i++)
			output[i - 1] = temp[i];
		output[len - 1] = '\0';
		glRasterPos2i(Windows_x - 22 * len, 420);  //��ʼλ��  
		//cout << output << endl;
		drawString(output);   //������ַ���  
	}
	else
	{
		int count;
		for (count = 0; output[count] <= '9'&&output[count] >= '0'; count++);
		glRasterPos2f(Windows_x - 22 * count, 420);
		drawString(output);
	}
	glFlush();
	glutSwapBuffers();
}

void onKeyboard(unsigned char key, int x1, int y1)
{

}

void myMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		ifanswer = false;
		char result = System->myMouse(x, Windows_y - y, temp);
		if (result == '#')
		{
			cout << temp << endl;
			calculate(temp);
			ifanswer = true;
			temp = '#';
		}
		else if (result == 'C')
		{
			temp = '#';
		}
	}
}

void 	MyInit()
{
	//glClearColor(0.0, 0.0, 0.0, 0.0);//������ɫΪ��ɫ;
	glClearColor(0.95, 0.95, 0.95, 0.0);//������ɫΪ����ɫ;
	gluOrtho2D(0.0, Windows_x, 0.0, Windows_y);//�������ű�,��������ϵ;
}

//ɨ�����ֵĺ���  
bool isnumber(char x) {
	if (x >= '0' && x <= '9')
		return true;
	return false;
}

//�ж���������ȼ��ĺ���   
int priority(char x) {
	if (x == '+' || x == '-')
		return 0;
	else if (x == '*' || x == '/')
		return 1;
	else if (x == '(' || x == ')')
		return -1;
	else if (x == '#')
		return -2;
}

//����ĺ���   
int calculate(string s)
{
	stack<int> number;
	stack<char> operate;
	char top;
	int a, b;

	for (unsigned int i = 0; i < s.size(); ++i)
	{
		if (isnumber(s[i]))
		{
			int Temp = 0;
			string temp;

			temp += s[i];
			while (isnumber(s[++i]))
				temp += s[i];
			for (unsigned int j = 0; j < temp.size(); ++j)
			{
				Temp = Temp * 10 + temp[j] - 48;
			}
			number.push(Temp);
			temp.clear();
		}//���ַ�����ת������������    
		if (!isnumber(s[i]))
		{
			if (operate.ifempty())
			{
				operate.push(s[i]);
			}//��ջ��һ������'#'    
			else
			{
				operate.get_top(top);

				if (priority(s[i]) > priority(top) || s[i] == '(')
				{
					operate.push(s[i]);
				}//��ջ�����ȼ��������    
				else
				{
					while (priority(s[i]) <= priority(top))
					{
						if (top == '#'&&s[i] == '#') {
							int answer;
							operate.pop();
							number.get_top(answer);
							_itoa_s(answer, output, 10);
							number.pop();
							return 0;
						}//�������ʵ����ȫ��ֻʣ��'#'    
						else if (top == '('&&s[i] == ')')
						{
							++i;
						}//��������������ʱ�����������ţ�ɾ��������    
						else
						{
							number.get_top(a);
							number.pop();
							number.get_top(b);
							number.pop();
						}
						if (top == '+')
						{
							b += a;
							number.push(b);
						}
						else if (top == '-')
						{
							b -= a;
							number.push(b);
						}
						else if (top == '*')
						{
							b *= a;
							number.push(b);
						}
						else if (top == '/')
						{
							b /= a;
							number.push(b);
						}
						operate.pop();
						operate.get_top(top);//ȡǰһ�������������������ɨ�����������бȽ�      
					}//�����ȼ��ߵ������ʵ�ּ���    
					operate.push(s[i]);//���ڵ�top=='#'ʱ�������һ���������ջ    
				}
			}
		}//ɨ������������ж����ȼ����Լ�����    
	}//��ѭ��    
}//���������ɨ�裬�������ַ���ת�����Լ�����    
