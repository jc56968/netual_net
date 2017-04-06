#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<cmath>
#include <iomanip>  
#include <fstream>  

//every layer's node <30
using namespace std;
double ui = 1;
typedef struct net_node
{
	double weight[11];
	double value;
	int layer;
	int layer_node_num;
	int weight_num;
	int input_num;
	int output_num;
	
	double grad;
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
		if (q== now_layer_node_link[4][80])
		{
			cout << "";
		}
		if (now_layer_node_num[layer_num-1] <= 783)
		{
			double a;
			srand(time(NULL));
			a = rand() % 20- 10;
			netnode *p;
			p = (netnode *)malloc(sizeof(netnode));
			for (int u = 1; u <= (*q).input_num; u++)
			{
				a=a+ layer_num - 1;
				a = a + now_layer_node_num[layer_num - 1] + 1;
				srand(a);     //设置随机数种子，使每次运行获取到的随机数值不同。
     	
				
				a = rand() % 20- 10;

				
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
			double a;
			srand(time(NULL));
			a = rand() % 200 - 100;
			for (int u = 1; u <= (*q).input_num; u++)
			{
				a = a + layer_num - 1;
				a = a + now_layer_node_num[layer_num - 1] + 1;
				srand(a);     //设置随机数种子，使每次运行获取到的随机数值不同。


				a = rand() % 20 - 10;


				(*q).weight[u] = a;


			}
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
	int hub[10] = { 784,784,784,784,80,35,5,1 };
	
	double wrong = inputlabel-(*q).value ;
	double  VA = -log(1 / (*q).value - 1);
	double daoshu = (exp(-1 * VA)) / ((1 + exp(-2 * VA) + 2 * exp(-1 * VA)));
	(*q).grad= wrong*daoshu;
	if ((*q).grad > 100)
		(*q).grad = 100;
	if ((*q).grad < -100)
		(*q).grad = -100;
	
	//求导后
	//各层传递误差计算
	for (int i = 6; i >= 1; i--)
	{

		for (int j = 1; j <= hub[i]; j++)
		{
			wrong = 0;
			VA = -log(1 / (*now_layer_node_link[i][j]).value - 1);
			daoshu = (exp(-1 * VA)) / ((1 + exp(-2 * VA) + 2 * exp(-1 * VA)));
			for (int k = 1; k <= (*now_layer_node_link[i][j]).output_num; k++)
			{
				int next_layer_weight;
				for (int z = 1; z <= (*(*now_layer_node_link[i][j]).output_value[k]).input_num; z++)
				{
					if (int((*(*now_layer_node_link[i][j]).output_value[k]).input_value[z]) == int(now_layer_node_link[i][j]))
						next_layer_weight = (*(*now_layer_node_link[i][j]).output_value[k]).weight[z];
				}
				wrong = wrong + (*(*now_layer_node_link[i][j]).output_value[k]).grad   * next_layer_weight;
			}

			int you = daoshu*wrong * 1;
			if (you > 100)
				you = 100;
			if (you < -100)
				you = -100;
			(*now_layer_node_link[i][j]).grad = you;

		}
	 
	}
	
	//ui = abs((*q).value * 10 - 5) / 5  *ui    ;

	//
	//权值修正
	for (int i = 7; i >= 1; i--)
	{

		for (int j = 1; j <= hub[i]; j++)
		{

			for (int k = 1; k <= (*now_layer_node_link[i][j]).weight_num; k++)
			{
				(*now_layer_node_link[i][j]).weight[k] = (*now_layer_node_link[i][j]).weight[k] + ui * (*now_layer_node_link[i][j]).grad * (  (*(*now_layer_node_link[i][j]).input_value[k]).value);
				if ((*now_layer_node_link[i][j]).weight[k] > 100)
					(*now_layer_node_link[i][j]).weight[k] = 100;
				if ((*now_layer_node_link[i][j]).weight[k] < -100)
					(*now_layer_node_link[i][j]).weight[k] = -100;


			}

		}
	}



	
}
void  net_forward_train(netnode *q, double * inputdata, int inputlabel)
{
	int hub[10] = { 784,784,784,784,315,35,5,1 };
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
				if(abs((*now_layer_node_link[j][i]).weight[k])!=0)
		     //	he = abs((*now_layer_node_link[j][i]).weight[k])*he;
				(*now_layer_node_link[j][i]).value = (*now_layer_node_link[j][i]).value + ((*(*now_layer_node_link[j][i]).input_value[k]).value)*(*now_layer_node_link[j][i]).weight[k];
				
			}
//			(*now_layer_node_link[j][i]).value = (*now_layer_node_link[j][i]).value /100;
		(*now_layer_node_link[j][i]).value = 1 / (1 + (exp(-(*now_layer_node_link[j][i]).value)));
			
		}
	}
}
void  net_set(netnode *q, double * inputdata, int inputlabel)
{
	for (int i = 1; i <= 784; i++)

		(*now_layer_node_link[0][i]).value = inputdata[i];
	net_forward_train(q, inputdata, inputlabel);
}


int main()
{
	double **input;

	input = new double *[15001];
	int Qlabel[15001];
	for (int i = 1; i <= 15000; i++)
		input[i] = new double[785];
	char buf[4000];
	char buffer[20];
	ifstream myfile, lable;
	lable.open("C:\\Users\\JIC-PC\\Desktop\\train.txt");
	if (!lable) {
		cout << "Unable to open myfile";
		exit(1); // terminate with error  
	}
	if (lable.is_open())          //文件打开成功,说明曾经写入过东西  
	{
		int o = 1;
		while (lable.good() && !lable.eof() && o == 1)
		{

			o = 2;
			for (int i = 1; i <= 15000; i++)
			{
				int k = 0, obj = 0, m, s = 1;
				memset(buffer, 0, 20);
				lable.getline(buffer, 20);
				while (buffer[k] != ' ')
				{
					k++;
				}
				k++;
				m = k;
				while (buffer[k] >= '0'&&buffer[k] <= '9')
				{
					s = pow(10, k - m);
					obj = obj*s + (buffer[k] - '0');
					k++;
				}
				Qlabel[i] = obj;

			}

		}

	}

	myfile.open("C:\\Users\\JIC-PC\\Desktop\\image_cov_15000.txt");
	if (!myfile) {
		cout << "Unable to open myfile";
		exit(1); // terminate with error  
	}
	if (myfile.is_open())          //文件打开成功,说明曾经写入过东西  
	{
		int y = 1,L=1;
		while (myfile.good() && !myfile.eof())
		{


			int k = 0; int s = 1;
			memset(buf, 0, 4000);
			myfile.getline(buf, 4000);
			while (buf[k] !='\0')
			{
				int obj = 0;
				if (buf[k] == ',')
				{
					k++;
				}
				else
				{
				
					while (buf[k]!=',')
					{
					
						obj = obj*10 + (buf[k] - '0');
						k++;
					}
					
					input[L][s] = obj;
					s++;

				}
				
				
				
			}
			L++;
		
		}

	}

	myfile.close();


	double *inputdata = input[5];
	//double inputdata[501][785] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,84,222,67,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,185,254,114,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,159,254,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,151,254,114,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,60,254,163,0,0,0,0,0,0,0,0,0,0,0,0,0,0,61,121,121,0,0,0,0,0,0,0,0,36,241,227,17,0,0,0,0,0,0,0,0,0,0,0,31,133,242,254,254,0,0,0,0,0,0,0,0,0,198,254,66,0,0,0,0,0,0,0,0,0,3,38,224,254,254,254,207,0,0,0,0,0,0,0,0,0,198,225,14,0,0,0,0,0,0,0,0,19,203,254,254,254,254,219,18,0,0,0,0,0,0,0,0,0,198,254,67,0,0,0,0,0,0,0,75,221,254,254,115,52,52,40,0,0,0,0,0,0,0,0,0,0,198,254,67,0,0,0,0,0,9,126,251,254,219,77,1,0,0,0,0,0,0,0,0,0,0,0,0,0,198,254,67,0,0,0,59,133,205,254,240,166,35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,198,250,59,0,22,129,249,254,248,182,57,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,198,229,21,83,233,254,254,187,58,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,198,254,236,253,255,238,62,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,170,254,254,209,83,44,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,52,140,106,18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	double inputlabel = 7;
	int layer_num, max_link;
	// cin>>layer_num;
	//cin >> max_link;
	layer_num = 7;
	max_link = 10;
	netnode *result;
	result = (netnode *)malloc(sizeof(netnode));
	(*result).layer = 7;
	now_layer_node_link[layer_num][1] = result;
	(*result).output_num = 0;
	(*result).layer_node_num = 1;

	net_frame_creat(result, layer_num, max_link);

	//net_set(result, inputdata, inputlabel);//inputdata=1*(28*28)reshape 700,inputlabel={1,2,3,4.5,6,7,8,9,10}每次训练一个，至少100个起

		//cout<<(*result).value * 1000<<endl;
	for (int i = 1; i <= 10000; i++)
	{  //ui小 改最底层，大该高层；
		inputdata = input[i];
		inputlabel = Qlabel[i];
	//	if (int(inputlabel) == 8)
	//	{

			inputdata = input[i];
			inputlabel = 1;
			inputlabel = 1;
			ui = 0.01;
			//ui = ui / pow(10, i);
			net_set(result, inputdata, inputlabel);
			cout << "inputlabel      ===" << inputlabel << "      " << (*result).value << endl;

			//back_net(result, inputdata,1);
		//}

		//cout << pow(   (   (*result).value * 10   ) , 1.67895     ) << endl;
	}
	for (int i = 1; i <= 10000; i++)
	{  //ui小 改最底层，大该高层；
		inputdata = input[i];
		inputlabel = Qlabel[i];
		if (int(inputlabel)!= 8)
		{

			inputdata = input[i];
			inputlabel = 1;
			inputlabel = 1;
			ui = 1;
			//ui = ui / pow(10, i);
			net_set(result, inputdata, inputlabel);
			cout << "inputlabel      ===" << inputlabel << "      " << (*result).value << endl;

			back_net(result, inputdata, 0);
		}

		//cout << pow(   (   (*result).value * 10   ) , 1.67895     ) << endl;
	}



	double z = 0, t = 0, z2 = 0, t2 = 0;
	for (int i = 1; i <= 1000; i++)
	{  //ui小 改最底层，大该高层；
		inputdata = input[i];
		inputlabel = Qlabel[i];

		if (int(inputlabel) == 8)
		{
			net_set(result, inputdata, inputlabel);
			t++;
			if (abs((*result).value) - 1 >= 0.1)
				z++;

		}
		else
		{
			t2++;
			if (abs((*result).value) - 0 >= 0.1)
				z2++;

		}
	}

	cout << "    " << z <<t << "    " << z2 <<t2 << endl;




	
	for (int n = 1; n < 1; n++)
	{
		for (int i = 1; i <= 10000; i++)
		{  //ui小 改最底层，大该高层；
			inputdata = input[i];
			inputlabel = Qlabel[i];
			if (int(inputlabel) == 8)
			{
				inputlabel = 1;
				ui = 1;
				//ui = ui / pow(10, i);
				net_set(result, inputdata, inputlabel);
				cout << "inputlabel      ===" << inputlabel << "      " << (((*result).value) * 10) << endl;
				if (abs((*result).value) - 1 >= 0.1)
				{
					back_net(result, inputdata, inputlabel);
					cout << (*result).value  << endl;
				}

			


			}
			else
			{
				inputlabel = 0;
				ui = 100;

				net_set(result, inputdata, inputlabel);

				if (abs((*result).value) - 0 >= 0.1)
				{
					back_net(result, inputdata, inputlabel);

				}
			}
		}
	}
 z = 0, t=0,z2=0,t2=0;
	for (int i = 1; i <= 1000; i++)
	{  //ui小 改最底层，大该高层；
		inputdata = input[i];
		inputlabel = Qlabel[i];
		
		if (int(inputlabel) == 8)
		{
			net_set(result, inputdata, inputlabel);
			t++;
			if (abs((*result).value) - 1 >= 0.1)
				z++;
			
		}
		else
		{
			t2++;
			if (abs((*result).value) - 0 >= 0.1)
				z2++;
			
		}
	}

	cout << "    " <<z/t<<"    "<<z2/t2<< endl;




	
	for (int k = 1; k <= 10; k++)
	{
		ui = 2;
		if (k < 50)
			ui = 10;

		for (int i = 1; i <= 10000; i++)
		{
			
			inputdata = input[i];
			inputlabel = Qlabel[i];
			net_set(result, inputdata, inputlabel);

			if (((*result).value * 10 - inputlabel) <= 0.01 && ((*result).value * 10 - inputlabel) >= -0.01)
			{
			}
			else
			{
				back_net(result, inputdata, inputlabel);
			
				net_set(result, inputdata, inputlabel);
				//cout << ((*result).value * 10) << endl;
			}
		}
	}

	//  迭代1000次，1000张输入数据，同时测试；
	
	ui = 1;

		double c = 0,t7=0;
		for (int i = 1; i <= 5000; i++)
		{

			inputdata = input[i];
			inputlabel = Qlabel[i];	
			
			if ((*result).value * 10 - inputlabel <= 0.5 && (*result).value * 10 - inputlabel >= -0.5)
			{

				cout << " right     " << "==      " << i  << "    loss=    " << (*result).value * 10 << endl;
				c++;
			
			}
			else
			{
					//	back_net(result, inputdata, inputlabel);
					//	net_set(result, inputdata, inputlabel);
					//	cout << "    wrong=           " << i << "  chance=   " << k << "    loss=    " << (*result).value * 10 << endl;
			}
			
		}
		
			cout << c <<"  /  "<<5000<<endl;
		layer_num++;

		system("pause");
		return 0;

	}
	//偏移迭代测试
