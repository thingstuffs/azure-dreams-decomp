#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80175CD8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_90;   /* overlapping accesses */
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



extern s32 D_80010234;
extern s32 D_80012090;
extern s16 D_80081468[3];
extern s16 D_8008146C;
extern u8 D_80082E6B;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern u8 D_80083780[];
extern s32 D_80083788;
extern u16 D_8008378A;
extern s16 D_800DCED4[];
extern u8 D_800E2348[];
extern u8 D_800E2368[];
extern u8 *D_800E3D7C;
extern u8 D_80170940[];
extern u8 D_80170950[];
extern u8 D_80170988[];
extern u8 D_80170994[];
extern u8 D_801709B8[];
extern void *const D_801709F0[];
extern s32 D_80171F1C;

extern void func_80040AA0(u8, s16 *);
extern s32 func_800429E4(void *);
extern void func_80047784(void *, u8, s32);
extern void func_800481E0(void);
extern void func_800945E8(void *);
extern void func_800948BC(void);
extern void func_80094E34(void);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099734(void *, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800A6780(void);
extern void func_800AD594(void *, s32);
extern void func_800C542C(void *, s16, s32, s32);

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
    u8 *target_tile;
    u8 *destination;
    u8 *companion;

    {
        static void *const state_labels[] = {
            &&state_0, &&state_1, &&state_2, &&state_3, &&state_4,
            &&state_5, &&state_6, &&state_7, &&state_8, &&state_9,
            &&done, &&done, &&done, &&done, &&done, &&done,
            &&done, &&done, &&done, &&done, &&done
        };
        u32 state = ((S_80175CD8_0 *)action)->unk_9B;

        if (state >= 0x15) {
            goto done;
        }
        (void)state_labels;
        goto *D_801709F0[state];
    }

state_0:
    {
        register u8 *effect_actor ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        s32 effect_flags;
        register s32 tile_dx ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        s32 tile_dy;
        u8 target_tile_x;
        u8 sprite_tile_x;
        u8 sprite_tile_y;
        u8 target_tile_y;

        effect_actor = actor;
        target_tile = D_80082E80;
        ASM_KEEP(target_tile);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        effect_flags = 0x2000;
        ASM_KEEP(effect_flags);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        target_tile_x = target_tile[0x24];
        sprite_tile_x = ((Rec_D_80082E80 *)sprite)->unk_24;
        sprite_tile_y = ((Rec_D_80082E80 *)sprite)->unk_25;
        tile_dx = target_tile_x;
        tile_dx -= sprite_tile_x;
        target_tile_y = target_tile[0x25];
        if (tile_dx < 0) {
            tile_dx = -tile_dx;
        }
        tile_dy = target_tile_y;
        tile_dy -= sprite_tile_y;
        if (tile_dy < 0) {
            tile_dy = -tile_dy;
        }
        ((S_80175CD8_0 *)action)->unk_96.s = ((tile_dx + tile_dy) * 4) + 9;
        ((S_80175CD8_0 *)action)->unk_9B++;
        func_800AD594(effect_actor, effect_flags);
    }

    if (target_tile[0x24] == ((Rec_D_80082E80 *)sprite)->unk_24) {
        if (target_tile[0x25] > ((Rec_D_80082E80 *)sprite)->unk_25) {
            direction = 2;
        } else {
            direction = 6;
        }
    } else if (target_tile[0x25] == ((Rec_D_80082E80 *)sprite)->unk_25) {
        direction = (((Rec_D_80082E80 *)sprite)->unk_24 >= target_tile[0x24]) * 4;
    } else if (((Rec_D_80082E80 *)sprite)->unk_24 < target_tile[0x24]) {
        if (((Rec_D_80082E80 *)sprite)->unk_25 < target_tile[0x25]) {
            direction = 1;
        } else {
            direction = 7;
        }
    } else if (((Rec_D_80082E80 *)sprite)->unk_25 < target_tile[0x25]) {
        direction = 3;
    } else {
        direction = 5;
    }
    (*(s16 *)((u8 *)actor + 0x2A)) = direction << 9;

    if ((D_80012090 != 0) || (D_8008146C != 0x28)) {
        if (((Rec_D_800E3D7C *)actor)->unk_10.at01_u8.v >= D_8008146C) {
            slot = 0;
            do {
                companion = *(u8 **)(D_800E3D7C + 0xAC + slot * 4);
                if ((companion != 0) && (companion != (u8 *)actor)) {
                    companion_type = func_800429E4(companion);
                    func_800C542C(companion, D_800DCED4[companion_type], (s16)slot, 0);
                }
                slot++;
            } while (slot < 2);
        }
    }

state_1:
    destination = D_80082E80;
    target_x = ((destination[0x24] << 6) + 0x20) << 16;
    target_y = ((destination[0x25] << 6) + 0x20) << 16;
    target_z = D_80083788 - 0x600000;
    approach_ticks = ((S_80175CD8_0 *)action)->unk_96.s;
    if (approach_ticks >= 0xE) {
        ((S_80175CD8_3 *)motion)->unk_0C = (target_x - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / (approach_ticks - 9);
        ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
            (((S_80175CD8_0 *)action)->unk_96.s - 9);
        ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
            (((S_80175CD8_0 *)action)->unk_96.s - 9);
    } else if (approach_ticks >= 0xB) {
        ((S_80175CD8_3 *)motion)->unk_0C = (target_x - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / (approach_ticks - 7);
        ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
            (((S_80175CD8_0 *)action)->unk_96.s - 7);
        ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
            (((S_80175CD8_0 *)action)->unk_96.s - 7);
    } else if (approach_ticks >= 5) {
        ((S_80175CD8_3 *)motion)->unk_0C = (target_x - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / (approach_ticks - 2);
        ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
            (((S_80175CD8_0 *)action)->unk_96.s - 2);
        ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
            (((S_80175CD8_0 *)action)->unk_96.s - 2);
    } else {
        ((S_80175CD8_3 *)motion)->unk_0C = (target_x - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / approach_ticks;
        ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
            ((S_80175CD8_0 *)action)->unk_96.s;
        ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
            ((S_80175CD8_0 *)action)->unk_96.s;
    }
    goto decrement_timer;

state_2:
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_800E2368;
    facing = (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(sprite, D_800E2368[facing & 7], 0);
    ((S_80175CD8_0 *)action)->unk_96.s = 0;
    ((S_80175CD8_0 *)action)->unk_9B++;
    func_80094E34();
    goto done;

state_3:
    {
        u16 old_timer = ((S_80175CD8_0 *)action)->unk_96.u;

        ((S_80175CD8_0 *)action)->unk_96.s = old_timer + 1;
        if ((s16)old_timer < 7) {
            goto done;
        }
    }
    ((S_80175CD8_0 *)action)->unk_9B++;
    {
        u8 *player = D_800E3D7C;

        ((S_80175CD8_0 *)action)->unk_96.s = 0;
        ((S_80175CD8_4 *)player)->unk_14 |= 0x100000;
    }
    func_800A56E0(0x603);
    goto done;

state_4:
    {
        u8 *scene = D_80083780;
        s32 fall_speed = (s32)0xFFF40000;

        ((S_80175CD8_3 *)motion)->unk_14 = fall_speed;
        ((S_80175CD8_5 *)scene)->unk_08 += fall_speed;
    }
    {
        u16 old_timer = ((S_80175CD8_0 *)action)->unk_96.u;

        ((S_80175CD8_0 *)action)->unk_96.s = old_timer + 1;
        if ((s16)old_timer < 0x1B) {
            goto done;
        }
    }
    ((S_80175CD8_0 *)action)->unk_96.s = 0;
    ASM_KEEP(action);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    if ((D_80012090 == 0) && (D_8008146C == 0x28)) {
        ((S_80175CD8_0 *)action)->unk_9B = 7;
    } else if (((Rec_D_800E3D7C *)actor)->unk_10.at01_u8.v >= D_8008146C) {
        ((S_80175CD8_0 *)action)->unk_9B++;
    } else {
        ((S_80175CD8_0 *)action)->unk_9B = 7;
    }
    goto done;

state_5:
    ((S_80175CD8_0 *)action)->unk_96.s = 0;
    ((S_80175CD8_0 *)action)->unk_9B++;
    goto done;

state_6:
    func_800945E8(D_800E3D7C);
    func_800948BC();
    func_800A6780();
    {
        u8 *scene_page;
        u8 *counter_page;
        s16 *floor_stats;
        register u8 map_id ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        s32 visit_count;
        s32 floor_count;

        scene_page = (u8 *)0x80080000;
        ASM_KEEP(scene_page);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        counter_page = (u8 *)0x80010000;
        ASM_KEEP(counter_page);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        floor_stats = D_80081468;
        map_id = scene_page[0x2E6B];
        visit_count = *(s32 *)(counter_page + 0x234);
        floor_count = *(u16 *)((u8 *)floor_stats + 4);
        visit_count++;
        floor_count++;
        *(s32 *)(counter_page + 0x234) = visit_count;
        *(u16 *)((u8 *)floor_stats + 4) = floor_count;
        func_80040AA0(map_id, floor_stats);
    }
    func_800481E0();
    ((S_80175CD8_3 *)motion)->unk_14 = 0;
    ((S_80175CD8_3 *)motion)->unk_10 = 0;
    ((S_80175CD8_3 *)motion)->unk_0C = 0;
    ((S_80175CD8_0 *)action)->unk_96.s = 0;
    ((S_80175CD8_0 *)action)->unk_9B = 0x14;
    goto clear_object_flag;

state_7:
    {
        u8 *player = D_800E3D7C;
        u8 *scene;
        u32 player_flags;
        u16 height;

        player_flags = ((S_80175CD8_6 *)player)->unk_14 & 0xFFEFFFFF;
        ASM_KEEP(player_flags);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        scene = D_80083498;
        scene += 0x20;
        ((S_80175CD8_6 *)player)->unk_14 = player_flags;
        height = D_8008378A - ((S_80175CD8_5 *)scene)->unk_88.s;
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

state_8:
    target_x = ((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 16;
    target_y = ((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 16;
    target_z = (((S_80175CD8_0 *)action)->unk_B4.s - 0x20) << 16;
    return_ticks = ((S_80175CD8_0 *)action)->unk_96.s;
    if (return_ticks >= 0xE) {
        ((S_80175CD8_3 *)motion)->unk_0C = (target_x - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / (return_ticks - 9);
        ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
            (((S_80175CD8_0 *)action)->unk_96.s - 9);
        ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
            (((S_80175CD8_0 *)action)->unk_96.s - 9);
    } else if (return_ticks >= 0xB) {
        ((S_80175CD8_3 *)motion)->unk_0C = (target_x - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / (return_ticks - 7);
        ((S_80175CD8_3 *)motion)->unk_10 = (target_y - ((S_80175CD8_3 *)motion)->unk_04.at00.v) /
            (((S_80175CD8_0 *)action)->unk_96.s - 7);
        ((S_80175CD8_3 *)motion)->unk_14 = (target_z - ((S_80175CD8_0 *)action)->unk_90.at00.v) /
            (((S_80175CD8_0 *)action)->unk_96.s - 7);
    } else if (return_ticks >= 5) {
        ((S_80175CD8_3 *)motion)->unk_0C = (target_x - ((S_80175CD8_3 *)motion)->unk_00.at00.v) / (return_ticks - 2);
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
        goto done;
    }
    ((S_80175CD8_0 *)action)->unk_96.s = 0;
    ((S_80175CD8_0 *)action)->unk_9B++;
    ((S_80175CD8_3 *)motion)->unk_14 = 0;
    ((S_80175CD8_3 *)motion)->unk_10 = 0;
    ((S_80175CD8_3 *)motion)->unk_0C = 0;
    goto done;

state_9:
    ((S_80175CD8_3 *)motion)->unk_14 = 0;
    ((S_80175CD8_3 *)motion)->unk_10 = 0;
    ((S_80175CD8_3 *)motion)->unk_0C = 0;
    ((S_80175CD8_0 *)action)->unk_8C = &D_80171F1C;
    ((S_80175CD8_0 *)action)->unk_9A = 0xE;
    D_8008346C = 0;
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 |= 0x40000;
    (*(u16 *)((u8 *)action + 0x98)) &= 0xFFF7;
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_800E2348;
    facing = (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(sprite, D_800E2348[facing & 7], 0);
    ((Rec_D_80082E80 *)sprite)->unk_05.as_u8 = 1;
    ((S_80175CD8_0 *)action)->unk_A2.s = 0;
    ((S_80175CD8_0 *)action)->unk_9E = 0;
    ((S_80175CD8_0 *)action)->unk_90.at02.v = -0x20;
    ((Rec_D_800E3D7C *)actor)->unk_88.as_u16 = ((S_80175CD8_0 *)action)->unk_B4.u;
    ((S_80175CD8_3 *)motion)->unk_00.at02.v = (((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20;
    ((S_80175CD8_3 *)motion)->unk_04.at02.v = (((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20;
    ((S_80175CD8_3 *)motion)->unk_0A = ((Rec_D_800E3D7C *)actor)->unk_88.as_u16 +
        ((S_80175CD8_0 *)action)->unk_90.at02u.v - ((S_80175CD8_0 *)action)->unk_A2.u;

clear_object_flag:
    ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;

done:
    return;
}

#undef FIELD

