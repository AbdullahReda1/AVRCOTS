/**********************************************************
 * Author:               Abdullah R.Hebashi
 * Creation Data:    22 MAR, 2023
 * Version:              v1.0
 * Compiler:           GNU GCC
 **********************************************************/
/**********************************************************
 * Version      Date                  Author                              Description
 * v1.0          22 MAR, 2023     Abdullah R.Hebashi           Initial Creation
***********************************************************/


#ifndef 	BIT_MATH_H_
#define 	BIT_MATH_H_


/************ Functions Like Macro To Manipulate Over Specific Bit ******************/
#define 	REGISTER_SIZE         		8
#define 	SET_BIT(REG, BIT)      		REG|=(1<<BIT)
#define 	CLR_BIT(REG, BIT)      		REG&=(~(1<<BIT))
#define 	TOG_BIT(REG, BIT)      	    REG^=(1<<BIT)
#define 	GET_BIT(REG, BIT)    		((REG&(1<<BIT))>>BIT)
#define 	IS_BIT_SET(REG, BIT)  	    ((REG&=(1<<BIT))>>BIT)
#define 	IS_BIT_CLR(REG, BIT)  	    !((REG&=(1<<BIT))>>BIT)
#define 	ROR(REG, NUM)         		REG=(REG<<(REGISTER_SIZE-NUM))|(REG>>(NUM))
#define 	ROL(REG, NUM)         		REG=(REG>>(REGISTER_SIZE-NUM))|(REG<<(NUM))


/************ Functions Like Macro To Manipulate Over Specific Bit ******************/
#define     SET_REG(REG_NAME, VALUE)                  (REG_NAME = VALUE)
#define     GET_REG(REG_NAME)                   	  (REG_NAME)
#define     CLR_REG(REG_NAME)                	      (REG_NAME = 0x00)


#endif