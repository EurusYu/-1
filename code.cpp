#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct
{
	int c_custkey;    	   //顾客编号
	char c_mkgsegment[20]; //市场部门
}customer;

typedef struct
{
	int o_orderkey;    	 //订单号 
	int o_custkey;    	 //顾客编号
	char o_orderdate[10];//订货日期 
}orders;

typedef struct
{
	int l_orderkey;//订单号
	double l_extendedprice;//额外价格
	char l_shipdate[10];//发货日期 
}lineitem;

typedef struct
{
	int l_orderkey;//订单号
	char o_orderdate[10];//订货日期 
	double l_extendedprice;//额外价格
}select_result;


customer * read_customer_txt()
{
	FILE * fp;
	customer *a = NULL;
	a = (customer *)malloc(100 * sizeof(customer));
	int i = 0;
	char b;
	fp = fopen("C:\\Users\\Administrator\\Desktop\\customer.txt", "r");
	if (NULL == fp)
	{
		printf("cannot open customer.txt!");
		return NULL;
	}
	while (!feof(fp))
	{
		//printf("%d  ",i);
		fscanf(fp, "%d%c%s", &a[i].c_custkey, &b, &a[i].c_mkgsegment);
		//printf("%d%c%s\n",a[i].c_custkey,b,a[i].c_mkgsegment);
		i++;
	}
	fclose(fp);
	return a;
}
orders * read_orders_txt()//读取orders.txt内容 
{
	int i = 0;
	orders * a = NULL;
	a = (orders *)malloc(4000 * sizeof(orders));
	char b, c;
	long long d;
	FILE *fp;
	fp = fopen("C:\\Users\\Administrator\\Desktop\\orders.txt", "r");
	if (fp == NULL)
	{
		printf("cannot open orders.txt!");
		return NULL;
	}
	while (!feof(fp))
	{
		//printf("%d!",i);
		fscanf(fp, "%d%c%lld%c%s", &a[i].o_orderkey, &b, &d, &c, &a[i].o_orderdate);
		a[i].o_custkey = d % 100;
		//printf("%d	%c	%lld	%c	%s\n",a[i].o_orderkey,b,a[i].o_custkey,c,a[i].o_orderdate);
		i++;
	}
	fclose(fp);
	return a;
}

lineitem * read_lineitem_txt()//读取lineitem.txt内容
{
	FILE * fp;
	lineitem * l = NULL;
	l = (lineitem *)malloc(10000 * sizeof(lineitem));
	int i = 0;
	char b, c;
	fp = fopen("C:C:\\Users\\Administrator\\Desktop\\lineitem.txt", "r");
	if (fp == NULL)
	{
		printf("cannot open lineitem.txt!");
		return NULL;
	}
	while (!feof(fp))
	{
		//printf("%d!",i);
		fscanf(fp, "%d%c%lf%c%s", &l[i].l_orderkey, &c, &l[i].l_extendedprice, &b, &l[i].l_shipdate);
		//printf("%d,%lf,%s\n",l[i].l_orderkey,l[i].l_extendedprice,l[i].l_shipdate);
		i++;
	}
	fclose(fp);
	return l;
}

select_result * select(customer * cus, orders * ord, lineitem * item, char * order_date, char * ship_date)
{
	int i, j, k, l = 0, m = 0;
	select_result * result1 = NULL;
	select_result * result2 = NULL;
	select_result  temp;
	result1 = (select_result *)malloc(1050 * sizeof(select_result));
	result2 = (select_result *)malloc(1050 * sizeof(select_result));
	for (i = 0; i < 150; i++)
	{
		for (j = 0; j < 4000; j++)
		{
			for (k = 0; k < 1050; k++)
				if (cus[i].c_custkey == ord[j].o_custkey&&ord[j].o_orderkey == item[k].l_orderkey && (strcmp(ord[j].o_orderdate, order_date) < 0) && (strcmp(item[k].l_shipdate, ship_date) > 0))
				{
					//printf("%d,%s,%lf\n",item[k].l_orderkey,ord[j].o_orderdate,item[k].l_extendedprice);
					result1[l].l_orderkey = item[k].l_orderkey;
					strcpy(result1[l].o_orderdate, ord[j].o_orderdate);
					result1[l].l_extendedprice = item[k].l_extendedprice;
					l++;
				}
		}
	}
	/*printf("求和\n\n\n");*/
	for (i = 0; i < l; i++)
	{
		//printf("%d\n",i);
		if (i == 0)
		{
			result2[m].l_orderkey = result1[i].l_orderkey;
			strcpy(result2[m].o_orderdate, result1[i].o_orderdate);
			result2[m].l_extendedprice = result1[i].l_extendedprice;
			continue;
		}
		if (result1[i].l_orderkey == result1[i - 1].l_orderkey)
		{
			result2[m].l_extendedprice = result2[m].l_extendedprice + result1[i].l_extendedprice;

		}
		else
		{

			m++;
			result2[m].l_orderkey = result1[i].l_orderkey;
			strcpy(result2[m].o_orderdate, result1[i].o_orderdate);
			result2[m].l_extendedprice = result1[i].l_extendedprice;

		}
	}
	for (i = 0; i < m - 1; i++)//冒泡排序 
	{
		for (j = 0; j < m - 1 - i; j++)
		{
			//printf("%lf->%lf\n",result2[j].l_extendedprice,result2[j+1].l_extendedprice);
			if (result2[j].l_extendedprice < result2[j + 1].l_extendedprice)
			{
				temp.l_extendedprice = result2[j].l_extendedprice;
				temp.l_orderkey = result2[j].l_orderkey;
				strcpy(temp.o_orderdate, result2[j].o_orderdate);
				result2[j].l_extendedprice = result2[j + 1].l_extendedprice;
				result2[j].l_orderkey = result2[j + 1].l_orderkey;
				strcpy(result2[j].o_orderdate, result2[j + 1].o_orderdate);
				result2[j + 1].l_extendedprice = temp.l_extendedprice;
				result2[j + 1].l_orderkey = temp.l_orderkey;
				strcpy(result2[j + 1].o_orderdate, temp.o_orderdate);
			}
		}
	}
	return result2;
}

int main()
{
	int i, l;
	customer * cus = NULL;
	orders * ord = NULL;
	lineitem * item = NULL;
	select_result *result = NULL;
	cus = read_customer_txt();
	ord = read_orders_txt();
	item = read_lineitem_txt();
	printf("Input Limit:");
	scanf("%d", &l);
	char order_date[16];
	char ship_date[16];
	printf("Input Order Date:");
	scanf("%s", order_date);
	printf("Input Ship Date:");
	scanf("%s", ship_date);
	result = select(cus, ord, item, order_date, ship_date);
	printf("l_orderkey|o_orderdate|revenue\n");
	for (i = 0; i < l; i++)
	{
		if (result[i].l_orderkey < 0)
			printf("null      |null       |null   \n");
		else
			printf("%-10d|%-11s|%-20.2lf\n", result[i].l_orderkey, result[i].o_orderdate, result[i].l_extendedprice);
	}
	return 0;
}

