/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Simone Mannori, Roberto Bucher
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
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/
 
 
# include "scicos_block4.h"
# include "machine.h"
#include <stdio.h>

#if WIN32
#define NULL    0
#endif

//#include <essl.h>
typedef struct FCOMPLEX {double r,i;} fcomplex;
extern int C2F(zgetrf)();
typedef struct
{         int *ipiv;
          double *wrk;
} mat_det_struct ;
void matz_det(scicos_block *block,int flag)
{
 double *ur;
 double *yr;
 double *ui;
 double *yi;
 int nu;
 int info;
 int i;
 fcomplex D,l;
 double A;
 mat_det_struct *mdet;
 
 nu =GetInPortRows(block,1);
 ur=GetRealInPortPtrs(block,1);
 ui=GetImagInPortPtrs(block,1);
 yr=GetRealOutPortPtrs(block,1);
 yi=GetImagOutPortPtrs(block,1);
             /*init : initialization*/
if (flag==4)

   {if((*(block->work)=(mat_det_struct*) scicos_malloc(sizeof(mat_det_struct)))==NULL)
	{set_block_error(-16);
	 return;}
    mdet=*(block->work);
    if((mdet->ipiv=(int*) scicos_malloc(sizeof(int)*nu))==NULL)
	{set_block_error(-16);
	 scicos_free(mdet);
	 return;}
    if((mdet->wrk=(double*) scicos_malloc(sizeof(double)*(2*nu*nu)))==NULL)
	{set_block_error(-16);
	 scicos_free(mdet->ipiv);
	 scicos_free(mdet);
	 return;}
    }

       /* Terminaison */
else if (flag==5)
   {mdet=*(block->work);
    if(mdet->wrk!=NULL) {
	scicos_free(mdet->ipiv);
    	scicos_free(mdet->wrk);
    	scicos_free(mdet);
    	return;}
   }

else
   {
    mdet=*(block->work);
    for (i=0;i<(nu*nu);i++)
	{mdet->wrk[2*i]=ur[i];
	mdet->wrk[2*i+1]=ui[i];}
     C2F(zgetrf)(&nu,&nu,mdet->wrk,&nu,mdet->ipiv,&info);
    if (info !=0)
       {if (flag!=6)
    	{set_block_error(-7);
        return;}}
      D.r=1;
      D.i=0;
    for (i=0;i<nu;i++)
       {if((*(mdet->ipiv+i))!=i+1) {D.r=-D.r;D.i=-D.i;}
        l.r=*(mdet->wrk+i*2*(nu+1));
	l.i=*(mdet->wrk+1+i*2*(nu+1));
	A=D.r;
	D.r=D.r*l.r-D.i*l.i;
	D.i=D.i*l.r+A*l.i;
        };
     *yr=D.r;
     *yi=D.i;
    }
 }
