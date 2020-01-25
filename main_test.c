//
// Created by Jamar Slave on 16/12/2019.
//

#include <float.h>

#include "inc/ft_printf.h"
//c s p d i o u x X hh, h, l and ll %% #0-+
int         main()
{
printf("mine:\n");
int t = ft_printf("%.20f",        1.025978542436587568678);
//int t = ft_printf("text: %#.o %#.0o", 0, 0);

printf("<-\nreturned value : %i", t);

printf("\norigin:\n");
    t = printf("%.20f",        1.025978542436587568678);
printf("<-\nreturned value : %i", t);
printf("\n------------\n");
  return (0);
}
/*
 *  перекопать все на предсет маллока и фри со строками
 */

//transform hex format in hex.c refactor