#include<iom16v.h>
#include<macros.h>

void reset()
{
	WDTCR |= ((1 << WDTOE) | (1 << WDE));				/*Æô¶¯Ê±Ðò							*/
	WDTCR = (1<< WDE);		
}