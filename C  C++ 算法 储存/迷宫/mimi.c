#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define N 1000

typedef struct 
{
	int weight;
	int parent, lchild, rchild;
}hafuman;

typedef struct 
{
	char *data; //�ַ�����  
	char **copy;//����
}bianma;


void display(); 
char* readfile(int count[]);
void calculate(int w[], bianma *bm, int count[], char *s);
void creat_hafuman(hafuman ht[], int w[], int n);
void select(hafuman ht[], int m, int *s1,  int *s2);
void output_character(bianma *bm, int n)//��ʾ��ͬ�ַ��ı���
void output_data(hafuman ht[], bianma *bm, int n);
void encoding(hafuman ht[], bianma *bm, int n);
void coding(hafuman ht[], bianma *bm, int n);
void output(bianma *bm, int n);
int i, j, k;

void display()
{
	printf("\n\n\n");
	printf("\t\t\t1.�������\n\n");
	printf("\t\t\t2.��������\n\n");
	printf("\t\t\t3.�˳�\n\n");
	printf("\t\t��ѡ��(1~~3):  ");
}

char* readfile(int count[])
{
	char *s;
	char ch;
	if( (fp=fopen("SouceFile.txt","r") )==NULL )
	{
		printf("\nCannot open file strike any key exit!\n");
		exit(0);
	}
	
	if( s=(char *)malloc( sizeof(char) ) == NULL )
	{
		  printf("\n����ռ�ʧ��\n");
	      exit(0);
	}	
	size=_msize(s);
	i=0;
	while(1)
	{
		fsanf(fp, "%c", &ch);
		if(ch=='#')
		{
			fclose(fp);
			break;
		}	
		s[i]=ch;
	    i++;
		count[0]++;
		s=(char *)realloc(s, size+sizeof(char) );
		size=_msize(s);
	}

	printf("\n\n\t\t\t���ļ���ȡ������\n\n");
	for(i=0; i<count[0]; i++)
		putchar(s[i]);
	puts("\n\n");
	return s;
}


int* calculate(int *w, bianma *bm, int count[], char *s)
{
	int a[127]={0};
	for(i=0; i<count[0]; i++)
	{
		a[ s[i] ]++;
	}
	
	for(i=0; i<127; i++)//ͳ�Ʋ��ظ����ַ�����
		if(a[i] != 0)
			count[1]++;

	bm->data=(char *)malloc( count[1]*sizeof(char) );
	w=(int *)malloc( count[1]*sizeof(int) );
	for(i=0, j=0; i<127 && j<count[1]; i++)
	{
		if( a[i]!=0 )
		{
			bm->data[j]=i;
			w[j] = a[i]; //��¼Ȩֵ
			j++;
		}
	}

	printf("\n\n\t\t\t��ͬ�ַ�����\n\n");
	for(i=0; i<count[1]; i++)
	{
		printf("%c", bm->data[i]);
	}
	return w;
}
	

void creat_hafuman(hafuman ht[], int w[], int n)
{
	int s1, s2;
	int t;
	for(t=1; t<=n; t++)
	{
		ht[t].weight=w[t-1];
		ht[t].parent=0;
		ht[t].lchild=0;
		ht[t].rchild=0;
	}

	for(t=n+1; t<=2*n-1; t++)
	{
		ht[t].weight=0;
		ht[t].parent=0;
		ht[t].lchild=0;
		ht[t].rchild=0;
	}
	

	for(t=n+1; t<=2*n-1; t++)
	{
		select(ht, t-1, &s1, &s2);//ǰi-1��ѡ˫��Ϊ0, Ȩֵ��С
		ht[t].weight=ht[s1].weight + ht[s2].weight;
		ht[t].lchild=s1, ht[t].rchild=s2;
		ht[s1].parent=t, ht[s2].parent=t;

	}
}

/*
void select(hafuman ht[], int m, int *s1,  int *s2)
{
	int min1, min2, a, b;
	i=1;
	while( ht[i].parent != 0)
	{
		i++;
	}
	min1=ht[i].weight; 
	a=i;

	for(j=i+1; j<=m; j++)
	{
		if(min1 > ht[j].weight && ht[j].parent==0)
		{
			min1=ht[j].weight;
			a=j;
		}

	}


	i=1;
	while( ht[i].parent != 0 || a==i )
	{
			i++;
	}
	
	min2=ht[i].weight;
	b=i;

	for(j=i+1; j<=m; j++)
	{
		if(j==a)
			continue;

		if(min2 > ht[j].weight && ht[j].parent==0)
		{
			min2=ht[j].weight;
			b=j;
		}
	}
	*s1=a; *s2=b;

}
*/

void select(hafuman ht[], int m, int *s1,  int *s2)
{
	int min1, min2;
	i=1;
	while( ht[i].parent != 0)
	{
		i++;
	}
	min1=ht[i].weight; 
	*s1=i;

	j=i+1;
	while(ht[j].parent != 0)
	{
		j++;
	}
	min2=ht[j].weight;
	*s2=j;

	for(i=*s1+1; i<m; i++)
	{
		if(ht[i].parent==0)
		{
			if(ht[i].weight < min1)
			{
				min2=min1;
				*s2=*s1;
				min1=ht[i].weight;
				*s1=i;
			}
			else
				if(ht[i].weight < min2)
				{
					min2=ht[i].weight;
					*s2=i;
				}
		}
	}
}


void output_data(hafuman ht[], bianma *bm, int n)//ÿ��Ҷ�ӽڵ����Ϣ
{
	printf("\n\n");
	for(i=0; i<n; i++)
	{
		printf("%-5d%-5cweight=%-5dparent=%-5dlchild=%-5drchild=%-5d\n", i+1, bm->data[i], ht[i+1].weight, ht[i+1].parent, ht[i+1].lchild, ht[i+1].rchild);
	}
}


void encoding(hafuman ht[], bianma *bm, int n)//���б���, *copy[]Ϊ���Ʊ���
{
	int start, c, p;
	char *ch;
	ch=(char *)malloc( n*sizeof(char) );
	ch[n-1]='\0';
	bm->copy=(char *)malloc( n*sizeof(char) );

	for(i=1; i<=n; i++)//n��Ҷ�ӽڵ�
	{
		start=n-1;
	    c=i, p=ht[i].parent; //pΪparent, cΪchild

		while(p!=0)
		{
			start--;
			if(ht[p].lchild==c)
				ch[start]='0';
			else
				ch[start]='1';

			c=p; p=ht[p].parent;	//printf("\n123\n");
		}

		bm->copy[i-1]=(char *)malloc( (n-start)*sizeof(char) );
        strcpy(bm->copy[i-1], &ch[start]);
		//printf("\n%s\n", bm->copy[i-1]);	
	}
	free(ch);
}

void output_character(bianma *bm, int count[])//��ʾ��ͬ�ַ��ı���
{
	puts("\n\n\t\t\t��ͬ�ַ��ı���������ʾ\n\n");
	printf("\n");
	for(i=0; i<count[1]; i++)
	{	
		printf("%c\t", bm->data[i]);
		printf("%s\n", bm->copy[i]);
	}
}


int output_article(bian *bm, char *s, int count[])//��ʾ���±���
{
	char *code;//���µı���
	for(i=0; i<count[0]; i++)
	{
		for(j=0; j<count[1]; j++)
		{
			if(s[i]==bm->data[j])
			{	
				length=strlen(bm->copy[j]);
				if(i==0)
				{
					code=(char *)malloc( (length+1)*sizeof(char) );
					strcpy(code, bm->copy[j]);
					size=_msize(code);
				}
				else
				{
					code=(char *)realloc( size+(length+1)*sizeof(char) );
					strcat(code, bm->copy[j]);
					size=_msize(code);
				}
			}
		}
	}

	if( fp=fopen("codefile.txt", "w") == NULL)
	{
			printf("\nCan not open\n");
			exit(0);
	}
	fprintf(fp, "%s", code);
	fclose(fp);	

    printf("\n\t\t\t���µı���Ϊ\n\n");
    puts(code);

	length=strlen(code)+1;
	return length;
}



void coding(hafuman ht[], bianma *bm, int count[], int length)//��������
{
	char code[length];
	int p;

	if( fp=fopen("codefile.txt", "r") == NULL )
	{
		printf("\nCan not open\n");
		exit(0);
	}
	fscanf(fp, "%s", code);
	fclose(fp);

	printf("\n\t\t\t��������\n\n");

	p=2*n-1;
	for(i=0; code[i] != '\0'; i++)
	{	
		
		if(code[i]=='0')
			p=ht[p].lchild;

		else
			if(code[i]=='1')
			p=ht[p].rchild;	
			
		if(ht[p].lchild == 0 && ht[p].rchild == 0)
		{ 
				printf("%c", bm->data[p-1]);//p: 1~~2*n-1, bm->data[0~~n-1]
				p=2*n-1;
				continue;
		}

	}
	puts("\n\n");

}

void show(bianma *bm, char s[],  hanfuman ht[], int w[], int count[])
{	
	int m;
loop:	display();
	scanf("%d", &m);
	switch(m)
	{
	case 1:    
	    output_character(bm, count)//��ʾ��ͬ�ַ��ı���
	    length=output_article(bm, s, count)//��ʾ���±���.���ر��볤��
		printf("\n\n�밴���������");
		getch();
		system("cls");
		goto loop;
		break;
	case 2:
		output_character(bm, count)//��ʾ��ͬ�ַ��ı���
		coding(ht, bm, length, count);//����
		printf("\n\n�밴���������");
		getch();
		system("cls");
		goto loop;
		break;
	case 3:
		break;
	default:
		system("cls");  
		goto loop;
	}
}

void main()
{

	bianma *bm;	
	hafuman *ht;//����������Ϣ
	char *s;//��ȡ�ļ��������ַ�
	int *w;//��¼��ͬ�ַ���Ȩֵ
	int count[2]={0};//count[0]��¼�ַ�������count[1]��¼���ظ��ַ�����
	bm=(bianma *)malloc( sizeof(bianma) );

	s=readfile(count);
	w=calculate(w, bm, count, s);

	ht=(hanfuman *)malloc( (count[1]+1)*sizeof(hanfuman) );
    creat_hafuman(ht, w, count[1]); 
	output_data(ht, bm, count[1]);//ÿ��Ҷ�ӽڵ����Ϣ
	encoding(ht, bm, count[1]);//��ÿ���ַ�����

	getch();
    system("cls");
	show(bm, s, ht, w, count);

}





 



