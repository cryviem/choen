# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2013  Evidence Srl
# 
# This file is part of ERIKA Enterprise.
# 
# ERIKA Enterprise is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation, 
# (with a special exception described below).
# 
# Linking this code statically or dynamically with other modules is
# making a combined work based on this code.  Thus, the terms and
# conditions of the GNU General Public License cover the whole
# combination.
# 
# As a special exception, the copyright holders of this library give you
# permission to link this code with independent modules to produce an
# executable, regardless of the license terms of these independent
# modules, and to copy and distribute the resulting executable under
# terms of your choice, provided that you also meet, for each linked
# independent module, the terms and conditions of the license of that
# module.  An independent module is a module which is not derived from
# or based on this library.  If you modify this code, you may extend
# this exception to your version of the code, but you are not
# obligated to do so.  If you do not wish to do so, delete this
# exception statement from your version.
# 
# ERIKA Enterprise is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License version 2 for more details.
# 
# You should have received a copy of the GNU General Public License
# version 2 along with ERIKA Enterprise; if not, write to the
# Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301 USA.
# ###*E*###

##
## Author: 2013 Mauro Marinoni
##

ifeq ($(call iseeopt, __ATMEL_SAM3__), yes)

EEOPT += SAM3

# Provide a default crt0, but don't overwrite it if it's been already defined
# (by the board)
ifndef CRT0_SRCS

# MM: ToDo
#ifeq ($(call iseeopt, __KEIL__), yes)
#CRT0_SRCS = pkg/mcu/atmel_sam3/src/startup_sam3xa_keil.s
#endif	# __KEIL__

ifeq ($(call iseeopt, __GNU__), yes)
CRT0_SRCS = pkg/mcu/atmel_sam3/src/startup_sam3xa_gnu.S
#CRT0_SRCS = pkg/mcu/atmel_sam3/src/startup_sam3xa.c
endif	# __GNU__

endif	# !CRT0_SRCS


ifeq ($(call iseeopt, __SAM3X8E__), yes)
SRCS += pkg/mcu/atmel_sam3/src/system_sam3xa.c
endif	# __SAM3X8E__

endif	# __ATMEL_SAM3__
