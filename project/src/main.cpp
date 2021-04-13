#include "main.h"
#include "main_pp.h"


extern ApClass ap;


int main(void)
{
	HwInit();
	ApInit();

	for(;;)
	{
		ApMain();
		ap.ApppMain();
	}
}
