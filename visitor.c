  #include <REGX51.H>
  #define lcd_port P3
  sbit ir1=P1^0;
  sbit ir2=P1^7;
  sbit rs=P2^1;
sbit rw=P2^2;
sbit en=P2^3;
  void delay(unsigned int);
void lcd_cmd(unsigned char);
 void lcd_data(unsigned char);
 void lcd_ini(void);
void lcd_str(unsigned char);
 void lcd_str(unsigned char *str)
 {
  while(*str!='\0')
  {
   lcd_data(*str);
   str++;
   delay(100);
  }
 }
 void delay(unsigned int msec)
{
 unsigned j;
 for(j=0;j<msec;j++)
 {
  TMOD=0x01;
    TH0=0xFC;
   TL0=0x66;
   TR0=1;
   while(TF0==0);
   TF0=0;
   TR0=0;
 }
}
void lcd_cmd(unsigned char dat)
 {
   rw=0;
   rs=0;
   P3=dat;
   en=1;
   delay(5);
   en=0;
   delay(5);
 }
 void lcd_data(unsigned char dat)
 {
  rs=1;
  rw=0;
  P3=dat;
  en=1;
  delay(5);
  en=0;
  delay(5);
 } 
 void lcd_ini(void)
 {
   lcd_cmd(0x38);
   lcd_cmd(0x0c);
   lcd_cmd(0x01);
   lcd_cmd(0x80);
 }

void main()
{
unsigned int count=0,k=0,l=0;
P1=0xFF;
P3=0x00;
back: lcd_ini();
  lcd_cmd(0x82);
  lcd_str("***WELCOME***");
  delay(3000);
  lcd_cmd(0x01);
  lcd_cmd(0x82);
  lcd_str("VISITORS IN");
  lcd_cmd(0xC2);
  lcd_str("OFFICE = ");
  lcd_cmd(0xCB);
  lcd_data(count+0x30); 
 while(1)
 {
   if(ir1==0&&ir2==1)
   {
   count++;
   k=count;
   if(k>9)
   {
	l=k;
	lcd_cmd(0xCB);
  lcd_data(l/10+0x30); 
  delay(200);
  lcd_cmd(0xCC);
  lcd_data(l%10+0x30); 
  delay(6000);
   }
 else
 {
  lcd_cmd(0xCB);
  lcd_data(0x30);
  delay(100);
  lcd_cmd(0xCC);
  lcd_data(k+0x30); 
  delay(6000);
  }
   }
   if(ir1==1&&ir2==0)
   {
	if(k==0)
	{
	  lcd_cmd(0x01);
  lcd_cmd(0x82);
  lcd_str("***ILLEGAL***");
  delay(6000);
  goto back;
	}
	else
	{
	 count--;
	k=count;
	if(k>9)
   {
	l=k;
	lcd_cmd(0xCB);
  lcd_data(l/10+0x30); 
  delay(100);
  lcd_cmd(0xCC);
  lcd_data(l%10+0x30); 
  delay(6000);
   }
else
{
  lcd_cmd(0xCB);
  lcd_data(0x30);
  delay(100);
   lcd_cmd(0xCC);
  lcd_data(k+0x30);
  delay(6000); 
  }
   }
   }
 }
 }