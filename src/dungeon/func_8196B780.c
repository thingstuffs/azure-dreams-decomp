#include "common.h"

typedef struct S_8196B780_0 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    u8 pad_2E[0x5E];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    u8 pad_98[0x8];
    s32 unk_A0;
} S_8196B780_0;   /* sub in func_8196B780 */

typedef struct S_8196B780_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8196B780_1;   /* node in func_8196B780 */

typedef struct S_8196B780_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_8196B780_2;   /* part in func_8196B780 */

typedef struct S_8196B780_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8196B780_3;   /* coords in func_8196B780 */

typedef struct S_8196B780_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8196B780_4;   /* coord_base in func_8196B780 */

typedef struct S_8196B780_5 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_8196B780_5;   /* arg0 in func_8196B780 */



typedef struct {
    u8 bytes[0x20];
} LocalPoints;

typedef struct {
    s16 x;
    u16 y;
} LocalPoint;

extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8003DB94();
extern s16 rand();

extern LocalPoints D_80024004;
extern u8 D_80024874[];
extern s32 D_80045340;
extern u8 D_80083780[];
extern u8 D_800DECF8[];

/* Spawns an effect with randomized position and direction-based motion. */
void func_8196B780(S_8196B780_5 *source, s32 unused_1, s32 unused_2, s32 x, s32 y,
                   s32 z)
{
    LocalPoints points;
    void *effect;
    S_8196B780_0 *motion;
    S_8196B780_2 *sprite;
    S_8196B780_3 *position;
    u8 *position_base;
    LocalPoint *point_base;
    LocalPoint *point;
    s32 point_index;
    register s32 offset_y ASM_REG("$19") = y;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 offset_z ASM_REG("$20") = z;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

    points = D_80024004;
    point_base = (LocalPoint *)&points;
    effect = func_8003FC64(0x212);
    if (effect != 0) {
        motion = (u8 *)effect + 0x20;
        motion->unk_2C = 0x4;
        ((S_8196B780_1 *)effect)->unk_10 = D_80024874;
        func_8004491C(effect, &D_80045340);

        sprite = ((S_8196B780_1 *)effect)->unk_0C;
        sprite->unk_10 = 0x20;
        sprite->unk_14 |= 0xC;
        sprite->unk_1A = (rand() & 7) << 9;
        sprite->unk_06 = 0;

        position = ((S_8196B780_1 *)effect)->unk_08;
        position_base = D_80083780;
        position->unk_02 = x;
        position->unk_06 = offset_y;
        position->unk_0A = offset_z;
        position->unk_02 += ((S_8196B780_4 *)position_base)->unk_02;
        position->unk_06 += ((S_8196B780_4 *)position_base)->unk_06;
        position->unk_0A += ((S_8196B780_4 *)position_base)->unk_0A;

        position->unk_02 += (rand() & 0x3F) - 0x20;
        position->unk_06 += (rand() & 0x3F) - 0x20;
        position->unk_0A += (rand() & 0x3F) - 0x40;

        motion->unk_94 = -0x60000;
        motion->unk_A0 = 0x20000;
        point = point_base;
        point_index = source->unk_26;
        point += point_index;
        motion->unk_8C = point->x << 18;
        point = point_base;
        point_index = source->unk_26;
        point += point_index;
        motion->unk_90 = point->y << 18;

        motion->unk_8C +=
            -0x80000 + ((rand() & 0x3FFF) << 6);
        motion->unk_90 +=
            -0x80000 + ((rand() & 0x3FFF) << 6);
        motion->unk_94 +=
            -0x80000 + ((rand() & 0x3FFF) << 6);

        sprite = ((S_8196B780_1 *)effect)->unk_0C;
        sprite->unk_1C = sprite->unk_1E = 0x1000;
        sprite->unk_0C = sprite->unk_0D =
            sprite->unk_0E = 0x80;
        sprite->unk_12 = 0x7DCE;
        sprite->unk_14 |= 0x100;
        func_8003DB94(sprite, D_800DECF8, 0);
    }
    ASM_KEEP(x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}

/* MECHANISM: The 0x20 byte-aligned copy object preserves the 0x58 frame and lwl/lwr stack copy;
   a held D_80083780 base plus RMW updates restores the load-delay moves and $a0 base.
   Epilogue-held arg pins and split point base/index/add produce the retail saved roles and $s6+$v0 order. */
