#include <stdio.h>
#include <stdlib.h>

struct node{
	int number;
	int position;        
	struct node* upnode;
};
struct node* start;
struct node* queue[100];
struct node* list1[100];
int n,Count=0,Front=0,Rear=-1,list2[100][2],N=0;




int isEmpty(){
	if(Count)
		return 0;
	else
		return 1;
}

int enqueue(struct node* p){
		Rear=(Rear+1)%10;
		queue[Rear]=p;
		Count++;
		return 1;
}

struct node* dequeue(){
		struct node* temp=queue[Front];
		Front=(Front+1)%10;
		Count--;
		return temp;	
}


int function1(struct node* x,struct node* y,int n1,int n2){
	int dif=(x->position>=y->position)?(x->position-y->position):(y->position-x->position);         
	int i;
	for(i=0;i<dif;i++){                                                              
		if(x->position>y->position){
			x=x->upnode;
			if(x->number<n1 || x->number>n2)
				return 0;
		}
		if(x->position<y->position){                                                       
			y=y->upnode;                                                            
			if(y->number<n1 || y->number>n2)
				return 0;
		}
	}
	if(x==y)
		return 1;
	while(1){
		x=x->upnode;
		y=y->upnode;
		if(x==y){    
			if(x->number<n1 || x->number>n2)
				return 0;
			else
				return 1;
		}
	}
}

int function2(int n1,int n2){
	int i,j;
	struct node* x,* y;
	for(i=n1;i<=n2;i++){    
		x=list1[i];
		for(j=i+1;j<=n2;j++){
			y=list1[j];
			if(!function1(x,y,n1,n2))
				return 0;		
		}		
	}
	return 1;
}

void function3(){
	int i,j,n1,n2;
	for(i=1;i<=n;i++){
		n1=i;
		for(j=i+1;j<=n;j++){
			n2=j;
			if(function2(n1,n2))
				N++;        
		}
	}
}

			



int main(){
	scanf("%d",&n);
	int i;
	for(i=1;i<=n;i++){
		struct node* p=(struct node*)malloc(sizeof(struct node));
		p->number=i;
		p->position=-1;
		p->upnode=NULL;
		list1[i]=p;
	}
	for(i=0;i<n-1;i++){
		scanf("%d %d",&list2[i][0],&list2[i][1]);
		struct node* x = list1[list2[i][0]];
		struct node* y = list1[list2[i][1]];
		if(i==0){
			y->upnode=x;
			start=x;
			x->position=0;
			y->position=1;
		}
		else{
			if(x==start || y==start){
				if(x==start){
					y->upnode=x;
					y->position=1;
				}
				else{
					x->upnode=y;
					x->position=1;
				}		
			}
			else if(x->upnode==NULL && y->upnode==NULL){
				enqueue(x);
				enqueue(y);
				continue;
			}
			else if(x->upnode==NULL){
				x->upnode=y;
				x->position=y->position+1;
			}
			else if(y->upnode==NULL){
				y->upnode=x;
				y->position=x->position+1;
			}
		}
		if(x->upnode)
			printf("x %d upnode %d position %d\n",x->number,x->upnode->number,x->position);
		if(y->upnode)
			printf("y %d upnode %d position %d\n",y->number,y->upnode->number,y->position);
		
	}
	while(!isEmpty()){
			struct node* x=dequeue();
			struct node* y=dequeue();
			printf("x %d y %d\n",x->number,y->number);
			if(x->upnode==NULL){
				x->upnode=y;
				x->position=y->position+1;
				printf("x %d upnode %d position %d\n",x->number,x->upnode->number,x->position);
			}
			else if(y->upnode==NULL){
				y->upnode=x;
				y->position=x->position+1;
				printf("y %d upnode %d position %d\n",y->number,y->upnode->number,y->position);
			}
	}
	N=n;
	function3();
	printf("\n%d",N);
	return 0;
}



