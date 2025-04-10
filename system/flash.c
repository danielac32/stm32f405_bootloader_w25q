#include <interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stm32.h>
#include <memory.h>
#include <kernel.h>
#include <delay.h>
#include <uart.h>
#include <stdlib.h>
#include "fat_filelib.h"
#include <flash.h>
#include <shell.h>
 
void unlock_flash() {
    if (FLASH->CR & FLASH_CR_LOCK) {
        FLASH->KEYR = KEY1;
        FLASH->KEYR = KEY2;
    }
}

void lock_flash() {
    FLASH->CR |= FLASH_CR_LOCK; // bit 31
}


void erase_flash_sector(uint32_t sec) {
   irq_disable();
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR |= FLASH_CR_SER;
    FLASH->CR |= (sec << 3); // SNB bit 3:6
    FLASH->CR |= FLASH_CR_STRT; // start
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR &= ~FLASH_CR_SER; // clear SER bit
    FLASH->CR &= ~(0xFU << 3); // clear SNB bit 3:6
    irq_enable();
}

void erase_flash_sector3() {
    const uint32_t sec = 3;
    irq_disable();
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR |= FLASH_CR_SER;
    FLASH->CR |= (sec << 3); // SNB bit 3:6
    FLASH->CR |= FLASH_CR_STRT; // start
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR &= ~FLASH_CR_SER; // clear SER bit
    FLASH->CR &= ~(0xFU << 3); // clear SNB bit 3:6
    irq_enable();
}
void erase_flash_sector4() {     //64
    const uint32_t sec = 4;
    irq_disable();
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR |= FLASH_CR_SER;
    FLASH->CR |= (sec << 3); // SNB bit 3:6
    FLASH->CR |= FLASH_CR_STRT; // start
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR &= ~FLASH_CR_SER; // clear SER bit
    FLASH->CR &= ~(0xFU << 3); // clear SNB bit 3:6
    irq_enable();
}

void erase_flash_sector5() {     //128
    const uint32_t sec = 5;
    irq_disable();
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR |= FLASH_CR_SER;
    FLASH->CR |= (sec << 3); // SNB bit 3:6
    FLASH->CR |= FLASH_CR_STRT; // start
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR &= ~FLASH_CR_SER; // clear SER bit
    FLASH->CR &= ~(0xFU << 3); // clear SNB bit 3:6
    irq_enable();
}

void erase_flash_sector6() {      //128
    const uint32_t sec = 6;
    irq_disable();
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR |= FLASH_CR_SER;
    FLASH->CR |= (sec << 3); // SNB bit 3:6
    FLASH->CR |= FLASH_CR_STRT; // start
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR &= ~FLASH_CR_SER; // clear SER bit
    FLASH->CR &= ~(0xFU << 3); // clear SNB bit 3:6
    irq_enable();
}

void erase_flash_sector7() {     //128
    const uint32_t sec = 7;
    irq_disable();
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR |= FLASH_CR_SER;
    FLASH->CR |= (sec << 3); // SNB bit 3:6
    FLASH->CR |= FLASH_CR_STRT; // start
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR &= ~FLASH_CR_SER; // clear SER bit
    FLASH->CR &= ~(0xFU << 3); // clear SNB bit 3:6
    irq_enable();
}

void erase_flash_sector8() {       //128
    const uint32_t sec = 8;
    irq_disable();
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR |= FLASH_CR_SER;
    FLASH->CR |= (sec << 3); // SNB bit 3:6
    FLASH->CR |= FLASH_CR_STRT; // start
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR &= ~FLASH_CR_SER; // clear SER bit
    FLASH->CR &= ~(0xFU << 3); // clear SNB bit 3:6
    irq_enable();
}

void erase_flash_sector9() {       //128
    const uint32_t sec = 9;
    irq_disable();
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR |= FLASH_CR_SER;
    FLASH->CR |= (sec << 3); // SNB bit 3:6
    FLASH->CR |= FLASH_CR_STRT; // start
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR &= ~FLASH_CR_SER; // clear SER bit
    FLASH->CR &= ~(0xFU << 3); // clear SNB bit 3:6
    irq_enable();
}

void erase_flash_sector10() {     //128
    const uint32_t sec = 10;
    irq_disable();
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR |= FLASH_CR_SER;
    FLASH->CR |= (sec << 3); // SNB bit 3:6
    FLASH->CR |= FLASH_CR_STRT; // start
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR &= ~FLASH_CR_SER; // clear SER bit
    FLASH->CR &= ~(0xFU << 3); // clear SNB bit 3:6
    irq_enable();
}

void erase_flash_sector11() {     //128
    const uint32_t sec = 11;
    irq_disable();
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR |= FLASH_CR_SER;
    FLASH->CR |= (sec << 3); // SNB bit 3:6
    FLASH->CR |= FLASH_CR_STRT; // start
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR &= ~FLASH_CR_SER; // clear SER bit
    FLASH->CR &= ~(0xFU << 3); // clear SNB bit 3:6
    irq_enable();
}

void erase_flash_sector12() {     //128
    const uint32_t sec = 12;
    irq_disable();
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR |= FLASH_CR_SER;
    FLASH->CR |= (sec << 3); // SNB bit 3:6
    FLASH->CR |= FLASH_CR_STRT; // start
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR &= ~FLASH_CR_SER; // clear SER bit
    FLASH->CR &= ~(0xFU << 3); // clear SNB bit 3:6
    irq_enable();
}

void write_flash(uint32_t addr, uint32_t data){
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR |= FLASH_CR_PG;
    FLASH->CR &= ~(0x3U << 8); // clear PSIZE bit 8:9
    FLASH->CR |= (0x2 << 8);   // program PSIZE
    *(volatile uint32_t*)addr = data;
    while(FLASH->SR & FLASH_SR_BSY); // check if busy
    FLASH->CR &= (~FLASH_CR_PG); // disable PG bit
}
/*
char *getUrlTargetFileBoot(){
	//char *s=full_path("/config/kernel");
	FILE *fptr;
	if ((fptr = fopen("/config/kernel","r")) == NULL){
		kprintf("Error! opening file\n");
		kprintf("jump app\n");
		return NULL;
	}
	fseek(fptr, 0, SEEK_END);
	int lsize = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
    char *b= malloc(lsize+1);
	fread(b,lsize,1, fptr);
 
	//kprintf("%s %s\n",t,b);
	fclose(fptr);
    return (char *)b;
}*/
char *getUrlTargetFileBoot() {
    FILE *fptr;
    // Abrir el archivo en modo lectura
    if ((fptr = fopen("/config/kernel", "r")) == NULL) {
        kprintf("Error! opening file\n");
        kprintf("jump app\n");
        return NULL; // Salir si no se puede abrir el archivo
    }

    // Obtener el tamaño del archivo
    fseek(fptr, 0, SEEK_END);
    int lsize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    // Si el archivo está vacío, salir
    if (lsize == 0) {
        kprintf("File is empty\n");
        fclose(fptr);
        return NULL;
    }

    // Asignar memoria para el búfer (+1 para el carácter nulo)
    char *b = malloc(lsize + 1);
    if (b == NULL) {
        kprintf("Memory allocation failed\n");
        fclose(fptr);
        return NULL;
    }

    // Leer el contenido del archivo
    fread(b, lsize, 1, fptr);

    // Cerrar el archivo
    fclose(fptr);

    // Añadir el carácter nulo al final del búfer
    b[lsize] = '\0';

    // Eliminar caracteres no deseados (saltos de línea, espacios, etc.)
    for (int i = lsize - 1; i >= 0; i--) {
        if (b[i] == '\n' || b[i] == '\r' || b[i] == ' ') {
            b[i] = '\0'; // Reemplazar caracteres no deseados con '\0'
        } else {
            break; // Detenerse cuando se encuentre un carácter válido
        }
    }

    // Devolver el búfer limpio
    return b;
}

void setUrlTargetFileBoot(char *str){
    FILE* fd;
    remove("/config/kernel");
    fd = fopen("/config/kernel", "w");
    if(!fd){
       kprintf(" found!\n" );
       return;
    }
    str[strlen(str)]='\0';
    fputs(str,fd);
    fputc(0x00,fd);
    fclose(fd);
}
