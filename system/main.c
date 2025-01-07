#include <interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stm32.h>
#include <memory.h>
#include <kernel.h>
#include <delay.h>
#include <gpio.h>
#include <uart.h>
#include <math.h>
#include <usb.h>
#include "usb_cdc.h"
#include "usb-msc.h"
#include "sd-spi.h"
#include "disk.h"
#include "fat_filelib.h"
#include <flash.h>


extern uint32_t SystemCoreClock;
extern void check_msc();




void toggle(int m){
  for (int i = 0; i < m*2; ++i)
  {
    hw_toggle_pin(GPIOx(GPIO_A),8);
    delay(200);
  }
  hw_set_pin(GPIOx(GPIO_A),8, 0);
}


int main()
{

    //char buff[100];

	kprintf("bootloader sdcard\n");
     

    //sprintf(buff,"(%s)", menu[0]);
    //GFX_print(buff);
    
    //sprintf(buff,"(%s)", menu[1]);
    //GFX_print(buff);

    //hw_cfg_pin(GPIOx(GPIO_C),13,GPIOCFG_MODE_OUT | GPIOCFG_OSPEED_VHIGH  | GPIOCFG_OTYPE_PUPD | GPIOCFG_PUPD_PUP);
    //hw_cfg_pin(GPIOx(GPIO_A),0,GPIOCFG_MODE_INP | GPIOCFG_OSPEED_VHIGH  | GPIOCFG_OTYPE_OPEN | GPIOCFG_PUPD_PUP);
    //hw_set_pin(GPIOx(GPIO_C),13, 1);
    //hw_cfg_pin(GPIOx(GPIO_C),9,GPIOCFG_MODE_OUT | GPIOCFG_OSPEED_VHIGH  | GPIOCFG_OTYPE_PUPD | GPIOCFG_PUPD_PUP);
    //hw_cfg_pin(GPIOx(GPIO_A),8,GPIOCFG_MODE_OUT | GPIOCFG_OSPEED_VHIGH  | GPIOCFG_OTYPE_PUPD | GPIOCFG_PUPD_PUP);
    
    hw_cfg_pin(GPIOx(GPIO_A),8,GPIOCFG_MODE_OUT | GPIOCFG_OSPEED_VHIGH  | GPIOCFG_OTYPE_PUPD | GPIOCFG_PUPD_PUP);



    check_msc();

    uint32 size;
    again:
    size = sd_init();
    if(size<0){
        kprintf("error init memory\n");
         
        return -1;
    }
    fl_init();
    if (fl_attach_media(sd_readsector, sd_writesector) != FAT_INIT_OK){
        kprintf("ERROR: Failed to init file system\n");
         
        if (fl_format(size, "")){
            kprintf("format ok\n");
            
            goto again;
        }
        toggle(2);
      return -1;
    }
    fl_listdirectory("/");
 
    
    FILE *fptr;
    char *file=getUrlTargetFileBoot();

    if ((fptr = fopen(file,"r")) == NULL){
         
        kprintf("jump app\n");
        toggle(3);
       delay(1000);
        goto jump_app;
    }
    delay(1000);
    int part=0;
    fseek(fptr, 0, SEEK_END);
    int lsize = ftell(fptr);
    unlock_flash();
    if (lsize < 64000){
        erase_flash_sector4();
    }else if (lsize > 64000 && lsize < 192000){
        erase_flash_sector4();
        erase_flash_sector5();
    }else if (lsize > 192000 && lsize < 320000){
        erase_flash_sector4();
        erase_flash_sector5();
        erase_flash_sector6();
    }else if (lsize>320000 && lsize < 448000){
        erase_flash_sector4();
        erase_flash_sector5();
        erase_flash_sector7();
    }else if(lsize>448000 && lsize < 576000){
        erase_flash_sector4();
        erase_flash_sector5();
        erase_flash_sector7();
        erase_flash_sector8();
        erase_flash_sector9();
    }else if(lsize>576000 && lsize < 704000){
        erase_flash_sector4();
        erase_flash_sector5();
        erase_flash_sector7();
        erase_flash_sector8();
        erase_flash_sector9();
        erase_flash_sector10();
    }else if(lsize>704000 && lsize < 832000){
        erase_flash_sector4();
        erase_flash_sector5();
        erase_flash_sector7();
        erase_flash_sector8();
        erase_flash_sector9();
        erase_flash_sector10();
        erase_flash_sector11();
    }

    lock_flash();

    //kprintf("size: %d\n",lsize );
    #define SIZEBUF 4
    uint8_t b[SIZEBUF];
    uint32_t hex=0;
    uint32_t count=0;
    fseek(fptr, 0, SEEK_SET);
    unlock_flash();
  
     //irq_enable();
    kprintf("updating........\n");
     
    while(!feof(fptr)){
       fread(b,SIZEBUF,1, fptr);
       hex = *(uint32_t *)b;
       write_flash(FLASH_BASE2+count, hex);
       count+=SIZEBUF;
       hw_toggle_pin(GPIOx(GPIO_A),8);
    }
    lock_flash();
    kprintf("writed........\n");
     
    fclose(fptr);
    remove(file);

    
    static uint32_t jump_addr;
    jump_app:
    toggle(5);
    irq_disable();
    jump_addr = *((uint32_t*)(FLASH_BASE2+4u));

    // Disable all interrupts
    NVIC->ICER[0] = 0xFFFFFFFF;
    NVIC->ICER[1] = 0xFFFFFFFF;
    NVIC->ICER[2] = 0xFFFFFFFF;

    NVIC->ICPR[0] = 0xFFFFFFFF;
    NVIC->ICPR[1] = 0xFFFFFFFF;
    NVIC->ICPR[2] = 0xFFFFFFFF;

    NVIC_DisableIRQ(OTG_FS_IRQn);
    SysTick->CTRL = 0;
    SCB->VTOR = FLASH_BASE2;
    __DSB();
    __ISB();
    __set_MSP((*(__IO uint32_t*)FLASH_BASE2));

    ((void (*) (void)) (jump_addr)) ();
    while(1);
}