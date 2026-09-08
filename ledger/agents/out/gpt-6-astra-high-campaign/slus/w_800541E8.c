#include "common.h"

extern void func_8005B300(void);
extern void func_8005B418(int arg0);
extern void func_8005B348(void);
extern void func_8005E7E0(int arg0);
extern void func_8005B320(void);

/* Runs audio setup and uploads voice 4 sample data to the SPU. */
void func_800541E8(void)
{
    func_8005B300();
    func_8005B418(0);
    func_8005B348();
    func_8005E7E0(4);
    func_8005B320();
}
