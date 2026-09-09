#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_800E3D7C.h"


extern s16 D_80083228;
extern u8 D_800DD050[];
extern u8 D_800DD0E0[];

extern void func_80048A44(void *, s16, s16, s32);




void func_8008C468(void *arg0, void *arg1, void *arg2, void *arg3) {
    if (!(((Rec_func_8008ACDC_arg0 *)arg0)->unk_98 & 0xC)) {
        u8 *page;
        u8 *dead_v1;

        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_u8 = 0x16;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_u8 = 0;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_s32 = 0;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 &= 0xFFFE;
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x100000) {
            register u8 *page_v0 ASM_REG("$2"); /* MATCH: keep the page high half before the pointer load. */

            page_v0 = (u8 *)0x800E0000;
            ASM_KEEP(page_v0); /* MATCH: keep the page high half before the pointer load. */
            dead_v1 = (*(u8 * volatile *) ((u8 *)arg2 + 0x2C));
            page = page_v0 - 0x2F20;
        } else {
            dead_v1 = (*(u8 * volatile *) ((u8 *)arg2 + 0x2C));
            page = D_800DD050;
        }
        if (dead_v1 != page) {
            register void *call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            call_arg = arg2;
            (*(u8 * *)((u8 *)call_arg + 0x2C)) = page;
            func_80048A44(call_arg, *(u8 *)((((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7) + (u32)page), 0, 1);
        }
    }
}
