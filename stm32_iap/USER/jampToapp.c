#include "stm32f10x.h"
#include "jampToapp.h"
#include "stdio.h"

pFunction Jump_To_Application;
uint32_t JumpAddress;
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
void initFlash()
{
	uint32_t NbrOfPage;
	FLASH_Unlock();
	/* Define the number of page to be erased */
	NbrOfPage = (WRITE_SIZE) / FLASH_PAGE_SIZE;

	/* Clear All pending flags */
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

	/* Erase the FLASH pages */
	for(int EraseCounter = 0; (EraseCounter <= NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
	{
		FLASHStatus = FLASH_ErasePage(WRITE_ADDRESS + (FLASH_PAGE_SIZE * EraseCounter));
	}
}
static uint32_t Address = WRITE_ADDRESS+4;
void writeDataToflash(char *Send_Buffer,int len)
{
	/* Program Flash Bank1 */
	len = len - len % 4;
	uint32_t addr_data = 0;
	while((Address < WRITE_ADDRESS + WRITE_SIZE) && (FLASHStatus == FLASH_COMPLETE) && addr_data < len)
	{
		/* Convert u8 to u32 then write to flash */
			uint32_t Data = Send_Buffer[addr_data] | (Send_Buffer[addr_data+1] << 8) | (Send_Buffer[addr_data+2] << 16) | (Send_Buffer[addr_data+3] << 24);
			FLASHStatus = FLASH_ProgramWord(Address, Data);
			Address = Address + 4;
			addr_data = addr_data +4;
			printf("%X\r\n",Address);			
	}
}
void saveFlash()
{
	FLASH_LockBank1();
}
