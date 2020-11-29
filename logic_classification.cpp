#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 130
void push(int);
char pop();
void in2prefix();
 
char stk[130],in[130],postfix[130];
int top=-1;
int lim,p=0,q=0,r;
int n,bit,value;
char arr[MAX],chars[MAX];
int pos=0;
#define small(j) ((j<='z')&&(j>='a'))
void push(int sop)
{
 
    if(top==130-1)
    {
        printf("stackfull!!!!");
    }
 
    else {
        top++;
        stk[top] = in[sop];
    }
}
char pop()
{
    char ch;
 
    if(top < 0)
    {
        printf("stackempty!!!!");
        exit(0);
    }
    else
    {
        ch=stk[top];
        stk[top]='\0';
        top--;
        return(ch);
    }
    return 0;
}
void in2prefix()
{
    int i=0,j=0,k=0;
 
    i=0;
    j=strlen(in)-1;
    char temp;

    while(i<j)
    {
        temp=in[i];
        in[i]=in[j];
        in[j]=temp;
        i++;
        j--;
    }
  i=0;
  j=0;
    while(in[i]!='\0')
    {
        if(in[i]>='a' && in[i]<='z')        
        {
            postfix[j]=in[i];
            j++;
            i++;
        }
            else if(in[i]==')' || in[i]=='}'  || in[i]==']')      
            {
                push(i);
                i++;
            }
        else if(in[i]=='(' || in[i]=='{'  || in[i]=='[')       
        {
            if(in[i]=='(')
            {
                while(stk[top]!=')')         
                {
                    postfix[j]=pop();
                    j++;
                }
                pop();
                i++;
            }
 
            else if(in[i]=='[')
            {
                while(stk[top]!=']')      
                {
                    postfix[j]=pop();
                    j++;
                }
                pop();
                i++;
            }
 
            else if(in[i]=='{')
            {
            while(stk[top]!='}')     
                {
                    postfix[j]=pop();
                    j++;
                }
                pop();
                i++;
            }
        }
       else            
        {
            if(top==-1)        
            {
                push(i);
                i++;
            }
            else
            {
                push(i);
                i++;
            }
        }
    }
    while(top!=-1)
    {
        postfix[j]=pop();
        j++;
    }
    i=0;
    k=strlen(postfix)-1;

    while(i<k)
    {
        temp=postfix[i];
        postfix[i]=postfix[k];
        postfix[k]=temp;
        i++;
        k--;
    }
  i=0;
    postfix[j]='\0';
}
int findliterals(const char *s,char *chars)
{
   int cnt=0;
   int found[MAX]={};
   while(*s){
      if(small(*s))
         if(!found[*s]){
            chars[cnt++]=*s;
            found[*s]=1;
         }
      s++;
   }
   chars[cnt]='\0';
   return cnt;
}
void assignvaluestoliterals(int bit,int n,char *chars,char *arr)
{
   int i;
   for(i=0;i<n;i++)
      if(bit&(1<<i))
         {arr[chars[i]]=1;}
      else 
      {arr[chars[i]]=0;}
}
int compute(char ch, int old,int o)
{
   switch(ch){
      case 'V': return old&o;
                break;
      case '^': return old|o;
                break;
      case '-': 
                if(old &&(!o)) return 0;
                else return 1;
                break;
      case '=': return 1^old^o;
                break;

   };
   return 87243238;
}

int evaluate(char *postfix,char *arr)
{
   int ans,a,b;
   char op;
   if(small(postfix[pos])){
      ans=arr[postfix[pos]];
      pos++;
      return ans;
   }
   else{
      if(postfix[pos]=='~'){
         pos++;
         ans= 1^evaluate(postfix,arr);
         return ans;
      }
      else{
         op=postfix[pos];
         pos++;
         a=evaluate(postfix,arr);
         b=evaluate(postfix,arr);
         ans=compute(op,a,b);
         return ans;
      }
   }
}
int main()
{
   int cont;
   printf("\n\nyour expression should follow these rules\n1)  Variables should be p and q only\n2)  Use V for AND\n3)  Use ^ for OR \n4)  Use - for if\n5)  Use = for if and only if\n6)  Use ~for nagation\n7)  Use simple brackets '()' for every expression\n") ;
    printf("\nEnter your expression\n");
      scanf("%s",in);
      in2prefix();
      
    
      n=findliterals(postfix,chars);
      lim=1<<n;
      for(bit=0;bit<lim;bit++){
         assignvaluestoliterals(bit,n,chars,arr);
         pos=0;
         value=evaluate(postfix,arr);
         if(value==1) {p=1;}
         if(value!=1){q=1;}

      }
      if(bit==lim&&q==0) 
         {printf("THIS STATEMENT IS TAUTOLOGY\n");}
      else if(p==0)
      {
          printf("THIS STATEMENT IS CONTRADICTION\n");
      }  
      else printf("THIS STATEMENT IS CONTINGENCY\n");
   
   return 0;
}
