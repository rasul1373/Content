
#ifndef	_COMMON__
#define	_COMMON__

#define  uint8_t       unsigned char 
#define  uint16_t      unsigned int
#define  uint32_t     unsigned long
#define  BOOL          bit

#define  DISPLAY_EN

 #ifdef   DISPLAY_EN
void DisplayInitial(void);
#endif	
    
#endif	