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
 
 
#include "scicos_block4.h"
# include "machine.h"

/* A swithcing mechansim for building hybrid automata */
/* Masoud Najafi, 2007, INRIA */

void automat(scicos_block *block,int flag)
{
  double * y0, *y1, *ui;
  double* g=block->g;
  double* x=block->x;
  double* xd=block->xd;
  double* res=block->res; 
  void**   work=block->work;
  double* rpar=block->rpar;
  double* evout=block->evout;

  int* ipar=block->ipar;
  int* jroot=block->jroot;
  int  nevprt=block->nevprt;
  int* insz=block->insz;
  int ng=block->ng;

  int* Mode;
  int  NMode, NX, Minitial,i,j,k,Mi,Mf,indice;
  int* property;
  int* iparXp;
  int* iparCx;
  double* rparX0;
  int test;
  NMode=ipar[0];
  Minitial=ipar[1];
  NX=ipar[2];
  iparXp=ipar+3;
  iparCx=iparXp+NX*NMode;
  rparX0=rpar;


  if (flag ==4){/*----------------------------------------------------------*/
    if ((*work=scicos_malloc(sizeof(int)*(2+NX)))== NULL ) {set_block_error(-16); return; }
    Mode=*work;
    property=Mode+2;
    Mode[0]=Minitial;/*Current Mode;*/
    Mode[1]=Minitial;/* Previous Mode*/
    for (i=0;i<NX;i++) property[i]=0; /* xproperties*/
    for (i=0;i<NX;i++) x[i]=rparX0[i];

  }else if (flag ==5){/**----------------------------------------------------------*/
    scicos_free(*work);
  }else if  (flag ==1 || flag ==6){/*----------------------------------------------------------*/
    y0=GetRealOutPortPtrs(block,1);
    y1=GetRealOutPortPtrs(block,2);

    Mode=*work;
    Mi=Mode[0];
    y0[0]=Mi;/*current Mode*/
    y0[1]=Mode[1];/*prevous Mode*/
    for (i=0;i<NX;i++){
      y1[i]=x[i];
      y1[i+NX]=xd[i];
    }
  }else if (flag==0){ /*----------------------------------------------------------*/
    Mode=*work;
    Mi=Mode[0];
    ui=GetRealInPortPtrs(block,Mi);
    for (i=0;i<NX;i++)
      res[i]= ui[i];

  }else if (flag==7){/*----------------------------------------------------------*/
    Mode=*work;
    property=Mode+2;
    Mi=Mode[0];
    for (i=0;i<NX;i++)
      property[i] = iparXp[(Mi-1)*NX+i];

    set_pointer_xproperty(property);
  }else if (flag==9){/*----------------------------------------------------------*/
    Mode=*work;
    Mi=Mode[0];
    ui=GetRealInPortPtrs(block,Mi);

    for (j=0;j<ng;j++) g[j]=0;
    for (j=0;j<insz[Mi-1]-2*NX;j++) {
      g[j]=ui[j+2*NX];
      }

  }else if ((flag==3)&&(nevprt<0)){
    Mode=*work;
    Mi=Mode[0];
    indice=0;
    for (i=1;i<Mi;i++)  
      indice+=insz[i-1]-2*NX; /*number of modes before Mi_th Mode */
    for (k=0;k<insz[Mi-1]-2*NX;k++)
      if(jroot[k]==1){
	evout[0]=0.0;
	break;
      }
  }else if ((flag==2)&&(nevprt<0)){/*----------------------------------------------------------*/
    Mode=*work;
    Mi=Mode[0];
    indice=0;
    Mf=Mi;/* in case where the user has defined a wrong mode destination or ZC direction.*/
    for (i=1;i<Mi;i++)  
      indice+=insz[i-1]-2*NX; /*number of modes before Mi_th Mode*/
    test=0;
    for (k=0;k<insz[Mi-1]-2*NX;k++){
      if(jroot[k]==1){
	Mf=iparCx[indice+k]; 
	Mode[0]=Mf;/* saving the new Mode*/
	Mode[1]=Mi;/* saving the previous Mode*/
	test=1;
	break;
      }
    }
    if (test==0){
      for (k=0;k<insz[Mi-1]-2*NX;k++) if(jroot[k]==-1) break;
      /*      sciprint("\n\r Warning!: In Mode=%d, the jump condition #%d has crossed zero in negative dierction",Mi,k+1); */
    }
    ui=GetRealInPortPtrs(block,Mf);
    for (i=0;i<NX;i++)
      x[i]=ui[i+NX]; /*reinitialize the states*/    
  }
}

