#include <stdio.h>

typedef struct date
{
    int month, day, year;
}Date;

typedef struct time
{
    int hour, min, sec;
}Time;

typedef struct datetime
{
    struct date d;
    struct time t;
}DT;

double datetimetojulian(DT y)
{
    int JDN = (1461.0*(y.d.year+4800.0+(y.d.month-14.0)/12.0))/4.0+(367.0*(y.d.month-2.0-12.0*((y.d.month-14.0)/12.0)))/12.0-(3.0*((y.d.year+4900.0+(y.d.month-14.0)/12.0)/100.0))/4.0+y.d.day-32075.0;
    double JDD = JDN + ((y.t.hour-12.0)/24.0) + (y.t.min/1440.0) + (y.t.sec/86400.0);
    
    return JDD;
}

DT datetimefromjulian(double JDN)
{
    int q = JDN;
    double JDD =  JDN - (double) q;
    
    if (JDD >= 0.5){
        JDD -=1;
        q +=1;
    }
    int H = 0;
    int N = 0;
    int S = 0;
    
    while ((JDD-((H-12.0)/24.0))>=((60.0/1440.0)+(60.0/86400.0)))
    H++;
    while ((JDD-((H-12.0)/24.0)-(N/1440.0))>=((60.0/86400.0)))
    N++;
    while ((JDD-((H-12.0)/24.0)-(N/1440.0)-(S/86400.0))>=(1/86400.0))
    S++;
    
    int f = q + 1401 +(((4*q+274277)/146097)*3)/4-38;
    int e = 4 * f + 3;
    int g = (e % 1461)/ 4;
    int h = 5 * g + 2;
    int D = (h % 153)/ 5 + 1;
    int M = ((h/153 + 2 )% 12) + 1;
    int Y = (e/1461) - 4716 + (12 + 2 - M)/12;
   
    Time t = { .hour = H, .min = N, .sec = S};
    Date d = { .month = M, .day = D, .year = Y, };
    DT result = { d, t};
    
    return result;
}

int main()
{
    //gregorian date to julian day number
    Date d = {1, 1, 1970};
    Time t = {4,23,12};
    DT y = {d, t};
    printf("Julian Day Number = %f\n", datetimetojulian(y));
    
    //julian day number to gregorian date/time
    double JDN;
    printf("enter julian day number: \n");
    scanf("%lf", &JDN);                      //jdn = 2440588 ; date = 1/1/1970 
    DT dt = datetimefromjulian(JDN);
    printf("time = %d:%d:%d date = %d/%d/%d", dt.t.hour, dt.t.min, dt.t.sec, dt.d.month, dt.d.day, dt.d.year);
    
    return 0;
}

