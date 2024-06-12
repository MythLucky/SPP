#include<iostream>
#include<cstdio>
using namespace std;
int m,n,fin_price=0,anstop=0;
int *conLength,*eleLength,*eleNum,*ans,*p;
int **con,**ele;
bool *eleFlag,*conFlag;
bool ansFlag;
void input()
{
	int x,t;
	int i,j,k;
	//aa03,aa05 
	freopen("SPP_C++/sppaa05.txt","r",stdin);
	cin>>m>>n;//m为约束,n为元素

	eleFlag=new bool[n];//元素是否已被移除
	conFlag=new bool[m];//约束是否已被移除
	conLength=new int[n];//元素下的约束数量
	eleLength=new int[m];//约束下的元素数量
	eleNum=new int[m];//优化后约束下的元素数量

	fill_n(eleFlag,n,0);
	fill_n(conFlag,m,0);
	fill_n(conLength,n,0);
	fill_n(eleLength,m,0);
	fill_n(eleNum,m,0);//数组初始化
	p=new int[n];
	con = new int*[n]; //行指针
    for(j=0;j<=n-1;j++) 
		*(con+j) = new int[m]; //列生成
	ele = new int*[m]; //行指针
    for(j=0;j<=m-1;j++)
		*(ele+j) = new int[n]; //列生成

	for(j=0;j<=n-1;j++)//错位存储，所有元素左移一位
	{ //823 8904
		cin>>*(p+j);//price
		cin>>*(conLength+j);
		t=*(conLength+j);
		for(int i=0;i<=t-1;i++)
		{
			cin>>x;
			x--;//错位存储
			con[j][i]=x;//元素j所占第i个约束为x
			ele[x][eleLength[x]++]=j;//约束x的下一个元素为j
		}
	}
	for(i=0;i<=m-1;i++)
	{
		eleNum[i]=eleLength[i];
	}
	return;
}
void setKeyElement(int x)//将x约束下的唯一元素设为关键元素
{
	int i=0,j,k,t,t1,t2;
	while (i<=eleLength[x]-1 && eleFlag[ele[x][i]])
		i++;
	t=ele[x][i];//t为关键元素
	cout<<"Because con:"<<x+1<<"  ele:"<<t+1<<"  is keyElement"<<endl;
	ans[anstop++]=t;
	fin_price+=p[t];
	eleFlag[t]=true;//弃用
	for(i=0;i<=conLength[t]-1;i++)//关键元素包含的约束全部弃用
	{
		t1=con[t][i];//遍历关键元素所包含的约束
		if(!conFlag[t1])
		{
			conFlag[t1]=true;//弃用
			for(j=0;j<=eleLength[t1]-1;j++)
			{
				t2=ele[t1][j];//弃用约束下的所有元素
				if (!eleFlag[t2])
				{
					eleFlag[t2]=true;//元素弃用
					for(k=0;k<=conLength[t2]-1;k++)
					{
						eleNum[con[t2][k]]--;
					}
				}
			}
		}
	}
	return;
}
bool key_element()//循环遍历，去除所有关键元素
{
	int timer=m,i=0;
	while (timer!=0)
	{
		if (conFlag[i%m]);
		else if (eleNum[i%m]==0)//如果约束下无元素，则无解
			return false;
		else if (eleNum[i%m]==1)//关键元素前置条件:约束下元素唯一
		{
			setKeyElement(i%m);//i为约束
			timer=m;
		}
		timer--;
		i++;
	}
	return true;
}
bool spp_init()
{
	ans=new int[n];
	fill_n(ans,n,0);
	fin_price=0;
	anstop=0;
	if(!key_element()){
		return false;
	}
	return true;
}
void release()
{
	delete[] conLength;
	delete[] eleLength;
	delete[] eleFlag;
	delete[] conFlag;
	delete[] p;
	for(int i=0;i<=n-1;i++)
        delete[] con[i];
    delete[] con;
	for(int i=0;i<=m-1;i++)
        delete[] ele[i];
    delete[] ele;
	delete[] ans;
	return;
}
void output_init_result()
{
	int i,j,h1=0,h2=0;
	for(i=0;i<=m-1;i++)
	{
		if (!conFlag[i]) h1++;
	}
	for(i=0;i<=n-1;i++)
	{
		if (!eleFlag[i]) h2++;
	}
	cout<<endl<<"    M:"<<m<<"  N:"<<n<<endl;
	cout<<"NEW M:"<<h1<<"  N:"<<h2<<endl;
	return;
}
void NoAnswer()
{
	cout<<"NO ANSWER";
	return;
}
int main()
{
	input();
	if (!spp_init())
	{
		NoAnswer();
		return 0;
	}
	output_init_result();
	release();

	return 0;
}
