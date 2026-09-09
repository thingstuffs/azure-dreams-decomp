#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80171570_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    s16 unk_8A;
} S_80171570_0;   /* state in func_80171570 */


typedef struct S_80171570_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_80171570_2;   /* arg0 in func_80171570 */

typedef struct S_80171570_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171570_3;   /* (u8 *)state + ((S_80171570_0 *)state)->unk_8A in func_80171570 */



extern void func_80047784(void *, s16, s16);
extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern s16 func_8009A66C(s16, void *, void *, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_80171EFC(void *, s32, void *, void *);

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174138[];

void func_80171570(void *arg0, s32 arg1, void *arg2, void *arg3) {
    register void *state ASM_REG("$17") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 mode;
    s16 result;
    s16 next;
    s32 x;
    s32 y;
    s32 count;
    u8 a24;
    u8 a25;

    if (((S_80171570_0 *)state)->unk_71.s <= 0) {
        return;
    }
    if (((S_80171570_0 *)state)->unk_71.u <= ((S_80171570_0 *)state)->unk_8A) {
        return;
    }

    if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 != D_80174138) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174138;
        func_80047784(
            arg2,
            D_80174138[((D_80083228 + ((S_80171570_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = ((Rec_D_80082E80 *)arg2)->unk_24;
    y = ((Rec_D_80082E80 *)arg2)->unk_25;
    mode = 0x3000;
    if (((S_80171570_0 *)state)->unk_1C & 0x2000) {
        mode = 0x300;
    }
    func_8009A3D0(x, y, mode);

    next = func_800A0818(
        x,
        y,
        ((S_80171570_3 *)((u8 *)state + ((S_80171570_0 *)state)->unk_8A))->unk_74,
        ((S_80171570_3 *)((u8 *)state + ((S_80171570_0 *)state)->unk_8A))->unk_7C,
        (u8 *)arg0 + 0x98);
    result = func_8009A66C(next, arg2, state, 0x20);

    ((Rec_D_80082E80 *)arg2)->unk_24 =
        ((S_80171570_3 *)((u8 *)state + ((S_80171570_0 *)state)->unk_8A))->unk_74;
    mode = 0x3000;
    ((Rec_D_80082E80 *)arg2)->unk_25 =
        ((S_80171570_3 *)((u8 *)state + ((S_80171570_0 *)state)->unk_8A))->unk_7C;
    ((S_80171570_0 *)state)->unk_8A = (u16)((S_80171570_0 *)state)->unk_8A + 1;

    a24 = ((Rec_D_80082E80 *)arg2)->unk_24;
    a25 = ((Rec_D_80082E80 *)arg2)->unk_25;
    if (((S_80171570_0 *)state)->unk_1C & 0x2000) {
        mode = 0x300;
    }
    func_8009A21C(a24, a25, mode);
    ((S_80171570_0 *)state)->unk_2A = next;

    if (result == 3 && !(D_80083462 & 0x80) && !(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        func_80171EFC(arg0, arg1, arg2, state);
        ((S_80171570_2 *)arg0)->unk_8C = 0;
    } else {
        ((S_80171570_2 *)arg0)->unk_9A = 0x0F;
        ((S_80171570_2 *)arg0)->unk_8C = 0;
    }
    (*(s32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (D_80083462 & 0x80) {
        ((S_80171570_2 *)arg0)->unk_96 = 0;
        return;
    }

    ((S_80171570_2 *)arg0)->unk_96 = 8;
    count = ((S_80171570_0 *)state)->unk_71.u;
    if (count > 0) {
        ((S_80171570_2 *)arg0)->unk_96 = 8 / count;
    }
}

/* MECHANISM: The pinned state base supplies retail's long-lived $s1 role and exact 0x38 frame/save contract.
   Defaulting mode before each flags test, with the second default between the coordinate stores,
   reproduces the flags-load schedule, $a2 constant lifetime, and delayed $v0-to-$s0 result save. */
