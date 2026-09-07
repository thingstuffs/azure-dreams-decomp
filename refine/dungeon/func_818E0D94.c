#include "common.h"

typedef struct S_818E0D94_0_pre {
    u16 unk_00;
} S_818E0D94_0_pre;   /* the 0x2 bytes before arg0 in func_818E0D94, addressed as arg0[-1] */

typedef struct S_818E0D94_0 {
    void * unk_00;
    u8 pad_04[0x14];
    u16 unk_18;
    u8 pad_1A[0x2E];
    union { u16 u16; s16 s16; u8 u8; } unk_48;   /* accessed as both */
} S_818E0D94_0;   /* arg0 in func_818E0D94 */

typedef struct S_818E0D94_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_818E0D94_1;   /* inner in func_818E0D94 */

typedef struct S_818E0D94_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x6];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_818E0D94_2;   /* arg2 in func_818E0D94 */

typedef struct S_818E0D94_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818E0D94_3;   /* arg1 in func_818E0D94 */



typedef struct {
    u8 bytes[8];
} Unaligned8;

typedef struct {
    void *field0;
    void *field4;
    Unaligned8 field8;
    Unaligned8 field10;
    s16 field18;
    s16 field1A;
    u32 unused1C;
} CallRecord;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} OutputVector;

extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern s32 rand(void);
extern void func_800DBA90(void *);
extern u32 D_800814A0;

/* Advances effect motion and sprite appearance, marking completion after 32 ticks. */
void func_818E0D94(void *effect, S_818E0D94_3 *position, S_818E0D94_2 *sprite)
{
    CallRecord transform;
    OutputVector offset;
    S_818E0D94_1 *effect_state;
    u16 size;
    s8 shade;

    effect_state = ((S_818E0D94_0 *)effect)->unk_00;
    effect_state->unk_52 |= 0x8000;
    ((S_818E0D94_0 *)effect)->unk_48.u16++;

    size = sprite->unk_1E - 0x50;
    sprite->unk_1E = size;
    sprite->unk_1C = size;

    {
        register s32 phase ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
        s32 height_jitter;
        s32 height;

        height_jitter = rand() & 0x3F;
        phase = ((S_818E0D94_0 *)effect)->unk_48.s16 * 0x32;
        ASM_KEEP(phase);   /* MATCH pin: keeps a statement from moving across a call/branch */
        height = ((S_818E0D94_0 *)effect)->unk_18;
        phase += 0xC8;
        height += 0x200;
        height += height_jitter;
        ((S_818E0D94_0 *)effect)->unk_18 = height;
        offset.x = func_800644B8(phase) / 80;
    }
    offset.y = 0;
    {
        s32 z_jitter;
        s32 neg_tick;

        z_jitter = rand() & 3;
        neg_tick = 0 - ((S_818E0D94_0 *)effect)->unk_48.s16;
        offset.z = (neg_tick * 4) + z_jitter - 1;
    }

    shade = ((u8)offset.x + 0x28) - ((S_818E0D94_0 *)effect)->unk_48.u8;
    sprite->unk_0D = shade;
    sprite->unk_0C = shade;
    sprite->unk_0E = ((u8)offset.x + 0x60) - ((S_818E0D94_0 *)effect)->unk_48.u8;

    transform.field0 = &offset;
    transform.field4 = &offset;
    transform.field8 = *(Unaligned8 *)((u8 *)effect + 0x14);
    transform.field10 = *(Unaligned8 *)((u8 *)effect + 0x0C);
    transform.field18 = 1;
    transform.field1A = 0;
    func_800DBA90(&transform);

    position->unk_02 = offset.x;
    position->unk_06 = offset.y;
    position->unk_0A = offset.z;
    func_800478B8(sprite);

    if (sprite->unk_14 & 0x6000) {
        sprite->unk_04 = 0;
        sprite->unk_05 = 0;
    }

    if (((S_818E0D94_0 *)effect)->unk_48.s16 >= 0x20) {
        u32 *flags_base;

        ((S_818E0D94_0_pre *)effect)[-1].unk_00 |= 0x8000;
        flags_base = (u32 *)0x80080000;
        ASM_KEEP(flags_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        flags_base[0x528] |= 0x8000;
    }
}
