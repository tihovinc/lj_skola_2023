
#include "imageProcessing.h"
#include "bmp.h"

static const uint_least8_t bwTreshold = 128;
const int_least16_t brightnessMinimum = 20;
const int_least16_t brightnessMaximum = 220;


void adjustImageBrightness(uint_least8_t* iData, uint_least16_t iWidth, uint_least16_t iHeight,
		bool brighten, uint_least8_t adjustmentValue)
{
	uint_least32_t i;
	int_least16_t newValue;

	for (i=0; i<iWidth*iHeight*3; i++)
	{
		newValue = iData[i];
		if(brighten)
		{
			newValue += adjustmentValue;
		}
		else
		{
			newValue -= adjustmentValue;
		}

		if(newValue < brightnessMinimum)
		{
			newValue = brightnessMinimum;
		}
		else if(newValue > brightnessMaximum)
		{
			newValue = brightnessMaximum;
		}

		iData[i] = newValue;
	}
}

void bwImage(uint_least8_t* iData, uint_least16_t iWidth, uint_least16_t iHeight)
{
	uint_least16_t i;
	uint_least16_t j;
	uint_least16_t k;
	
	for (i=0; i<iHeight; i++)
	{
		for (j=0; j<iWidth; j++)
		{
			uint_least16_t sum = 0;
			for (k=0; k<3; k++)
			{
				sum += iData[i * iWidth * 3 + j * 3 + k];
			}
			sum = sum / 3;

			sum = (sum > bwTreshold)? 255 : 0;

			for (k=0; k<3; k++)
			{
				iData[i * iWidth * 3 + j * 3 + k] = sum;
			}
		}
	}
}

void effect(uint_least8_t* iData, uint_least16_t iWidth, uint_least16_t iHeight)
{
	uint_least16_t i;
	uint_least16_t j;
	uint_least8_t* ptr = iData;
	
	for (i=0; i<iHeight; i++)
	{
		for (j=0; j<iWidth; j++)
		{
			*ptr = (*ptr > bwTreshold)? 255 : 0;
			ptr++;
			*ptr = (*ptr > bwTreshold)? 255 : 0;
			ptr++;
			*ptr = (*ptr > bwTreshold)? 255 : 0;
			ptr++;;
		}
	}
}
