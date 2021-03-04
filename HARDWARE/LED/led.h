#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//≥ı ºªØ
void LED_Init(void);
#define LED     PBout(0)
#define PWRKEY  PAout(0)
#endif
