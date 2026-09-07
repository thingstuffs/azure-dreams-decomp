#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"



typedef struct {
    s8 a;
    s8 b;
    s8 c;
    s8 d;
} ByteBuf;

typedef struct {
    u8 x;
    u8 y;
} CoordBuf;

s32 func_80033BC0(s32);
void func_8003F80C(void *, s32, s32, s32);
s32 func_800A4E2C(u8 *, u8 *);
s32 func_800A7A38(void *);
void func_800A7A7C(u8, u8, s16, s32, void *);
s16 func_800BCB04(s32, s32, s16);
s32 func_800F61BC(s32, s32);
s32 func_800F6208(s32, s32);
extern u8 D_80081484[];
extern u8 D_800F6D48[];

#ifdef __mips__
static const u32 split_prefix[] __asm__("func_80921000")
    __attribute__((section(".text.func_80921000"), aligned(4))) = {
    0x00000001, 0x00010001, 0x00010000, 0x0001FFFF,
    0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001,
};
__asm__(".globl func_80921000\n"
        ".size func_80921000, 444");
#define BODY_NAME func_80921020
#else
#define BODY_NAME func_80921000
#endif

void BODY_NAME(Rec_D_800E3D7C *arg0) {
    ByteBuf sp18;
    CoordBuf sp20;
    s16 temp_s0;
    s16 temp_v0_3;
    s32 temp_v0_4;
    u16 temp_v0;
    u16 temp_v0_2;

    M2C_ERROR(/* Read from unset register $at */) << 0;
    temp_v0 = arg0->unk_00.at02_u16.v - 1;
    arg0->unk_00.at02_u16.v = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg0->unk_00.at02_u16.v = 1U;
        temp_v0_2 = arg0->unk_04.at02_u16.v + 8;
        arg0->unk_04.at02_u16.v = temp_v0_2;
        if ((s16) temp_v0_2 >= 0x70) {
            arg0->unk_04.at02_u16.v = 0U;
        }
        func_8003F80C(D_800F6D48 + ((s16) arg0->unk_04.at02_u16.v * 4), 0x7380, 1, 2);
    }
    if ((func_80033BC0(0xA2) != 0) && ((func_800F61BC(6, 3) << 0x10) == 0) && ((func_800F6208(6, 3) << 0x10) == 0)) {
        u8 *mode;
        mode = D_80081484;
        if ((mode[0] != 3) || (mode[1] != 6)) {
            if (arg0->unk_08.at00_s16.v == 0) {
                arg0->unk_08.at00_s16.v = 0x40;
                goto block_11;
            }
            goto block_12;
        }
    }
block_11:
    if (arg0->unk_08.at00_s16.v != 0) {
block_12:
        temp_v0_3 = (u16) arg0->unk_08.at00_s16.v - 1;
        arg0->unk_08.at00_s16.v = temp_v0_3;
        if ((temp_v0_3 << 0x10) == 0) {
            sp18.a = 3;
            sp18.b = 6;
            sp18.c = 0;
            sp18.d = 0;
            do {

            } while ((func_800A4E2C(&sp20.x, &sp20.y) << 0x10) < 0);
            temp_v0_4 = func_800BCB04((sp20.x << 6) | 0x20, (sp20.y << 6) | 0x20, -0x400);
            temp_s0 = temp_v0_4;
            func_800A7A7C(sp20.x, sp20.y, temp_s0, func_800A7A38(&sp18), &sp18);
        }
    }
}
