#include "common.h"

extern void func_8005B300(void);
extern void dispatch_combined_driver_flags(int unused);
extern void audio_disable_reverb(void);
extern void func_8005E7E0(int voice);
extern void func_8005B320(void);

/* Runs audio setup and uploads voice 4 sample data to the SPU. */
void func_800541E8(void)
{
    func_8005B300();
    dispatch_combined_driver_flags(0);
    audio_disable_reverb();
    func_8005E7E0(4);
    func_8005B320();
}
