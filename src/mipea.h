/*
 * mipea.h
 * Copyright (C) 2018  jasLogic
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

 #ifndef _MIPEA_H_
 #define _MIPEA_H_

#include "dma.h"
#include "gpio.h"
#include "i2c.h"
#include "pwm.h"
#include "spi.h"
#include "timer.h"

 #ifdef __cplusplus
 extern "C" {
 #endif//__cplusplus

int     mipea_map(void);
void    mipea_unmap(void);

 #ifdef __cplusplus
 }
 #endif//__cplusplus

 #endif//MIPEA_H_
