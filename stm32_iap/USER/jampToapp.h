#ifndef __JAMPTOAPP__H
#define __JAMPTOAPP__H


#define BASE_ADDRESS             ((uint32_t)0x08000000)
#define BASE_SIZE								 ((uint32_t)0x00010000)
#define WRITE_ADDRESS						 (BASE_ADDRESS + BASE_SIZE)
#define WRITE_SIZE							 ((uint32_t)0x00020000)
#define FLAG_ADRESS							 ((uint32_t)0x08030000)
#define FLASH_PAGE_SIZE					 ((uint32_t)0x00000800)	

typedef void(*pFunction)(void);

void writeDataToflash(char *Send_Buffer,int len);

void initFlash(void);
void saveFlash(void);













#endif
