/*
�Թ���Ϸ��
�����(��)�� VK_LEFT (75)
�����(��)�� VK_UP (72)
�����(��)�� VK_RIGHT (77)
�����(��)�� VK_DOWN (80)
*/
#include<string>
#include<fstream>
#include<iostream>
#include <conio.h>
#include<windows.h>
#include<cstdio>
using namespace std;
HANDLE h;
CONSOLE_CURSOR_INFO cci;
COORD cd;
						 
int X=2,Y=0;//X�������̨���ַ������ƶ�������Y����������򲽳�
int PX=1,PY=0;//PX�������ʵ�������е��У�Y���������
const int height=9,width=20; //���������
static int count=0;//����ƶ�����
int  cc[height+1][width+1]= {0};
int level=0;//�ȼ�
//��������
void cls() {
	system("cls");
}
//���ô���
void setStyle() {
	string color[3]= {"color f2","color f3","color f4"};
	system(color[level].c_str());//string.c_str��Borland��װ��String���е�һ�������������ص�ǰ�ַ��������ַ���ַ,system(char*),����Ҫת����const char*
	system("mode con cols=55 lines=16");
}
 
//�ؿ���ͼ��ӡ
void mapprint() {
	string mymap[3]= {"map\\mi.map","map\\mi2.map","map\\mi3.map"};
	ifstream file1(mymap[level].c_str());//string.c_str():string ���ص�ַ�� const char*
	{
		for(int i=0; i<=height; i++) {
			for (int j=0; j<width; j++) {
 
				char c;
				file1>>c;

				cc[i][j]=c-'0';//���ַ�ת��Ϊint

			}
		}
	}
	file1.close();
}
//��Ϸ������Ϣ��ӡ����
void author() {
	setStyle();
	ifstream file3("about.txt");//���ļ����ȡ����
	char str;
	while (file3.get(str)) { //file.get(var);
		cout<<str;
	}
	file3.close();//�ر��ļ�
}

//���ƹ���ƶ�
void setflags(int cols,int row) {
	COORD co;
	co.X=cols;
	co.Y=row;
	h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h,co);
	//���ع��

//	GetConsoleCursorInfo(h, &cci);
//	cci.bVisible=false;

}
void getcount() {

	setflags(41,5);
	cout<<"steps:"<<count<<"��";

}
void showauthor() {
	setflags(41,1);
	cout<<"�Թ���Ϸ";
	setflags(41,3);
	cout<<"��"<<level+1<<"�ؿ�";
	setflags(41,7);
	cout<<"���ߣ�Cendeal";
	setflags(41,9);
	cout<<"�汾��4.0";

}

void logo() {
	setStyle();
	cout<<"������������������������������������������������������\n"<<endl;
	cout<<"\t\t\t�Թ���Ϸ"<<endl<<endl;
	cout<<"\t\t1.��ʼ��Ϸ"<<endl<<endl;
	cout<<"\t\t2.�˳���Ϸ"<<endl<<endl;
	cout<<"\t\t3.����"<<endl<<endl;
	cout<<"������������������������������������������������������\n"<<endl;

	cout<<"���ѡ���ǣ�";
}

void map() {
	cls();

	setStyle();
	mapprint();
	for(int i=0; i<=height; i++) {
		for (int j=0; j<width; j++) {
			if(0==cc[i][j])
				cout<<"��";
			if(1==cc[i][j])
				cout<<"  ";
		}
		cout<<endl;
	}
	cout<<"\n����˵��:�����(��)\t �����(��)\n\t �����(��)\t �����(��)\n\t ����(ESC)";
}
void peopleGo(int &x,int &y) {
	h=GetStdHandle(STD_OUTPUT_HANDLE) ;
	if (count>0) {
		cout<<" ";
	}
	cd.X=x;
	cd.Y=y;

	SetConsoleCursorPosition(h,cd);

	cout<<"��";
	getcount();
	cd.X=x;
	SetConsoleCursorPosition(h,cd);

}


bool isok(int x,int y) {
	if (cc[y][x]==0) return 0;
	if (cc[y][x]==1) return 1;

}
void control(char c) {
	//up
	if (72==c&&PY&&isok(PX,PY-1)) {
		Y-=1;
		PY-=1;
		count++;
	}
	//down
	if (80==c&&PY<height&&isok(PX,PY+1)) {
		Y+=1;
		PY+=1;
		count++;
	}
	//right
	if (77==c&&PX<width&&isok(PX+1,PY)) {
		X+=2;
		PX+=1;
		count++;
	}
	//left
	if (75==c&&PX&&isok(PX-1,PY)) {
		X-=2;
		PX-=1;
		count++;
	}

}


void love() {
	system("mode con cols=92 lines=46");
	ifstream file2("love.dat");
	char c;
	while(file2.get(c)) {
		cout<<c;
	}
	file2.close();
}
void runinit() {
	setflags(2,0);
	SetConsoleTextAttribute(h,
	                        FOREGROUND_INTENSITY |FOREGROUND_RED
	                        |BACKGROUND_INTENSITY |BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE );
//	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout<<"��";
	PX=1;
	PY=0;
	X=2;
	Y=0;
	count=0;
}
void Game() {
	map();
	runinit();
	showauthor();
	getcount();
	char c;
	while (1) {
		c=getch();
		if (27==c) {
			cls();
			cout<<"�˳���<<\n";
			level=0;
			system("pause");
			return;
		} else {
			control(c);
			peopleGo(X,Y);
			//����
			if (PX+1==width||PY==height||(PX!=1&&PY==0)||(PX==0&&PY!=0)) {
				cout<<endl<<"youn win!!"<<endl;
				level++;

				//CloseHandle(hThread_2);
				if (level<3) {
					Sleep(1000);
					Game();


				} else {
					level=0;
					love();
					system("pause");
				}

				break;
			}
		}
	}
}
int runChose() {
	logo();
	string chose;
	cin>>chose;
	cci.bVisible=false;
	SetConsoleCursorInfo(h,&cci);
	if (chose.length()<2) {
		switch(chose[0]-'0') {
			case 1:
				Game();
				runChose();
				break;
			case 2:
				cls();
				return 0;
				break;
			case 3:
				cls();
				author();
				system("pause");
				cls();
				runChose();
				break;

		}
	} else {
		cls();
		cout<<"��Ч����,";
		system("pause");
		runChose();
	}
	return 0;

}

////////////////////////////////
int main() {
	h=GetStdHandle(STD_OUTPUT_HANDLE) ;
	//���ع��
	//CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(h, &cci);

	author();
	cout<<"   ���ڼ����Թ���Ϸ,";
	system("pause");
	runChose();
	system("pause");

	return 0;
}
