/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/**
    
**/

#ifndef __INCLUDE_R7F701503_CLOCK_H__
#define __INCLUDE_R7F701503_CLOCK_H__

#if defined __CRYSTAL8__
#define GAIN 0x07
#define Pll0cValue 0x6300023B
#define Pll1cValue 0x00000227

#elif defined __CRYSTAL16__
#define GAIN 0x6
#define Pll0cValue 0x63000A3B
#define Pll1cValue 0x00000A27

#elif defined __CRYSTAL24__
#define GAIN 0x4
#define Pll0cValue 0x6300123B
#define Pll1cValue 0x00001227
#else
#error no valid crystal speed. valid values are: 8 16 24
#endif

void EE_rh850_clock_init(void);


#endif /* __INCLUDE_R7F701503_CLOCK_H__ */

