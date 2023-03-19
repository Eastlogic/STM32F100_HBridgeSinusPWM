#ifndef USER_H_
#define USER_H_


// ---------- Выводы ключей Н-моста --------------------
// 

// 1-я транзисторная стойка моста
// PA8  -> Upper Transistor, Left Side
// PB13 -> Lower Transistor, Left Side

#define			T1H_Pin						GPIO_Pin_8
#define			T1H_Port					GPIOA

#define			T1L_Pin						GPIO_Pin_13
#define			T1L_Port					GPIOB

// 2-я транзисторная стойка моста
// PA9  -> Upper Transistor, Right Side
// PB14 -> Lower Transistor, Right Side

#define			T2H_Pin						GPIO_Pin_9
#define			T2H_Port					GPIOA

#define			T2L_Pin						GPIO_Pin_14
#define			T2L_Port					GPIOB


// -- System clocks init -------------------------------
void RCC_init(void);

// -- GPIOs init ---------------------------------------
void GPIO_init(void);

// -- TIM1 init ----------------------------------------
void TIM1_init(void);

// -- DMA init -----------------------------------------
void DMA1_init(void);

// -- NVIC init ----------------------------------------
void NVIC_init(void);



#endif
