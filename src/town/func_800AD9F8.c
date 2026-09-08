#include "common.h"

extern void func_800AAEFC(void);
extern s32 func_800AAE98(void *arg0);
extern u8 D_80083780[];
extern u8 D_800AB1E0[];
extern u8 D_800AB708[];

#ifdef NON_MATCHING
#define TF14_BARRIER() ((void)0)
#define TF14_KEEP(var) ((void)0)
#else
#define TF14_BARRIER() __asm__ __volatile__("" : : : "memory")
#define TF14_KEEP(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

/* Initialize state and copy default values, adjusting the final output value. */
void func_800AB158(void *state, void *output) {
    *(void **)((s8 *)state - 0x10) = D_800AB1E0;
    func_800AAEFC();
    *(s16 *)((s8 *)state + 0x90) = 0;
    *(void **)((s8 *)state + 0x50) = D_800AB708;
    *(s16 *)((s8 *)state + 0x6A) = 0;

    {
        u16 *defaults;
        TF14_BARRIER();
        defaults = (u16 *)D_80083780;
        TF14_KEEP(defaults);
        *(u16 *)((s8 *)output + 2) = defaults[1];
        *(u16 *)((s8 *)output + 6) = defaults[3];
        *(s16 *)((s8 *)output + 0xA) = defaults[5] - func_800AAE98(output);
    }
}
