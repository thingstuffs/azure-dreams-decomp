#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8196ACE4_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; volatile u16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_8196ACE4_0;   /* arg1 in func_8196ACE4 */

typedef struct S_8196ACE4_1_pre {
    u16 unk_00;
} S_8196ACE4_1_pre;   /* the 0x2 bytes before arg0 in func_8196ACE4, addressed as arg0[-1] */

typedef struct S_8196ACE4_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x4];
    u16 unk_34;
    u8 pad_36[0x56];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
} S_8196ACE4_1;   /* arg0 in func_8196ACE4 */

typedef struct S_8196ACE4_2 {
    u8 pad_00[0x69B4];
    s16 unk_69B4;
} S_8196ACE4_2;   /* page_8002 in func_8196ACE4 */


typedef struct S_8196ACE4_4 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_8196ACE4_4;   /* page_8008 in func_8196ACE4 */


M2C_UNK func_800478B8();                      /* extern */
s32 rand();                                /* extern */
s32 func_800A45D8();                   /* extern */
s16 func_800BCB04();                   /* extern */
extern s16 D_800269B4[];
extern M2C_UNK D_800814A0;

/* Update effect motion, collisions, sprite fading and growth, and expiration. */
void func_8196ACE4(void *effect, S_8196ACE4_0 *position, Rec_D_80082E80 *sprite) {
    s32 height;
    s16 life_left;
    s32 brightness;
    u16 anim_tick;
    u16 scale_x;
    u16 scale_y;
    u16 collide_x;
    u16 collide_y;
    s32 collide_z;

    position->unk_00.at00.v = (s32) (position->unk_00.at00.v + ((S_8196ACE4_1 *)effect)->unk_8C);
    ((S_8196ACE4_1 *)effect)->unk_8C = (s32) (((S_8196ACE4_1 *)effect)->unk_8C + ((S_8196ACE4_1 *)effect)->unk_98);
    collide_x = position->unk_00.at02.v;
    collide_y = position->unk_04.at02.v;
    collide_z = position->unk_08.at02.v;
    {
        u8 *collision_page = (u8 *)&D_800269B4 - 0x69B4;
        ((S_8196ACE4_2 *)collision_page)->unk_69B4 = 1;
    }
    if ((func_800BCB04(collide_x, collide_y, collide_z) < 0x200) && ((func_800A45D8(position->unk_00.at02.v, position->unk_04.at02.v, position->unk_08.at02.v) << 0x10) != 0)) {
        position->unk_00.at00.v = (s32) (position->unk_00.at00.v - ((S_8196ACE4_1 *)effect)->unk_8C);
        ((S_8196ACE4_1 *)effect)->unk_8C = 0;
        ((S_8196ACE4_1 *)effect)->unk_98 = 0;
    }
    position->unk_04.at00.v = (s32) (position->unk_04.at00.v + ((S_8196ACE4_1 *)effect)->unk_90);
    ((S_8196ACE4_1 *)effect)->unk_90 = (s32) (((S_8196ACE4_1 *)effect)->unk_90 + ((S_8196ACE4_1 *)effect)->unk_9C);
    if ((func_800BCB04(position->unk_00.at02.v, position->unk_04.at02.v, position->unk_08.at02.v) < 0x200) && ((func_800A45D8(position->unk_00.at02.v, position->unk_04.at02.v, position->unk_08.at02.v) << 0x10) != 0)) {
        position->unk_04.at00.v = (s32) (position->unk_04.at00.v - ((S_8196ACE4_1 *)effect)->unk_90);
        ((S_8196ACE4_1 *)effect)->unk_90 = 0;
        ((S_8196ACE4_1 *)effect)->unk_9C = 0;
    }
    position->unk_08.at00.v = (s32) (position->unk_08.at00.v + ((S_8196ACE4_1 *)effect)->unk_94);
    {
        s32 accel_z = ((S_8196ACE4_1 *)effect)->unk_A0;
        ((S_8196ACE4_1 *)effect)->unk_94 += accel_z;
    }
    ((S_8196ACE4_1 *)effect)->unk_8C = (s32) ((((S_8196ACE4_1 *)effect)->unk_8C * 0x60) / 100);
    ((S_8196ACE4_1 *)effect)->unk_90 = (s32) ((((S_8196ACE4_1 *)effect)->unk_90 * 0x60) / 100);
    height = position->unk_08.at02.v;
    if ((func_800BCB04(position->unk_00.at02.v, position->unk_04.at02.v, (s16) (position->unk_08.at02u.v - 4)) - 0x10) < height) {
        ((S_8196ACE4_1 *)effect)->unk_94 = 0;
        position->unk_08.at02.v = (s16) (func_800BCB04(position->unk_00.at02.v, position->unk_04.at02.v, (s16) ((u16) position->unk_08.at02.v - 4)) - 0x11);
        position->unk_08.at00u.v = 0;
        if (((S_8196ACE4_1 *)effect)->unk_2A == 0) {
            ((S_8196ACE4_1 *)effect)->unk_2A = 1;
            ((S_8196ACE4_1 *)effect)->unk_8C = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 2);
            ((S_8196ACE4_1 *)effect)->unk_90 = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 2);
        }
    }
    brightness = (s32) (((S_8196ACE4_1 *)effect)->unk_2C << 7) / (s16) ((S_8196ACE4_1 *)effect)->unk_2E;
    sprite->unk_0C.at02_s8.v = (s8) brightness;
    sprite->unk_0C.at01_s8.v = (s8) brightness;
    sprite->unk_0C.at00_s8.v = (s8) brightness;
    anim_tick = ((S_8196ACE4_1 *)effect)->unk_34 + 1;
    ((S_8196ACE4_1 *)effect)->unk_34 = anim_tick;
    if ((s16) anim_tick == 3) {
        func_800478B8(sprite);
        ((S_8196ACE4_1 *)effect)->unk_34 = 0U;
    }
    scale_x = sprite->unk_1C.at00_u16.v + 0xC8;
    sprite->unk_1C.at00_u16.v = scale_x;
    if ((u32) (scale_x & 0xFFFF) >= 0x1001U) {
        sprite->unk_1C.at00_u16.v = 0x1000U;
    }
    scale_y = sprite->unk_1C.at02_u16.v + 0xC8;
    sprite->unk_1C.at02_u16.v = scale_y;
    if ((u32) (scale_y & 0xFFFF) >= 0x1001U) {
        sprite->unk_1C.at02_u16.v = 0x1000U;
    }
    life_left = (u16) ((S_8196ACE4_1 *)effect)->unk_2C - 1;
    ((S_8196ACE4_1 *)effect)->unk_2C = life_left;
    if ((life_left << 0x10) <= 0) {
        ((S_8196ACE4_1_pre *)effect)[-1].unk_00 = (u16) (((S_8196ACE4_1_pre *)effect)[-1].unk_00 | 0x8000);
        {
            u8 *status_page = (u8 *)0x80080000;
            ((S_8196ACE4_4 *)status_page)->unk_14A0 |= 0x8000;
        }
    }
    if (sprite->unk_14.at00_u16.v & 0x8000) {
        ((S_8196ACE4_1_pre *)effect)[-1].unk_00 = (u16) (((S_8196ACE4_1_pre *)effect)[-1].unk_00 | 0x8000);
        {
            u8 *status_page = (u8 *)0x80080000;
            ((S_8196ACE4_4 *)status_page)->unk_14A0 |= 0x8000;
        }
    }
}
