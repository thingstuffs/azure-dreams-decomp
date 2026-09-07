#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_800E3D7C.h"


extern s16 D_80083228;
extern u8 D_800DD050[];
extern u8 D_800DD0E0[];

extern void func_80048A44(void *, s16, s16, s32);
extern void func_8008C4C8(void *, u8 *);




void func_8008C468(void *arg0, void *arg1, void *arg2, void *arg3) {
    if (!(((Rec_func_8008ACDC_arg0 *)arg0)->unk_98 & 0xC)) {
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_u8 = 0x16;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8 = 0;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_s32 = 0;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 &= 0xFFFE;
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x100000) {
#ifndef NON_MATCHING
            register u8 *page_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
#endif
            u8 *dead_v1;

#ifndef NON_MATCHING
            page_v0 = (u8 *)0x800E0000;
            ASM_KEEP(page_v0);   /* MATCH pin: load-bearing for the whole function shape */
#endif
            dead_v1 = (*(u8 * volatile *)((u8 *)arg2 + 0x2C));
#ifndef NON_MATCHING
            return func_8008C4C8(arg0, page_v0 - 0x2F20);
#else
            return func_8008C4C8(arg0, D_800DD0E0);
#endif
        }
        if ((*(u8 * *)((u8 *)arg2 + 0x2C)) != D_800DD050) {
            register void *call_arg ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */

            call_arg = arg2;
            (*(u8 * *)((u8 *)call_arg + 0x2C)) = D_800DD050;
            func_80048A44(call_arg, D_800DD050[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
        }
    }
}
