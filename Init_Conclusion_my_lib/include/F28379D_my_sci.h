/*
 * F28379D_my_sci.h
 *
 *  Created on: 2024Äê7ÔÂ22ÈÕ
 *      Author: Lenovo
 */

#include "F28x_Project.h"

#ifndef INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_SCI_H_
#define INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_SCI_H_

extern void ConfigureSCIB(void);
extern void scib_send(unsigned char a);
extern unsigned char scib_read(void);
extern void scib_send_string(unsigned char *a, unsigned int len);


extern void ConfigureSCIC(void);
extern void scic_send(unsigned char a);
extern unsigned char scic_read(void);
extern void scic_send_string(unsigned char *a, unsigned int len);



#endif /* INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_SCI_H_ */
