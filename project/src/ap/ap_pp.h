/*
 * app_pp.h
 *
 *  Created on: 2021. 4. 13.
 *      Author: sungjinkim
 */

#ifndef SRC_AP_AP_PP_H_
#define SRC_AP_AP_PP_H_


#include "hw_pp.h"


class ApClass
{
public:
	     ApClass         (void);
	bool ApppInit        (void);
	bool ApppMain        (void);
	bool ApppOLEDInit    (void);
	bool ApppOLEDOperate (void);
};


#endif /* SRC_AP_AP_PP_H_ */
