#include "shared/dungeon_item_entries.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

extern s32 func_80098864();
extern s32 func_8008D344();
extern s32 func_800A6480();
extern s32 func_800AD6FC();
extern s32 func_800A5F38();
extern s32 func_8009BF7C();
extern s32 func_800A56E0();
extern s32 func_8009D6F4();
extern s32 func_800403BC();
extern s32 func_800997FC();
extern s32 func_80098B38();

extern u8 D_800E36C8[];
extern u8 D_800E3648[];
extern u8 D_800E39C8[];
extern u8 D_800E1863;
extern u8 D_800CE028[];

#define U8(p, o)  (*(u8  *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

/* Apply a target effect and clear dungeon entities and tiles when requested. */
s32 func_800C3D3C(void *target, s32 effect_arg, s16 effect_id, s32 context) {
    s32 *dungeon_state = ((s32 *)(&gameWork));
    u8 *grid_info;
    s32 grid_base;
    void *entity;
    void *first_entity;
    u8 *entry_data;
    u8 *entry_flags;
    s32 x;
    s32 y;
    s32 cell_index;
    s32 cleared_tile;
    s32 clear_mask;
    s32 effect_counter;
    s32 effect_code;
    u16 *cell;

    grid_info = (u8 *) (dungeon_state + 119);
    grid_base = dungeon_state[119];
    effect_code = effect_id;
    if (effect_code == 13) {
        return func_80098864(effect_arg, context);
    }
    if (target == D_800E3D7C) {
        S32(target, 0x110) = effect_arg;
        func_8008D344(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }
    if ((u32) target <= 0x9FFFFFFFU) {
        func_800A6480(target, effect_arg, effect_code);
        if (func_800AD6FC(target, U16(((u8 *)D_800DDE84), U8(target, 0x13) * 2) & 3, effect_arg) == 0) {
            func_800A5F38(target, effect_arg);
            return 1;
        }
    } else if (D_800E296C & 0x20000000) {
        func_8009BF7C(1, 8);
        func_800A56E0(0x80F);
        entity = D_800E3D7C;
        first_entity = entity;
        do {
            S16(entity, 0x88) = 0;
            S32(entity, 0x1C) = S32(entity, 0x1C) | 0x40000000;
            entity = (void *) (S32(entity, 0x5C) + 0x20);
        } while (entity != first_entity);
        entry_data = D_800E36C8;
        entry_flags = ((u8 *)D_800E3548);
        for (effect_counter = 0; effect_counter < 0x40; effect_counter++) {
            if (U8(entry_flags, effect_counter * 4 + 1) != 0) {
                S16(entry_data, effect_counter * 0xC + 4) = 0;
            }
        }
        entry_data = D_800E39C8;
        entry_flags = D_800E3648;
        for (effect_counter = 0; effect_counter < 0x20; effect_counter++) {
            if (U8(entry_flags, effect_counter * 4 + 1) != 0) {
                S16(entry_data, effect_counter * 0x18 + 0x12) = 0;
            }
        }
        y = 1;
        cleared_tile = 0x68;
        do {
            x = 1;
            do {
                cell = (u16 *) ((x + (y << S16(grid_info, 0x14))) * 6 + grid_base);
                if (*cell >= 0xBU) {
                    *cell = cleared_tile;
                    cell = (u16 *) ((x + (y << S16(grid_info, 0x14))) * 6 + grid_base);
                    U16(cell, 4) = U16(cell, 4) & 0x7B32;
                }
                cell_index = x + (y << S16(grid_info, 0x14));
                x += 1;
                U16((u16 *) (cell_index * 6 + grid_base), 2) = 0;
            } while (x < 0x3F);
            y += 1;
        } while (y < 0x3F);
        func_8009D6F4();
        clear_mask = 0x3FF7FFFF;
        D_800E296C = D_800E296C & clear_mask;
        func_800403BC(D_800CE028);
    } else {
        func_800997FC(&D_800E1863, context, effect_code);
    }
    dungeonStatus.unk_0A = ((u16)dungeonStatus.unk_0A) - 1;
    func_80098B38(effect_arg);
    return 1;
}
