#include "common.h"

extern void func_8005B300(void);
extern void dispatchCombinedDriverFlags(int unused);
extern void audioDisableReverb(void);
extern void func_8005E7E0(int voice);
extern void func_8005B320(void);

/* Runs audio setup and uploads voice 4 sample data to the SPU. */
void func_800541E8(void)
{
    func_8005B300();
    dispatchCombinedDriverFlags(0);
    audioDisableReverb();
    func_8005E7E0(4);
    func_8005B320();
}
