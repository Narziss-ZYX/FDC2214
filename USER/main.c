#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "fdc2214.h"
#include "exti.h"
#include "math.h"
#include "myiic.h"


#define lea_number 200//�������һ��Ҫͬ���޸�
#define text_number 10


u32 ch0,ch1,ch2,ch3;

/*
  ����ģʽ��־λ
	work_mode=0��ѵ��ģʽ
	work_mode=1���о�ģʽ
*/
u8 work_mode=0;
/*
  ��Ϸģʽ��־λ
	game_mode=0����ȭ��Ϸ
	game_mode=1����ȭ��Ϸ
*/
u8 game_mode=0;

/*
  ��Աѡ���־λ
	staff_mode=0����Ա
	staff_mode=1��������
*/
u8 staff_mode=0;

//ѡ����ɱ�־λ
u8 staffsel_flag=0;
u8 gamesel_flag=0;
u8 compsel_flag=0;
//ѧϰȷ��
u8 learn=0;

/***********************������***********************/
u8 finger_text=0;
u8 text_chishu=0;
u32 q=0,ch=0,i=0,t,display_temp=20,display_flag1=1,display_flag2=1,fk=0;//��ʱ����


//��������
u32 check0_sum=0;
u32 check1_sum=0;
u32 check2_sum=0;
u32 check3_sum=0;
u32 check4_sum=0;
u32 check5_sum=0;
u32 check_rocksum=0;
u32 check_scissorssum=0;
u32 check_papersum=0;
//��������
u32 check0_js=0;
u32 check1_js=0;
u32 check2_js=0;
u32 check3_js=0;
u32 check4_js=0;
u32 check5_js=0;
u32 check_rock_js=0;
u32 check_scissors_js=0;
u32 check_paper_js=0;
//float old_res0;
//float res0;
//float old_res1;
//float res1;
//float old_res2;
//float res2;
//float old_res3;
//float res3;



//���ѧϰ������
u32 finger0[4][lea_number]={0};
u32 finger1[4][lea_number]={0};//1
u32 finger2[4][lea_number]={0};//2
u32 finger3[4][lea_number]={0};//3
u32 finger4[4][lea_number]={0};//4
u32 finger5[4][lea_number]={0};//5

u32 rock[4][lea_number]={0};  //ʯͷ
u32 paper[4][lea_number]={0};  //��
u32 scissors[4][lea_number]={0}; //����
////��������
//u32 finger0_check[4][text_number]={0};
//u32 finger1_check[4][text_number]={0};
//u32 finger2_check[4][text_number]={0};
//u32 finger3_check[4][text_number]={0};
//u32 finger4_check[4][text_number]={0};
//u32 finger5_check[4][text_number]={0};
u32 fingerx_check[4][text_number]={0};

//��������Ʋ��Ա���4��ͨ����ƽ��ֵ
u32 fingerx_check_avg[4]={0};



//��ֵ
u32 step=90000;
u32 step0=80000;
u32 step1=50000;
u32 step1UP=40000;
u32 step1DOWN=20000;
u32 step2=20000;
u32 step2UP=30000;
u32 step2DOWN=8000;
u32 step3=10000;
u32 step4=6000;
u32 step4UP=6000;
u32 step4DOWN=20000;
u32 step5=20000;
u32 step_rock=30000;
u32 step_scissors=30000;
u32 step_paper=45000;

void update_learn(void)
{

	if(game_mode==0)  
	{
	 LCD_Clear(WHITE);
	 LCD_ShowString(30,40,210,24,24,"0 learning"); 
	
	 while(learn==0);
		 for(t=0;t<lea_number;t++)
		 {
			 FDC2214_GetChannelData(FDC2214_Channel_2, finger0[0]+t);//����0
			 
			 printf("%d\r\n",finger0[0][t]);
		 }
		 printf("/****************************/\r\n");
	 LCD_ShowString(210,40,210,24,24,"OK");	 
	 learn=0;
	 LCD_ShowString(30,70,210,24,24,"1 learning"); 
	 while(learn==0);
		 for(t=0;t<lea_number;t++)
		 {
			 FDC2214_GetChannelData(FDC2214_Channel_2, finger1[0]+t);//����1
			printf("%d\r\n",finger1[0][t]);
		 }
		 printf("/****************************/\r\n");
	 LCD_ShowString(210,70,210,24,24,"OK"); 
	 learn=0;
		LCD_ShowString(30,100,210,24,24,"2 learning"); 
	 while(learn==0);
		 for(t=0;t<lea_number;t++)
		 {
			 FDC2214_GetChannelData(FDC2214_Channel_2, finger2[0]+t);//����2
			printf("%d\r\n",finger2[0][t]);
		 }
	 printf("/****************************/\r\n");
	 LCD_ShowString(210,100,210,24,24,"OK"); 
	 learn=0;
	 LCD_ShowString(30,130,210,24,24,"3 learning"); 
	 
	 while(learn==0);
		 for(t=0;t<lea_number;t++)
		 {
			 FDC2214_GetChannelData(FDC2214_Channel_2, finger3[0]+t);//����3
			printf("%d\r\n",finger3[0][t]);
		 }
	 printf("/****************************/\r\n");
	 LCD_ShowString(210,130,210,24,24,"OK"); 
	 learn=0;
	LCD_ShowString(30,160,210,24,24,"4 learning");  
	 while(learn==0);
	 
		 for(t=0;t<lea_number;t++)
		 {
			 FDC2214_GetChannelData(FDC2214_Channel_2, finger4[0]+t);;//����4
			printf("%d\r\n",finger4[0][t]);
		 }
		printf("/****************************/\r\n");
	 LCD_ShowString(210,160,210,24,24,"OK"); 
	 learn=0;
	 LCD_ShowString(30,190,210,24,24,"5 learning"); 
	 while(learn==0);
	 
		 for(t=0;t<lea_number;t++)
		 {
			 FDC2214_GetChannelData(FDC2214_Channel_2, finger5[0]+t);;//����5
			printf("%d\r\n",finger5[0][t]);
		 }
	 LCD_ShowString(210,190,210,24,24,"OK"); 
		learn=0;
	}
	else
	{
		 LCD_Clear(WHITE);
		 LCD_ShowString(30,40,210,24,24,"0 learning"); 
		 while(learn==0);
		 for(t=0;t<lea_number;t++)
		 {
			 FDC2214_GetChannelData(FDC2214_Channel_2, finger0[0]+t);//����0
			 printf("%d\r\n",finger0[0][t]);
		 }
		 printf("/****************************/\r\n");
		 LCD_ShowString(210,40,210,24,24,"OK"); 
		 learn=0;
		 LCD_ShowString(30,70,210,24,24,"rock learning"); 	
		 while(learn==0);
		 for(t=0;t<lea_number;t++)
		 {
			 FDC2214_GetChannelData(FDC2214_Channel_2, rock[0]+t);//ʯͷ
			 printf("%d\r\n",rock[0][t]);
		 }
		 printf("/****************************/\r\n");
		 LCD_ShowString(210,40,210,24,24,"OK"); 
		 learn=0;
		 LCD_ShowString(30,100,210,24,24,"scissors learning"); 	
		 while(learn==0);
		 for(t=0;t<lea_number;t++)
		 {
			 FDC2214_GetChannelData(FDC2214_Channel_2, scissors[0]+t);//����
			 printf("%d\r\n",scissors[0][t]);
		 }
		 printf("/****************************/\r\n");
		 LCD_ShowString(210,40,210,24,24,"OK"); 
		 learn=0;
		 LCD_ShowString(30,130,210,24,24,"paper learning"); 	
		 while(learn==0);
		 for(t=0;t<lea_number;t++)
		 {
			 FDC2214_GetChannelData(FDC2214_Channel_2, paper[0]+t);//��
			 printf("%d\r\n",paper[0][t]);
		 }
		 printf("/****************************/\r\n");
		 LCD_ShowString(210,40,210,24,24,"OK"); 
		 learn=0;
	}
			
}

void judge_action(void)
{
	if(game_mode==0)
	{
	  for(ch=0;ch<4;ch++) fingerx_check_avg[ch]=0;//���һ��
		for(q=0;q<text_number;q++)
		{
			FDC2214_GetChannelData(FDC2214_Channel_2, fingerx_check[0]+q);
	printf("%d\r\n",fingerx_check[0][q]);
			fingerx_check_avg[0]+=fingerx_check[0][q];
		}
		fingerx_check_avg[0]=fingerx_check_avg[0]/text_number;
			//��ռ�������ʼ�Աȸ������Ƶ�ѧϰ����
		check0_sum=0;
		check1_sum=0;
		check2_sum=0;
		check3_sum=0;
		check4_sum=0;
		check5_sum=0;
		//������
		for(i=0;i<lea_number;i++)
		{
			if(abs(fingerx_check_avg[0]-finger0[0][i])<=step) check0_sum++;
		}
		//�Ա�����1
		for(i=0;i<lea_number;i++)
		{
			if(fingerx_check_avg[0]>=finger1[0][i])
			{
				if(abs(fingerx_check_avg[0]-finger1[0][i])<=step1UP) check1_sum++;
			}
			else
			{
				if(abs(finger1[0][i]-fingerx_check_avg[0])<=step1DOWN) check1_sum++;
			}
		}
		//�Ա�����2 
		for(i=0;i<lea_number;i++)
		{
			if(fingerx_check_avg[0]>=finger2[0][i])
			{
				if(abs(fingerx_check_avg[0]-finger2[0][i])<=step2UP) check2_sum++;
			}
			else
			{
				if(abs(finger2[0][i]-fingerx_check_avg[0])<=step2DOWN) check2_sum++;
			}
		}
		//�Ա�����3
		for(i=0;i<lea_number;i++)
		{
			if(abs(fingerx_check_avg[0]-finger3[0][i])<=step3) check3_sum++;
		}
		//�Ա�����4
		for(i=0;i<lea_number;i++)
		{
			if(fingerx_check_avg[0]>=finger4[0][i])
			{
				if(abs(fingerx_check_avg[0]-finger4[0][i])<=step4UP) check4_sum++;
			}
			else
			{
				if(abs(finger4[0][i]-fingerx_check_avg[0])<=step4DOWN) check4_sum++;
			}
		}
	  //�Ա�����5 
		for(i=0;i<lea_number;i++)
		{
			if(abs(fingerx_check_avg[0]-finger5[0][i])<=step5) check5_sum++;
		}
		if(display_temp<check0_sum) display_temp=check0_sum;
		if(display_temp<check1_sum) display_temp=check1_sum;
		if(display_temp<check2_sum) display_temp=check2_sum;
		if(display_temp<check3_sum) display_temp=check3_sum;
		if(display_temp<check4_sum) display_temp=check4_sum;
		if(display_temp<check5_sum) display_temp=check5_sum;
				
		if(display_temp==check5_sum) check5_js++; 
		if(display_temp==check4_sum) check4_js++; 
		if(display_temp==check3_sum) check3_js++; 
		if(display_temp==check2_sum) check2_js++; 
		if(display_temp==check1_sum) check1_js++; 
		if(display_temp==check0_sum) check0_js++; 
		if((check0_js==4)||(check1_js==4)||(check2_js==4)||(check3_js==4)||(check4_js==4)||(check5_js==4))
		{
			LCD_Clear(WHITE);
			if(check0_js==4) LCD_ShowString(80,140,210,24,24,"none");
			if(check1_js==4) LCD_ShowString(80,140,210,24,24,"1");
			if(check2_js==4) LCD_ShowString(80,140,210,24,24,"2");
			if(check3_js==4) LCD_ShowString(80,140,210,24,24,"3");
			if(check4_js==4) LCD_ShowString(80,140,210,24,24,"4");
			if(check5_js==4) LCD_ShowString(80,140,210,24,24,"5");

			check0_js=0;
			check1_js=0;
			check2_js=0;
			check3_js=0;
			check4_js=0;
			check5_js=0;
		}
		display_temp=20;
		delay_ms(100);
	}
	else
	{
		for(ch=0;ch<4;ch++) fingerx_check_avg[ch]=0;//���һ��

		for(q=0;q<text_number;q++)
		{
			FDC2214_GetChannelData(FDC2214_Channel_2, fingerx_check[0]+q);
			printf("%d\r\n",fingerx_check[0][q]);
			//����ȡƽ���ĵ�RS
			fingerx_check_avg[0]+=fingerx_check[0][q];
		}
		fingerx_check_avg[0]=fingerx_check_avg[0]/text_number;
		//��ռ���
		check0_sum=0;
		check_rocksum=0;
		check_scissorssum=0;
		check_papersum=0;

		//������
		for(i=0;i<lea_number;i++)
		{
			if(abs(fingerx_check_avg[0]-finger0[0][i])<=step0) check0_sum++;
		}
		//����
		for(i=0;i<lea_number;i++)
		{
			if(abs(fingerx_check_avg[0]-scissors[0][i])<=step_scissors) check_scissorssum++;
		}
		//ʯͷ
		for(i=0;i<lea_number;i++)
		{
			if(abs(fingerx_check_avg[0]-rock[0][i])<=step_rock) check_rocksum++;
		}
		//��
		for(i=0;i<lea_number;i++)
		{
			if(abs(fingerx_check_avg[0]-paper[0][i])<=step_paper) check_papersum++;
		}
		if(display_temp<check0_sum) display_temp=check0_sum;
		if(display_temp<check_scissorssum) display_temp=check_scissorssum;
		if(display_temp<check_rocksum) display_temp=check_rocksum;
		if(display_temp<check_papersum) display_temp=check_papersum;
		
		if(display_temp==check_papersum) check_paper_js++; 
		if(display_temp==check_rocksum) check_rock_js++; 
		if(display_temp==check_scissorssum) check_scissors_js++; 
		if(display_temp==check0_sum) check0_js++; 

		if((check0_js==3)||(check_paper_js==3)||(check_rock_js==3)||(check_scissors_js==3))
		{
			LCD_Clear(WHITE);
			if(check0_js==3) LCD_ShowString(80,140,210,24,24,"none");
			if(check_scissors_js==3) LCD_ShowString(80,140,210,24,24,"scissors");
			if(check_rock_js==3) LCD_ShowString(80,140,210,24,24,"rock");
			if(check_paper_js==3) LCD_ShowString(80,140,210,24,24,"paper");

			check0_js=0;
			check_scissors_js=0;
			check_rock_js=0;
			check_paper_js=0;
		}
		display_temp=20;
		delay_ms(100);
	}	
}

int main(void)
{ 
	u8 lcd_id[12];				//���LCD ID�ַ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	LED_Init();					  //��ʼ��LED
 	LCD_Init();           //��ʼ��LCD FSMC�ӿ�
	POINT_COLOR=RED;      //������ɫ����ɫ
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣		
	KEY_Init();
	EXTIX_Init();
	IIC_Init();
	while(!(FDC2214_Init()));
	LCD_Clear(WHITE);
	/*����ԭʼѧϰ����*/
	update_learn(); //���»�ȭ
	game_mode=1;    
	update_learn(); //���²�ȭ
	game_mode=0;
	 LCD_Clear(WHITE);
  	while(1) 
	{
		staffsel_flag=0;
		gamesel_flag=0;
		POINT_COLOR=RED;	  
		/*******��Աѡ��ѡ�����*********/
	 while(compsel_flag==0)//���û��ȷ�ϣ���һֱ��������
	 {
		 while(staffsel_flag==0)
		 {
			 LCD_ShowString(80,40,210,24,24,"me"); 
			 LCD_ShowString(80,70,210,24,24,"other"); 
			 if(!staff_mode) LCD_ShowString(5,40,210,24,24,"--->"); 
			 else LCD_ShowString(5,70,210,24,24,"--->"); 
		 }
		 if(staff_mode)   //������
		 {
			 LCD_Clear(WHITE);
			 LCD_ShowString(80,40,210,24,24,"trial mode"); 
			 delay_ms(500);
			 while(gamesel_flag==0)
			 {
				 LCD_ShowString(25,40,210,24,24,"12345 trial"); 
				 LCD_ShowString(25,70,210,24,24,"Rock-paper-scissors"); 
				 if(!game_mode) LCD_ShowString(0,40,210,24,24,"->"); 
				 else LCD_ShowString(0,70,210,24,24,"->"); 
			 }
			 update_learn();  //ѧϰ
			 LCD_Clear(WHITE);
			 LCD_ShowString(80,40,210,24,24,"judge mode"); 
			 delay_ms(500);
			 compsel_flag=1; //���ѡ��
		 }
     else   //��Ա
		 {
			 LCD_Clear(WHITE);
			 LCD_ShowString(80,40,210,24,24,"judge mode"); 
			 delay_ms(500);
			 while(gamesel_flag==0)
			 {
				 LCD_ShowString(25,40,210,24,24,"12345 trial"); 
				 LCD_ShowString(25,70,210,24,24,"Rock-paper-scissors"); 
				 if(!game_mode) LCD_ShowString(0,40,210,24,24,"->"); 
				 else LCD_ShowString(0,70,210,24,24,"->"); 
			 }
			 compsel_flag=1; //���ѡ��
		 }			 
			 
	 }
	 judge_action();

	 
	} 
}


