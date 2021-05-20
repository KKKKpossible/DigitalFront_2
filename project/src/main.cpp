#include "main.h"
#include "main_pp.h"


extern ApClass ap;


int main(void)
{
	HwInit();
	HwppInit();
	ApInit();
	ap.ApppInit();

	while(true)
	{
		ApMain();
		ap.ApppMain();
	}

	return 0;
}
