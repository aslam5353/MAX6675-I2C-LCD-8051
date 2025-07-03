#include<reg51.h>
sbit sda=P2^0;
sbit scl=P2^1;
sbit SO  = P2^2;
sbit SCK = P2^3;
sbit CS  = P2^4;
#define LCD_ADDR 0x4E 
void delay(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 127; j++);
}
void start()
{sda=1;
	scl=1;
	delay(1);
	sda=0;
	delay(1);
	scl=0;
	
}
void stop()
{sda=0;scl=1;
delay(1);
sda=1;
}
void write(unsigned char dat)
{ unsigned int i; 
	scl=0;
		delay(1);
for(i=0;i<8;i++)
	{ sda= (dat & 0x80) ? 1 : 0;
	 
		scl=1;
		dat<<=1;
		scl=0;
		delay(1);
	}
	 sda = 1; 
scl = 1	;
    delay(1);
    scl = 0;
}
void cmd(unsigned char cmd)
{ unsigned char upper_data,lower_data;
 upper_data=cmd&0xF0;
	lower_data=(cmd<<4)&0xF0;
	
	start();
	write(LCD_ADDR);
	write(upper_data|0x0C);
	write(upper_data|0x08);
	stop();
	
	start();
	write(LCD_ADDR);
	write(lower_data|0x0C);
	write(lower_data|0x08);
	stop();
	
	
}
void init()
{ delay(50);
	cmd(0x33);
	cmd(0x32);
	cmd(0x28);
	cmd(0x0C);
	cmd(0x06);
	cmd(0x01);
	delay(2);
}


void dat(unsigned char dat)
{
	unsigned char upper_data,lower_data;
upper_data =dat&0xF0;
	lower_data=(dat<<4)&0xF0;
	
	start();
	write(LCD_ADDR); 
	write(upper_data|0x0D);
	write(upper_data|0x09);
	stop();
	
	start();
	write(LCD_ADDR); 
	write(lower_data|0x0D);
	write(lower_data|0x09);
	stop();


}
void print(char *str)
{ while(*str)
 dat(*str++);
}
void intToStr(unsigned int num, char *buf) {
    int i = 0, j;
    char temp[6];
    if (num == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
    while (num > 0) {
        temp[i++] = (num % 10) + '0';
        num /= 10;
    }
    for (j = 0; j < i; j++)
        buf[j] = temp[i - j - 1];
    buf[i] = '\0';
}

unsigned int read_temp_raw() {
    unsigned int value = 0;
    char i;
    SCK=0;
    CS = 0;
    delay(5);

    for (i = 0; i < 16; i++) {
        value <<= 1;

        SCK = 1;        // Rising edge: read data
        delay(5);
         
            value |= SO;
        SCK = 0;        // Falling edge
        delay(5);
    }

    CS = 1;
		 if ((value & 0x04)==0x04)
		 {return -1;}
		 else
        return ((value >> 3));
}


void main()
{ unsigned int temp;
	unsigned char str[10];
init();
	while(1){
		
		cmd(0x80);


	temp=read_temp_raw();
	if (temp==-1)
	{print("senor error");
		delay(1000);
cmd(0x01);}
	else
	{
		intToStr(temp/4,str);
	print("temp=");
		print(str);
		print(".");
		
		// Decimal part
            intToStr((temp % 4) * 25, str);
            if ((temp % 4) * 25 < 10) dat('0'); // Padding zero
            print(str);
	           print("C");               
	}

delay(100);
	}}
