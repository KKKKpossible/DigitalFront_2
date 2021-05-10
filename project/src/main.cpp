#include "main.h"
#include "main_pp.h"


extern ApClass ap;


int main(void)
{
	HwInit();
	ap.ApppInit();
	ApInit();

	while(true)
	{
		ApMain();
		ap.ApppMain();
	}

	return 0;
}
