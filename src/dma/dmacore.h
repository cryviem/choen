#ifndef _DMACORE_H_
#define _DMACORE_H_

#include "common_inc.h"

/* DMA status flag definition */
#define DMA_FLAG_TransferComplete								((uint32_t) 0x00000020)
#define DMA_FLAG_TransferHalfComplete							((uint32_t) 0x00000010)
#define DMA_FLAG_TransferError									((uint32_t) 0x00000008)
#define DMA_FLAG_DirectModeError								((uint32_t) 0x00000004)
#define DMA_FLAG_FIFOError										((uint32_t) 0x00000001)

#define DMA_SR_MASK												((uint32_t) 0x0000003D)

/* DMA control bit definition begin*/

/* 
	 Bits: CHSEL[25:27]
	 _CHNNL_ should only get value from 0 - 7 
*/
#define DMA_CR_ChannelSelect(_BASE_, _CHNNL_)									\
do{																				\
	_BASE_->CR &= 0xF1FFFFFF;													\
	_BASE_->CR |= ((((uint32_t)_CHNNL_) & 0x00000007) << 25);					\
}while(0)																														

/* 
	 Bits: MBURST[23:24]
*/
#define DMA_CR_MBURST_SINGLE													0x00
#define DMA_CR_MBURST_4BEAT														0x01
#define DMA_CR_MBURST_8BEAT														0x02
#define DMA_CR_MBURST_16BEAT													0x03

#define DMA_CR_MBURST_Cfg(_BASE_, _MBSRT_)										\
do{																				\
	_BASE_->CR &= 0xFE7FFFFF;													\
	_BASE_->CR |= ((((uint32_t)_MBSRT_) & 0x00000003) << 23);					\
}while(0)																														

/* 
	 Bits: PBURST[21:22]
*/
#define DMA_CR_PBURST_SINGLE													0x00
#define DMA_CR_PBURST_4BEAT														0x01
#define DMA_CR_PBURST_8BEAT														0x02
#define DMA_CR_PBURST_16BEAT													0x03

#define DMA_CR_PBURST_Cfg(_BASE_, _PBSRT_)										\
do{																				\
	_BASE_->CR &= 0xFF9FFFFF;													\
	_BASE_->CR |= ((((uint32_t)_PBSRT_) & 0x00000003) << 21);					\
}while(0)	

/* 
	 Bits: CT[19]
	- apply for doulbe buffer mode only
	- sw can only write when EN is 0 to indicate which buffer is used first.
	- when EN is 1, this bit become status flag (set and reset by hw).
*/
#define DMA_CR_CurrentTargetFlag												((uint32_t)0x00080000)

/* 
	 Bits: DBM[18]
	- enable/disable doule buffer mode.
	- 
	- 
*/
#define DMA_CR_DoubleBufferModeSwitch											((uint32_t)0x00040000)

/* 
	 Bits: PL[16:17]
	- Priority Level
*/
#define DMA_CR_Priority_Low														0x00
#define DMA_CR_Priority_Medium													0x01
#define DMA_CR_Priority_High													0x02
#define DMA_CR_Priority_VeryHigh												0x03

#define DMA_CR_Priority_Cfg(_BASE_, _PL_)										\
do{																				\
	_BASE_->CR &= 0xFFFCFFFF;													\
	_BASE_->CR |= ((((uint32_t)_PL_) & 0x00000003) << 16);						\
}while(0)	

/* 
	 Bits: PINCOS[15]
	- increament step configure: depend on PSIZE or fixed as 4 (32bits alignment)
	- no meaning if PINC = 0
	- forced to 0 when EN is 1 if: direct mode is used or PBURST is different from 0.
	- NOTED: need to check the role of this bit? 
*/
#define DMA_CR_PINCOS															((uint32_t)0x00008000)

/* 
	 Bits: MSIZE[13:14]
	- Memory Data Size
	- In direct mode, MSIZE will be forced by hw to the same value as PSIZE as soon as EN is 1
	- NOTED: value 0x03 is reserved, check the input value must be not 0x03.
*/
#define DMA_CR_MSIZE_8Bit														0x00
#define DMA_CR_MSIZE_16Bit														0x01
#define DMA_CR_MSIZE_32Bit														0x02

#define DMA_CR_MSIZE_Cfg(_BASE_, _MSIZE_)										\
do{																				\
	_BASE_->CR &= 0xFFFF9FFF;													\
	_BASE_->CR |= ((((uint32_t)_MSIZE_) & 0x00000003) << 13);					\
}while(0)	

/* 
	 Bits: PSIZE[11:12]
	- Peripheral Data Size
	- NOTED: value 0x03 is reserved, check the input value must be not 0x03.
*/
#define DMA_CR_PSIZE_8Bit														0x00
#define DMA_CR_PSIZE_16Bit														0x01
#define DMA_CR_PSIZE_32Bit														0x02

#define DMA_CR_PSIZE_Cfg(_BASE_, _PSIZE_)										\
do{																				\
	_BASE_->CR &= 0xFFFFE7FF;													\
	_BASE_->CR |= ((((uint32_t)_PSIZE_) & 0x00000003) << 11);					\
}while(0)	

/* 
	 Bits: MINC[10]
	- enable/disable memory address pointer increament after each data transfer.
	- increament step is based on MSIZE.
	- NOTED: check if PINCOS; burst mode affects to increament step? 
*/
#define DMA_CR_MemPtrIncSupport													((uint32_t)0x00000400)

/* 
	 Bits: PINC[9]
	- enable/disable peripheral address pointer increament after each data transfer.
	- increament step is based on PSIZE.
	- NOTED: check if PINCOS; burst mode affects to increament step? 
*/
#define DMA_CR_PeriphPtrIncSupport												((uint32_t)0x00000200)

/* 
	 Bits: CIRC[8]
	- enable/disable circular mode.
	- forced to 0 when EN is 1 if peripheral is flow control (PFCTRL = 1).
	- forced to 1 when EN is 1 if double buffer is used (DBM = 1). 
*/
#define DMA_CR_CircularModeSupport												((uint32_t)0x00000100)

/* 
	 Bits: DIR[6:7]
	- Data Transfer Direction
	- NOTED: value 0x03 is reserved, check the input value must be not 0x03.
*/
#define DMA_CR_DIR_Periph2Mem													0x00
#define DMA_CR_DIR_Mem2Periph													0x01
#define DMA_CR_DIR_Mem2Mem														0x02

#define DMA_CR_Direction_Cfg(_BASE_, _DIR_)										\
do{																				\
	_BASE_->CR &= 0xFFFFFF3F;													\
	_BASE_->CR |= ((((uint32_t)_DIR_) & 0x00000003) << 6);						\
}while(0)	

/* 
	 Bits: PFCTRL[5]
	- determine who is flow control of transaction.
	- 0 DMA is flow control.
	- 1 the peripheral is flow control.
	- forced to 0 if memory-memory is used (DIR = 2). 
*/
#define DMA_CR_PeriphFlowControl												((uint32_t)0x00000020)

/* 
Bits: TCIE-HTIE-TEIE-DMEIE[1:4]
	- group of interrupt enable/disable switch.
	- NOTED: should disable. 
*/
#define DMA_CR_IntEn_TransferComplete											((uint32_t)0x00000010)
#define DMA_CR_IntEn_HaflTransferred											((uint32_t)0x00000008)
#define DMA_CR_IntEn_TransferError												((uint32_t)0x00000004)
#define DMA_CR_IntEn_DirectModeError											((uint32_t)0x00000002)

/* 
	 Bits: EN[0]
	- enable/disable a stream.
	- can be cleared by hw in cases of: 
	- 	> On a DMA end of transfer.
	-		> If transfer error 
	-		> If FIFO threshold on memory AHB port is not compatible with size of burst.
	- NOTED: before setting EN to 1, status flags in LISR and HISR must be cleared by sw. 
	- Test: NotCovered.
*/
#define DMA_CR_StreamEnable														((uint32_t)0x00000001)
#define ClearAndWaitUntilENCleared(_BASE_)										\
{_BASE_->CR &= ~DMA_CR_StreamEnable;											\
while(_BASE_->CR & DMA_CR_StreamEnable);}	

/* DMA control bit definition end*/

/* DMA FIFO control bit definition begin*/
/* 
	 Bits: FEIE[7]
	- enable/disable interrupt on FIFO error.
*/
#define DMA_FCR_IntEn_FIFOError													((uint32_t)0x00000080)

/* 
	 Bits: DMDIS[2]
	- Direct mode disable.
*/
#define DMA_FCR_DirectModeDisable												((uint32_t)0x00000004)

/* 
	 Bits: FTH[0:1]
	- FIFO threshold selection
	- NOTED: threshold much be chosen bigger than MSIZE*MBURST.
	- 1 burst can choose 4 - 8 - 16 beats.
	- 1 beats is 1 data size: byte - hafl word - word. 
*/
#define DMA_FCR_1_of_4_FIFO														0x00
#define DMA_FCR_1_of_2_FIFO														0x01
#define DMA_FCR_3_of_4_FIFO														0x02
#define DMA_FCR_Full_FIFO														0x03

#define DMA_FCR_FIFO_Threshold_Cfg(_BASE_, _FTH_)								\
do{																				\
	_BASE_->FCR &= 0xFFFFFFFC;													\
	_BASE_->FCR |= (((uint32_t)_FTH_) & 0x00000003);							\
}while(0)	

/* DMA FIFO control bit definition end*/

/* further configured values definition */
/* dma_StreamCfgST->transfertype */
#define	DMA_TRANSTYPE_DIRECT													0x00
#define	DMA_TRANSTYPE_BURST														0x01

/* dma_StreamCfgST->addrincrement */
#define	DMA_ADDRINC_AllFixed													0x00
#define	DMA_ADDRINC_AllInc														0x01
#define	DMA_ADDRINC_PeriphFixedMemInc											0x02
#define	DMA_ADDRINC_PeriphIncMemFixed											0x03


typedef enum {
	DMA1_STREAM_0,
	DMA1_STREAM_1,
	DMA1_STREAM_2,
	DMA1_STREAM_3,
	DMA1_STREAM_4,
	DMA1_STREAM_5,
	DMA1_STREAM_6,
	DMA1_STREAM_7,
	DMA2_STREAM_0,
	DMA2_STREAM_1,
	DMA2_STREAM_2,
	DMA2_STREAM_3,
	DMA2_STREAM_4,
	DMA2_STREAM_5,
	DMA2_STREAM_6,
	DMA2_STREAM_7,
	DMA_ENDFLAG
} dma_StreamEN;

typedef enum {
	DMA_Status_NotStarted,
	DMA_Status_Triggered,
	DMA_Status_InProcess,
	DMA_Status_Error,
	DMA_Status_Completed,
} dma_StatusEN;

typedef struct {
	DMA_TypeDef* status;
	uint8_t	offset;	
	DMA_Stream_TypeDef* control;
} dma_StreamRegST;

typedef struct {
	dma_StreamRegST					reg;
	volatile dma_StatusEN			state;
} dma_StreamHandlerST;

typedef struct {
	dma_StreamEN		streamid;
	uint8_t				channelid;
	uint8_t				circularenable;
	uint8_t				transfertype;
	uint8_t				priority;
	uint8_t				direction;
	uint8_t				periphsize;
	uint8_t				memsize;
	uint8_t				addrincrement;
	uint32_t			periphaddress;
	uint32_t			mem0address;
	uint32_t			mem1address;
	
} dma_StreamCfgST;



void dmacore_updatestatus_cycle5ms(dma_StreamHandlerST* streamhler);
dma_StatusEN dmacore_getstreamstatus(dma_StreamHandlerST* streamhler);
RetType dmacore_starttransfer(dma_StreamHandlerST* streamhler, uint32_t memadr, uint16_t	size);
void dmacore_finishjob(dma_StreamHandlerST* streamhler);
void dmacore_forcestop(dma_StreamHandlerST* streamhler);
void dmacore_reset(dma_StreamHandlerST* streamhler);
void dmacore_init(const dma_StreamCfgST* dma_cfgtable, dma_StreamHandlerST* streamhlertb, uint16_t numOfInst);
#endif /* _DMACORE_H_ */
