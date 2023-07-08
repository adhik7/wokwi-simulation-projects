volatile int *ddrk=0x107,*ddrf=0x30,*ddra=0x21;
  volatile int *portk=0x108,*portf=0x31,*porta=0x22,*inpa=0x20;
  
void delays();
 int readbuttons(int br);
 int nums(int n);
 int cal(int num1,int num2,char sym);
 void disp(int ans);
 void clear();
void setup() {
  // put your setup code here, to run once:
  *ddrf=0xff;
  *ddrk=0xff;
  *ddra=0x0f;
 
    while(1){

      readbuttons(0);
    }

  
}
void delays(){
  for(volatile long int d=0;d<100;d++);
}
int readbuttons(int br){
  long int inp,num1,num2,num,temp,fl=0,tot=0,ans;
  char sym;
  if(br==1){
    *porta=(1<<3)&(0x0f);
    inp=*inpa & 0xf0;
    if(inp==0x10){
      
      clear();
      
    }
    return 0;
  }
  while(1){
    fl=0;
  for(int r=0;r<4;r++){
      *porta=(1<<r)&(0x0f);
        for(int c=0;c<4;c++){
            inp=*inpa & 0xf0;
            temp=1<<(c+4);
            if(temp==inp){
                  if((c<3 )&& ((r<3) || (r==3 && c==1))){
                      if((c<3) && (r<3)){
                        num=(3*r)+c+1;
                       
                       
                      }
                     if((r==3) &&(c==1)){
                        num=0;
                        
                      }
                      tot=(tot+num)*10;
                    
                       
                  }
                   else if(c==3){
                      if(r==0){
                        sym='+';
                       
                      }
                      if(r==1){
                        sym='-';
                      }
                      if(r==2){
                        sym='*';
                      }
                      if(r==3){
                        sym='/';
                      }
                      
                        num1=tot/10;
                       
             
                        tot=0;
                    
                    
                  }
                  else if((c==2 && r==3)||(c==0 && r==3)){
                      if(c==2 && r==3){
                        num2=tot/10;
            
             
                        ans=cal(num1,num2,sym);
                        disp(ans);
                        
                        return 0;
                      }
                      else{
                       
                        clear();
                        
                        return 0;
                      }
                  }
                 
           fl=1; 
            
            }
        }
        if(fl==1){
          break;

        }
 }
  inp=*inpa & 0xf0;
  while(fl==1&&inp!=0){
    inp=*inpa & 0xf0;
  }
  
  }
 return 0;
}
int cal(long int num1,long int num2,char sym){
  long int res;
  
   
            if(sym=='+'){
              res=num1+num2;
            }
            if(sym=='-'){
              res=num1-num2;
              
            }
            if(sym=='*'){
              res=num1*num2;
            }
            if(sym =='/'){
              res=num1/num2;
            }
            
            
            return res;
}
void disp(long int ans){
  
  long int i,temp;
  while(1){
     

     temp=ans;
     if(temp>9999){
        for(i=3;i>=0;i--){
     *portf=1<<i;
      *portk=0x06;
     delays();
     *portk=0xff;
     
   }
     }
     else{
     if(temp<0){
       temp=temp*(-1);
     }
   
   for(i=3;i>=0;i--){
     *portf=1<<i;
      *portk=nums(temp%10);
     delays();
     *portk=0xff;
      temp=temp/10;
      if(temp==0){
        break;
      }
   }
   temp=ans;
   if(temp<0){
     i--;
     temp=-1*ans;
     *portf=1<<i;
     
      *portk=0x3f;
     delays();
     *portk=0xff;
   }
    }
   readbuttons(1);
   if(*portf==0){
      
     break;
   }
  }
}
int nums(int n){
  
  int num[11];
  num[0]=0x40;
  num[1]=0x79;
  num[2]=0x24;
  num[3]=0x30;
  num[4]=0x19;
  num[5]=0x12;
  num[6]=0x02;
  num[7]=0x78;
  num[8]=0x00;
  num[9]=0x10;
  return num[n];
}
void clear(){
  *portf=0x00;
  
  *portk=0xff;
}
void loop() {
  // put your main code here, to run repeatedly:

}
