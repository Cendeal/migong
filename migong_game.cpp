/*
迷宫游戏：
方向键(←)： VK_LEFT (75)
方向键(↑)： VK_UP (72)
方向键(→)： VK_RIGHT (77)
方向键(↓)： VK_DOWN (80)
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
						 
int X=2,Y=0;//X代表控制台的字符横向移动步长，Y代表的是纵向步长
int PX=1,PY=0;//PX代表的是实际数组中的列，Y代表的是行
const int height=9,width=20; //数组的行列
static int count=0;//玩家移动步数
int  cc[height+1][width+1]= {0};
int level=0;//等级
//清屏函数
void cls() {
	system("cls");
}
//设置窗体
void setStyle() {
	string color[3]= {"color f2","color f3","color f4"};
	system(color[level].c_str());//string.c_str是Borland封装的String类中的一个函数，它返回当前字符串的首字符地址,system(char*),所以要转换成const char*
	system("mode con cols=55 lines=16");
}
 
//关卡地图打印
void mapprint() {
	string mymap[3]= {"map\\mi.map","map\\mi2.map","map\\mi3.map"};
	ifstream file1(mymap[level].c_str());//string.c_str():string 返回地址给 const char*
	{
		for(int i=0; i<=height; i++) {
			for (int j=0; j<width; j++) {
 
				char c;
				file1>>c;

				cc[i][j]=c-'0';//将字符转换为int

			}
		}
	}
	file1.close();
}
//游戏关于信息打印函数
void author() {
	setStyle();
	ifstream file3("about.txt");//从文件里获取内容
	char str;
	while (file3.get(str)) { //file.get(var);
		cout<<str;
	}
	file3.close();//关闭文件
}

//控制光标移动
void setflags(int cols,int row) {
	COORD co;
	co.X=cols;
	co.Y=row;
	h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h,co);
	//隐藏光标

//	GetConsoleCursorInfo(h, &cci);
//	cci.bVisible=false;

}
void getcount() {

	setflags(41,5);
	cout<<"steps:"<<count<<"步";

}
void showauthor() {
	setflags(41,1);
	cout<<"迷宫游戏";
	setflags(41,3);
	cout<<"第"<<level+1<<"关卡";
	setflags(41,7);
	cout<<"作者：Cendeal";
	setflags(41,9);
	cout<<"版本：4.0";

}

void logo() {
	setStyle();
	cout<<"▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉\n"<<endl;
	cout<<"\t\t\t迷宫游戏"<<endl<<endl;
	cout<<"\t\t1.开始游戏"<<endl<<endl;
	cout<<"\t\t2.退出游戏"<<endl<<endl;
	cout<<"\t\t3.关于"<<endl<<endl;
	cout<<"▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉\n"<<endl;

	cout<<"你的选择是：";
}

void map() {
	cls();

	setStyle();
	mapprint();
	for(int i=0; i<=height; i++) {
		for (int j=0; j<width; j++) {
			if(0==cc[i][j])
				cout<<"▉";
			if(1==cc[i][j])
				cout<<"  ";
		}
		cout<<endl;
	}
	cout<<"\n操作说明:方向键(←)\t 方向键(→)\n\t 方向键(↑)\t 方向键(↓)\n\t 返回(ESC)";
}
void peopleGo(int &x,int &y) {
	h=GetStdHandle(STD_OUTPUT_HANDLE) ;
	if (count>0) {
		cout<<" ";
	}
	cd.X=x;
	cd.Y=y;

	SetConsoleCursorPosition(h,cd);

	cout<<"●";
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
	cout<<"●";
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
			cout<<"退出中<<\n";
			level=0;
			system("pause");
			return;
		} else {
			control(c);
			peopleGo(X,Y);
			//过关
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
		cout<<"无效输入,";
		system("pause");
		runChose();
	}
	return 0;

}

////////////////////////////////
int main() {
	h=GetStdHandle(STD_OUTPUT_HANDLE) ;
	//隐藏光标
	//CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(h, &cci);

	author();
	cout<<"   正在加载迷宫游戏,";
	system("pause");
	runChose();
	system("pause");

	return 0;
}
