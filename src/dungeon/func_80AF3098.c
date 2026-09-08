#include "common.h"

typedef struct S_80174898_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174898_0;   /* arg0 in func_80174898 */

typedef struct S_80174898_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174898_1;   /* arg1 in func_80174898 */

typedef struct S_80174898_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80174898_2;   /* arg2 in func_80174898 */

typedef struct S_80174898_3 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
} S_80174898_3;   /* arg3 in func_80174898 */



typedef struct OffsetPair {
    s16 x;
    s16 y;
} OffsetPair;

typedef struct OffsetTable {
    OffsetPair entries[8];
} OffsetTable;

extern s16 D_80083228;
extern s32 D_8008346C;
extern OffsetTable D_80170854;
extern s32 D_801717F4;
extern u8 D_80175988[];

extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_8017442C(void *, s32, s32, s32);
extern void func_80174670(void *, s32, s32, s32);

/* Updates timed directional effects, then resets animation and action state. */
void func_80174898(void *action, void *position, void *sprite, void *entity)
{
    OffsetTable direction_offsets = D_80170854;
    s32 offset_coord;

    switch (((S_80174898_0 *)action)->unk_9B) {
    case 0:
        ((S_80174898_1 *)position)->unk_14 = 0;
        ((S_80174898_1 *)position)->unk_10 = 0;
        ((S_80174898_1 *)position)->unk_0C = 0;
        ((S_80174898_0 *)action)->unk_96 = 0x14;
        ((S_80174898_0 *)action)->unk_9B++;
        break;

    case 1:
        if ((--((S_80174898_0 *)action)->unk_96 == 0x11) ||
            (((S_80174898_2 *)sprite)->unk_14 & 0x8000)) {
            OffsetPair *direction_offset;
            u16 flags;
            s32 height;
            s32 target_x;
            s32 tile_x;
            s32 y_offset;
            s32 x_offset;

            flags = ((S_80174898_2 *)sprite)->unk_14;
            ((S_80174898_2 *)sprite)->unk_14 = flags | 0x0800;
            height = ((S_80174898_1 *)position)->unk_0A;
            tile_x = ((S_80174898_2 *)sprite)->unk_24;
            direction_offset = &direction_offsets.entries[(((S_80174898_3 *)entity)->unk_2A.s >> 9) & 7];
            x_offset = direction_offset->x;
            target_x = tile_x + x_offset;
            y_offset = direction_offset->y;
            offset_coord = ((S_80174898_2 *)sprite)->unk_25 + y_offset;
            target_x = target_x & 0xFFFF;
            func_80174670(entity, target_x, offset_coord & 0xFFFF, height);
        }
        if ((((S_80174898_0 *)action)->unk_96 == 0x0A) ||
            (((S_80174898_2 *)sprite)->unk_14 & 0x8000)) {
            ((S_80174898_2 *)sprite)->unk_14 &= 0xF7FF;
            func_800A56E0(0x606);
        }
        if ((((S_80174898_0 *)action)->unk_96 == 9) ||
            (((S_80174898_2 *)sprite)->unk_14 & 0x8000)) {
            OffsetPair *direction_offset;
            u16 angle;
            s32 height;
            s32 tile_x;
            s32 x;
            s32 target_x;
            s32 y_offset;

            angle = ((S_80174898_3 *)entity)->unk_2A.s;
            direction_offset = direction_offsets.entries + ((angle >> 9) & 7);
            height = ((S_80174898_1 *)position)->unk_0A;
            tile_x = ((S_80174898_2 *)sprite)->unk_24;
            offset_coord = direction_offset->x;
            target_x = tile_x + offset_coord;
            y_offset = direction_offset->y;
            offset_coord = ((S_80174898_2 *)sprite)->unk_25 + y_offset;
            x = target_x & 0xFFFF;
            func_8017442C(entity, x, offset_coord & 0xFFFF, height);
        }
        if ((((S_80174898_0 *)action)->unk_96 <= 0) ||
            (((S_80174898_2 *)sprite)->unk_14 & 0x8000)) {
            ((S_80174898_0 *)action)->unk_96 = 0;
            ((S_80174898_0 *)action)->unk_9B++;
        }
        break;

    case 2:
        if (((S_80174898_2 *)sprite)->unk_14 & 0xE000) {
            ((S_80174898_1 *)position)->unk_14 = 0;
            ((S_80174898_1 *)position)->unk_10 = 0;
            ((S_80174898_1 *)position)->unk_0C = 0;
            func_800A2B04(position,
                ((S_80174898_2 *)sprite)->unk_24, ((S_80174898_2 *)sprite)->unk_25);
            if (((S_80174898_2 *)sprite)->unk_2C != D_80175988) {
                ((S_80174898_2 *)sprite)->unk_2C = D_80175988;
                ((S_80174898_2 *)sprite)->unk_14 &= 0xF7FF;
                func_80047784(sprite,
                    ((S_80174898_2 *)sprite)->unk_2C[((D_80083228 +
                        ((S_80174898_3 *)entity)->unk_2A.u + 0x100) >> 9) & 7],
                    0);
                ((S_80174898_0 *)action)->unk_9B++;
            }
        }
        break;

    case 3:
        func_800AD594(entity, 0x400);
        ((S_80174898_0 *)action)->unk_8C = &D_801717F4;
        D_8008346C = 0;
        (*(u16 *)((u8 *)entity + 0x46)) &= 0x7FFF;
        break;
    }
}

