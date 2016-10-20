#include<iostream>
#include<stack>
#include <string.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include <math.h>
#include<graphics.h>
#include <algorithm>
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
    	//case 'l':
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
    	//case 'l':return log(a);
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

int main()
{
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
double start,stop,jump;
double xaxis[1000],yaxis[1000],xaxis2[1000],yaxis2[1000];
for(k=-10;k<=10;k=k+0.10000,++i){
    xaxis[i]=k;
    xaxis2[i]=k;
    //cout<<xaxis[i]<<",";
}
cout<<endl;
for(i=0;i<201;++i){
    strcpy(temp,to_send);
    replacex(temp,xaxis[i]);
    //cout<<temp;
    yaxis[i]=ineval(temp);
    yaxis2[i]=yaxis[i];
    //cout<<yaxis[i]<<",";
}
double* ymax=max_element(yaxis,yaxis+201);
double maxy=*ymax;
double* ymin=min_element(yaxis,yaxis+201);
double miny=*ymin;
double diff1=fabs(miny);
double diff2=fabs(maxy);
double range= (diff1>diff2)?diff1:diff2;

cout<<range;
int gd = DETECT, gm;
initgraph(&gd, &gm, "");
int x1,y1;
line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
line(getmaxx()/2,0,getmaxx()/2,getmaxy());
cout<<endl<<getmaxx();
cout<<endl<<getmaxy()/2;
for(i=0;i<201;++i)
    {if(xaxis[i]==0)
    cout<<"Zero element"<<xaxis[i];}

  for (i=0;i<201;++i)
  {
     xaxis[i]=(xaxis[i]+10)*((double)getmaxx()/20);
     long double scale=yaxis[i]*(long double)(getmaxy()/2);
     cout<<endl<<"scale1 "<<scale<<endl;
     scale=(long double)(scale/(long double)(range));
     cout<<scale;
     yaxis[i] = (double)(getmaxy()/2) - scale;
     putpixel(xaxis[i],yaxis[i],2);
  }
for(i=0;i<201;++i)
        cout<<"("<<xaxis2[i]<<" , "<<xaxis[i]<<" , "<<yaxis2[i]<<" , "<<yaxis[i]<<")\n";
for (i=0;i<200;++i)
    line(xaxis[i],yaxis[i],xaxis[i+1],yaxis[i+1]);
outtextxy(getmaxx()/2,getmaxy()/2+3,"(0,0");
for(i=0;i<201;i=i+10)
    {putpixel(xaxis[i],getmaxy()/2,1);

    //outtextxy(xaxis[i],(getmaxy()/2)+2,"%s"xaxis[i]);
    }


getch();
//replacex(to_send,10);
//float ans;
//ans=ineval(to_send);
//cout<<ans;

}
