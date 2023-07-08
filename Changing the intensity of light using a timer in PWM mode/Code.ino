void delays(){
  for(volatile long int i=0;i<5000;i++);

  
}
void setup() {
  // put your setup code here, to run once:
volatile long int *portd=0x2b,*ddrd=0x2a;
volatile long int *tccr0a=0x44,*tccr0b=0x45,*tcnt0=0x46,*ocrna0=0x47;
*ddrd=0xff;
*tccr0a=0x83;
*tccr0b=0x05;
tcnt0=0;

while(1){
  for(int i=0;i<255;i++){
    *ocrna0=i;
    delays();
  }
  
}

}

void loop() {
  // put your main code here, to run repeatedly:

}
