#include "common.h"

extern int func_8003F270(void);
extern void func_8003CB08(void);
extern void func_80044618(int);
extern void func_8003E758(void);

/* Repeat the update sequence while func_8003F270 reports pending work. */
void func_8003F320(void)
{
    while (func_8003F270())
    {
        func_8003CB08();
        func_80044618(2);
        func_8003E758();
    }
}
