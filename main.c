#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define SIG_LENGTH 320

extern void SystemClock_Config(void);
extern void Error_Handler(void);
void plot_input_signal(void);

extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LENGTH];
uint32_t freq;
float32_t inputSample;

int main(void)
{
	int i;
	
	HAL_Init();
	SystemClock_Config();
	
	freq = HAL_RCC_GetHCLKFreq();
	
	plot_input_signal();
	
	while(1)
	{

	}
}

void plot_input_signal(void)
{
	int i,j;
	
	for(i=0; i<SIG_LENGTH; i++)
	{
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		//add delay to prevent crush of logic analyzer
		for(j=0;j<3000;j++){}
		
	}
}
	
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
