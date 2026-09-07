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

void func_800AB158(void *arg0, void *arg1) {
    *(void **)((s8 *)arg0 - 0x10) = D_800AB1E0;
    func_800AAEFC();
    *(s16 *)((s8 *)arg0 + 0x90) = 0;
    *(void **)((s8 *)arg0 + 0x50) = D_800AB708;
    *(s16 *)((s8 *)arg0 + 0x6A) = 0;

    {
        u16 *p;
        TF14_BARRIER();
        p = (u16 *)D_80083780;
        TF14_KEEP(p);
        *(u16 *)((s8 *)arg1 + 2) = p[1];
        *(u16 *)((s8 *)arg1 + 6) = p[3];
        *(s16 *)((s8 *)arg1 + 0xA) = p[5] - func_800AAE98(arg1);
    }
}
