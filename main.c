#include <stdio.h>
#include "engin.h"

int main()
{
    if(0 == engin_init())
    {
         engin_run() ;
    }else
    {
        printf("engin init failed!\n") ;
        printf("Please adjust console font size\n") ;

    }


    getchar() ;
    return 0 ;
}
