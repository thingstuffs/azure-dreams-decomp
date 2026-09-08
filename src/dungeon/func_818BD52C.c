#include "common.h"

typedef struct S_818BD52C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818BD52C_0;   /* node in func_818BD52C */

typedef struct S_818BD52C_1 {
    s32 unk_00;
    u8 pad_04[0x14];
    void * unk_18;
} S_818BD52C_1;   /* arg0 in func_818BD52C */

typedef struct S_818BD52C_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
} S_818BD52C_2;   /* base in func_818BD52C */

typedef struct S_818BD52C_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818BD52C_3;   /* part in func_818BD52C */

typedef struct S_818BD52C_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BD52C_4;   /* coords in func_818BD52C */

typedef struct S_818BD52C_5 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818BD52C_5;   /* ((S_818BD52C_1 *)arg0)->unk_18 in func_818BD52C */


#define NORETURN

typedef struct {
    s32 word[6];
} Copy24;

extern void *func_8003FC64();
extern void func_8003DB94();
extern s32 rand();
extern void func_8004491C();
extern void func_80024F24() __attribute__((noreturn));

extern u8 D_80024BB0[];
extern s32 D_80045340;
extern u8 D_800DDC40[];
extern u8 D_800DEC70[];

/* Creates an effect node with phase-based color, random rotation, and offset coordinates. */
void *func_818BD52C(S_818BD52C_1 *owner, void *source_coords, s32 phase_index, s32 effect_param)
{
    s32 scaled_color;
    s32 color_level;
    s32 phase_half;
    s32 random_angle;
    s32 phase;
    s16 phase_bit;
    s16 phase_half_s16;
    S_818BD52C_3 *part;
    S_818BD52C_2 *base;
    S_818BD52C_4 *coords;
    void *node;
    s32 end_z;
    register void *pinned_node ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    node = func_8003FC64(0x212);
    if (node != 0) {
        ((S_818BD52C_0 *)node)->unk_10 = D_80024BB0;
        base = (u8 *)node + 0x20;
        ((S_818BD52C_0 *)node)->unk_20 = owner->unk_00;
        base->unk_04 = 0;
        base->unk_06 = 0x10;

        scaled_color = D_800DDC40[((S_818BD52C_5 *)(owner->unk_18))->unk_13] * 3;
        if (scaled_color < 0) {
            scaled_color += 3;
        }
        phase = (s16)(phase_index + 1);
        color_level = scaled_color >> 2;
        base->unk_0A = color_level;
        base->unk_08 = color_level;
        base->unk_0C = effect_param;

        part = ((S_818BD52C_0 *)node)->unk_0C;
        part->unk_0C = (phase / 4) * 0x80;
        phase_half = phase / 2;
        phase_half_s16 = phase_half;
        phase_bit = phase_half_s16 % 2;
        part->unk_0D = phase_bit * 0x80;
        phase_bit = phase - (phase_half * 2);
        part->unk_0E = phase_bit * 0x80;
        part->unk_12 = 0x7DCF;
        part->unk_14 |= 0xC;
        part->unk_10 |= 0x20;
        part->unk_14 |= 0x100;
        func_8003DB94(part, D_800DEC70, 0, phase);

        random_angle = rand();
        part->unk_1A = random_angle % 0x1000;
        part->unk_1E = 0xC00;
        part->unk_1C = 0xC00;
        func_8004491C(node, &D_80045340);

        coords = ((S_818BD52C_0 *)node)->unk_08;
        *(Copy24 *)coords = *(Copy24 *)source_coords;
        coords->unk_0C = coords->unk_00;
        coords->unk_10 = coords->unk_04;
        coords->unk_14 = coords->unk_08;
        pinned_node = node;
        end_z = coords->unk_14 + ((u32)base->unk_0A << 16);
        ASM_USE(pinned_node);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        coords->unk_14 = end_z;
        func_80024F24(coords, end_z);
    }
    return node;
}
