#include "common.h"

typedef struct S_801254D8_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    s8 unk_0A;
    u8 unk_0B;
    u8 pad_0C[0x1];
    u8 unk_0D;
    u8 pad_0E[0x5];
    u8 unk_13;
    u8 unk_14;
    u8 pad_15[0x1];
    u8 unk_16;
} S_801254D8_0;   /* arg0 in func_801254D8 */

typedef struct S_801254D8_1 {
    u8 pad_00[0x17];
    u8 unk_17;
} S_801254D8_1;   /* (u8 *)arg0 + ((S_801254D8_0 *)arg0)->unk_16 in func_801254D8 */


typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

extern s32 func_8003E4FC();
extern s32 func_8003F6D4();
extern s32 func_8004068C();
extern s32 func_800672D8();

extern s32 D_8003E140[];
extern s32 *D_80126D44[];
extern u8 D_8012A998[];
extern u8 D_8012E998[];
extern u8 D_80133198[];


void func_801254D8(void *arg0) {
    Rect rect0;
    Rect rect1;
    u8 state;

    state = ((S_801254D8_0 *)arg0)->unk_0B;
    if (state != 0) {
        if (state != 1) {
            return;
        }
        goto state_ready;
    }

    func_8003F6D4(8, D_8012A998, D_80133198,
                  D_80126D44[((S_801254D8_0 *)arg0)->unk_13][1]);
    func_8003E4FC(6, D_80133198, 0);
    ((S_801254D8_0 *)arg0)->unk_0D = 0;
    func_8003E4FC(0xFF, D_8003E140, (u8 *)arg0 + 0xD);
    ((S_801254D8_0 *)arg0)->unk_0B++;

state_ready:
    if (((S_801254D8_0 *)arg0)->unk_0D == 0) {
        return;
    }

    rect1.x = 0;
    rect1.y = ((S_801254D8_0 *)arg0)->unk_16 + 0x1CA;
    rect1.w = 0x100;
    rect1.h = 1;
    func_800672D8(&rect1, D_8012A998);

    func_8004068C(D_8012A998 + 0x200, D_8012E998);

    rect0.x = (((S_801254D8_0 *)arg0)->unk_16 << 6) + 0x240;
    rect0.y = 0x80;
    rect0.w = 0x40;
    rect0.h = 0x80;
    func_800672D8(&rect0, D_8012E998);

    ((S_801254D8_1 *)((u8 *)arg0 + ((S_801254D8_0 *)arg0)->unk_16))->unk_17 =
        ((S_801254D8_0 *)arg0)->unk_13;

    {
        u32 value = ((S_801254D8_0 *)arg0)->unk_13;
        register u32 rhs ASM_REG("$3") = ((S_801254D8_0 *)arg0)->unk_14;   /* MATCH pin: load-bearing for the whole function shape */

        value = value < rhs;
        if (value == 0) {
            value = 0xB;
        } else {
            value = 0xA;
        }
        ((S_801254D8_0 *)arg0)->unk_0A = value;
        value = 1;
        ((S_801254D8_0 *)arg0)->unk_04 = value;
    }
    ((S_801254D8_0 *)arg0)->unk_0B = 0;
    ((S_801254D8_0 *)arg0)->unk_06 = 0x19;
}

/* MECHANISM: Sibling Rect locals produce the 0x30 frame; arg0 and the active global base settle in $s1/$s0.
   One unsigned pinned $v0 serially carries lhs, sltu/result, 10/11, then 1; a short-lived pinned $v1 holds rhs.
   Splitting those roles removes the false cross-call literal-1 $s2 hold and restores the retail prologue/tail order. */
