#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80175CD8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    u8 pad_A4[0x10];
    union { s16 s; u16 u; } unk_B4;   /* accessed as both */
} S_80175CD8_0;   /* arg0 in func_80175CD8 */


typedef struct S_80175CD8_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175CD8_3;   /* arg1 in func_80175CD8 */

typedef struct S_80175CD8_4 {
    u8 pad_00[0x14];
    u32 unk_14;
} S_80175CD8_4;   /* held in func_80175CD8 */

typedef struct S_80175CD8_5 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    u32 unk_1C;
    u8 pad_20[0x68];
    union { u16 s; s16 u; } unk_88;   /* accessed as both */
} S_80175CD8_5;   /* globals in func_80175CD8 */

typedef struct S_80175CD8_6 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x7A];
    s16 unk_92;
} S_80175CD8_6;   /* global_ptr in func_80175CD8 */


typedef struct WorldStatePage {
    u8 pad_0000[0x2090];
    s32 actionMode;
} WorldStatePage;

extern s32 D_80012090;
extern s16 D_80081468[3];
extern s16 D_8008146C;
extern u8 D_80082E6B;
extern s16 D_800DCED4[];
extern u8 D_800E2348[];
extern u8 D_800E2368[];
extern u8 D_80170940[];
extern u8 D_80170950[];
extern u8 D_80170988[];
extern u8 D_80170994[];
extern u8 D_801709B8[];
extern s32 D_80171F1C;

extern void func_80040AA0(u8);
extern s32 func_800429E4(void *);
extern void func_80047784(void *, u8, s32);
extern void func_800481E0(void);
extern void func_800945E8(void *);
extern void func_800948BC(void);
extern void func_80094E34(void);
extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 func_8009929C(s8 value, s8 *dest);
extern s32 func_80099734(void *record, u8 *out);
extern void func_800A56E0(s32);
extern void func_800A5720(s8 *text);
extern void func_800A6780(void);
extern void func_800AD594(void *, s32);
extern void func_800C542C(void *owner, s16 effect_value, s16 direction, s16 effect_mode);

/* Updates the actor's approach, descent, and return sequence. */
void func_80175CD8(void *action, void *motion, void *sprite, void *actor)
{
    s32 slot;
    s32 companion_type;
    s32 facing;
    s32 text_end;
    s32 ticks_left;
    s32 target_x;
    s32 target_y;
    s32 target_z;
    s32 approach_ticks;
    s32 return_ticks;
    s32 direction;
    s32 text_start;
    u8 *companion;

    {
        u32 state = ((S_80175CD8_0 *)action)->unk_9B;

        switch (state) {
        case 0:
        {
            u8 *effect_actor;
            s32 effect_flags;
            s32 tile_dx;
            s32 tile_dy;
            u8 target_tile_x;
            u8 sprite_tile_x;
            u8 sprite_tile_y;
            u8 target_tile_y;

            effect_actor = actor;
            effect_flags = 0x2000;
            target_tile_x = D_80082E80.tileX;
            sprite_tile_x = ((Rec_D_80082E80 *)sprite)->unk_24;
            sprite_tile_y = ((Rec_D_80082E80 *)sprite)->unk_25;
            tile_dx = target_tile_x - sprite_tile_x;
            target_tile_y = D_80082E80.tileY;
            tile_dx = __builtin_abs(tile_dx);
            tile_dy = target_tile_y - sprite_tile_y;
            tile_dy = __builtin_abs(tile_dy);
            ((S_80175CD8_0 *)action)->unk_96.s = ((tile_dx + tile_dy) * 4) + 9;
            ((S_80175CD8_0 *)action)->unk_9B++;
            func_800AD594(effect_actor, effect_flags);
        }

            if (D_80082E80.tileX == ((Rec_D_80082E80 *)sprite)->unk_24) {
                if (D_80082E80.tileY > ((Rec_D_80082E80 *)sprite)->unk_25) {
                    direction = 2;
                } else {
                    direction = 6;
                }
            } else if (D_80082E80.tileY == ((Rec_D_80082E80 *)sprite)->unk_25) {
                direction = (((Rec_D_80082E80 *)sprite)->unk_24 >= D_80082E80.tileX) * 4;
            } else if (((Rec_D_80082E80 *)sprite)->unk_24 < D_80082E80.tileX) {
                if (((Rec_D_80082E80 *)sprite)->unk_25 < D_80082E80.tileY) {
                    direction = 1;
                } else {
                    direction = 7;
                }
            } else if (((Rec_D_80082E80 *)sprite)->unk_25 < D_80082E80.tileY) {
                direction = 3;
            } else {
                direction = 5;
            }
            (*(s16 *)((u8 *)actor + 0x2A)) = direction << 9;

            if ((D_80012090 != 0) || (D_8008146C != 0x28)) {
                if ((*(u8 *)((u8 *)&((EntityRec *)actor)->unk_10 + 1)) >= D_8008146C) {
                    slot = 0;
                    do {
                        companion = *(u8 **)(((u8 *)D_800E3D7C) + 0xAC + slot * 4);
                        if ((companion != 0) && (companion != (u8 *)actor)) {
                            companion_type = func_800429E4(companion);
                            func_800C542C(companion, D_800DCED4[companion_type], (s16)slot, 0);
                        }
                        slot++;
                    } while (slot < 2);
                }
            }

        case 1:
            target_x = ((D_80082E80.tileX << 6) + 0x20) << 16;
            target_y = ((D_80082E80.tileY << 6) + 0x20) << 16;
            target_z = D_80083780.z.v - 0x600000;
            approach_ticks = ((S_80175CD8_0 *)action)->unk_96.s;
            if (approach_ticks >= 0xE) {
                ((S_80175CD8_3 *)motion)->unk_0C = (target_x
                    - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / (approach_ticks - 9);
                ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
                    (((S_80175CD8_0 *)action)->unk_96.s - 9);
                ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
                    (((S_80175CD8_0 *)action)->unk_96.s - 9);
            } else if (approach_ticks >= 0xB) {
                ((S_80175CD8_3 *)motion)->unk_0C = (target_x
                    - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / (approach_ticks - 7);
                ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
                    (((S_80175CD8_0 *)action)->unk_96.s - 7);
                ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
                    (((S_80175CD8_0 *)action)->unk_96.s - 7);
            } else if (approach_ticks >= 5) {
                ((S_80175CD8_3 *)motion)->unk_0C = (target_x
                    - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / (approach_ticks - 2);
                ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
                    (((S_80175CD8_0 *)action)->unk_96.s - 2);
                ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
                    (((S_80175CD8_0 *)action)->unk_96.s - 2);
            } else {
                ((S_80175CD8_3 *)motion)->unk_0C = (target_x
                    - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / approach_ticks;
                ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
                    ((S_80175CD8_0 *)action)->unk_96.s;
                ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
                    ((S_80175CD8_0 *)action)->unk_96.s;
            }
            goto decrement_timer;

        case 2:
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_800E2368;
            facing = (gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9;
            func_80047784(sprite, D_800E2368[facing & 7], 0);
            ((S_80175CD8_0 *)action)->unk_96.s = 0;
            ((S_80175CD8_0 *)action)->unk_9B++;
            func_80094E34();
            return;

        case 3:
        {
            u16 old_timer = ((S_80175CD8_0 *)action)->unk_96.u;

            ((S_80175CD8_0 *)action)->unk_96.s = old_timer + 1;
            if ((s16)old_timer < 7) {
                return;
            }
        }
            ((S_80175CD8_0 *)action)->unk_9B++;
            {
                u8 *player = ((u8 *)D_800E3D7C);

                ((S_80175CD8_0 *)action)->unk_96.s = 0;
                ((S_80175CD8_4 *)player)->unk_14 |= 0x100000;
            }
            func_800A56E0(0x603);
            return;

        case 4:
        {
            u8 *scene = ((u8 *)(&D_80083780));
            s32 fall_speed = (s32)0xFFF40000;

            ((S_80175CD8_3 *)motion)->unk_14 = fall_speed;
            ((S_80175CD8_5 *)scene)->unk_08 += fall_speed;
        }
            {
                u16 old_timer = ((S_80175CD8_0 *)action)->unk_96.u;

                ((S_80175CD8_0 *)action)->unk_96.s = old_timer + 1;
                if ((s16)old_timer < 0x1B) {
                    return;
                }
            }
            ((S_80175CD8_0 *)action)->unk_96.s = 0;

            if ((((WorldStatePage *)0x80010000)->actionMode == 0) && (D_8008146C == 0x28)) {
                ((S_80175CD8_0 *)action)->unk_9B = 7;
            } else if ((*(u8 *)((u8 *)&((EntityRec *)actor)->unk_10 + 1)) >= D_8008146C) {
                ((S_80175CD8_0 *)action)->unk_9B++;
            } else {
                ((S_80175CD8_0 *)action)->unk_9B = 7;
            }
            return;

        case 5:
            ((S_80175CD8_0 *)action)->unk_96.s = 0;
            ((S_80175CD8_0 *)action)->unk_9B++;
            return;

        case 6:
            func_800945E8(((u8 *)D_800E3D7C));
            func_800948BC();
            func_800A6780();
            {
                u8 *scene_page;
                u8 *counter_page;
                s16 *floor_stats;
                u8 map_id;
                s32 visit_count;
                s32 floor_count;
                s32 next_visit;
                s32 next_floor;

                scene_page = &D_80082E6B;
                counter_page = (u8 *)0x80010000;
                floor_stats = D_80081468;
                map_id = *scene_page;

                visit_count = *(s32 *)(counter_page + 0x234);
                floor_count = *(u16 *)((u8 *)floor_stats + 4);
                next_visit = visit_count + 1;
                next_floor = floor_count + 1;
                *(s32 *)(counter_page + 0x234) = next_visit;
                *(u16 *)((u8 *)floor_stats + 4) = next_floor;
                func_80040AA0(map_id);
            }
            func_800481E0();
            ((S_80175CD8_3 *)motion)->unk_14 = 0;
            ((S_80175CD8_3 *)motion)->unk_10 = 0;
            ((S_80175CD8_3 *)motion)->unk_0C = 0;
            ((S_80175CD8_0 *)action)->unk_96.s = 0;
            ((S_80175CD8_0 *)action)->unk_9B = 0x14;
            goto clear_object_flag;

        case 7:
        {
            u8 *player = ((u8 *)D_800E3D7C);
            u8 *scene;
            u8 *scene_base;
            u32 player_flags;
            u16 height;

            player_flags = ((S_80175CD8_6 *)player)->unk_14 & 0xFFEFFFFF;

            scene_base = ((u8 *)(&D_80083498));
            scene = scene_base + 0x20;
            ((S_80175CD8_6 *)player)->unk_14 = player_flags;
            height = ((u16)D_80083780.z.w.i) - ((S_80175CD8_5 *)scene)->unk_88.s;
            ((S_80175CD8_6 *)player)->unk_92 = height;
            ((S_80175CD8_5 *)scene)->unk_88.u = height;
            ((S_80175CD8_5 *)scene)->unk_1C |= 0x40000000;
        }
            (*(s16 *)((u8 *)action + 0x96)) = 0x28;
            ((S_80175CD8_0 *)action)->unk_9B++;

            if ((D_80012090 != 0) || (D_8008146C != 0x28)) {
                text_start = func_800990FC();
                text_end = func_80099194(D_80170940, text_start);
                text_end = func_8009929C(0xA, text_end);
                text_end = func_80099194(D_80170950, text_end);
                text_end = func_8009929C(0xA, text_end);
                text_end = func_80099194(D_80170988, text_end);
                text_end = func_80099734(actor, text_end);
                text_end = func_80099194(D_80170994, text_end);
            } else {
                text_start = func_800990FC();
                text_end = func_80099194(D_801709B8, text_start);
            }
            func_80099290(text_end);
            func_800A5720(text_start);

        case 8:
            target_x = ((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 16;
            target_y = ((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 16;
            target_z = (((S_80175CD8_0 *)action)->unk_B4.s - 0x20) << 16;
            return_ticks = ((S_80175CD8_0 *)action)->unk_96.s;
            if (return_ticks >= 0xE) {
                ((S_80175CD8_3 *)motion)->unk_0C = (target_x - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / (return_ticks
                    - 9);
                ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
                    (((S_80175CD8_0 *)action)->unk_96.s - 9);
                ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
                    (((S_80175CD8_0 *)action)->unk_96.s - 9);
            } else if (return_ticks >= 0xB) {
                ((S_80175CD8_3 *)motion)->unk_0C = (target_x - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / (return_ticks
                    - 7);
                ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
                    (((S_80175CD8_0 *)action)->unk_96.s - 7);
                ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
                    (((S_80175CD8_0 *)action)->unk_96.s - 7);
            } else if (return_ticks >= 5) {
                ((S_80175CD8_3 *)motion)->unk_0C = (target_x - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / (return_ticks
                    - 2);
                ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
                    (((S_80175CD8_0 *)action)->unk_96.s - 2);
                ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
                    (((S_80175CD8_0 *)action)->unk_96.s - 2);
            } else {
                ((S_80175CD8_3 *)motion)->unk_0C = (target_x - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / return_ticks;
                ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
                    ((S_80175CD8_0 *)action)->unk_96.s;
                ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
                    ((S_80175CD8_0 *)action)->unk_96.s;
            }

decrement_timer:
            ticks_left = ((S_80175CD8_0 *)action)->unk_96.u - 1;
            ((S_80175CD8_0 *)action)->unk_96.s = ticks_left;
            if ((ticks_left << 16) != 0) {
                return;
            }
            ((S_80175CD8_0 *)action)->unk_96.s = 0;
            ((S_80175CD8_0 *)action)->unk_9B++;
            ((S_80175CD8_3 *)motion)->unk_14 = 0;
            ((S_80175CD8_3 *)motion)->unk_10 = 0;
            ((S_80175CD8_3 *)motion)->unk_0C = 0;
            return;

        case 9:
            ((S_80175CD8_3 *)motion)->unk_14 = 0;
            ((S_80175CD8_3 *)motion)->unk_10 = 0;
            ((S_80175CD8_3 *)motion)->unk_0C = 0;
            ((S_80175CD8_0 *)action)->unk_8C = &D_80171F1C;
            ((S_80175CD8_0 *)action)->unk_9A = 0xE;
            dungeonStatus.unk_0C = 0;
            ((EntityRec *)actor)->flags1C |= 0x40000;
            (*(u16 *)((u8 *)action + 0x98)) &= 0xFFF7;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_800E2348;
            facing = (gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9;
            func_80047784(sprite, D_800E2348[facing & 7], 0);
            ((Rec_D_80082E80 *)sprite)->unk_05.as_u8 = 1;
            ((S_80175CD8_0 *)action)->unk_A2.s = 0;
            ((S_80175CD8_0 *)action)->unk_9E = 0;
            ((S_80175CD8_0 *)action)->unk_90.at02.v = -0x20;
            ((EntityRec *)actor)->unk_88 = ((S_80175CD8_0 *)action)->unk_B4.u;
            ((S_80175CD8_3 *)motion)->unk_00.at02.v = (((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20;
            ((S_80175CD8_3 *)motion)->unk_04.at02.v = (((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20;
            ((S_80175CD8_3 *)motion)->unk_0A = ((u16)((EntityRec *)actor)->unk_88) +
                ((S_80175CD8_0 *)action)->unk_90.at02u.v - ((S_80175CD8_0 *)action)->unk_A2.u;

clear_object_flag:
            ((EntityRec *)actor)->unk_46 &= 0x7FFF;

        case 20:
        default:
            break;
        }
    }
    return;
}

#undef FIELD
