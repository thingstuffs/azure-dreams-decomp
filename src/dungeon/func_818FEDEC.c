#include "common.h"
#include "m2c_compat.h"

typedef struct S_818FEDEC_0_pre {
    u16 unk_00;
} S_818FEDEC_0_pre;   /* the 0x2 bytes before arg0 in func_818FEDEC, addressed as arg0[-1] */

typedef struct S_818FEDEC_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x18];
    s16 unk_1C;
    union { s16 s; u16 u; } unk_1E;   /* accessed as both */
    u8 pad_20[0x8];
    u8 unk_28;
    u8 unk_29;
} S_818FEDEC_0;   /* arg0 in func_818FEDEC */

typedef struct S_818FEDEC_1 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_818FEDEC_1;   /* arg2 in func_818FEDEC */


typedef struct {
    u8 pad_00[0x1E];
    u16 field_1E;
    u8 pad_20[8];
    u8 field_28;
    u8 field_29;
} TargetState;

extern s16 D_80025E80[5];
extern u8 D_80020000[];
extern s32 D_800814A0;
extern void *D_80024008[];
extern void func_800246C0() __attribute__((noreturn));

/* Advances an eight-frame animation and flags expiration when its countdown ends. */
M2C_UNK func_818FEDEC(void *anim_state, s32 unused_arg, void *render_state) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    u16 ticks_left;
    s32 frame;
    s32 *page_base;

    ticks_left = ((S_818FEDEC_0 *)anim_state)->unk_02;
    *D_80025E80 = 1;
    ((S_818FEDEC_0 *)anim_state)->unk_02 = (u16) (ticks_left - 1);
    ((S_818FEDEC_1 *)render_state)->unk_1C = 0x2000;
    ((S_818FEDEC_1 *)render_state)->unk_1E = 0x2000;
    if (((S_818FEDEC_0 *)anim_state)->unk_1C != 0) {
        goto block_9;
    }
    frame = ((S_818FEDEC_0 *)anim_state)->unk_1E.s;
    ((S_818FEDEC_0 *)anim_state)->unk_1C = 0;
    if ((u32) frame >= 8U) {
        goto block_10;
    }
    (void)jt_keep; goto *D_80024008[(u32)(frame)];
jt_c0:
jt_c1:
jt_c2:
jt_c4:
jt_c5:
jt_c6:
    ((S_818FEDEC_0 *)anim_state)->unk_1E.s = (s16) ((u16) ((S_818FEDEC_0 *)anim_state)->unk_1E.s + 1);
    ((S_818FEDEC_0 *)anim_state)->unk_28 = (u8) (((S_818FEDEC_0 *)anim_state)->unk_28 + 0x20);
    func_800246C0();
    return;
jt_c3:
    ((S_818FEDEC_0 *)anim_state)->unk_1E.u += 1;
    ((S_818FEDEC_0 *)anim_state)->unk_28 -= 0x60;
    ((S_818FEDEC_0 *)anim_state)->unk_29 += 0x20;
    func_800246C0();
    return;
jt_c7:
    {
        u16 tex_u;
        s32 tex_v;
        tex_u = ((S_818FEDEC_0 *)anim_state)->unk_28;
        tex_v = ((S_818FEDEC_0 *)anim_state)->unk_29;
        ((S_818FEDEC_0 *)anim_state)->unk_1E.s = 0;
        tex_u = tex_u - 0x60;
        tex_v = tex_v - 0x20;
        ((S_818FEDEC_0 *)anim_state)->unk_28 = tex_u;
        ((S_818FEDEC_0 *)anim_state)->unk_29 = tex_v;
        func_800246C0();
        return;
    }
block_9:
    ((S_818FEDEC_0 *)anim_state)->unk_1C = (s16) ((u16) ((S_818FEDEC_0 *)anim_state)->unk_1C + 1);
block_10:
    if ((s16) ((S_818FEDEC_0 *)anim_state)->unk_02 > 0) {
        goto block_12;
    }
    (*(u16 *)((u8 *)anim_state + -2)) = (u16) (((S_818FEDEC_0_pre *)anim_state)[-1].unk_00 | 0x8000);
    D_800814A0 = D_800814A0 | 0x8000;
block_12:
    return;
}
