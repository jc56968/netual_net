#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
//every layer's node <30
using namespace std;
typedef struct net_node
{
	double value;
	int layer;
	int layer_node_num;
	int weight_num;
	int input_num;
	int output_num;
	int weight[11];
	net_node *input_value[11];
	net_node *output_value[785];
	
}netnode;
int gecengnode[10] = {};
int now_layer_node_num[10] = {0};
netnode * now_layer_node_link[10][785] ;
int check(int a, netnode *q)
{
	int i=1;
	while (int((*q).input_value[i])!= 0xcdcdcdcd&&i<=10)
	{
		if (int((*q).input_value[i]) == a)
			return 1;
		i++;
	}
	return 0;
}
void  net_frame_creat(netnode *q,int layer_num,int max_link)
{
	
	//cout << (*q).layer;
	(*q).weight_num =(max_link+1) / 2 + ( 7- layer_num) * 2;
	if ((*q).weight_num > max_link)
		(*q).weight_num = max_link;
	(*q).input_num = (*q).weight_num;
	for (int i =1; i <= (*q).input_num; i++)
	{
		
		if (now_layer_node_num[layer_num-1] <= 783)
		{
			int a;
			srand(time(NULL));
			a = rand() % 100 + 1;
			netnode *p;
			p = (netnode *)malloc(sizeof(netnode));
			for (int u = 1; u <= (*q).input_num; u++)
			{
				
				srand(a);     //设置随机数种子，使每次运行获取到的随机数值不同。
				a = rand() % 100 + 1; //获取1-100的随机数。
				if (u % 2 == 0)
					a = 0-a;
				(*q).weight[u] = a;
			}
			(*q).input_value[i] = p;
			(*p).output_value[1] = q;
			now_layer_node_num[layer_num-1]++;
			now_layer_node_link[layer_num-1][now_layer_node_num[layer_num-1]] = p;
			(*p).layer_node_num = now_layer_node_num[layer_num-1];
			if (layer_num >= 2)
			{
				(*p).layer = layer_num - 1;
				net_frame_creat(p, layer_num - 1, max_link);
			}
			else
				(*p).layer = 1;
			(*p).output_num = 1;
		}
		else
		{
			now_layer_node_num[layer_num-1]++;
			int c = now_layer_node_num[layer_num-1] / 784;
			int d = now_layer_node_num[layer_num-1] % 784;
			d = d + c;
			while (d > 784)
			{
				d = d - 784;

				while (check(int(now_layer_node_link[layer_num - 1][d]), q))
					d++;
			}

				(*q).input_value[i] = now_layer_node_link[layer_num - 1][d];
				int g =1 ;
			while (int((*now_layer_node_link[layer_num-1][d]).output_value[g] )!=0xcdcdcdcd&&g<=784)//NULL=0xdddddddddd
			{
				g++;
			}
			
			(*now_layer_node_link[layer_num-1][d]).output_num = g;
			(*now_layer_node_link[layer_num-1][d]).output_value[g] = q;
		}
		
		
		
	} 



	
	
}
void back_net(netnode *q, double * inputdata, int inputlabel)
{
	int a = (*q).value * 1000 - inputlabel;
	//for(int i=1;i<= (*q).weight_num;i++)
	//	a*(*q).weight[i]
}
void  net_forward_train(netnode *q, double * inputdata, int inputlabel)
{
	int hub[10] = {784,784,784,784,315,35,5,1};
//	int he=1;
	for (int j = 1; j <= 7; j++)   //第j层--->
	{
		for (int i = 1; i <= hub[j]; i++)
		{
			(*now_layer_node_link[j][i]).value = 0;
		}

		for (int i = 1; i <= hub[j]; i++)
		{

			for (int k = 1; k <= (*now_layer_node_link[j][i]).weight_num; k++)
			{
			//	if(abs((*now_layer_node_link[j][i]).weight[k])!=0)
			///	he = abs((*now_layer_node_link[j][i]).weight[k])*he;
				(*now_layer_node_link[j][i]).value = (*now_layer_node_link[j][i]).value + ((*(*now_layer_node_link[j][i]).input_value[k]).value)*(*now_layer_node_link[j][i]).weight[k];
				
			}
			(*now_layer_node_link[j][i]).value = (*now_layer_node_link[j][i]).value / 10000000;
		}
	}
}
void  net_set(netnode *q, double * inputdata, int inputlabel)
{
	for (int i = 1; i <= 784; i++)
		for(int j=1;j<=10;j++)
		(*now_layer_node_link[0][i]).value = inputdata[i];
	net_forward_train(q, inputdata, inputlabel);
}
int main()
{
	double inputdata[785] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,84,222,67,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,185,254,114,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,159,254,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,151,254,114,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,60,254,163,0,0,0,0,0,0,0,0,0,0,0,0,0,0,61,121,121,0,0,0,0,0,0,0,0,36,241,227,17,0,0,0,0,0,0,0,0,0,0,0,31,133,242,254,254,0,0,0,0,0,0,0,0,0,198,254,66,0,0,0,0,0,0,0,0,0,3,38,224,254,254,254,207,0,0,0,0,0,0,0,0,0,198,225,14,0,0,0,0,0,0,0,0,19,203,254,254,254,254,219,18,0,0,0,0,0,0,0,0,0,198,254,67,0,0,0,0,0,0,0,75,221,254,254,115,52,52,40,0,0,0,0,0,0,0,0,0,0,198,254,67,0,0,0,0,0,9,126,251,254,219,77,1,0,0,0,0,0,0,0,0,0,0,0,0,0,198,254,67,0,0,0,59,133,205,254,240,166,35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,198,250,59,0,22,129,249,254,248,182,57,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,198,229,21,83,233,254,254,187,58,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,198,254,236,253,255,238,62,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,170,254,254,209,83,44,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,52,140,106,18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int i = 1; i <= 784; i++)
		inputdata[i] = inputdata[i] ;
	double inputlabel = 7;
	int layer_num,max_link;
	// cin>>layer_num;
	//cin >> max_link;
	layer_num = 7;
	max_link = 10;
	netnode *result;
	result = (netnode *)malloc(sizeof(netnode));
	(*result).layer =7;
	now_layer_node_link[layer_num][1] = result;
	(*result).output_num = 0;
	(*result).layer_node_num = 1;
	
		net_frame_creat(result, layer_num, max_link);

		net_set(result, inputdata, inputlabel);//inputdata=1*(28*28)reshape 700,inputlabel={1,2,3,4.5,6,7,8,9,10}每次训练一个，至少100个起
		
			cout<<(*result).value * 1000<<endl;
			net_set(result, inputdata, inputlabel);
			cout << (*result).value * 1000;
		if ((*result).value * 1000 != 7)
			back_net(result, inputdata, inputlabel);
		
	layer_num++;

	system("pause");
	return 0;

}