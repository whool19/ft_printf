//
// Created by Jamar Slave on 16/12/2019.
//

#include "inc/ft_printf.h"
//c s p d i o u x X hh, h, l and ll %% #0-+

int         main()//1698test
{
    /*
    static char	a01;
    static unsigned char a02;
    static short a03;
    static unsigned short a04;
    static int a05;
    static unsigned int a06;
    static long a07;
    static unsigned long a08;
    static long long a09;
    static unsigned long long a10;
    static char *a11;
    static void *a12;
    static unsigned int		mx_u = 235;
    static long double			mx_Lf = 0.375l;
    static double				mx_f = 0.625;
    static long				mx_li =  4223372036854775800;
    static long long			mx_lli = 3223372036654775200;
    static char				mx_c = 'G';
    static short				mx_hi = -3244;
    static char				mx_hhi = 'F';
    static char			   *mx_s = "Hello, World!";
    static int					mx_i = 42;
    static char 		ch_pos_1 = 100, ch_neg_1 = -87;
    static short		sh_pos_1 = 3047, sh_neg_1 = -8875;
    static int			i_pos_1 = 878023;
    static long		l_pos_1 = 22337203685477, l_neg_1 = -22337203685477;
    static long long	ll_pos_1 = 22337203685477, ll_neg_1 = -22337203685477;
    static long		lmax	= 9223372036854775807;
    static long		lmin	= -9223372036854775807;
    static long long llmax = 9223372036854775807;
    static long long	llmin = -9223372036854775807ll;
    ft_printf("%s\n", "Slaves of printf");


    printf("or: [%i] [%i]\n", i_pos_1, i_pos_1);
    ft_printf("[%i] [%i]", i_pos_1, i_pos_1);
printf("hello, %s.          ", NULL);
    ft_printf("hello, %s.", NULL);
    printf("hello, %.3s.", "gavin");printf("    ");
    ft_printf("hello, %.3s.", "gavin");printf("\n");
    printf("%-16s", "nark nark");printf("    ");
   ft_printf("%-16s", "nark nark");printf("\n");
      printf("%7.7s%7.3s", "hello", "world");printf("    ");
       ft_printf("%7.7s%7.3s", "hello", "world");printf("\n");
    printf("this %d number", 17);printf("\n    ");
       ft_printf("this %d number", 17);printf("\n");
        printf("%8.5i", 0);printf("    ");//////////////
       ft_printf("%8.5i", 0);printf("\n");
       printf("%+3.7i", 3267);printf("    ");
       ft_printf("%+3.7i", 3267);printf("\n");
       printf("%4u", 94827);printf("    ");
       ft_printf("%4u", 94827);printf("\n");
       printf("%8.3u", 8375);printf("    ");
       ft_printf("%8.3u", 8375);printf("\n");
    printf("%08.5u", 0);printf("    ");
    ft_printf("%08.5u", 0);printf("\n");

    printf("%5x", 52625);printf("    ");
    ft_printf("%5x", 52625);printf("\n");

    printf("%2.7x", 3267);printf("    ");
    ft_printf("%2.7x", 3267);printf("\n");
    printf("%0-8.3x",8375);printf("    ");
    ft_printf("%0-8.3x", 8375);printf("\n");
    printf("%2o", 94827);printf("    ");
    ft_printf("%2o", 94827);printf("\n");
    printf("%hho", (unsigned char)45);printf("    ");
    ft_printf("%hho", (unsigned char)45);printf("\n");
    printf("%32p%32p%32p%32p%32p%32p%32p%32p%32p%32p%32p%32p",&a01,&a02,&a03,&a04,&a05,&a06,&a07,&a08,&a09,&a10,&a11,&a12);printf("    ");
    ft_printf("%32p%32p%32p%32p%32p%32p%32p%32p%32p%32p%32p%32p",&a01,&a02,&a03,&a04,&a05,&a06,&a07,&a08,&a09,&a10,&a11,&a12);printf("\n");
    printf("%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c",(char)1,(char)2,(char)3,(char)4,(char)5,(char)6,(char)7,(char)8,(char)9,(char)10,(char)11,(char)12,(char)13,(char)14,(char)15,(char)16,(char)17,(char)18,(char)19,(char)20,(char)21,(char)22,(char)23,(char)24,(char)25,(char)26,(char)27,(char)28,(char)29,(char)30,(char)31);printf("    ");
    ft_printf("%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c",(char)1,(char)2,(char)3,(char)4,(char)5,(char)6,(char)7,(char)8,(char)9,(char)10,(char)11,(char)12,(char)13,(char)14,(char)15,(char)16,(char)17,(char)18,(char)19,(char)20,(char)21,(char)22,(char)23,(char)24,(char)25,(char)26,(char)27,(char)28,(char)29,(char)30,(char)31);printf("\n");
    printf("  %c    %i    %hi    %o    %x    %u  ", mx_c, mx_i, mx_hi, mx_u, mx_u, mx_u);printf("    ");

ft_printf("  %c    %i    %hi    %o    %x    %u  ", mx_c, mx_i, mx_hi, mx_u, mx_u, mx_u);printf("\n");

*/
    static unsigned int		mx_u = 235;
    static long double			mx_Lf = 0.375l;
    static double				mx_f = 0.625;
    static long				mx_li =  4223372036854775800;
    static long long			mx_lli = 3223372036654775200;
    static char				mx_c = 'G';
    static short				mx_hi = -3244;
    static char				mx_hhi = 'F';
    static char			   *mx_s = "Hello, World!";
    static int					mx_i = 42;
printf("mine:\n");
int t = ft_printf("%f", -5.9999996);
printf("<-\nreturned value : %i", t);
printf("\norigin:\n");
t = printf("%f", -5.9999996);
printf("<-\nreturned value : %i", t);
printf("\n------------\n");
/*
    ft_printf("\n");
    ft_printf("%%\n");
    ft_printf("%d\n", 42);
    ft_printf("%d%d\n", 42, 41);
    ft_printf("%d%d%d\n", 42, 43, 44);
    ft_printf("%ld\n", 2147483647);
    ft_printf("%lld\n", 9223372036854775807);
    ft_printf("%x\n", 505);
    ft_printf("%X\n", 505);
    ft_printf("%p\n", &ft_printf);
    ft_printf("%20.15d\n", 54321);
    ft_printf("%-10d\n", 3);
    ft_printf("% d\n", 3);
    ft_printf("%+d\n", 3);
    ft_printf("%010d\n", 1);
    ft_printf("%hhd\n", 0);
    ft_printf("%jd\n", 9223372036854775807);
    ft_printf("%zd\n", 4294967295);
    ft_printf("%\n");
    ft_printf("%U\n", 4294967295);
    ft_printf("%u\n", 4294967295);
    ft_printf("%o\n", 40);
    ft_printf("%%#08x\n", 42);
    ft_printf("%x\n", 1000);
    ft_printf("%#X\n", 1000);
    ft_printf("%s\n", NULL);
    ft_printf("%s%s\n", "test", "test");
    ft_printf("%s%s%s\n", "test", "test", "test");
    ft_printf("%C\n", 15000);
*/
return (0);
}

