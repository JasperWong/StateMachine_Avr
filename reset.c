#include<iom16v.h>
#include<macros.h>

void reset()
{
	WDTCR |= ((1 << WDTOE) | (1 << WDE));				/*����ʱ��							*/
	WDTCR = (1<< WDE);		
}