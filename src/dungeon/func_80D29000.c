#include "common.h"

typedef long long s64;

typedef struct S_80D29000_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80D29000_0;   /* arg1 in BODY_NAME */

typedef struct S_80D29000_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80D29000_1;   /* arg2 in BODY_NAME */

typedef struct S_80D29000_2 {
    u8 pad_00[0x94];
    s16 unk_94;
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x10];
    void * unk_A8;
} S_80D29000_2;   /* arg0 in BODY_NAME */

typedef struct S_80D29000_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D29000_3;   /* other in BODY_NAME */



extern void func_800478B8(void *);
extern s32 func_80065420(void *, void *, void *, void *);

extern s32 D_800814A0;
extern s16 D_80083228;
extern s8 D_800DCECC[8];

typedef struct StackWork {
    u16 xyz[3];
    u16 pad;
    s64 out18;
    s32 out20;
    s32 out24;
} StackWork;

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80D29000")
    __attribute__((section(".text.func_80D29000"), aligned(4))) = {
    0x80159190, 0x80159358, 0x80159B58, 0x80159B58,
    0x80159B58, 0x80159B84, 0x80159B04, 0x80159B04,
    0x80159B04, 0x80159AB0, 0x80159AE8, 0x80159B84,
    0x80159B84, 0x80159B48, 0x00000001, 0x00010001,
    0x00010000, 0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFF0000, 0xFFFF0001, 0x8015B76C, 0x8015B764,
    0x8015B75C, 0x8015B774, 0x8015B71C, 0x8015B714,
    0x8015B70C,
};
__asm__(".globl func_80D29000\n"
        ".size func_80D29000, 720");
#define BODY_NAME func_80D29074
#else
#define BODY_NAME func_80D29000
#endif

/* Advance and damp effect motion, expand and fade its sprite, and mark expiration. */
void BODY_NAME(void *effect, void *motion, void *sprite)
{
    StackWork projection;
    s16 next_life;
    s16 life;
    s32 motion_depth;
    s32 render_value;
    void *anchor_pos;

    ((S_80D29000_0 *)motion)->unk_00.at00.v += ((S_80D29000_0 *)motion)->unk_0C;
    ((S_80D29000_0 *)motion)->unk_04.at00.v += ((S_80D29000_0 *)motion)->unk_10;
    ((S_80D29000_0 *)motion)->unk_08.at00.v += ((S_80D29000_0 *)motion)->unk_14;
    ((S_80D29000_0 *)motion)->unk_0C = ((S_80D29000_0 *)motion)->unk_0C * 9 / 10;
    ((S_80D29000_0 *)motion)->unk_10 = ((S_80D29000_0 *)motion)->unk_10 * 9 / 10;
    ((S_80D29000_0 *)motion)->unk_14 = ((S_80D29000_0 *)motion)->unk_14 * 8 / 10;

    if (((S_80D29000_1 *)sprite)->unk_1C == 0) {
        ((S_80D29000_1 *)sprite)->unk_1E = 0x400;
        ((S_80D29000_1 *)sprite)->unk_1C = 0x400;
    }

    render_value = ((S_80D29000_1 *)sprite)->unk_1E + 0x32;
    ((S_80D29000_1 *)sprite)->unk_1E = render_value;
    ((S_80D29000_1 *)sprite)->unk_1C = render_value;

    projection.xyz[0] = ((S_80D29000_0 *)motion)->unk_00.at02.v;
    projection.xyz[1] = ((S_80D29000_0 *)motion)->unk_04.at02.v;
    projection.xyz[2] = ((S_80D29000_0 *)motion)->unk_08.at02.v;
    motion_depth = func_80065420(projection.xyz, &projection.out18, &projection.out20, &projection.out24);

    anchor_pos = ((S_80D29000_2 *)effect)->unk_A8;
    projection.xyz[0] = ((S_80D29000_3 *)anchor_pos)->unk_02;
    projection.xyz[1] = ((S_80D29000_3 *)anchor_pos)->unk_06;
    projection.xyz[2] = ((S_80D29000_3 *)anchor_pos)->unk_0A;
    ((S_80D29000_1 *)sprite)->unk_06 = motion_depth -
        func_80065420(projection.xyz, &projection.out18, &projection.out20, &projection.out24) -
        D_800DCECC[((D_80083228 + ((S_80D29000_2 *)effect)->unk_94 + 0x100) >> 9) & 7] * 2;

    life = ((S_80D29000_2 *)effect)->unk_96.s;
    if (life < 10) {
        ((S_80D29000_1 *)sprite)->unk_10 = 0x20;
        ((S_80D29000_1 *)sprite)->unk_12 = 0xFF80;
        ((S_80D29000_1 *)sprite)->unk_14 |= 0xC;
        render_value = (life << 7) / 10;
        ((S_80D29000_1 *)sprite)->unk_0E = render_value;
        ((S_80D29000_1 *)sprite)->unk_0D = render_value;
        ((S_80D29000_1 *)sprite)->unk_0C = render_value;
    }

    func_800478B8(sprite);
    next_life = ((S_80D29000_2 *)effect)->unk_96.u - 1;
    ((S_80D29000_2 *)effect)->unk_96.u = next_life;
    if ((next_life << 16) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
