
void init_lcd();
void delays();
void lcd_command(char command);
void lcd_data(char data);
void num_to_str(char *word,long long int num);
long long int read_buttons();
void print_in_lcd (char *str);
void erase(char *str);
long long int calc(int num1, int num2 ,char chars);
volatile int * portb=0x25,*portd=0x2b,*inpb=0x23,* portc=0x28;
volatile int  *ddrb=0x24,*ddrd=0x2a,*ddrc=0x27;
  
void setup() {
  
  *ddrb=0xf0;
  *ddrd=0xff;
  *ddrc=0xff;
   init_lcd();
  long long int num;
  char str[10];
  while(1){
    num=read_buttons();
    num_to_str(str,num);
    print_in_lcd(str);
    erase(str);
  }

}
void erase(char *str){
   for(int z=0;z<10;z++){
               str[z]="\0";
             }
}
void num_to_str(char *str , long long int num){
  long long int count=1,temp=num;
  char c=0;
  if(num<0){
    temp=(-1)*(num);
    num=temp;
    str[c]='-';
    c++;
  }
  while(temp>0){
    temp=temp/10;
    count=count*10;
  }
  count=count/10;
  
  while(count>0){
    str[c]=(((num/count)%10)+48);
    c++;
    count=count/10;
  }
}

void print_in_lcd (char *str){
  while(*str){
    lcd_data(*str);
    str++;
  }
}

 long long int read_buttons(){
  long long int r,c,dig=0,num=0,num1,num2,res,inp,t;
  char chars;
  while(1){
    while((*inpb & 0x0f)!=0);
  for(r=0;r<4;r++){
    dig=0;
     *portc=(1<<r)&(0x0f);
    for(c=0;c<4;c++){
      
      inp=*inpb & 0x0f;
      t=1<<c;
      if(inp==t){
         dig=(r*3)+(c+1);
         
         if(((dig>=1 &&dig<=9)&&c!=3)||(r==3 && c==1)){
           if(r==3 && c==1){
             dig=0;
           }
           num=(num*10)+dig;
           lcd_data(dig+48);
            
         }
         else if(c==3){
           if(r==0){
             chars='+';
             
           }
           if(r==1){
             chars='-';
           }
           if(r==2){
             chars='*';
           }
           if(r==3){
             chars='/';
           }
            lcd_data(chars);

           num1=num;
           num=0;
         }
         else{
           if(r==3 && c==0){
             lcd_command(0x01);
             lcd_command(0x80);
             
           }
           else{
             num2=num;
             lcd_command(0xc0);
            lcd_data('=');
            
             res=calc(num1,num2,chars);
             
             return res;
           }
         }
      }
    }
    if(dig!=0){
      break;
    }
  }
  
  }
  return 0;
}
long long int calc(long long int num1,long long int num2 ,char chars){
  long long int res;
           if(chars=='+'){
             res=num1+num2;
           }
           if(chars=='-'){
             res=num1-num2;
           }
           if(chars=='/'){
             res=num1/num2;
           }
           if(chars=='*'){
             res=num1*num2;
           }
           return res;
}
void init_lcd(){
   lcd_command(0x38);//8bit mode
   lcd_command(0x01);//clear screen
   lcd_command(0x0f);//display cursor blink on
   lcd_command(0x80);//cursor position;
   
}
void lcd_data(char data){
   *portb=0x10;
   *portd=data;
   *portb=0x30;
  delays();
  
}
void lcd_command(char command){
 
 
  *portb=0x00;
  *portd=command;
  *portb=0x20;
  delays();
  
}
void delays(){
  for(volatile long int i;i<100;i++);
}
void loop() {
  // put your main code here, to run repeatedly:

}
