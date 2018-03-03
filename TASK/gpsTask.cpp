#include "gpsTask.h"
#include "math.h"

void gpsTask(void* arg)
{
    
}

float latitude, longtitude;

void unpackUART6_Data(uint8_t* p)
{
    for(uint8_t i = 0; i < 254; i++)
    {
        if(p[i] == 0x0d && p[i+1] == 0x0a)
        {
            if(p[i-6] == 'A')
            {
                uint8_t j = 7;
                latitude = 0;
                
                while(p[j] != '.')
                {
                    latitude = latitude *10 + p[j] - '0';
                    j++;
                }
                uint8_t k = j;
                j++;
                while(p[j] != ',')
                {
                    latitude += (p[j]-'0') * pow(0.1, j-k);
                    j++;
                }
                latitude *= 0.01f;
                
                j+=3;
                longtitude = 0;
                while(p[j] != '.')
                {
                    longtitude = longtitude *10 + p[j] - '0';
                    j++;
                }
                k = j;
                j++;
                while(p[j] != ',')
                {
                    longtitude += (p[j]-'0') * pow(0.1,j-k);
                    j++;
                }
                longtitude *= 0.01f;
                
                return;
            }
            else if(p[i-6] == 'V')
            {
                return;
            }
        }
    }
}

