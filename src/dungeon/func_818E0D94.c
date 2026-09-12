#include "common.h"
#include "records/Rec_D_80082E80.h"

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
void func_818E0D94(void *effect, S_818E0D94_3 *position, Rec_D_80082E80 *sprite)
{
    CallRecord transform;
    OutputVector offset;
    S_818E0D94_1 *effect_state;
    u16 size;
    s8 shade;

    effect_state = ((S_818E0D94_0 *)effect)->unk_00;
    effect_state->unk_52 |= 0x8000;
    ((S_818E0D94_0 *)effect)->unk_48.u16++;

    size = sprite->unk_1C.at02_u16.v - 0x50;
    sprite->unk_1C.at02_u16.v = size;
    sprite->unk_1C.at00_u16.v = size;

    {
        register s32 phase ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 height_jitter;
        s32 height;

        height_jitter = rand() & 0x3F;
        phase = ((S_818E0D94_0 *)effect)->unk_48.s16 * 0x32;
        ASM_KEEP(phase);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
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
    sprite->unk_0C.at01_s8.v = shade;
    sprite->unk_0C.at00_s8.v = shade;
    sprite->unk_0C.at02_s8.v = ((u8)offset.x + 0x60) - ((S_818E0D94_0 *)effect)->unk_48.u8;

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

    if (sprite->unk_14.at00_u16.v & 0x6000) {
        sprite->unk_04.as_s8 = 0;
        sprite->unk_05.as_s8 = 0;
    }

    if (((S_818E0D94_0 *)effect)->unk_48.s16 >= 0x20) {
        u32 *flags_base;

        ((S_818E0D94_0_pre *)effect)[-1].unk_00 |= 0x8000;
        flags_base = (u32 *)0x80080000;
        flags_base[0x528] |= 0x8000;
    }
}
