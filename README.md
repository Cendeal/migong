# 窗口台迷宫--无闪屏

 1. 编译环境
 2. 处理方法
 3. 关键代码
 4. 下载example
 5. 文件说明
## 1.编译环境
主要是在decv++IDE下进行的项目，如果需要搬到vs下编译自行处理，主要语言c/c++
## 2. 处理方法
这与普通的黑窗体迷宫不一样，普通的处理是每一步都要重新更新整一个窗口。而这个迷宫处理的思想是只改变变化的位置，比如向前移动，就只需要在前一个位置输入角色，把原来的擦处掉，其他位置保持不变。
## 3.关键代码
```
    //人物移动处理
    void peopleGo(int &x,int &y) {
	h=GetStdHandle(STD_OUTPUT_HANDLE) ;//获取句柄
	if (count>0) {
		cout<<" ";
	}
	cd.X=x;
	cd.Y=y;
	SetConsoleCursorPosition(h,cd);//设置输出的位置
	cout<<"●";
	getcount();
	cd.X=x;
	SetConsoleCursorPosition(h,cd);
	} 
```
## 4.下载example
[下载](https://raw.githubusercontent.com/Cendeal/migong/project/migong.7z)

[项目地址](https://github.com/Cendeal/migong)

图示:

![pic](https://github.com/Cendeal/migong/blob/project/res/migong.gif)
## 5.文件说明
| 文件夹        | 说明          |  
| ------------- |:-------------:| 
| project    | 源代码| 
| map     | 地图文件    |
| res    | 示例图    |  
