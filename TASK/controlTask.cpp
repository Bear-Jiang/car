#include "controlTask.h"
#include "stdlib.h"

static Led_t led;
static Gimbal_t gimbal(1000,1950);
static Motor_t motor;

float f_b_speed = 0;
float l_r_speed = 0;

void controlTask(void* arg)
{
    led.init();
    gimbal.init();
    motor.init();
    
    for(;;)
    {
        motor.getSpeedCount();
        motor.setSpeed(-f_b_speed - l_r_speed, f_b_speed - l_r_speed);
        vTaskDelay(500);
    }
}

/*********************************Call back************************************/
void unpackControlData(uint8_t* p)
{
    f_b_speed = (p[0] - p[1]) * 1990;
    l_r_speed = (p[2] - p[3]) * 1990;
}

void unpackLedData(uint8_t* p)
{
    for(uint8_t i=0; i<3; i++)
    {
        led.setIntensity(i, p[i]*400);
    }
}

void unpackGimbalData(uint8_t* p)
{
    gimbal.setYaw(p[0]);
    gimbal.setPitch(p[1]);
}

/*********************************For gimbal***********************************/
Gimbal_t::Gimbal_t(uint16_t yaw, uint16_t pitch)
:yaw_mid(yaw), pitch_zero(pitch)
{   
}
    
void Gimbal_t::init()
{
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, pitch_zero);//Pitch
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, yaw_mid);//Yaw
}

void Gimbal_t::setPitch(uint8_t v)//0--100
{
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, pitch_zero - v * 10);
}

void Gimbal_t::setYaw(uint8_t v)//0--100
{
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, yaw_mid + (v - 50) * 10);
}

/*********************************For led**************************************/
Led_t::Led_t()
{
}
    
void Led_t::init()
{
    for(uint8_t i=0; i<3; i++)
    {
        led.setIntensity(i, 0);
    }
}

void Led_t::setIntensity(uint8_t id, uint16_t value)
{
    value = value>=2000?2000:value;
    if(id == 0)//Ç°
    {
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, value);
    }
    else if(id == 1)//ÉÏ
    {
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, value);
    }
    else if(id == 2)//ºó
    {
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, value);
    }
}

/*********************************For motor************************************/
Motor_t::Motor_t()
{
    r_speed = 0;
    l_speed = 0;
}

void Motor_t::init()
{
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//L_PWM
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);//R_PWM
}
    
void Motor_t::getSpeedCount()
{
    r_speed = r_count;
    l_speed = l_count;
    r_count = 0;
    l_count = 0;
}

void Motor_t::setSpeed(float left, float right)
{   
    if(left >= 0)
    {
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
        left*=-1;
    }
    
    if(right >= 0)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
        right*=-1;
    }
    
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, (uint16_t)left);//L_PWM
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (uint16_t)right);//R_PWM
}

/******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
void EXTI15_10_IRQHandler(void);
#ifdef __cplusplus
}
#endif

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_10)
    {
        motor.l_count += 1;
    }
    else if(GPIO_Pin == GPIO_PIN_11)
    {
        motor.r_count += 1;
    }
}

/**
* @brief This function handles EXTI line[15:10] interrupts.
*/
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
}



