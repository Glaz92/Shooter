#include "Score.h"

Score::Score(void)
    : score(0), killTime(0), multiple(0), spree(0)
{
}


Score::~Score(void)
{
}

int Score::calculate(float weapon, float h, int base) 
{
    if(h>300)
        h = 0;
    
    switch(static_cast<int>(weapon))
    {
    case 1:
        weapon = 2;
        break;
    case 2:
        weapon = 1;
        break;
    case 3:
        weapon = 1.5;
        break;
    case 4:
        weapon = 1.25;
        break;
    }

    return weapon * (base - h) * multiple; 
}

void Score::calculateMultiple()
{
    killTime++;

    if(killTime>400)
    {
        spree = 0;
    }

    multiple = 1 + 0.2*spree;

}