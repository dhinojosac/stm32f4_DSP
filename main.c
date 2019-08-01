#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define SIG_LENGTH 320
#define NUM_TAPS   29		//TAPS for FIR filter
#define BLOCK_SIZE 32

extern void SystemClock_Config(void);
extern void Error_Handler(void);
void plot_input_signal(void);

extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LENGTH];
uint32_t freq;
float32_t inputSample;

float32_t outputSignal[SIG_LENGTH];
static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];

//FIR filter coefficients (low pass)
const float32_t firCoeffs32[NUM_TAPS] = {
  -0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f, +0.0085302217f, -0.0000000000f, -0.0173976984f,
  -0.0341458607f, -0.0333591565f, +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f, +0.2229246956f,
  +0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f, -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f,
  +0.0080754303f, +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
};

int main(void)
{
	int i;
	
	HAL_Init();
	SystemClock_Config();
	
	arm_fir_instance_f32 _1kHz_15kHz_sig;
	
	arm_fir_init_f32(&_1kHz_15kHz_sig, NUM_TAPS,(float32_t *)&firCoeffs32, &firStateF32[0], BLOCK_SIZE);

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
		for(j=0;j<30000;j++){}
			if(i==(SIG_LENGTH-1)) i=0; // restart signal
	}
}
	
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
