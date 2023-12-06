
#include "main.h"
#include<stdio.h>
#include <string.h>
#include <math.h>
void lcd_cmd(char cmd){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0);//RS=0 command register select
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, (cmd&0x10));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, (cmd&0x20));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (cmd&0x40));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (cmd&0x80));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);//EN=1
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);//EN=0
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, ((cmd<<4)&0x10));
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, ((cmd<<4)&0x20));
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, ((cmd<<4)&0x40));
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, ((cmd<<4)&0x80));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);//EN=1
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);//EN=0

}
void lcd_data(char data){
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1);//RS=1 data register select
	    //sending higher nibble
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, (data&0x10));
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, (data&0x20));
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (data&0x40));
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (data&0x80));
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);//EN=1
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);//EN=0
		//sending Lower nibble
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, ((data<<4)&0x10));
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, ((data<<4)&0x20));
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, ((data<<4)&0x40));
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, ((data<<4)&0x80));
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);//EN=1
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);//EN=0
}
void lcd_string(char *s){
	while(*s!='\0'){
		lcd_data(*s);
		s++;
	}
}
void lcd_init(){
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x01);
	lcd_cmd(0x0C);
}

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
int check_R1(){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==1){
		return '1';
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1){
			return '2';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1){
			return '3';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==1){
			return 'A';
		}
	return '\0';
}
int check_R2(){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==1){
		return '4';
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1){
			return '5';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1){
			return '6';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==1){
			return 'B';
		}
	return '\0';
}
int check_R3(){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==1){
		return '7';
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1){
			return '8';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1){
			return '9';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==1){
			return 'C';
		}
	return '\0';
}
int check_R4(){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==1){
		   return '*';
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1){
			return '0';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1){
			return '#';
		}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==1){
			return 'D';
		}
	return '\0';
}
int key_Press(){
	char key;
	GPIOB->ODR&=0x00000000;
	GPIOB->ODR|=0x1000;//PB12-PB15 row pins
	key=check_R1();
    if(key!='\0'){
    	return key;
      HAL_Delay(50);
    }HAL_Delay(10);

    GPIOB->ODR&=0x0000;
    GPIOB->ODR|=0x2000;
    key=check_R2();
    if(key!='\0'){
      return key;
      HAL_Delay(50);
       }HAL_Delay(10);

    GPIOB->ODR&=0x0000;
    GPIOB->ODR|=0x4000;
    key=check_R3();
     if(key!='\0'){
      return key;
      HAL_Delay(50);
      }HAL_Delay(10);

     GPIOB->ODR&=0x0000;
     GPIOB->ODR|=0x8000;
     key=check_R4();
      if(key!='\0'){
      return key;
      HAL_Delay(50);
      }HAL_Delay(10);
      return '\0';
}

int main(void)
{


	  HAL_Init();
	  SystemClock_Config();
	  MX_GPIO_Init();
	  int i,j,k,sum,sub,mul,N1=0,N2=0;
	  float div;
	  char num1[16]={},sel[]={},num2[16]={},ans[16]={},operation;
	  lcd_init();

	  while(1){
		  begin:
		  i=0;
	// lcd_cmd(0x01);
	 lcd_cmd(0x80);
	  lcd_string("select any one:");
	  lcd_cmd(0xC0);
	  lcd_string(" 1)CALC 2)CONV");
	  while(i==0){
     if(key_Press()!='\0') // for selecting whether you want use calculator or converter
     { 
	  sel[i]=key_Press();
	  HAL_Delay(1000);
       i++;
       lcd_cmd(0x01);
     }
	  }
	  if(sel[0]=='1'){
		  j=0;
		  memset(num1,0,16);
		  lcd_cmd(0x01);
		  lcd_cmd(0x80);
		  lcd_string("Enter 1st number:");
		  HAL_Delay(5000);
		  lcd_cmd(0xC0);
		  while (key_Press() != '#') { // '#' is for the equal sign
		                  if (key_Press() != '\0') {
		                	 if( key_Press() != '#'){
		                      num1[j] = key_Press();
		                      lcd_data(num1[j]);
		                      HAL_Delay(500);
		                      j++;
		                  }}
		              }

		              num1[j] = '\0'; // Terminate the string

		              N1 = atoi(num1);
		              lcd_cmd(0x01);
		              lcd_cmd(0x80);
		              sprintf(ans,"%d",N1);
		              lcd_string(ans);
		              HAL_Delay(2000);
		              lcd_cmd(0x01);
		              lcd_cmd(0x80);
		              lcd_string("Select operation:");
		              lcd_cmd(0xC0);
		              lcd_string("+,-,*,/ ?");

		              while (1) {
		                  if (key_Press() != '\0') {
		                      operation = key_Press();
		                      HAL_Delay(100);
		                      break;
		                  }
		              }
		              memset(num2, 0, sizeof(num2));
		              lcd_cmd(0x01);
		              lcd_cmd(0x80);
		              lcd_string("Enter 2nd Number:");
		              HAL_Delay(100);
		              lcd_cmd(0xC0);
                      j=0;
		              while (key_Press() != '#') // '#' is for the equal sign
		            	  {   

		                  if (key_Press() != '\0' ) {
		                	  if(key_Press() != '#'){
		                      num2[j] = key_Press();
		                      lcd_data(num2[j]);
		                      HAL_Delay(500);
		                      j++;

		                  }}
		              }

		              num2[j] = '\0'; // Terminate the string

		              N2 = atoi(num2); // Convert the string to an integer
		              lcd_cmd(0x01);
		              lcd_cmd(0x80);
		              memset(ans,0,sizeof(ans));
		              sprintf(ans,"%d",N2);
		              lcd_string(ans);
		              HAL_Delay(2000);
		              lcd_cmd(0x01);
		              lcd_cmd(0x80);

		              switch (operation) {
		                  case 'A':              //here 'A' on 4*4 keypad matrix represent '+' sign
		                	  memset(ans,0,16);
		                      sum = N1 + N2;
		                      sprintf(ans, "%d", sum);
		                      lcd_string("SUM=");
		                      lcd_cmd(0xC0);
		                      lcd_string(ans);
		                      while(1){
		                      if(key_Press()=='*') //here '*' on keypad matrix is taken for clear button of calculator 
		                      {
		                    
		                      break;
		                      }}
		                      break;

		                  case 'B':            //here 'B' on 4*4 keypad matrix represent '-' sign
		                	 memset(ans,0,16);
		                	 sub = N1 - N2;
		                     sprintf(ans, "%d", sub);
		                     lcd_string("Subtraction=");
		                     lcd_cmd(0xC0);
		                	 lcd_string(ans);
		                	 while(1){
		                	 if(key_Press()=='*'){
		                	  break;
		                	  }}
		                      break;
		                  case 'C':            //here 'C' on 4*4 keypad matrix represent '*' sign
		                	  memset(ans,0,16);
		                	  mul = N1 * N2;
		                	  sprintf(ans, "%d", mul);
		                	  lcd_string("Multiplication=");
		                	  lcd_cmd(0xC0);
		                	  lcd_string(ans);
		                	  while(1){
		                	  if(key_Press()=='*'){
		                	  break;
		                	  }}
		                      break;
		                  case 'D':
		                	  memset(ans,0,16);
		                	  div = (float)N1 / N2;
		                	  sprintf(ans,"%.3f", div);
		                	  lcd_string("Division=");
		                	  lcd_cmd(0xC0);
		                	  lcd_string(ans);
		                	  while(1){
		                	   if(key_Press()=='*'){
		                	  break;
		                	 	}}
		                      break;
		                  default:
		                      lcd_string("Invalid operation!");
		                      break;
		              }

		              if (key_Press() == '*') {
		                  lcd_cmd(0x01);
		                  goto begin;
		              }
		          }
	  //Code for number converter calculator begin here
		          else if (sel[0] == '2') {
		          int rem,div,res,t;
		          char res1[16];
                  lcd_cmd(0x01);
                  lcd_cmd(0x80);
                  lcd_string("1.Bin-D 2.D-Bin");
                  lcd_cmd(0xC0);
                  lcd_string("3.D-Hex 4.Hex-D");
                  while (1) {
                  		                  if (key_Press() != '\0') {
                  		                      operation = key_Press();
                  		                      HAL_Delay(100);
                  		                      break;
                  		                  }
                  		              }
                  switch (operation) {
                  		                  case '1':// binary to decimal conversion
                  		                	 start:
                  		                    lcd_cmd(0x01);
                  		                    lcd_cmd(0x80);
                  		                    lcd_string("Enter 8 bit No:");
                  		                    lcd_cmd(0xC0);
                  		                     j=0,k=0,res=0;
                  		                  		  memset(num1,0,16);
                  		                          memset(ans,0,16);
                  		                  		  while (key_Press() != '#') { // '#' is for the equal sign
                  		                  		                  if (key_Press() != '\0') {
                  		                  		                	 if( key_Press() != '#'){
                  		                  		                      num1[j] = key_Press();
                  		                  		                      lcd_data(num1[j]);
                  		                  		                      HAL_Delay(500);
                  		                  		                      j++;
                  		                  		                  }}
                  		                  		              }
                  		                  		              num1[j] = '\0'; // Terminate the string

                  		                  		              N1 = atoi(num1);
                  		                  		              lcd_cmd(0x01);
                  		                  		              lcd_cmd(0x80);
                  		                  		              sprintf(ans,"%d",N1);
                  		                  		              lcd_string(ans);
                  		                  		              HAL_Delay(2000);
                  		                              for(k=0;k<8;k++){
                  		                            	 rem=N1%10;
                  		                            	 div=N1/10;
                  		                            	 res=rem*pow(2,k)+res;
                  		                            	 N1=div;
                  		                            	 if(rem<0||rem>1)// In case user enter some other digit rather than 0 and 1 in binary number
                  		                            		 {
                  		                            		 lcd_cmd(0x01);
                  		                            		 lcd_cmd(0x80);
                  		                            		 lcd_string("Invalid Input!");
                  		                            		 HAL_Delay(2000);
                  		                            		 goto start;
                  		                            	 }
                  		                              }
                  		                              memset(ans,0,16);
                  		                              sprintf(ans,"%d",res);
                  		                              lcd_cmd(0x01);
                  		                              lcd_cmd(0x80);
                  		                              lcd_string("The decimal No=");
                  		                              lcd_cmd(0xC0);
                  		                              lcd_string(ans);
                  		                            while(1){
                  		                              if(key_Press()=='*'){
                  		                               break;
                  		                              }}
                  		                      break;

                  		                  case '2':               // Program For Decimal to Binary conversion
                  		                	lcd_cmd(0x01);
                  		                    lcd_cmd(0x80);
                  		                    lcd_string("Enter Decimal No:");
                  		                    lcd_cmd(0xC0);
                  		                    j=0,k=0,res=0;
                  		                   memset(num1,0,16);
                  		                   memset(ans,0,16);
                  		                 while (key_Press() != '#') { // '#' is for the equal sign
                  		                 if (key_Press() != '\0') {
                  		                 if( key_Press() != '#'){
                  		                 num1[j] = key_Press();
                  		                  lcd_data(num1[j]);
                  		                  HAL_Delay(500);
                  		                  j++;
                  		                  }}
                  		                   }
                  		                   num1[j] = '\0'; // Terminate the string

                  		                   N1 = atoi(num1);
                  		                    lcd_cmd(0x01);
                  		                    lcd_cmd(0x80);
                  		                   sprintf(ans,"%d",N1);
                  		                   lcd_string(ans);
                  		                   HAL_Delay(2000);
                  		                   if(N1==0){
                  		                	 lcd_cmd(0x01);
                  		                	 lcd_cmd(0x80);
                  		                	 lcd_string("The binary No=");
                  		                	 lcd_cmd(0xC0);
                  		                	 lcd_string("00000000");
                  		                	while(1){
                  		                	if(key_Press()=='*'){
                  		                	 break;
                  		                	 }}
                  		                   }
                  		                   while(N1>0){
                  		                	   rem=N1%2;
                  		                	   div=N1/2;
                  		                	   res=rem*pow(10,k)+res;
                  		                	   N1=div;
                  		                	   k++;
                  		                   }
                  		                 memset(ans,0,16);
                  		                 sprintf(ans,"%d",res);
                  		                 lcd_cmd(0x01);
                  		                 lcd_cmd(0x80);
                  		                 lcd_string("The binary No=");
                  		                 lcd_cmd(0xC0);
                  		                 lcd_string(ans);
                  		                 while(1){
                  		                 if(key_Press()=='*'){
                  		                    break;
                  		                     }}
                  		                    break;

                  		                  case '3':                       //Program for Decimal to Hexadecimal Conversion
                  		                	lcd_cmd(0x01);
                  		                	lcd_cmd(0x80);
                  		                    lcd_string("Enter Decimal No:");
                  		                	lcd_cmd(0xC0);
                  		                    j=0,k=0,res=0;
                  		                    memset(num1,0,16);
                  		                	memset(ans,0,16);
                  		                	while (key_Press() != '#') { // '#' is for the equal sign
                  		                	if (key_Press() != '\0') {
                  		                	if( key_Press() != '#'){
                  		                	 num1[j] = key_Press();
                  		                	 lcd_data(num1[j]);
                  		                	 HAL_Delay(500);
                  		                	 j++;
                  		                	 }}
                  		                	 }
                  		                	 num1[j] = '\0'; // Terminate the string

                  		                	 N1 = atoi(num1);
                  		                	 lcd_cmd(0x01);
                  		                	 lcd_cmd(0x80);
                  		                	 sprintf(ans,"%d",N1);
                  		                     lcd_string(ans);
                  		                	 HAL_Delay(2000);
                  		                	 while(N1>0){
                  		                		 rem=N1%16;
                  		                		 div=N1/16;
                  		                		 if(rem<10){
                  		                			res1[k]=rem+'0';
                  		                		 }
                  		                		 else{
                  		                			 res1[k]=rem-10+'A';
                  		                		 }
                  		                		N1=div;
                  		                		k++;
                  		                	 }
                  		                	 memset(ans,0,16);
                  		                	 for(k=k-1;k>=0;k--){
                  		                		 ans[k]=res1[k];
                  		                	 }
                  		                	lcd_cmd(0x01);
                  		                    lcd_cmd(0x80);
                  		                    lcd_string("The Hex No=");
                  		                    lcd_cmd(0xC0);
                  		                    for(t=strlen(ans);t>=0;t--){
                  		                    if(ans[t]!='\0'){
                  		                    lcd_data(ans[t]);}
                  		                    }
                  		                  while(1){
                  		                  if(key_Press()=='*'){
                  		                   break;
                  		                     }}
                  		                    break;

                  		                  case '4':  //Program for Hexadecimal to decimal conversion
                                            lcd_cmd(0x01);
                                            lcd_cmd(0x80);
                                            lcd_string("Enter Hex Number");
                                            lcd_cmd(0xC0);
                                             j=0,k=0,res=0;
                                            memset(num1,0,16);
                                            memset(ans,0,16);
                                           while (key_Press() != '#') { // '#' is for the equal sign
                                            if (key_Press() != '\0') {
                                            if( key_Press() != '#'){
                                            num1[j] = key_Press();
                                            lcd_data(num1[j]);
                                            HAL_Delay(500);
                                            j++;
                                            }}
                                             }
                                             num1[j] = '\0'; // Terminate the string

                  		                	 N1 = atoi(num1);
                  		                	 lcd_cmd(0x01);
                  		                	 lcd_cmd(0x80);
                  		                	 sprintf(ans,"%d",N1);
                  		                     lcd_string(ans);
                  		                	 HAL_Delay(2000);
                  		                	 while(N1>0){
                  		                		 rem=N1%10;
                  		                		 div=N1/10;
                  		                		 res=rem*pow(16,k)+res;
                  		                		 N1=div;
                  		                		 k++;
                  		                	 }
                  		                	memset(ans,0,16);
                  		                	sprintf(ans,"%d",res);
                  		                	 lcd_cmd(0x01);
                  		                	lcd_cmd(0x80);
                  		                	 lcd_string("The decimal No=");
                  		                	 lcd_cmd(0xC0);
                  		                	lcd_string(ans);
                  		                	 while(1){
                  		                if(key_Press()=='*'){
                  		                	  break;
                  		                	       }}
                  		                      break;
                  		                  default:
                  		                	lcd_cmd(0x01);
                  		                	lcd_cmd(0x80);
                  		                      lcd_string("Invalid input!");
                  		                      HAL_Delay(2000);
                  		                      break;
                  		              }

		          }
		          else {
		              lcd_string("Invalid input!");
		              HAL_Delay(2000);
		              goto begin;
		          }
		      }

}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 PB12 PB13
                           PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA9 PA10 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
