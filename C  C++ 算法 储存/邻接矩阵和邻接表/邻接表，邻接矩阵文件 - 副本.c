#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int i, j, *v;
FILE *fp;

typedef struct s
{
	char data;
	int sign; //���ÿ�������λ��
	struct s *next;
}s;

typedef struct 
{
	s *front;
	s *rear;
}queue;


typedef struct node
{
	char data;

}node;

typedef struct 
{
	node *vex;
	int **arcs;
	int vexnum;//������Ŀ
	int arcnum; //����Ŀ
}Adjmatrix;



typedef struct arcnode
{
	int adjvex;
	struct arcnode *next;
}arcnode;

typedef struct vertexnode
{
	char data;
	arcnode* head;
}vertnode;

typedef struct 
{
	vertnode *vertex;
	int vexnum;
	int arcnum;
}adlist;






queue *initqueue();
void inqueue(queue* H,  char ch, int sign);
int outqueue(queue *H);

Adjmatrix *creat1(int count[]);
void output1(Adjmatrix *A);
void traverse1(Adjmatrix *A);
void DFS1(Adjmatrix *A, int w);//��һ�ε���w==1
int adjvex(Adjmatrix *A, int w, int g);//������ڽӵ�
void traverse2(Adjmatrix *A);//�����������
void  BFS1(Adjmatrix *A, int w);

adlist *creat2(int count[]);
void output2(adlist *B);
void traverse3(adlist *B);
void DFS2(adlist *B, int w);//��һ�ε���w==1

void traverse4(adlist *B);
void  BFS2(adlist *B, int w);

queue *initqueue()
{
	queue *H=( queue *)malloc( sizeof(queue) );
	s* p=( s* )malloc( sizeof(s) );
	p->next=NULL;
	H->front=H->rear=p;
	return H;
}


void inqueue(queue* H,  char ch, int sign)
{
	s *p=(s*)malloc( sizeof(s) );
	p->data=ch;
	p->sign=sign;

	p->next = H->rear->next;
	H->rear->next=p;
	H->rear=p;
}

int outqueue(queue *H)
{
	s *p;
	int sign;
	if(H->front->next == NULL)
	{
		printf("\n�ӿ�\n");
		return 0;
	}

	p=H->front->next;
	H->front->next=p->next;
	sign=p->sign;

	free(p);
	if(H->front->next == NULL) //ɾ�����һ���ڵ�󣬻��q->rearָ��Ŀռ��ͷ�
		H->rear=H->front;
	return sign;
}


int *read_file()//�����ļ��еĶ������ͱ���
{
	static int count[2];
	if( (fp=fopen("b.txt","r+") )==NULL)
	{
		printf("\nCannot open file strike any key exit!\n");
		exit(0);
	}

     fscanf(fp, "%d", &count[0]);
	 fscanf(fp, "%d", &count[1]);

	 v=(int *)malloc( (count[0]+1)*sizeof(int) );//��int *v����ռ�
	 return count;	 
}


Adjmatrix *creat1(int count[])//�����ڽӾ���
{
	char ch;
	int n, a, b;
	Adjmatrix *A=(Adjmatrix *)malloc( sizeof(Adjmatrix) );	
	 A->vexnum=count[0]; 

	 printf("����ͼ�Ķ�����: %d\n",  A->vexnum);
	 A->vex=(node *)malloc( (count[0]+1)*sizeof(node) );
	 
	 printf("\n����ͼ�Ķ���\n");

	 for(i=0; i<=A->vexnum; i++)
	 {
		 fscanf(fp, "%c", &ch);
		 if( i!=0 ) //�����ļ��еĻ��з�
		 {
			 printf("%c ", ch);
			 A->vex[i].data=ch;
		 }
	 }

	 A->arcnum=count[1];	 
	 printf("\n\n����ͼ�ı���: %d\n", A->arcnum);

	 A->arcs=(int **)malloc( (count[1]+1)*sizeof(int*) );

	 for(i=1; i<=A->arcnum; i++)
	 {	
		 A->arcs[i]=(int *)malloc( (count[1]+1)*sizeof(int) );
	 }

	 for(i=1; i<=A->arcnum; i++)
	 {
		 fscanf(fp, "%d", &n);
		 a=n/10;
		 b=n%10;
		 A->arcs[a][b]=1;
		 A->arcs[b][a]=1;
	 }
    fclose(fp);
	return A;
}



void output1(Adjmatrix *A)
{	
	printf("\n\n");
	for(i=1; i<=A->vexnum; i++)
		for(j=1; j<=A->vexnum; j++)
		{
			if(A->arcs[i][j] == 1)
			{
				printf("%c---%c   ", A->vex[i].data, A->vex[j].data);
			}
		}
		printf("\n\n");
}




//�����������
void traverse1(Adjmatrix *A)
{
	int k;
	printf("\n�ڽӾ���������������\n\n");
	for(k=1; k<=A->vexnum; k++)
	{
		v[k]=0;
	}
	for(k=1; k<=A->vexnum; k++)
	{
		if( !v[k] )
		{	
			DFS1(A, k);
		}
	}
}

void DFS1(Adjmatrix *A, int w)//��һ�ε���w==1
{
	int g;

	printf("%-3c", A->vex[w].data);
	v[w]=1;
	g=adjvex(A, w, 1);//��һ�β��Ҷ���w���ڽӵ�

	while( g != -1)
	{
		if( !v[g] )
		DFS1(A, g);

		g=adjvex(A, w, g+1);//����w����һ���ڽӵ�,����w����һ���ڽӵ㿪ʼ����
	}
}

int adjvex(Adjmatrix *A, int w, int g)//�����                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            �ڽӵ�
{
	for(i=g; i<=A->vexnum; i++)//����w����һ���ڽӵ㿪ʼ����
	{
		if(A->arcs[w][i] == 1)
			return i;//�ҵ��ڽӵ�ͷ���
	}
	return -1;
}

//�����������
void traverse2(Adjmatrix *A)
{
	int k;
	printf("\n\n�ڽӾ���Ĺ����������\n\n");
	
	for(k=1; k<=A->vexnum; k++)
	{
		v[k]=0;
	}

	for(k=1; k<=A->vexnum; k++)
	{
		if( !v[k] )
		{	
			BFS1(A, k);
		}
	}
	putchar('\n');
}

void  BFS1(Adjmatrix *A, int w)
{	
	int g;
	queue *Q=NULL;//��ʼ������Ȼ����local variable 'Q' used without having been initialized
	printf("%-3c", A->vex[w].data);
	v[w]=1;
	Q=initqueue(Q);

    inqueue(Q, A->vex[w].data, w);

	while( Q->front->next )
	{
		w = outqueue(Q);
	    g=adjvex(A, w, 1);	
		while( g!= -1)
		{
			if( !v[g] )
			{	
				printf("%-3c", A->vex[g].data);
				v[g]=1;
				inqueue(Q, A->vex[g].data, g);	
				
			} 
			g=adjvex(A, w, g+1);	
		}
	}

}
				

adlist *creat2(int count[])
{
	char ch;
	int n, a, b;
	arcnode *p, *q;
	adlist *B=(adlist *)malloc( sizeof(adlist) );

	B->vexnum=count[0];
	printf("����ͼ�Ķ�����: %d\n", B->vexnum);

	B->vertex=(vertnode *)malloc( (B->vexnum+1)*sizeof(vertnode) );

	printf("\n����ͼ�Ķ���\n");
	for(i=0; i<=B->vexnum; i++)
	{
		fscanf(fp, "%c", &ch);
		if( i!=0 )
		{
			printf("%c ", ch);
			B->vertex[i].data=ch;
	     	B->vertex[i].head=(arcnode *)malloc( sizeof(arcnode) );
			B->vertex[i].head->next=NULL;
		}
	}
	

	B->arcnum=count[1];
	printf("\n\n����ͼ�ı���: %d", B->arcnum);
	
	for(j=1; j<=B->arcnum; j++)
	{
			fscanf(fp, "%d", &n);
			a=n/10;
			b=n%10;

	     	p=B->vertex[a].head;
			while( p->next )
				p=p->next;	
			
			q=(arcnode *)malloc( sizeof(arcnode) );	

			q->adjvex=b;
			q->next=p->next;
			p->next=q;

         	p=B->vertex[b].head;
			while( p->next )
				p=p->next;	
			
			q=(arcnode *)malloc( sizeof(arcnode) );	
			q->adjvex=a;
			q->next=p->next;
			p->next=q;

		}	
	fclose(fp);
	return B;
}


void output2(adlist *B)
{	
	arcnode *p;
	puts("\n\n");

	for(i=1; i<=B->vexnum; i++)
	{ 
		p=B->vertex[i].head->next;
		while( p )
		{
			printf("%c---%c   ", B->vertex[i].data, B->vertex[p->adjvex].data);
			p=p->next;
		}
	}
	puts("\n\n");
}






//�����������
void traverse3(adlist *B)
{	
	int k;
	printf("\n�ڽӱ�������������\n\n");
	for(k=1; k<=B->vexnum; k++)
	{
		v[k]=0;
	}

	for(k=1; k<=B->vexnum; k++)
	{
		if( !v[k] )
		{	
			DFS2(B, k);
		}
	}
}

void DFS2(adlist *B, int w)//��һ�ε���w==1
{
	arcnode *p;

	printf("%-3c", B->vertex[w].data);
	v[w]=1;

	p=B->vertex[w].head->next;

	while( p )
	{
		if( !v[p->adjvex] )
		DFS2(B, p->adjvex);

		p=p->next;
	
	}

}



//�����������
void traverse4(adlist *B)
{
	int k;
	printf("\n\n�ڽӱ�Ĺ����������\n\n");
	for(k=1; k<=B->vexnum; k++)
	{
		v[k]=0;
	}
	for(k=1; k<=B->vexnum; k++)
	{
		if( !v[k] )
		{	
			BFS2(B, k);
		}
	}
}

void  BFS2(adlist *B, int w)
{
	queue *Q=NULL;
	arcnode *p;

	printf("%-3c", B->vertex[w].data);
	v[w]=1;

	Q=initqueue(Q);
    inqueue(Q, B->vertex[w].data, w);
	while( Q->front->next )
	{	
		w=outqueue(Q);
	    p=B->vertex[w].head->next;

		while(p)
		{
			if( !v[p->adjvex] )
			{	
				printf("%-3c", B->vertex[p->adjvex].data);

				v[p->adjvex]=1;

				inqueue(Q, B->vertex[p->adjvex].data, p->adjvex);
			}
			p=p->next;
		}
	}
}




void main()
{

    Adjmatrix *A;
	adlist *B;
	int n;
	int *count;


loop:	printf("\n\n\n\t\t\t1.�ڽӾ��󴴽�����ͼ");
	printf("\n\n\t\t\t2.�ڽӱ�������ͼ");
	printf("\n\n\t\t\t��ѡ��1��2: ");
	scanf("%d", &n);

	system("cls");
	switch(n)
	{
	case 1:	
		count=read_file();
		A=creat1(count);//�����ڽӾ���
        output1(A);
	    traverse1(A);
	    traverse2(A);
		
		getch();
		system("cls");
		goto loop;
		break;
	case 2:		
		
		count=read_file();
		B=creat2(count);
        output2(B);
	    traverse3(B);
		traverse4(B);
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

