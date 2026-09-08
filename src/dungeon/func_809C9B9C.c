#include "common.h"
#include "records/Rec_D_80082E80.h"


extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern void func_80171574() __attribute__((noreturn));
extern void func_80171578() __attribute__((noreturn));
extern s32 func_80171D3C();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80173C74[];


typedef struct S_8017139C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_8017139C_0;   /* state in func_8017139C */


typedef struct S_8017139C_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    u8 unk_9A;
} S_8017139C_2;   /* arg0 in func_8017139C */

typedef struct S_8017139C_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8017139C_3;   /* (u8 *)state + ((S_8017139C_0 *)state)->unk_8A.s in func_8017139C */

void func_8017139C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *state ASM_REG("$17") = arg3;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 move_flags;
    s16 action;
    s16 result;
    s32 x;
    s32 y;
    register u16 flags ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */

    if (((S_8017139C_0 *)state)->unk_71.s <= 0) {
        return;
    }

    if (((S_8017139C_0 *)state)->unk_71.u <= ((S_8017139C_0 *)state)->unk_8A.s) {
        return;
    }

    if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 != D_80173C74) {
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80173C74;
        func_80047784(
            arg2,
            D_80173C74[((D_80083228 + ((S_8017139C_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = ((Rec_D_80082E80 *)arg2)->unk_24;
    y = ((Rec_D_80082E80 *)arg2)->unk_25;
    move_flags = 0x3000;
    if (((S_8017139C_0 *)state)->unk_1C & 0x2000) {
        move_flags = 0x300;
    }
    func_8009A3D0(x, y, move_flags);

    action = func_800A0818(
        x,
        y,
        ((S_8017139C_3 *)((u8 *)state + ((S_8017139C_0 *)state)->unk_8A.s))->unk_74,
        ((S_8017139C_3 *)((u8 *)state + ((S_8017139C_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)arg0 + 0x98);
    result = func_8009A66C(action, arg2, state, 0x20);

    ((Rec_D_80082E80 *)arg2)->unk_24 =
        ((S_8017139C_3 *)((u8 *)state + ((S_8017139C_0 *)state)->unk_8A.s))->unk_74;
    move_flags = 0x3000;
    ((Rec_D_80082E80 *)arg2)->unk_25 =
        ((S_8017139C_3 *)((u8 *)state + ((S_8017139C_0 *)state)->unk_8A.s))->unk_7C;
    ((S_8017139C_0 *)state)->unk_8A.u++;

    {
        s32 next_x = ((Rec_D_80082E80 *)arg2)->unk_24;
        s32 next_y = ((Rec_D_80082E80 *)arg2)->unk_25;

        if (((S_8017139C_0 *)state)->unk_1C & 0x2000) {
            move_flags = 0x300;
        }
        func_8009A21C(next_x, next_y, move_flags);
    }

    ((S_8017139C_0 *)state)->unk_2A = action;
    if (result == 3) {
        if (!(D_80083462 & 0x80) && !(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
            func_80171D3C(arg0, arg1, arg2, state);
            ((S_8017139C_2 *)arg0)->unk_8C = 0;
            func_80171578();
            return;
        }
        ((S_8017139C_2 *)arg0)->unk_9A = 0xF;
        func_80171574();
        return;
    }

    flags = ((S_8017139C_2 *)arg0)->unk_98;
    ((S_8017139C_2 *)arg0)->unk_9A = 0xF;
    flags &= ~8;
    ((S_8017139C_2 *)arg0)->unk_98 = flags;
    ASM_KEEP(flags);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_8017139C_2 *)arg0)->unk_8C = 0;
    (*(s32 *)((u8 *)state + (0x1C))) |= 0x40000000;
    if (D_80083462 & 0x80) {
        ((S_8017139C_2 *)arg0)->unk_96 = 0;
        return;
    }

    ((S_8017139C_2 *)arg0)->unk_96 = 8;
    {
        s32 count = ((S_8017139C_0 *)state)->unk_71.u;
        if (count > 0) {
            ((S_8017139C_2 *)arg0)->unk_96 = 8 / count;
        }
    }
}
