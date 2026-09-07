#include "common.h"

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

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

void func_801254D8(void *arg0) {
    Rect rect0;
    Rect rect1;
    u8 state;

    state = FIELD(arg0, u8, 0xB);
    if (state != 0) {
        if (state != 1) {
            return;
        }
        goto state_ready;
    }

    func_8003F6D4(8, D_8012A998, D_80133198,
                  D_80126D44[FIELD(arg0, u8, 0x13)][1]);
    func_8003E4FC(6, D_80133198, 0);
    FIELD(arg0, u8, 0xD) = 0;
    func_8003E4FC(0xFF, D_8003E140, (u8 *)arg0 + 0xD);
    FIELD(arg0, u8, 0xB)++;

state_ready:
    if (FIELD(arg0, u8, 0xD) == 0) {
        return;
    }

    rect1.x = 0;
    rect1.y = FIELD(arg0, u8, 0x16) + 0x1CA;
    rect1.w = 0x100;
    rect1.h = 1;
    func_800672D8(&rect1, D_8012A998);

    func_8004068C(D_8012A998 + 0x200, D_8012E998);

    rect0.x = (FIELD(arg0, u8, 0x16) << 6) + 0x240;
    rect0.y = 0x80;
    rect0.w = 0x40;
    rect0.h = 0x80;
    func_800672D8(&rect0, D_8012E998);

    FIELD((u8 *)arg0 + FIELD(arg0, u8, 0x16), u8, 0x17) =
        FIELD(arg0, u8, 0x13);

    {
        register u32 value ASM_REG("$2") = FIELD(arg0, u8, 0x13);
        register u32 rhs ASM_REG("$3") = FIELD(arg0, u8, 0x14);

        value = value < rhs;
        if (value == 0) {
            value = 0xB;
        } else {
            value = 0xA;
        }
        ASM_KEEP(value);
        FIELD(arg0, s8, 0xA) = value;
        value = 1;
        ASM_KEEP(value);
        FIELD(arg0, s16, 4) = value;
    }
    FIELD(arg0, u8, 0xB) = 0;
    FIELD(arg0, s16, 6) = 0x19;
}

/* MECHANISM: Sibling Rect locals produce the 0x30 frame; arg0 and the active global base settle in $s1/$s0.
   One unsigned pinned $v0 serially carries lhs, sltu/result, 10/11, then 1; a short-lived pinned $v1 holds rhs.
   Splitting those roles removes the false cross-call literal-1 $s2 hold and restores the retail prologue/tail order. */
