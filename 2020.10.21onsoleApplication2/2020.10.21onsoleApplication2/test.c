#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
	int i, t, n;
	float a = 2, b = 1, s = 0;
	n = 20;
	for (i = 1; i < n; i++)
	{
		s = s + a / b;
		t = a;
		a = a + b;
		b = t;
	}
	printf("%f\n", s);
	return 0;
}

//#include<stdio.h>
//int Max(int a, int b)
//{
//	if (a > b)
//		return a;
//	else
//		return b;
//}
//int main()
//{
//	int a, b,max;
//	printf("请输入两个数：");
//	scanf("%d%d", &a, &b);
//	max = Max(a, b);
//	printf("较大的数是：%d\n", max);
//}

//int Add(int a, int b)
//{
//	int sum;
//	sum = a + b;
//	return sum;
//}
//int main()
//{
//	int sum=0;
//	sum=Add(3, 5);
//	printf("%d\n", sum);
//	return 0;
//}


//#include<stdio.h>
//char ShowChar();
//int main()
//{
//	char cResult;
//	cResult = ShowChar();
//	printf("%c\n", cResult);
//	return 0;
//}
//char ShowChar()
//{
//	int iNumber;
//	printf("please input a number:\n");
//	scanf("%d", &iNumber);
//	return iNumber;
//}


//#include<stdio.h>
//int Max(int x, int y)
//{
//	int sum;
//	sum = x + y;
//	return sum;
//}
//int main()
//{
//	int a, b, m;
//	printf("请输入两个数：");
//	scanf("%d,%d", &a, &b);
//	m = Max(a, b);
//	printf("Max is %d\n", m);
//	return 0;
//}