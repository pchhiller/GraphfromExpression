#include<iostream>
#include<stack>
#include <string.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include <math.h>
#include<graphics.h>
#include <algorithm>
#include <errno.h>
using namespace std;
int weight(char ch);
int unary(char ch);
void replacex(char exp[],float num);
float ineval(char infix[]);
int isvalid( char op[],int i);

void replacex(char exp[],float num){
char temp[200]="",number[20],temp1[20];
sprintf(number,"%lf",num);
if(num<0)
    {strcpy(temp1,"`");
    strcat(temp1,number);
    strcpy(number,temp1);
    }
int i=0;
	while(exp[i]!='\0'){
		if(exp[i]=='x')
            strcat(temp,number);
		else
		{temp[strlen(temp)]=exp[i];
		temp[strlen(temp)]='\0';}
		++i;

	}
	strcpy(exp,temp);
}
int isvalid(char op[],int i){
char exp[4];
exp[0]=op[i];
exp[1]=op[i+1];
exp[2]=op[i+2];
if(strcmp(exp,"sin")==0||strcmp(exp,"cos")==0||strcmp(exp,"tan")==0||strcmp(exp,"log")==0)
    return 1;
else
    return 0;
}
int unary(char ch){
	switch (ch){
		case 's':
    	case 'c':
    	case 'l':
    	case 't':return 1;
    	default:return 0;
	}
}
float compute(float a, float b, char ch)
{
	switch (ch) {
    	case '/':return b/a;
    	case '*': return a*b;
    	case '+':return a+b;
    	case '-':return b-a;
    	case '^':return pow(b,a);
    	}
    }
float computeu(float a,char ch)
{
	switch (ch) {
    	case 's':return sin(a);
    	case 'c': return cos(a);
    	case 't':return tan(a);
    	case 'l':return log(a);
    	}
}
int isoprtr(char ch) {
   switch (ch) {
    	case '/':
    	case '*':
    	case '+':
    	case '-':
        case '^':
    	case 's':
    	case 'c':
    	case 'l':
    	case 't': return 1;
    	default : return 0;
   }
}
int weight(char ch) {
   switch (ch) {
        case '^': return 4;
    	case '/':
    	case '*': return 3;
    	case '+':
    	case '-': return 2;
    	case 's':
    	case 'c':
    	case 'l':
    	case 't':return 5;
    	case '(':return 0;
    	default : return 0;
   }
}

float ineval(char infix[]) {
	stack <char> oprtr;
	stack <double> oprnd;
	char* end_ptr=infix;
	while(*end_ptr!='\0'){
		char b= *end_ptr;
		if (isoprtr(*end_ptr)){

			if(unary(oprtr.top())){
				float a=oprnd.top();
				oprnd.pop();
				char ch= oprtr.top();
				oprtr.pop();
				float c= computeu(a,ch);
				oprnd.push(c);
				//end_ptr;
				infix=end_ptr;
			}
			else if (oprtr.empty() || (!oprtr.empty() && (weight(*end_ptr)>weight(oprtr.top())))){
			oprtr.push(*end_ptr);
			end_ptr++;
			infix=end_ptr;}



			else if (weight(*end_ptr)<=weight(oprtr.top())){
			if(!unary(oprtr.top()))
			{float a= oprnd.top();
			oprnd.pop();
			float b= oprnd.top();
			oprnd.pop();
			char ch= oprtr.top();
			oprtr.pop();
			float c=compute(a,b,ch);
			oprnd.push(c);
			oprtr.push(*end_ptr);
			}
			else
			{float a= oprnd.top();
			oprnd.pop();
			char ch= oprtr.top();
			oprtr.pop();
			float c= computeu(a,ch);
			oprnd.push(c);}
			end_ptr++;
			infix=end_ptr;}
		}



		else if (*end_ptr=='(')
		{oprtr.push(*end_ptr);
			end_ptr++;
			infix=end_ptr;}
		else if (*end_ptr==')' ){

			while(oprtr.top()!='(')
			{
			if(!unary(oprtr.top()))
			{float a= oprnd.top();
			oprnd.pop();
			float b= oprnd.top();
			oprnd.pop();
			char ch= oprtr.top();
			oprtr.pop();
			float c=compute(a,b,ch);
			oprnd.push(c);
			}
			else
			{float a= oprnd.top();
			oprnd.pop();
			char ch= oprtr.top();
			oprtr.pop();
			float c= computeu(a,ch);
			oprnd.push(c);}


			}
		oprtr.pop();
		end_ptr++;
		infix=end_ptr;
		}


		else if(isdigit(*end_ptr)|| b=='`'){
			if(*end_ptr=='`')
            {end_ptr++;
            infix=end_ptr;}
			float k=strtod(infix,&end_ptr);
			oprnd.push(k);
			infix=end_ptr;
		}
		//cout<<infix<<" ";

	}
//	int len=oprnd.size();
//	for(int i=0;i<len;++i)
//	{cout<<oprnd.top()<<" ";
//	oprnd.pop();
//	}
//	len=oprtr.size();
//	for(int i=0;i<len;++i)
//	{cout<<oprtr.top()<<" ";
//	oprnd.pop();
//	}
	return oprnd.top();
}
double xaxis[100000],yaxis[100000],xaxis2[100000],yaxis2[100000];

int main()
{
    cout<<"Enter the function with proper brackets\n";
char input[200],to_send[200],temp[200];
gets(input);
char infix[200]={'('};
strcat(infix,input);
strcat(infix,")");
int i=0,j=0;
while(infix[i]!='\0'){
if(infix[i]==' '){
    ++i;
}else if(isvalid(infix,i)){
to_send[j]=infix[i];
i=i+3;
++j;}
else{
    to_send[j]=infix[i];
    ++i,++j;
}

}
to_send[j]='\0';
//cout<<to_send;
double k;
i=0;
char answer;
double start,stop,jump;
cout<<"Would you like to enter range manually? (y/n) ";
cin>>answer;
if(answer=='y'||answer=='Y'){
    cout<<"Enter starting and ending of graph \n";
    cin>>start>>stop;
    start=(double)start;
    stop=(double)(stop);
}
else{
        start=-10.0;
        stop=10.0;

}
answer='n';
cout<<"Would you like to enter jump manually? (y/n) ";
cin>>answer;
if(answer=='y'||answer=='Y'){
    cout<<"Enter the jump for graph \n";
    cin>>jump;
    jump=(double)jump;
}
else{
        jump=((stop-start))/((sizeof(xaxis)-1)/sizeof(*xaxis));


}
for(k=start;k<=stop+jump;k=k+jump,++i){
    xaxis[i]=k;
    xaxis2[i]=k;
    //cout<<xaxis[i]<<",";
}
double length=(((double)(stop-start))/(double)(jump)) +1;
cout<<endl<<endl;
//for(i=0;i<length;++i){
  i=0;
  cout<<"Y values \n";
  for(k=start;k<=stop+jump;k=k+jump,++i){

  strcpy(temp,to_send);
    replacex(temp,xaxis[i]);
    //cout<<temp;
    yaxis[i]=ineval(temp);
    //cout<<errno<<endl;
    if(errno==33||errno==34){
        yaxis[i]=0;
    }
   /* if(yaxis[i]>1000)
        yaxis[i]=1000;
    else if(yaxis[i]<-1000)
       yaxis[i]=-1000;
       */
    yaxis2[i]=yaxis[i];
    //cout<<yaxis[i]<<"\n";
}
double* ymax=max_element(yaxis,yaxis+(int)length);
double maxy=*ymax;
double* ymin=min_element(yaxis,yaxis+(int)length);
double miny=*ymin;
double diff1=fabs(miny);
double diff2=fabs(maxy);
double range= (diff1>diff2)?diff1:diff2;

cout<<range;
int gd = DETECT, gm;
initgraph(&gd, &gm, "");
double x1,y1;
x1=(0-(start))*((double)getmaxx()/(stop-start));
line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
line(x1,0,x1,getmaxy());
cout<<endl<<getmaxx();
cout<<endl<<getmaxy()/2;
for(i=0;i<length;++i)
    {if(xaxis[i]==0)
    cout<<"Zero element"<<xaxis[i];}

  for (i=0;i<length;++i)
  {
     xaxis[i]=((xaxis[i])-(start))*((double)getmaxx()/(stop-start));
     long double scale=yaxis[i]*(long double)(getmaxy()/2);
     //cout<<"scale1 "<<scale<<endl;
     scale=(long double)(scale/(long double)(range));
     //cout<<scale;

     yaxis[i] = (double)(getmaxy()/2) - scale;
     putpixel(xaxis[i],yaxis[i],4);
  }
//for(i=0;i<length;++i)
        //cout<<"("<<xaxis2[i]<<" , "<<xaxis[i]<<" , "<<yaxis2[i]<<" , "<<yaxis[i]<<")\n";
setcolor(RED);
for (i=0;i<length-2;++i){
        //cout<<"line at"<<xaxis[i]<<" "<<yaxis[i]<<" "<<xaxis[i+1]<<" "<<yaxis[i+1]<<endl;
        //cout<<"value of i is "<<i<<"length is "<<length<<endl;
    line(xaxis[i],yaxis[i],xaxis[i+1],yaxis[i+1]);}
setcolor(WHITE);
outtextxy(x1,getmaxy()/2+3,"(0,0");


    //outtextxy(xaxis[i],(getmaxy()/2)+2,"%s"xaxis[i]);

//char
//sprintf(number,"%d",start)
//outtextxy(getmaxx()/2,getmaxy()/2+3,);


getch();
//replacex(to_send,10);
//float ans;
//ans=ineval(to_send);
//cout<<ans;

}
