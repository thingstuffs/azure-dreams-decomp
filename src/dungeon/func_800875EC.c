#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"

typedef struct S_8008CD4C_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    union { u8 s; volatile u8 u; } unk_25;   /* accessed as both */
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8008CD4C_0;   /* arg2 in func_8008CD4C */


typedef struct S_8008CD4C_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_8008CD4C_2;   /* actor in func_8008CD4C */

typedef struct S_8008CD4C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    s16 unk_04;
} S_8008CD4C_3;   /* control in func_8008CD4C */



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

M2C_UNK func_80048A44();
M2C_UNK func_80094ED4();
M2C_UNK func_8009A21C();
M2C_UNK func_8009A3D0();
s32 func_8009ADB8();
s32 func_8009B25C();
M2C_UNK func_8009F644();
M2C_UNK func_800A56E0();

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228[5];
extern u8 D_80083460[9];
extern u8 D_800DCFB8[];
extern u8 D_800DD018[];

void func_8008CD4C(Rec_func_8008ACDC_arg0 *arg0, M2C_UNK arg1, S_8008CD4C_0 *arg2, void *arg3, s32 arg4) {
    register S_8008CD4C_2 *actor ASM_REG("$20") = arg3;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 state ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 offset;
    s32 x;
    s32 y;
    s32 ent;
    u16 *xstep;
    u16 *ystep;
    u8 *control;

    arg2->unk_2C = D_800DD018;
    state = arg4;
    arg0->unk_9A.as_u8 = 0x18;
    arg0->unk_9B.as_u8 = 0;
    arg0->unk_8C.as_s32 = 0;

    if ((s16)state != -2) {
        offset = ((actor->unk_2A.s >> 8) & 0xE);
        xstep = (u16 *)((u8 *)D_8006CCD8 + offset);
        x = arg2->unk_24 + *xstep;
        ystep = (u16 *)((u8 *)D_8006CCE8 + offset);
        y = arg2->unk_25.s + *ystep;
        ent = func_8009B25C(actor, x & 0xFFFF, y & 0xFFFF,
                            actor->unk_88);
        if (ent != 0) {
            if ((func_8009ADB8(actor, ent, (s16)x, (s16)y,
                               actor->unk_88) << 16) != 0) {
                arg0->unk_124 = ent;
                func_8009A3D0(arg2->unk_24,
                              arg2->unk_25.s, 0x300);
                arg2->unk_24 =
                    arg2->unk_24 + *(u8 *)xstep;
                arg2->unk_25.u =
                    arg2->unk_25.s + *(u8 *)ystep;
                func_8009A21C(arg2->unk_24,
                              arg2->unk_25.u, 0x300);

                actor->unk_1C |= 0x40000000;
                control = D_80083460;
                ((S_8008CD4C_3 *)control)->unk_04 = 0x20;
                ((S_8008CD4C_3 *)control)->unk_02 |= 8;
                arg0->unk_9B.as_u8 = 0x10;
                arg2->unk_2C = D_800DCFB8;
                arg0->unk_96.as_s16 = 4;
                func_8009F644(actor, 8, 0, 0);
                func_800A56E0(0x50B);
                func_80094ED4(arg0, arg1, arg2, actor);
            }
        }
    }

    func_80048A44(
        arg2,
        arg2->unk_2C
            [((D_80083228[0] + actor->unk_2A.u + 0x100) >> 9) & 7],
        0, 1);
    ASM_KEEP(actor);   /* MATCH pin: retail schedule: same instructions, different order without it */
}
