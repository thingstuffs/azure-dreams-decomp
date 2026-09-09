#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80170838[];
void func_80047784();
M2C_UNK func_8009C12C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
M2C_UNK func_800AD594();
extern u8 D_8006CCD8;
extern u8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_80170E9C;
extern u8 D_80174F30;
extern u8 D_80174F38;
extern u8 D_80174F40;


typedef struct S_80172524_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
} S_80172524_0;   /* arg0 in func_80172524 */




void func_80172524(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5 };
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;
    register u8 *tail_arg ASM_REG("$5"); /* MATCH: shared animation pointer stays in a1 across the incoming jumps. */

    temp_v1 = ((S_80172524_0 *)arg0)->unk_9B.n;
    if (temp_v1 >= 6U) {
        goto block_31;
    }
    (void)jt_keep; goto *D_80170838[(u32)(temp_v1)];
jt_c0:
    ((S_80172524_0 *)arg0)->unk_98 = (u16) (((S_80172524_0 *)arg0)->unk_98 | 8);
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        goto block_5;
    }
    ((S_80172524_0 *)arg0)->unk_9B.n = 5U;
    ((S_80172524_0 *)arg0)->unk_96.u = 0U;
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v | 0x6000);
    func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
    return;
block_5:
    /* LEAD 29: keep block_5's D_8006CCD8 base lui out of the beqz delay slot
     * (retail fills that slot with the fall-through move a0,s3). */
    __asm__ __volatile__("" ::: "memory");
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = (s32) (*(s16 *)(&D_8006CCD8 + (((u16) ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 >> 8) & 0xE)) << 0x14);
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = (s32) (*(s16 *)(&D_8006CCE8 + (((u16) ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 >> 8) & 0xE)) << 0x14);
    goto block_increment;
jt_c1:
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = (s32) ((s32) ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 >> 1);
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = (s32) ((s32) ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v >> 1);
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto block_31;
    }
    tail_arg = &D_80174F30;
    goto block_animation;
jt_c2:
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = (s32) ((s32) ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 >> 1);
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = (s32) ((s32) ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v >> 1);
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto block_31;
    }
    func_800A56E0(0x808);
    tail_arg = &D_80174F38;
    goto block_animation;
jt_c3:
    if (((Rec_D_80082E80 *)arg2)->unk_04.as_s8 != 2) {
        goto block_17;
    }
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x1000)) {
        goto block_17;
    }
    func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
    {
        register u16 six ASM_REG("$3") = 6;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        temp_v1 = ((S_80172524_0 *)arg0)->unk_9B.v;
        ((S_80172524_0 *)arg0)->unk_96.u = six;
    }
    goto block_increment_store;
block_17:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto block_31;
    }
    (*(M2C_UNK **)((u8 *)arg2 + (0x2C))) = &D_80174F40;
    func_80047784(arg2, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_80174F40), 0);
    func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
    ((S_80172524_0 *)arg0)->unk_9B.n = 5U;
    ((S_80172524_0 *)arg0)->unk_96.u = 0;
    return;
jt_c4:
    temp_v0 = ((S_80172524_0 *)arg0)->unk_96.u - 1;
    ((S_80172524_0 *)arg0)->unk_96.u = temp_v0;
    if ((s16) temp_v0 <= 0) {
        goto block_23;
    }
    {
        s32 coord = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
        s32 current = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = ((coord - current) << 0x10) / (s16) temp_v0;
    }
    {
        s32 coord = ((Rec_D_80082E80 *)arg2)->unk_25 << 6;
        s32 current = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = ((coord - current) << 0x10) / ((S_80172524_0 *)arg0)->unk_96.s;
    }
    goto block_23_tail;
block_23:
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
block_23_tail:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto block_31;
    }
    tail_arg = &D_80174F40;
block_animation:
    (*(M2C_UNK **)((u8 *)arg2 + (0x2C))) = (M2C_UNK *)tail_arg;
    func_80047784(arg2, *(u8 *)((((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7) + (u32)tail_arg), 0);
block_increment:
    temp_v1 = ((S_80172524_0 *)arg0)->unk_9B.n;
block_increment_store:
    ((S_80172524_0 *)arg0)->unk_9B.n = temp_v1 + 1;
    return;
jt_c5:
    temp_v0_2 = ((S_80172524_0 *)arg0)->unk_96.u - 1;
    ((S_80172524_0 *)arg0)->unk_96.u = temp_v0_2;
    if ((s16) temp_v0_2 <= 0) {
        goto block_29;
    }
    {
        s32 coord = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
        s32 current = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = ((coord - current) << 0x10) / (s16) temp_v0_2;
    }
    {
        s32 coord = ((Rec_D_80082E80 *)arg2)->unk_25 << 6;
        s32 current = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = ((coord - current) << 0x10) / ((S_80172524_0 *)arg0)->unk_96.s;
    }
    goto block_29_tail;
block_29:
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
block_29_tail:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto block_31;
    }
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    ((S_80172524_0 *)arg0)->unk_98 = (u16) (((S_80172524_0 *)arg0)->unk_98 & 0xFFF7);
    func_800AD594(arg3, 0x100);
    ((S_80172524_0 *)arg0)->unk_8C = &D_80170E9C;
    D_8008346C = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = (u16) ((*(u16 *)((u8 *)arg3 + (0x46))) & 0x7FFF);
    func_800A4ACC(arg3);
block_31:
    return;
}
