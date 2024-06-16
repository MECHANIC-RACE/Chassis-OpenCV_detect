/*
 * @Author: X311
 * @Date: 2024-05-13 09:00:14
 * @LastEditors: doge60 3020118317@qq.com
 * @LastEditTime: 2024-06-16 23:57:27
 * @FilePath: \Gantry\UserCode\Upper\Upper_Start\UpperStart.c
 * @Brief: 
 * 
 * Copyright (c) 2024 by X311, All Rights Reserved. 
 */
#include "UpperStart.h"

/**
 * @brief 默认任务，启动其他线程
 *
 * @param argument
 */
void StartDefaultTask(void *argument)
{
    /*** 接受树莓派串口初始化 ***/
    Upper_Target_Init();

    osDelay(1000);
    Target_Decode_TaskStart();
    while (Uart_State != 2) {
        ; // 若未收到上位机数据则一直循环
    }
    
    // weight_placement[0]=1;
    // weight_placement[1]=1;

    /*串口使能*/
    Gantry_usart_init();

    /*初始化函数*/
    // Upper_StateMachine_Init_01();
    // Upper_StateMachine_Init_02();
    // Upper_Motor_init();

    HAL_GPIO_WritePin(cylinder_03_GPIO_Port, cylinder_03_Pin, GPIO_PIN_SET);   //  SET 气缸抬升
    HAL_GPIO_WritePin(cylinder_04_GPIO_Port, cylinder_04_Pin, GPIO_PIN_SET);   //  SET 气缸抬升
    HAL_GPIO_WritePin(electromagnet_03_GPIO_Port, electromagnet_03_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(electromagnet_04_GPIO_Port, electromagnet_04_Pin, GPIO_PIN_SET);
    osDelay(1000);
    /*开启线程*/
    // Upper_Decode_TaskStart();
    // Upper_StateMachine_TaskStart_01();
    // Upper_StateMachine_TaskStart_02();
    // Upper_Servo_TaskStart();
    Upper_Debug_TaskStart();
    //Target_Decode_TaskStart();

    for (;;) {
        HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
        osDelay(800);
    }
}