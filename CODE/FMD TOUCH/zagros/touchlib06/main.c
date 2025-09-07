
//continue scan

#include "common.h"
#include "syscfg.h"
#include "touch.h" 



#define LED1     PORTB = 0x04; PORTC = 0x00   //RB3
#define LED2     PORTB = 0x0c; PORTC = 0x00   //RB2
#define LED3     PORTB = 0x0c; PORTC = 0x08
#define LED4     PORTB = 0x4c; PORTC = 0x08   //RB4
#define LED5     PORTB = 0x4c; PORTC = 0x0A   //RB1


//===========================================================
//Variable definition
volatile char W_TMP  @ 0x70 ;//系统占用不可以删除和修改
volatile char BSR_TMP  @ 0x71 ;//系统占用不可以删除和修改
void user_isr();//用户中断程序，不可删除
//===========================================================
volatile uint16_t 	readKeyNum;    	//返回的键值  bit0~bit14对应key1~key15  0没有按下，1按下
extern uint8_t      fmd_channels;

uint16_t  lastkey=0;
uint16_t   TouchTimeCount;
volatile unsigned char power_index=0;

//===========================================================
//Function name：interrupt ISR
//parameters：无
//returned value：无
//===========================================================
void interrupt ISR(void)
{  
#asm;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
	NOP;//系统设置不可以删除和修改
#endasm;//系统设置不可以删除和修改

	user_isr(); //用户中断函数
}

//===========================================================
//	Function name：user_isr
//	parameters：
//	returned value：无 
//===========================================================
void user_isr() //用户中断函数
{
     if(T4UIE && T4UIF)                	
	{
		T4UIF = 1;                            
        
		TouchTimeCount++;
	} 
}

//===========================================================
//	Function name：SysInit
//	parameters：
//	returned value：无 
//===========================================================
void SysInit(void)
{
	OSCCON = 0B01100001;		//WDT 32KHZ IRCF=110=8M Hz
												//Bit0=1,系统时钟为内部振荡器
												//Bit0=0,时钟源由FOSC<2：0>决定即编译选项时选择
	INTCON = 0;  						//暂禁止所有中断
    PORTA = 0B00000000;
TRISA = 0B00000000; //PA input and output 0-output 1-input PA0(CH1)-OUT
PORTB = 0B00000000;
TRISB = 0B00000000; //PB input and output 0-output 1-input
PORTC = 0B00000001;
TRISC = 0B00010000; //PC input and output 0-output 1-input PC0(CH1N)-OUT
 PORTD = 0B00000000;
}
//===========================================================
//	Function name：Time4Initial
//	parameters：
//	returned value：无 
//===========================================================
void Time4Initial(void)
{
	PCKEN |=0B00001000;      //TIME4模块时钟使能
    //CKOCON=0B00110000;
    //TCKSRC=0B00000011;		
    
    TIM4CR1	=0B00000101;
    //BIT7: 0：TIM1_ARR寄存器没有缓冲，它可以被直接写入; 1：TIM1_ARR寄存器由预装载缓冲器缓冲。
    //BIT6:保留
    //BIT5~BIT4:timer4时钟选择位。
        		//00：系统时钟/主时钟
				//01：内部快时钟HIRC
				//10：LP时钟，只有当FOSC选择LP模式时才有意义
				//11：XT时钟，只有当FOSC选择XT模式时才有意义

    //BIT3:
    //			0：在发生更新事件时，计数器不停止；
	//			1：在发生下一次更新事件(清除CEN位)时，计数器停止。

    //BIT2:
   	// 		0：如果UDIS允许产生更新事件，则下述任一事件产生一个更新中断：
				//寄存器被更新(计数器上溢/下溢)
				//软件设置UG位
				//时钟/触发控制器产生的更新
	//		1：如果UDIS允许产生更新事件，则只有当下列事件发生时才产生更新中断，并UIF置1：
				//寄存器被更新(计数器上溢/下溢)

    //BIT1:
    //		0：一旦下列事件发生，产生更新(UEV)事件：
				//计数器溢出/下溢
				//产生软件更新事件
				//时钟/触发模式控制器产生的硬件复位被缓存的寄存器被装入它们的预装载值。
	//		1：不产生更新事件，影子寄存器(ARR、PSC、CCRx)保持它们的值。如果设置了UG位或时钟/触发控制器发出了一个硬件复位，则计数器和预分频器被重新初始化。

    // BIT0: 0：禁止计数器；1：使能计数器。


    TIM4IER	=0B00000001;
    //BIT0:  0：禁止更新中断；1：允许更新中断。

    TIM4SR	=0B00000000;
    //BIT0:当产生更新事件时该位由硬件置1。它由软件写1清0
			//0：无更新事件产生；
			//1：更新事件等待响应。当寄存器被更新时该位由硬件置1：
			//若TIM4_CR1寄存器的UDIS=0，当计数器上溢或下溢时；
			//若TIM4_CR1寄存器的UDIS=0、URS=0，当设置TIM4_EGR寄存器的UG位软件对计数器
			//CNT重新初始化时；
			//若TIM4_CR1寄存器的UDIS=0、URS=0，当计数器CNT被触发事件重新初始化时。

    TIM4EGR	=0B00000000;
    //BIT0:该位由软件置1，由硬件自动清0。
	//0：无动作；
	//1：重新初始化计数器，并产生一个更新事件。注意预分频器的计数器也被清0(但是预分频系数不变)。若在中心对称模式下或DIR=0(向上计数)则计数器被清0；若DIR=1(向下计数)则计数器取TIM1_ARR的值。

    TIM4CNTR=0; //TIM4 8位计数器
    
    TIM4PSCR=0B00000110;
    //预分频器对输入的CK_PSC时钟进行分频。
	//计数器的时钟频率fCK_CNT等于fCK_PSC/2(PSC[2:0])。PSC[7:3]由硬件清0。
	//PSCR包含了当更新事件产生时装入当前预分频器寄存器的值(包括由于清除TIMx_EGR寄存器的UG位产生的计数器清除事件)。这意味着如要新的预分频值生效，必须产生更新事件或者CEN=0。

    TIM4ARR	=124;
    //ARR包含了将要装载入实际的自动重装载寄存器的值。
	//当自动重装载的值为空时，计数器不工作。

    INTCON |= 0B11000000;    //开总中断和外设中断
  }
//===========================================================
//Function name：main
//parameters：    无
//returned value：无
//===========================================================
void main(void)
{
	SysInit();
    Time4Initial();  
    TouchInital();
    
	while(1)
	{ 
        if(TouchTimeCount>=(1000/SCANNINGTIME/(fmd_channels+1)))  	//按键扫描频率
        {
            TouchTimeCount=0;
            
			readKeyNum = TouchKeyScan();  					//按键扫描并获取按键值
        }
        //-----------以下用户代码--------------------------
         if(readKeyNum!=0)  											//有按键
        {        
				if(lastkey !=readKeyNum)		
				{
					 if(readKeyNum&0x0001)			
					{  
                        NOP();
					}
                    
                    if(readKeyNum ==0x4000)			
					{ 
                                                
                        if(power_index == 0)power_index=0;
                        if(power_index == 255)power_index=0;
                        power_index--;

					}
                    if(readKeyNum == 0x2)			
					{  
                          
                         if(power_index == 4)power_index=4;
                         power_index++;

					}
				}
                
			   lastkey =  readKeyNum;
        }
        else
        {
             lastkey=0;
        }
        
        if(power_index == 0){LED1;}
        if(power_index == 1){LED2;}
        if(power_index == 2){LED3;}
        if(power_index == 3){LED4;}
        if(power_index == 4){LED5;}
	}
}
