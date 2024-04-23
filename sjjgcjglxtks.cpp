#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;
#define MAX 100
int renshu = 0;
int lg = 0;//注册的人数
long  ac[100][2];//记录注册的账号密码


typedef struct Student {
	char name[20];//姓名
	int num;//学号
	double score[3];//三门科目分数
	double ave;//平均分
	double sum;//总成绩
	int pm;//班级排名
}Student;


typedef struct
{
	Student elem[MAX];//线性表占用数组空间
	int last; //最后一个元素下标
}SeqList;

//通过学号来检索学生信息
int Student_SearchByIndex(SeqList* L, int id) 
{
	int i;
	for (i = 1; i <= renshu; i++)
	{
		if (L->elem[i].num == id)
		{
			return i;
		}
	}
	return -1; //未找到返回 -1
}

//总分排名
void SortSum(SeqList* L) {
	int i = 1;
	int j = 1;
	Student stu = L->elem[j];
	for (i = 1; i <= L->last; i++)
	{
		for (j = 1; j <= L->last - i; j++)
		{
			if (L->elem[j].sum < L->elem[j + 1].sum)
			{
				stu = L->elem[j];
				L->elem[j] = L->elem[j + 1];
				L->elem[j + 1] = stu;
			}
		}
	}
	for (i = 1; i <= L->last; i++)
	{
		L->elem[i].pm = i;
	}
}

 //录入学生数据
void InList(SeqList *L,int i) {
	int x;
	cout << "请输入学生数量：" << endl;
	cin >> x;
	renshu = x;
	cout << "请录入学生信息：学号 姓名 英语 大物 马原（数据直接用空格隔开）" << endl;
	for (i = 1; i <=x; i++)
	{
		cin >> L->elem[i].num;
		cin >> L->elem[i].name;
		cin >> L->elem[i].score[0];
		cin >> L->elem[i].score[1];
		cin >> L->elem[i].score[2];
		L->elem[i].sum = L->elem[i].score[0] + L->elem[i].score[1] + L->elem[i].score[2]; //输完数据后自动计算总成绩与平均成绩
		L->elem[i].ave = (L->elem[i].score[0] + L->elem[i].score[1] + L->elem[i].score[2]) / 3;
	}
	cout << "录入成功! " << endl;
	L->last = x;
	SortSum(L);
}

//输出成绩
void OutList(SeqList* L, int i)
{
	SortSum(L);
	for (i = 1; i <=L->last; i++)
	{
		cout << "学号:" << L->elem[i].num << " 姓名:" << L->elem[i].name << " 英语成绩:" << L->elem[i].score[0] << " 大物成绩:" << L->elem[i].score[1] << " 马原成绩:" << L->elem[i].score[2] << " 总分:" << L->elem[i].sum << " 平均分:" << L->elem[i].ave << " 班级排名: " << L->elem[i].pm << endl;
	}
}

//以学号查找学生
void XFind(SeqList* L)
{
	SortSum(L);
	int i = 1;
	int n ;
	cout << "请输入要查找学生的学号:" << endl;
	cin >> n;
	
	if (Student_SearchByIndex(L, n) == -1)
	{
		cout << "输入学号错误，请重新输入！" << endl;
		return;
	}
	else {
		cout << "该生成绩如下：" << endl;
		int q = Student_SearchByIndex(L, n);
		cout << "学号:" << L->elem[q].num << " 姓名:" << L->elem[q].name << " 英语成绩:" << L->elem[q].score[0] << " 大物成绩:" << L->elem[q].score[1] << " 马原成绩:" << L->elem[q].score[2] << " 总分:" << L->elem[q].sum << " 平均分:" << L->elem[q].ave <<" 班级排名: "<<L->elem[q].pm << endl;
	
	}

	
}

//删除学生
int Delete(SeqList* L) {
	int j;
	int k;
	int i;
	cout << "请输入要删除的学生学号: ";
	cin >> i;
	if (L->last < 1)
	{
		cout << "空表！";
		return 0;
	}
	for (k = 1; k <= L->last; k++)
	{
		if (L->elem[k].num==i)
			break;
	}
	if (k > L->last)
	{
		cout << "未找到该学生!" << endl;
		return 0;
	}
	else {
		for (j = k; j <= L->last; j++)
			L->elem[j] = L->elem[j + 1];//将位序j+1及以后的元素前移
		L->last--;//last仍指向最后元素
		return 1;
	}
	
	
}

//修改学生数据
void Change(SeqList* L)
{
	int num;
	int i = 1, flag = 0;
	int course = 0;
	int temp;
	int english = 0, dawu = 0, mayuan = 0;
	cout << "请输入要修改学生的学号: " << endl;
	cin >> num;
	for (i = 1; i <=L->last; i++)
	{
		if (num==L->elem[i].num)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "请输入正确的学号！" << endl;
		return;
	}
	cout << "该学生当前信息如下: " << endl;
	cout << "学号:" << L->elem[i].num << " 姓名:" << L->elem[i].name << " 英语成绩:" << L->elem[i].score[0] << " 大物成绩:" << L->elem[i].score[1] << " 马原成绩:" << L->elem[i].score[2] << " 总分:" << L->elem[i].sum << " 平均分:" << L->elem[i].ave << endl;
	cout << "是否需要修改成绩?(需要输入【1】不需要输入【0】)" << endl;
	cin >> temp;
	switch (temp)
	{
	case 1:
	{
		cout << "请按指示修改课程成绩..." << endl;
		cout << "是否需要修改英语成绩？（需要输入【1】不需要输入【0】）" << endl;
		cin >> course;
		if (course == 1)
		{
			cout << "请输入修改后的英语成绩："; cin >> L->elem[i].score[0];
		}
		course = 0;

		cout << "是否需要修改大物成绩？（需要输入【1】不需要输入【0】）" << endl;
		cin >> course;
		if (course == 1)
		{
			cout << "请输入修改后的大物成绩："; cin >> L->elem[i].score[1];
		}
		course = 0;

		cout << "是否需要修改马原成绩？（需要输入【1】不需要输入【0】）" << endl;
		cin >> course;
		if (course == 1)
		{
			cout << "请输入修改后的马原成绩："; cin >> L->elem[i].score[2];
		}
		course = 0;

		L->elem[i].sum = L->elem[i].score[0] + L->elem[i].score[1] + L->elem[i].score[2];
		L->elem[i].ave = L->elem[i].sum / 3;

		cout << "修改后的信息如下： " << endl;
		cout << "学号:" << L->elem[i].num << " 姓名:" << L->elem[i].name << " 英语成绩:" << L->elem[i].score[0] << " 大物成绩:" << L->elem[i].score[1] << " 马原成绩:" << L->elem[i].score[2] << " 总分:" << L->elem[i].sum << " 平均分:" << L->elem[i].ave << endl;
	}
	break;
	case 0:
	{
		break;
	}
	break;
	default:
	{cout << "输入有误..." << endl; }

	}
	SortSum(L);
}

//学号排序学生
void SortStudent(SeqList* L)
{
	SortSum(L);
	int i = 1;
	int j = 1;
	Student stu = L->elem[j];
	for (i = 1; i <=L->last; i++)
	{
		for (j = 1; j <=L->last - i; j++)
		{
			if (L->elem[j].num>L->elem[j + 1].num)
			{
				stu = L->elem[j];
				L->elem[j] = L->elem[j + 1];
				L->elem[j + 1] = stu;
			}
		}
	}
	
	cout << "按学号排序后信息如下:" << endl;
	for (i = 1; i <= L->last; i++)
	{
		cout << "学号:" << L->elem[i].num << " 姓名: " << L->elem[i].name << " 英语成绩:" << L->elem[i].score[0] << " 大物成绩:" << L->elem[i].score[1] << " 马原成绩:" << L->elem[i].score[2] << " 总分:" << L->elem[i].sum << " 平均分:" << L->elem[i].ave <<" 班级排名："<<L->elem[i].pm << endl;
	}
}

//按英语成绩排序学生
void Sortenglish(SeqList *L) {
	int i = 1;
	int j = 1;
	Student stu = L->elem[j];
	for (i = 1; i <= L->last; i++)
	{
		for (j = 1; j <= L->last - i; j++)
		{
			if (L->elem[j].score[0] < L->elem[j + 1].score[0])
			{
				stu = L->elem[j];
				L->elem[j] = L->elem[j + 1];
				L->elem[j + 1] = stu;
			}
		}
	}
	cout << "英语成绩如下：" << endl;
	for (i = 1; i <= L->last; i++)
	{
		cout << "学号:" << L->elem[i].num << " 姓名:" << L->elem[i].name << " 英语成绩:" << L->elem[i].score[0]<<" 排名: "<<i<<endl;
	}
}

//按大物成绩排序学生
void Sortdawu(SeqList* L) {
	int i = 1;
	int j = 1;
	Student stu = L->elem[j];
	for (i = 1; i <= L->last; i++)
	{
		for (j = 1; j <= L->last - i; j++)
		{
			if (L->elem[j].score[1] < L->elem[j + 1].score[1])
			{
				stu = L->elem[j];
				L->elem[j] = L->elem[j + 1];
				L->elem[j + 1] = stu;
			}
		}
	}
	cout << "大物成绩如下：" << endl;
	for (i = 1; i <= L->last; i++)
	{
		cout << "学号:" << L->elem[i].num << " 姓名:" << L->elem[i].name << " 大物成绩:" << L->elem[i].score[1] << " 排名: " << i << endl;
	}
}

//按马原成绩排序学生
void Sortmayuan(SeqList* L) {
	int i = 1;
	int j = 1;
	Student stu = L->elem[j];
	for (i = 1; i <= L->last; i++)
	{
		for (j = 1; j <= L->last - i; j++)
		{
			if (L->elem[j].score[2] < L->elem[j + 1].score[2])
			{
				stu = L->elem[j];
				L->elem[j] = L->elem[j + 1];
				L->elem[j + 1] = stu;
			}
		}
	}
	cout << "马原成绩如下：" << endl;
	for (i = 1; i <= L->last; i++)
	{
		cout << "学号:" << L->elem[i].num << " 姓名:" << L->elem[i].name << " 马原成绩:" << L->elem[i].score[2] << " 排名: " << i << endl;
	}
}

//查询各科目学生成绩情况
void SearchLow(SeqList* L)
{
	int a = 1; 
	double sume = 0, sumd = 0, summ = 0;//各科平均分
	int eb = 0, db = 0, mb = 0;//不及格人数
	int ey = 0, dy = 0, my = 0;//优秀人数
	int temp;
	cout << "请输入你想查询的科目：（英语【1】，大物【2】，马原【3】）" << endl;
	cin >> temp;
	switch (temp) {
	case(1):
	{for (a = 1; a <= L->last; a++)
	{
		sume = sume + L->elem[a].score[0];
		if (L->elem[a].score[0] < 60)
		{
			eb++;
		}
		if (L->elem[a].score[0] >= 90)
		{
			ey++;
		}

	}
	Sortenglish(L);
	printf("英语不及格的有：%d人 优秀的有：%d人 平均分为：%.2lf\n", eb, ey, sume / L->last);
	}break;
	case(2):
	{for (a = 1; a <= L->last; a++)
	{
		sumd = sumd + L->elem[a].score[1];
		if (L->elem[a].score[1] < 60)
		{
			db++;
		}
		if (L->elem[a].score[1] >= 90)
		{
			dy++;
		}

	}
	Sortdawu(L);
	printf("大物不及格的有：%d人 优秀的有：%d人 平均分为：%.2lf\n", db, dy, sumd / L->last);
	}break;
	case(3):
	{
		for (a = 1; a <= L->last; a++)
		{
			summ = summ + L->elem[a].score[2];
			if (L->elem[a].score[2] < 60)
			{
				mb++;
			}
			if (L->elem[a].score[2] >= 90)
			{
				my++;
			}

		}
		Sortmayuan(L);
		printf("马原不及格的有：%d人 优秀的有：%d人 平均分为：%.2lf\n", mb, my, summ / L->last);
	}break;
	default:
	{cout << "输入有误..." << endl; }
	system("pause");
	}
}

//登录系统菜单
int menu() {
	int option;
	time_t timep;    //系统时间 
	struct tm* p_1;
	time(&timep);
	p_1 = gmtime(&timep);
	printf("                           当前时间%02d时%02d分%\n", 8 + p_1->tm_hour, p_1->tm_min);
	printf("                                   %d年%02d月%02d日\n", 1900 + p_1->tm_year, 1 + p_1->tm_mon, p_1->tm_mday);
	printf("-------------------------------------------------------------------------\n");
	printf("                        欢迎使用高校学生信息管理系统                     \n");
	printf("-------------------------------------------------------------------------\n");
	printf("                             1.登录系统                          \n");
	printf("                             2.注册账号                    \n");
	printf("-------------------------------------------------------------------------\n");
	cout << "第一次使用请先注册账号!" << endl;
	printf("请选择(1/2):>");
	cin >> option;
	return option;
}

//注册
int zc() {
	long  un;
	long  ps;
	int a;
	cout << "请输入用户名(仅支持1~9位数字): ";
	cin >> un;
	cout << "请输入密码(仅支持1~9位数字): ";
	cin >> ps;
	if (lg >= 100)
	{
		cout << "注册已满" << endl;
		return 0;
	}
	else
	{
		ac[lg][0] = un;
		ac[lg][1] = ps;
		lg++;
		cout << "注册成功" << endl;
		cout << "要继续注册吗？（1/0）: " << endl;
		getchar();
		cin >> a;
		if (a == 1) { return 1; }
		else { return 0; }
	}

}

//登录
int dl()
{
	long a, b;
	int  c, d;
	for (c = 0; c < 3; c++)
	{
		cout << "请输入用户名(仅支持1~9位数字): ";
		cin >> a;
		cout << "请输入密码(仅支持1~9位数字): ";
		cin >> b;
		for (d = 0; d < lg; d++)
		{
			if (a == ac[d][0] && b == ac[d][1])
			{
				cout << "登录成功！" << endl;
				return 1;
				break;
			}
			else
			{
				cout << "用户名或密码错误！" << endl;
				continue;
			}
		}

	}cout << "三次登录失败，程序结束。" << endl;
}

//录入文件中的信息
void initdata(SeqList* L)
{
	FILE* fp;
	int n=0;
	int j = 1;
	fp = fopen("D://student.txt", "r");
	if (fp == NULL)
	{
		cout << "error!";
			return;
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp,"%d %s %lf %lf %lf", &L->elem[j].num,L->elem[j].name,&L->elem[j].score[0], &L->elem[j].score[1], &L->elem[j].score[2]);
		
			L->elem[j].sum = L->elem[j].score[0] + L->elem[j].score[1] + L->elem[j].score[2];
			L->elem[j].ave = L->elem[j].sum / 3;
			j++;
			n++;
		}
		cout << "文件录入成功！" << endl;
	}
	L->last = n-1;
	fclose(fp);
}

//存储排序后的信息
void savedata(SeqList*L) {
	FILE* fp;
	fp = fopen("D://sortstudent.txt", "w");
	if (fp == NULL)
	{
		cout << "error!";
		return;
	}
	else
	{
		fprintf(fp, "学号  姓名    英语 大物 马原 平均分  总分 班级排名\n");
		for(int j=1;j<=L->last;j++)
		{
			fprintf(fp, "%d %s  %.0lf   %.0lf    %.0lf    %.2lf   %.0lf      %d\n", L->elem[j].num, L->elem[j].name, L->elem[j].score[0], L->elem[j].score[1], L->elem[j].score[2],L->elem[j].ave, L->elem[j].sum,L->elem[j].pm);
		}
		cout << "文件已成功保存至D://sortstudent.txt中！" << endl;
	}
	
	fclose(fp);


}
int main()
{
	
	int a, b;
	int i;
	int j=1;
	SeqList  L;
	
	int option;
	option = menu();
	for (;;) {
		if (option == 2)
		{
			a = zc();
			if (a == 1) { continue; }
			else { option = menu(); }
		}
		else if (option == 1)
		{
			b = dl();
			if (b == 1) { break; }
			else { return 0; }
		}
	
	}

	while (1)
	{

		printf("-------------------------------------------------------------------------\n");
		printf("                               请选择系统功能                     \n");
		printf("-------------------------------------------------------------------------\n");
		printf("                        欢迎使用高校学生信息管理系统               \n");
		printf("-------------------------------------------------------------------------\n");
		printf("                             0.退出系统                          \n");
		printf("                             1.学生信息的录入                    \n");
		printf("                             2.学生信息的修改                    \n");
		printf("                             3.学生信息的删除                    \n");
		printf("                             4.学生信息的打印                    \n");
		printf("                             5.学生信息的查找                    \n");
		printf("                             6.学生成绩的排序                    \n");
		printf("                             7.查询各科学生分数信息           \n");
		printf("                             8.从文件中录入信息          \n");
		printf("                             9.存储排序后信息到文件中          \n");
		
		printf("请选择(0-9):>");
		cin >> i;
		switch (i)
		{
		case 1:
			InList(&L,j);
			break;
		case 2:
			Change(&L);
			break;
		case 3:
			Delete(&L);
		case 4:
			OutList(&L, j);
			break;
		case 5:
			XFind(&L);
			break;
		case 6:
			SortStudent(&L);
			break;
		case 7:
			SearchLow(&L);
			break;
		case 8:
			
			initdata(&L);
			break;
		case 9:
			savedata(&L);
			break;
		case 0:
			printf("感谢您的使用，再见！");
			exit(0);
		default:;
		}
	}
	return 0;
}