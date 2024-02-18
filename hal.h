/*
 * hal.h
 *
 *  Created on: Feb 18, 2024
 *      Author: nick
 */

#ifndef HAL_H_
#define HAL_H_

#include <stdio.h>

void HAL_Init();

extern FILE *scia;
extern FILE *scib;

#define SCPI_SCI scib
#define DBG_SCI scia

#endif /* HAL_H_ */
