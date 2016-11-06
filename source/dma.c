/***************************************************************************
*
*  	Filename: dma.c
*	Description: DMA initialization and basic functions/interrupts
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/

/* Included libraries */
#include "dma.h"

// enable/disable DMAMUX CFG
void dmamux_en(uint8_t enable)
{
    if(enable)
    	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;
    else
    	DMAMUX0_CHCFG0 = 0x00;
}

// Check for errors and done bit.  
// Return 1 when done bit is set and all errors accounted for.
void dma_status()
{
    // Clear errors or done bit out of Byte Count Register (DMA_DSR_BCRn) (if any)
    if(/* Bit30 Config Err          */ ((DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK  ) == DMA_DSR_BCR_CE_MASK  )
       |/*Bit29 Bus error on source */ ((DMA_DSR_BCR0 & DMA_DSR_BCR_BES_MASK ) == DMA_DSR_BCR_BES_MASK )
       |/*Bit28 Bus error on dest   */ ((DMA_DSR_BCR0 & DMA_DSR_BCR_BED_MASK ) == DMA_DSR_BCR_BED_MASK )
       |/*Bit24 Transaction done    */ ((DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK) == DMA_DSR_BCR_DONE_MASK) )
    {
	
        // except during init, this should be used in an interrupt service routine to clear the DMA interrupt and error bits   
    	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK; //0x1000000u (24th bit) //setting done bit resets the status bits
    }

}

void dma_init() 
{
    //Enable DMA0_IRQInterrupt
    //enable_irq(INT_DMA0 -16);
	NVIC_EnableIRQ(DMA0_IRQn);

    // Enable DMAMUX AND DMA Clocks
    SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK; //0x2u
    SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;    //0x100u
    
    //Disable DMAMUX before configuring
    dmamux_en(DMAMUX_DISABLE);

    // Important first step for DMA -- if has errors or the done bit is not set, then may have problems writing DMA registers
    dma_clear_status(DMA_INIT);

    //Clear source/destination size fields
    DMA_DCR0 &= ~(DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK);

    //Set DMA_DCR0 fields
    DMA_DCR0 |= (/*  Bit31    Enable interrupt for error or done condition    */ DMA_DCR_EINT_MASK
		 //|/*Bit30    Enable peripheral request                        */ DMA_DCR_ERQ_MASK
		 //|/*Bit29    Cycle Steal                                      */ DMA_DCR_CS_MASK
		 //|/*Bit28    Auto Align                                       */ DMA_DCR_AA_MASK
		 /*Bit27-24   Reserved                            	      */ 
		 //|/*Bit23    Enable Async DMA Requests OFF                    */ DMA_DCR_EADREQ_MASK
		 |/*Bit22    Enable Source Increments by transfer size        */ DMA_DCR_SINC_MASK
		 |/*Bit21-20 Source Size (00b-32,01b-8,10b-16,11b-ERROR)      */ DMA_DCR_SSIZE(0)
		 |/*Bit19    Enable Destination Increments by transfer size   */ DMA_DCR_DINC_MASK
		 |/*Bit18-17 Destination Size (00b-32,01b-8,10b-16,11b-ERROR) */ DMA_DCR_DSIZE(0)
		 //|/*Bit16    Start Transfer                                   */ DMA_DCR_START_MASK
		 //|/*Bit15-12 Source address modulo (disabled if 0000)         */ DMA_DCR_SMOD_MASK
		 //|/*Bit11-8  Destination address modulo (disabled if 0000)    */ DMA_DCR_DMOD_MASK
		 //|/*Bit7     Disable Request (ERQ bit is cleared when BCR is 0*/ DMA_DCR_D_REQ_MASK
		 /*Bit6       Reserved                                        */ 
		 //|/*Bit5-4   Link channel Control (00 no channel2channel      */ DMA_DCR_LINKCC_MASK
		 //|/*Bit3-2   Link channel 1 - cannot be current channel       */ DMA_DCR_LCH1_MASK
		 //|/*Bit1-0   Link channel 2 - cannot be current channel       */ DMA_DCR_LCH2_MASK
	); //1000_0000_0100_1000_0000_0000_0000_0000 = 0x80480000 32bit src/dest transfer with increment
    
    
    //Enable DMAMUX after configuring
    dmamux_en(DMAMUX_ENABLE);
}


//DMA writes and reads
uint8_t dma_transfer(uint8_t * src, uint8_t * dst, uint32_t byte_length)
{    
    if(byte_length/4 > 0)
    {
    	uint32_t word_length = byte_length/4;
    	//split dma request in terms of words and bytes
    	dma_word(src, dst, word_length);
		if(byte_length%4 > 0) {
			uint8_t * new_src = src+word_length*4;
			uint8_t * new_dst = dst+word_length*4;
			dma_byte(new_src,new_dst,byte_length - word_length*4); //leftover bytes (between 1 and 3)
		}
    }

    return 0;
}

//Run DMA in byte mode
uint8_t dma_byte(uint8_t * src, uint8_t * dst, uint32_t byte_length)
{

    //Disable DMAMUX before configuring
    dmamux_en(DMAMUX_DISABLE);

    // Set source and destination address (will be changed during dma_cmd function)
    /* DMA_SAR0 - source, DMA_DAR0 - destination*/
    // only 32 bit writes are allowed, 16 and 8 bit writes result in a bus error
    // bits 31-20 must be written with 0x000x_xxxx, 0x1FFx_xxxx, 0x200x_xxxx, or 0x400x_xxxx or a Config err occurs
    DMA_SAR0 = (uint32_t)src;
    DMA_DAR0 = (uint32_t)dst;
    
    dma_set_bcr_length(byte_length);

    //Clear source/destination size fields
    //DMA_DCR0 &= ~(DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK);
    DMA_DCR0 |= (/* Bit21-20 Source Size (00b-32,01b-8,10b-16,11b-ERROR)      */ DMA_DCR_SSIZE(1)
		 |/*Bit18-17 Destination Size (00b-32,01b-8,10b-16,11b-ERROR) */ DMA_DCR_DSIZE(1)
	);

    //Enable DMAMUX after configuring
    dmamux_en(DMAMUX_ENABLE);

    //Start DMA Transfer
    DMA_DCR0 |= /*Bit16    Start Transfer*/ DMA_DCR_START_MASK;

    // Check for dma done
    dma_clear_status(0);

    return 0;
}


//Run DMA in word mode
uint8_t dma_word(uint8_t * src, uint8_t * dst, uint32_t word_length)
{        
    // Check for dma done
    dma_status();

    //Disable DMAMUX before configuring
    dmamux_en(DMAMUX_DISABLE);

    // Set source and destination address (will be changed during dma_cmd function)
    /* DMA_SAR0 - source, DMA_DAR0 - destination*/
    // only 32 bit writes are allowed, 16 and 8 bit writes result in a bus error
    // bits 31-20 must be written with 0x000x_xxxx, 0x1FFx_xxxx, 0x200x_xxxx, or 0x400x_xxxx or a Config err occurs
    DMA_SAR0 = (uint32_t)src;
    DMA_DAR0 = (uint32_t)dst;

    dma_set_bcr_length(word_length*4);

    //Clear source/destination size fields
    //DMA_DCR0 &= ~(DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK);
    DMA_DCR0 |= (/* Bit21-20 Source Size (00b-32,01b-8,10b-16,11b-ERROR)      */ DMA_DCR_SSIZE(0)
		 |/*Bit18-17 Destination Size (00b-32,01b-8,10b-16,11b-ERROR) */ DMA_DCR_DSIZE(0)
	);
    
    
    //Enable DMAMUX after configuring
    dmamux_en(DMAMUX_ENABLE);


    //Start DMA Transfer
    DMA_DCR0 |= /*Bit16    Start Transfer*/ DMA_DCR_START_MASK;

    // Check for dma done
    dma_clear_status(0);
    return 0;
}

//Set byte_length transfer
void dma_set_bcr_length(uint32_t byte_length)
{
    /* Set BCR byte transfer mode */
    // BCR must be written with value equal to or less than 0F_FFFFh
    // Bits 23-20 will read back as 1110b if equal to or less, otherwise if larger then 1111b
    uint8_t error_toolarge [256]= "Byte transfer length is too large for DMA, Expected less than 0x0F_FFFF but received \0";
    if(byte_length > 0x0FFFFF) { LOG_1(error_toolarge, count2null(error_toolarge), byte_length, UI32); } //Continue on as DMA BCR will show an error if one occurs
    DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(byte_length);

}

// Clears errors and sets done bit. 
void dma_clear_status(uint8_t in_init)
{
    uint8_t error_CE [256] = "Config error occurred";
    uint8_t error_BES [256] = "Bus error on source occurred";
    uint8_t error_BED [256] = "Bus error on destination occurred";
    uint8_t log_transfer [256] = "\nFinished DMA Transfer\0";
    // Clear errors or done bit out of Byte Count Register (DMA_DSR_BCRn) (if any)
    if(/* Bit30 Config Err          */ ((DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK  ) == DMA_DSR_BCR_CE_MASK  )
       |/*Bit29 Bus error on source */ ((DMA_DSR_BCR0 & DMA_DSR_BCR_BES_MASK ) == DMA_DSR_BCR_BES_MASK )
       |/*Bit28 Bus error on dest   */ ((DMA_DSR_BCR0 & DMA_DSR_BCR_BED_MASK ) == DMA_DSR_BCR_BED_MASK )
       |/*Bit24 Transaction done    */ ((DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK) == DMA_DSR_BCR_DONE_MASK) )
    {
    	if(!in_init)
    	{
    		if((DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK  ) == DMA_DSR_BCR_CE_MASK  )
    			LOG_0(error_CE,count2null(error_CE));
    		if((DMA_DSR_BCR0 & DMA_DSR_BCR_BES_MASK ) == DMA_DSR_BCR_BES_MASK )
    			LOG_0(error_BES,count2null(error_BES));
    		if((DMA_DSR_BCR0 & DMA_DSR_BCR_BED_MASK ) == DMA_DSR_BCR_BED_MASK )
    			LOG_0(error_BED,count2null(error_BED));
    	}
    }
    	
    // except during init, this should be used in an interrupt service routine to clear the DMA interrupt and error bits   
    DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK; //0x1000000u (24th bit) //setting done bit resets the status bits

    LOG_0(log_transfer, count2null(log_transfer));
}


// Handles DMA0 interrupt request at end of data transfer
void DMA0_IRQHandler()
{
    dma_clear_status(0);

}
