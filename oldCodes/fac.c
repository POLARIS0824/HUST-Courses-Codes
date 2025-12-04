#include<stdio.h>
double mulx(double x,int n);
long fac(int n);
double sum(double x,int n);

// 计算总和
double sum(double x,int n)
{
    int i;
    double z = 1.0;
    for (i = 1; i <= n; i++)
    {
        z = z + mulx(x, i) / fac(i);
    }
    return z;
}

double mulx(double x,int n)
{
	int i;
	double z=1.0;
	for(i=0;i<n;i++)
	{
		z=z*x;
	}
	return z;
}

// 计算阶乘
long fac(int n)
{
	long h = 1;
    for (int i = 2; i <= n; i++)
    {
        h *= i;
    }
    return h;
}

int main()
{
	double x;
	int n;
	scanf("%lf%d",&x,&n);
	printf("The result is %lf",sum(x,n));
	return 0;
} 