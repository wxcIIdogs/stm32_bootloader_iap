#include "stm32f10x.h"
#include "jampToapp.h"
#include "stdio.h"

pFunction Jump_To_Application;
uint32_t JumpAddress;
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
void jampToload(uint32_t address)
{
//	uint32_t aa = ((*(uint32_t *)address + 4)&0xFF000000);
//	if(((*(uint32_t *)address + 4)&0xFF000000)==0x08000000)
//	{
		Jump_To_Application=(pFunction)(*(vu32*)(address+4)); 
		__set_MSP(*(vu32*)address);
		Jump_To_Application();
//	}
}
//void iap_load_app(u32 appxaddr)
//{
//       if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)      //??????????.
//       {
//              jump2app=(iapfun)*(vu32*)(appxaddr+4);        
////????????????????(????)         
//              MSR_MSP(*(vu32*)appxaddr);                               
////???APP????(??????????????????)
//              jump2app();    //???APP.
//       }
//}
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
static uint32_t Address = WRITE_ADDRESS;
void writeDataToflash(char *Send_Buffer,int len)
{
	/* Program Flash Bank1 */
	len = len - len % 2;
	uint16_t addr_data = 0;
	while((Address < WRITE_ADDRESS + WRITE_SIZE) && (FLASHStatus == FLASH_COMPLETE) && addr_data < len)
	{
		/* Convert u8 to u32 then write to flash */
			uint16_t Data = Send_Buffer[addr_data] | (Send_Buffer[addr_data+1] << 8);
			FLASHStatus = FLASH_ProgramHalfWord(Address, Data);
			Address = Address + 2;
			addr_data = addr_data + 2;					
	}
}
void saveFlash()
{
	FLASH_LockBank1();
}
