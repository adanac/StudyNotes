 #include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
	int weight;
	int parent, Lchild, Rchild;
}HTree;


//�����ַ�����Ȩ��
typedef struct
{
	char character;
	int weight;
}bit;

typedef struct
{
	bit ascii[256];//һ���ֽ�256����ϣ������ͣ���0��ʼ��
	int num;
}ASCII;


//����ѹ���ļ���Ϣ
typedef struct
{
	unsigned char free;
	int size;
}INFO;


void cht();//create huffman tree
void chc();//create huffman code
void thc();//translate huffman code
void complie();
void select();
void weight();
void readfile();
void savefile();
void savebin();
void readbin();
void chartobin();
void bintochar();


int main()
{
	int i;
	int n;//n = charlist.num;
	int w[256] = {0};//Ȩ�أ���ʼ��Ϊ0
	char str[1000];//������ַ�
	char str2[1000];//���ʱ���ַ�
	char zip[1000];//�������Ҫѹ���ı���

	char zip2[1000];//�����ѹ���ļ������ı���

	unsigned char bin[200] = {0};//���ڱ���ѹ����Ķ������ļ�

	unsigned char bin2[200] = {0};//����Ӷ������ļ������ı���
	char **hc;//char **hc; ���hc = (char **)malloc(sizeof(char*)*(n+1));��ͬ��char *hc[n+1];
	HTree ht[512];
	ASCII charlist;
	INFO info, info2;//һ���Ƕ��룬һ���Ƕ���


	zip[0] = '\0';//һ��Ҫ��ʼ������˵�ˣ�ȫ���ᡭ��
	charlist.num = 0;//��ʼ�����ַ�������
	//��ʼ����Ȩ������
	for(i=0; i<=255; i++)
		charlist.ascii[i].weight = 0;
	

	printf("���ļ�\n");
	
	readfile(str);

	printf("������ַ���:\n%s\n", str);

	weight(&charlist, str);//��Ȩ��
	
	n = charlist.num;//����ĺ������õ���n��͵�������ˣ�

	hc = (char **)malloc(sizeof(char*)*(n+1));//�����typedef char *HCode[n+1];һ����n+1��charָ�빹�ɵ�����

	//Ϊ�˴����ô���ĸĶ�Сһ�㣬��Ȩ�ظ��Ƴ���
	for(i=0; i<=charlist.num; i++)
		w[i] = charlist.ascii[i].weight;


	cht(ht, w, n);
	printf("\n####������������####\n");

	chc(ht, hc ,n);
	printf("\n####��������������####\n");

	complie(hc, &str, &zip, &charlist);
	printf("\n####���ַ����б���####\n");

//	printf("zip����: %d\n", strlen(zip));

	chartobin(zip, bin, &info);
	printf("\n####ת��Ϊѹ���ļ�####\n");

	savebin(bin, &info);
	printf("\n####����ѹ���ļ�####\n");

	readbin(bin2, &info2);
	printf("\n####��ȡѹ���ļ�####\n");

	bintochar(bin2, zip2, &info2);
	printf("\n####��ԭѹ���ļ�####\n");
	
	thc(ht, str2, &zip2, n, &charlist);
	printf("\n####�������####\n");

	printf("��ԭ���ַ���:\n%s\n", str2);

	savefile(str2);
	printf("\n####�����ļ�####\n");

//	printf("%s\n", zip);

/*	for(i=0; i<n; i++)
	{
		printf("�ַ�:%c Ȩ��:%d ����:%s\n", charlist.ascii[i].character, charlist.ascii[i].weight, hc[i+1]);
	}*/

//	printf("%d",hc[1]);
	return 0;
}


//��Ȩ�أ�
//char *str,������ַ���
void weight(ASCII *p, char *str)
{
	int i, j;
	int sign;
	for(i=0; str[i] != '\0'; i++)//ɨ���ַ�����Ч�ʵ�
	{
		for(j=0; j <= p->num; j++)
		{
			if(p->ascii[j].character != str[i])//�����µı��һ��
				sign = 0;
			else//���ظ��ľ�����
			{
				sign = 1;
				break;
			}
		}

		if(sign == 0)
		{
			p->ascii[p->num].character = str[i];//�����ַ�
			sign = 0;
			p->ascii[p->num].weight++;//Ȩ��++
			p->num++;//�ַ��鳤��++
		}
		else
		{
			p->ascii[j].weight++;//Ȩ��++
			sign = 0;
		}
	}
}


/*
//min1Ϊ��С��min2Ϊ��С�����˳�����������в�ͬ��
//���ϵ�select��˳�����ģ����ܳ���min2Ϊ��С��min1Ϊ��С�����
//����������ش�bug�����������������
void select(HTree *ht, int p, int* min1, int* min2)
{
	int max = 2147483647;//�����int�����ֵ
	int i;
	i = 1;
	*min1=1;
	*min2=1;

	//����ѭ�����Ӵ���С��
	//����С
	for(i=1; i<=p; i++)
	{
		//if(ht[i].parent == 0 && ht[i].weight <= max)//ע��<=��<������
		if(ht[i].parent == 0 && ht[i].weight < max)
		{
			max = ht[i].weight;//�ҵ���Сֵ
			*min1 = i;//�±�ҲҪ��
		}
	}
	printf("��ţ�%d Ȩ�أ�%d\n", *min1, ht[*min1].weight);


	//�Ҵ�С
	max = 2147483647;//�����int�����ֵ
	for(i=1; i<=p; i++)
	{
	//	if(ht[i].parent == 0 && ht[i].weight <= max && ht[i].weight != ht[*min1].weight)
	//	if(ht[i].parent == 0 && ht[i].weight < max && ht[i].weight != ht[*min1].weight)
	//	if(i == *min1 && ht[i].weight != ht[*min1].weight)
		if(i == *min1)
			i++;
		if(ht[i].parent == 0 && ht[i].weight < max)
		{
			max = ht[i].weight;//�ҵ���Сֵ
			*min2 = i;//�±�ҲҪ��
		}
	}
	printf("��ţ�%d Ȩ�أ�%d\n\n", *min2, ht[*min2].weight);
}*/


void select(HTree *ht, int p, int* min1, int* min2)
{
	int max = 2147483647;//�����int�����ֵ
	int m1, m2;
	int i;

	m1 = max;
	m2 = max;
	
	i = 1;
	*min1=1;//��������Ҫ���ص��±�
	*min2=1;

	//һ��ɨ�輴���ҳ���С��Сֵ
	for(i=1; i<=p; i++)
	{
		if(ht[i].parent == 0 && ht[i].weight < m1)
		{
			*min2 = *min1;
			m2 = m1;
			*min1 = i;
			m1 = ht[i].weight;
		}
		else if(ht[i].weight < m2 && ht[i].parent == 0)
		{
			*min2 = i;
			m2 = ht[i].weight;
		}
	}

//	printf("��ţ�%d Ȩ�أ�%d\n", *min1, ht[*min1].weight);
//	printf("��ţ�%d Ȩ�أ�%d\n\n", *min2, ht[*min2].weight);
}



void cht(HTree *ht, int *w, int n)
{
	int i, m;
	int s1, s2;
	m = 2*n-1;

	//��ʼ��
	for(i=1; i<=n; i++)
	{
		ht[i].weight = w[i-1];//Ȩ���Ǵ�0�±꿪ʼ��
		ht[i].parent = 0;
		ht[i].Lchild = 0;
		ht[i].Rchild = 0;
	}
	for(i=n+1; i<=m; i++)
	{
		ht[i].weight = w[i-1];
		ht[i].parent = 0;
		ht[i].Lchild = 0;
		ht[i].Rchild = 0;
	}

	for(i=n+1; i<=m; i++)
	{
		select(ht, i-1, &s1, &s2);
		ht[i].weight = ht[s1].weight + ht[s2].weight;
		ht[i].Lchild = s1;
		ht[i].Rchild = s2;
		ht[s1].parent = i;
		ht[s2].parent = i;
	}
/*
	for(i=1; i<=m; i++)
	{
		printf("���:%d ",i);
		printf("Ȩ��:%d ",ht[i].weight);
		printf("˫��:%d ",ht[i].parent);
		printf("��:%d ",ht[i].Lchild);
		printf("�Һ�:%d\n",ht[i].Rchild);
	}*/
}


void chc(HTree *ht, char** hc, int n)//С��**
{
	char *cd;
	int start;
	int i, c, p;
	cd = (char *)malloc(sizeof(char)*n);
	cd[n-1] = '\0';
	for(i=1; i<=n; i++)
	{
		start = n-1;
		c = i;
		p = ht[i].parent;
		while(p != 0)
		{
			--start;
			if(ht[p].Lchild == c)
				cd[start] = '0';
			else
				cd[start] = '1';
			c = p;
			p = ht[p].parent;
		}
		hc[i] = (char *)malloc((n - start) * sizeof(char));

		strcpy(hc[i], &cd[start]);//��cd���Ƶ�hc��������˳��Ū���ˣ�������
	//	printf("## %s ##\n", hc[i]);
	}
//	for(i=1; i<=n; i++)
//		printf("## %s ##\n", hc[i]);
	free(cd);
}

//����
//zip�������ļ�����������ַ�����
void thc(HTree *ht, char* str, char* zip, int n, ASCII *c)
{
	int i, p, x;
	i = 0;//���ַ����ͷ��ʼ����
	p = 2*n-1;//׼����˫�׽�㿪ʼ��
	x = 0;

	while(zip[i] != '\0')
	{
		//��0Ϊ��
		if(zip[i] == '0')
		{
			p = ht[p].Lchild;
			if(ht[p].Lchild == 0 || ht[p].Rchild == 0)//����Ҷ�ӽ���������Ȼ���ͷ����
			{
				str[x] = c->ascii[p-1].character;//���������Ǵ�1��ʼ���ҵ��ַ����Ǵ�0��ʼ������Ҫ-1
				p = 2*n-1;//��ͷ����
				x++;
			}
		}

		//��1Ϊ��
		else if(zip[i] == '1')
		{
			p = ht[p].Rchild;
			if(ht[p].Lchild == 0 || ht[p].Rchild == 0)//����Ҷ�ӽ���������Ȼ���ͷ����
			{
				str[x] = c->ascii[p-1].character;//���������Ǵ�1��ʼ���ҵ��ַ����Ǵ�0��ʼ������Ҫ-1
				p = 2*n-1;//��ͷ����
				x++;
			}
		}
		i++;
	}
	str[x] = '\0';//�ַ���������������

	//printf("%s",str);
	//printf("\n");
}


void complie(char** hc, char* str, char* zip, ASCII* p)
{
	int i=0, j, len;
	len = strlen(str);
	//printf("$$ %d $$", len);
	//while(str[i] != '\0')
	while(i != len)
	{
		for(j=0; j<=p->num; j++)
		{
			if(str[i] == p->ascii[j].character)
			{
				strcat(zip, hc[j+1]);//��hc������zip���棬�ҵ��ַ��Ǵ�0��ʼ�ģ������������Ǵ�1��ʼ�ģ�����Ҫ��1�������Ǹ�ǿ������ת����ע�⣡��
				break;//�ҵ�����˳��������һ��Ч��
			}
		}
		i++;
	}
}

void readfile(char* str)
{
	FILE *fp;
	int i;
	i=0;
	
	if((fp = fopen("text.txt","rb")) == NULL)
	{
		printf("�ļ�������\n");
		return;
	}

	while(!feof(fp))//�ļ�û������һֱ��
	{
		str[i] = fgetc(fp);//��һ���ַ���fpָ���Զ�����
		if(feof(fp))//����һ���ַ�֮������ļ������������һ���ַ��ĳ�\0
		{
			str[i] = '\0';
		}
		i++;
	}

	fclose(fp);
}

void savebin(unsigned char* bin, INFO *p)
{
	FILE *fp;
	int i;
	i=0;
	
	if((fp = fopen("yasuo.bin","wb")) == NULL)
	{
		printf("�����ļ�ʧ��\n");
		return;
	}

	fwrite(&p->size,4,1,fp);//ǰ�ĸ��ֽڱ���ѹ���ļ�����p->size
	fwrite(&p->free,1,1,fp);//������ֽڱ����ļ����һ�ֽڲ�0�ĸ���

	for(i=0; i<p->size; i++)//�ӵ�6�ֽڿ�ʼ����ѹ���ļ�
	{
		fwrite(&bin[i],1,1,fp);
	}
	fclose(fp);
}


void chartobin(char* zip, unsigned char* bin, INFO *p)
{
	unsigned char tmp;
	int i, j;
	
	p->size = strlen(zip)/8;//�����ֽڵĳ���

//	printf("size: %d\n", p->size);

	for(j=0; j<p->size; j++)//�ȱ��������ֽ�
	{
		for(i=j*8; i<(j+1)*8; i++)//��Ƭ������ˣ�λ����С��˼
		{
			if(zip[i] == '0')
			{
				tmp = (tmp<<1)|0x00;
			}
			if(zip[i] == '1')
			{
				tmp = (tmp<<1)|0x01;
			}
		}

		bin[j] = tmp;//ÿ�չ�һ�ֽڣ��ͱ���
	}
	
	p->free = 8 - (strlen(zip)%8);//�ļ�β����ĸ���
	if(p->free == 8)//������
		p->free = 0;

//	printf("free: %d\n", p->free);

	if(p->free)//�������ȫ��һ�ֽ�
	{
		for(j=0; j<8 - (p->free); j++)//�ȱ���������������Ǽ�λ
		{
			if(zip[p->size * 8 + j] == '0')
			{
				tmp = (tmp<<1)|0x00;
			}
			if(zip[p->size * 8 + j] == '1')
			{
				tmp = (tmp<<1)|0x01;
			}
		}

		for(j=8 - (p->free); j<8; j++)//����λ��0
			//tmp = (tmp<<1)|0x00;
			tmp = (tmp<<1);
		bin[p->size] = tmp;//�����size��ʵ��size-1
		p->size++;//��������size++������ʵsize
	}

//	printf("free: %d\n", p->free);


/*	printf("\n\n��ͷϷ����\n\n");

	for(i=0; i<p->size; i++)
	{
		printf("%x ", bin[i]);
	}
*/
//	printf("\n\n���Ա�־1\n\n");
//	printf("size: %d\n", size);
}

void bintochar(unsigned char* bin, char* zip, INFO *p)
{
	unsigned char tmp, save;
	int n,j,i;
	n=0;

	for(j=0; j<p->size; j++)//��ʼ����
	{
		tmp = bin[j];//�ȸ���һ��

		for(i=0; i<8; i++)//λ���������Բ���Ƭ����CYλ�����Ծ���0x80�����������������ȡCYλ
		{
			save = tmp & 0x80;

			if(save == 0x00)
				zip[n] = '0';
			if(save == 0x80)//0x80 = 1000 0000
				zip[n] = '1';

			tmp = tmp<<1;
			n++;
		}
	}

	zip[p->size*8 - p->free] = '\0';//��ȥ���һ�ֽڶಹ��0
//	printf("strlen 2: %d\n", strlen(zip));
}

void readbin(unsigned char* bin, INFO *p)
{
	FILE *fp;
	int i;
	i=0;
	
	if((fp = fopen("yasuo.bin","rb")) == NULL)
	{
		printf("�����ļ�ʧ��\n");
		return;
	}

	fread(&p->size,4,1,fp);//ǰ�ĸ��ֽڱ���ѹ���ļ�����
	fread(&p->free,1,1,fp);//������ֽڱ����ļ����һ�ֽڲ�0�ĸ���

	for(i=0; i<p->size; i++)//�ӵ�6�ֽڿ�ʼ����ѹ���ļ�
	{
		fread(&bin[i],1,1,fp);
	}
	fclose(fp);
}

void savefile(char* str)
{
	FILE *fp;
	int i;
	i=0;
	
	if((fp = fopen("output.txt","wb")) == NULL)
	{
		printf("�ļ�������\n");
		return;
	}

	while(str[i] != '\0')//�ַ���û������һֱ��
	{
		fputc(str[i],fp);
		i++;
	}

	fclose(fp);
}