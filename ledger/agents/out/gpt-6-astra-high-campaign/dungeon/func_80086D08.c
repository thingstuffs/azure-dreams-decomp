#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_800E3D7C.h"

extern s16 D_80083228;
extern u8 D_800DD050[];
extern u8 D_800DD0E0[];

extern void func_80048A44(void *, s16, s16, s32);

/* Reset entity state and select its animation page and directional entry. */
void func_8008C468(void *entity, void *unused, void *animation, void *state) {
    if (!(((Rec_func_8008ACDC_arg0 *)entity)->unk_98 & 0xC)) {
        u8 *page;
        u8 *current_page;

        ((Rec_func_8008ACDC_arg0 *)entity)->unk_9A.as_u8 = 0x16;
        ((Rec_func_8008ACDC_arg0 *)entity)->unk_9B.as_u8 = 0;
        ((Rec_func_8008ACDC_arg0 *)entity)->unk_8C.as_s32 = 0;
        ((Rec_func_8008ACDC_arg0 *)entity)->unk_A2 &= 0xFFFE;
        if (((Rec_D_800E3D7C *)state)->unk_1C.as_s32 & 0x100000) {
            u8 *page_base;

            page_base = (u8 *)0x800E0000;
            ASM_KEEP(page_base);
            current_page = (*(u8 * volatile *) ((u8 *)animation + 0x2C));
            page = page_base - 0x2F20;
        } else {
            current_page = (*(u8 * volatile *) ((u8 *)animation + 0x2C));
            page = D_800DD050;
        }
        if (current_page != page) {
            register void *animation_arg ASM_REG("$4");

            animation_arg = animation;
            (*(u8 * *)((u8 *)animation_arg + 0x2C)) = page;
            func_80048A44(animation_arg, *(u8 *)((((D_80083228 + ((Rec_D_800E3D7C *)state)->unk_2A.as_s16 + 0x100) >> 9) & 7) + (u32)page), 0, 1);
        }
    }
}
