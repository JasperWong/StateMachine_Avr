#include<iom16v.h>
#include<macros.h>


#define uchar unsigned char 
#define uint  unsigned int

//计时值=65536-系统时钟/分频系数/音调频率/2   
//      音符 计时值  频率Hz 
#define LL6	 62464   //220	
#define LL7  62712   //247   	
#define L1	 62728   //262    
#define L2	 63236   //294	
#define L3	 63221   //330   	
#define L4	 63304   //349	
#define L5	 63461   //392	
#define L6	 64500   //440	
#define L7	 63724   //494	
#define N1	 63779   //523	
#define N2	 63885   //587	
#define N3	 63978   //659	
#define N4	 64020   //698	
#define N5	 64099   //784	
#define N6	 64168   //880	
#define N7	 64230   //988	
#define H1	 64259   //1047	 
#define H2	 64311   //1175	
#define H3	 64357   //1319
	
#define H4	 64279   //1397	
#define H5	 64418   //1568	
#define H6	 64352   //1760	
#define H7	 64383   //1976	
#define HH1	 64398   //2093
#define O    0       //休止符

void Bell_Init();
void Bell();
void Music(unsigned int *pMusic);

