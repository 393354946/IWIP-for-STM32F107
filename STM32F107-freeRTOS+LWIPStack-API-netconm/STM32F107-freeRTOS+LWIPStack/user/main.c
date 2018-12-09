#include "system_stm32f10x.h"
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
//#include "timers.h"
#include "semphr.h"

#include "lwip/netif.h"
#include "lwipopts.h"
#include "drv_ethernet.h"
#include "tcpecho_raw.h"
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/init.h"
#include "ethernet.h" 
#include "drv_ethernet.h"
#include "tcp_server_demo.h" 
#include "tcpecho.h"


////ΪLWIP�ṩ��ʱ
extern u32 lwip_localtime;

#if LWIP_DHCP
extern u8  dhcpstatus;
#endif

void TASK_MAIN(void* pvParameters);

xTaskHandle x_Handle_MAIN;
xTaskHandle x_Handle_TcpEcho;
int main(void)
{
	  SystemInit();	/* ϵͳ��ʼ�� */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�JTAG���Խӿڴ򿪣ӣףĵ��Խӿ�
		#if LWIP_DHCP
		while(dhcpstatus!=2&&dhcpstatus!=0xFF);
		{
			lwip_periodic_handle();
		}
		#endif
		xTaskCreate(TASK_MAIN, "Main", 500, NULL, 3, &x_Handle_MAIN);//��������
		//tcpecho_raw_init();//��ʼ��lwip
		vTaskStartScheduler();
	  
			
		return 0;																						
}

void TASK_MAIN(void* pvParameters)
{
	while(lwip_comm_init());
	tcpecho_init();
	while(1)
	{	
		lwip_localtime = xTaskGetTickCount();
		//tcp_server_test();  	//TCP Serverģʽ
		//lwip_periodic_handle();
	}

}

