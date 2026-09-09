#include "common.h"

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

extern s32 D_80083160[];
extern void *D_800E3D7C;
extern s32 D_800E296C;
extern u8 D_800DDE84[];
extern u16 D_80083460[];
extern u8 D_800E3548[];
extern u8 D_800E36C8[];
extern u8 D_800E3648[];
extern u8 D_800E39C8[];
extern u8 D_800E1863;
extern u8 D_80083780[];
extern u8 D_80082E80[];
extern u8 D_800CE028[];

#define U8(p, o)  (*(u8  *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

/* Apply a target effect and clear dungeon entities and tiles when requested. */
s32 func_800C3D3C(void *target, s32 effect_arg, s16 effect_id, s32 context) {
    s32 *dungeon_state = D_80083160;
    u8 *grid_info;
    s32 grid_base;
    void *entity;
    void *first_entity;
    u8 *entry_data;
    u8 *entry_flags;
    register s32 slot ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 x;
    s32 y;
    s32 cell_index;
    s32 cleared_tile;
    register s32 clear_mask ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 effect_value ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 effect_code;
    u16 *cell;

    effect_value = effect_arg;
    grid_info = (u8 *) (dungeon_state + 119);
    grid_base = dungeon_state[119];
    effect_code = effect_id;
    ASM_KEEP_NV(effect_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (effect_code == 13) {
        return func_80098864(effect_value, context);
    }
    if (target == D_800E3D7C) {
        S32(target, 0x110) = effect_value;
        func_8008D344(target, D_80083780, D_80082E80, target);
        return 0;
    }
    if ((u32) target <= 0x9FFFFFFFU) {
        func_800A6480(target, effect_value, effect_code);
        if (func_800AD6FC(target, U16(D_800DDE84, U8(target, 0x13) * 2) & 3, effect_value) == 0) {
            func_800A5F38(target, effect_value);
            return 1;
        }
        D_80083460[5] = D_80083460[5] - 1;
        func_80098B38(effect_value);
        return 1;
    }
    if (D_800E296C & 0x20000000) {
        func_8009BF7C(1, 8, effect_code);
        func_800A56E0(0x80F);
        entity = D_800E3D7C;
        first_entity = entity;
        do {
            S16(entity, 0x88) = 0;
            S32(entity, 0x1C) = S32(entity, 0x1C) | 0x40000000;
            entity = (void *) (S32(entity, 0x5C) + 0x20);
        } while (entity != first_entity);
        slot = 0;
        entry_data = D_800E36C8;
        entry_flags = D_800E3548;
        do {
            if (U8(entry_flags, 1) != 0) {
                S16(entry_data, 4) = 0;
            }
            entry_data += 0xC;
            slot += 1;
            entry_flags += 4;
        } while (slot < 0x40);
        slot = 0;
        entry_data = D_800E39C8;
        entry_flags = D_800E3648;
        do {
            if (U8(entry_flags, 1) != 0) {
                S16(entry_data, 0x12) = 0;
            }
            entry_data += 0x18;
            slot += 1;
            entry_flags += 4;
        } while (slot < 0x20);
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
        func_800403BC(D_800CE028, clear_mask);
    } else {
        func_800997FC(&D_800E1863, context, effect_code);
    }
    D_80083460[5] = D_80083460[5] - 1;
    func_80098B38(effect_value);
    return 1;
}
