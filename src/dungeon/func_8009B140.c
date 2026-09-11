#include "common.h"
extern int abs(int);

typedef void *(*SpawnFunc)(s32, s32, s32, s32);

extern s32 D_800814A0;
extern u8 D_80082E80[];
extern u8 D_80083478[];
extern s16 D_8008347C;
extern u32 D_800835E4[];
extern u8 D_800E2968;
extern s32 D_800E296C;

extern void func_80042640(void *, s32);
extern void func_8009A028(void *);
extern void func_8009A3D0(s32, s32, s32);
extern s32 func_8009FB34(s32, s32);
extern SpawnFunc func_800A0B94(s32, void *, s32);
extern void func_800A152C(s32, s32);
extern void *func_800A1618(s32, s32);
extern void func_800A1D4C(void *, s32);
extern void func_800A32A4(void *);
extern void func_800A4E2C(u8 *, u8 *);
/* Retail 0x800A6D30 (+0xC15D0 in DUNGEON.BIN), 48 bytes: RNG reads no argument registers, including a3. */
extern s32 func_800A6D30(void);
extern s32 func_800A9230(void *);
extern s32 func_800BCB04(s32, s32, s32);

/* Places a monster from the spawn table and raises it to the selected level. */
void func_800A08A0(s32 spawn_mode) {
    void *monster;
    s32 monster_type;
    s32 mode;
    s32 spawn_level;
    register u8 raw_variant ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s16 attempt;
    s32 distance;
    u8 *reference_object;
    s32 fixed_entry_offset;
    s32 spawn_height;
    s32 dx;
    s32 dy;
    u8 tile_x;
    u8 tile_y;
    register u32 *limits ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    SpawnFunc spawn_monster;
    void *level_monster; /* MATCH: Both threshold arms supply the call argument in the branch delay slot. */

    distance = 0x100;
    if (D_800E296C & 0x10000000) {
        return;
    }
    if (D_8008347C >= 0x20) {
        return;
    }

    attempt = 0;
    reference_object = D_80082E80;
    mode = (s16)spawn_mode;
    fixed_entry_offset = (mode - 2) * 2;

    do {
        func_800A4E2C(&tile_x, &tile_y);
        if ((s16)func_8009FB34(tile_x, tile_y) < 0) {
            continue;
        }

        if (mode == 0) {
            s32 tile_y_value;
            {
                s32 x_value;
                do {
                    dx = reference_object[0x24];
                    x_value = tile_x;
                } while (0);
                tile_y_value = tile_y;
                dx -= x_value;
            }
            dy = reference_object[0x25];
            dx = abs(dx);
            dy -= tile_y_value;
            dy = abs(dy);
            distance = dx + dy;
        }
        if ((s16)distance < 0x21) {
            continue;
        }

        {
            s16 entry_offset;
            u8 *spawn_entry;

            entry_offset = (mode < 2) ?
                             ((func_800A6D30() & 0xF) * 2) : fixed_entry_offset;
            {
                u8 **spawn_table_addr = (u8 **)&D_80083478;
                s32 signed_entry_offset = entry_offset;
                u8 *spawn_table = *spawn_table_addr;
                spawn_entry = (u8 *)(signed_entry_offset + (s32)spawn_table);
            }
            raw_variant = spawn_entry[1];
            D_800E2968 = raw_variant;
            monster_type = spawn_entry[0];
        }

        if (monster_type == 0) {
            return;
        }
        spawn_level = raw_variant;
        monster = func_800A1618(monster_type, 1);
        if (monster == 0) {
            continue;
        }

        ASM_CLOBBER("$6");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        spawn_height = func_800BCB04((tile_x << 6) | 0x20, (tile_y << 6) | 0x20, -0x400);
        spawn_monster = func_800A0B94(monster_type, monster, 1);
        monster = spawn_monster(0, tile_x, tile_y, (s16)spawn_height);
        if (monster == 0) {
            return;
        }

        func_800A152C(monster_type, 1);
        func_80042640(monster, monster_type);
        ((u8 *)monster)[0x43] = func_800A6D30();
        ((u8 *)monster)[0x12] = 0;

        if (mode >= 2) {
            u8 *owner = *(u8 **)((u8 *)monster - 0x14);
            func_8009A3D0(owner[0x24], owner[0x25], 0x3000);
            func_800A32A4(monster);
            func_8009A028(monster);
            *(u16 *)((u8 *)monster - 2) |= 0x8000;
            D_800814A0 |= 0x8000;
            return;
        }

        limits = D_800835E4;
        ((u32 *)((u8 *)monster + 0x18))[0] = limits[spawn_level];
        limits++;
        if (*(u32 *)((u8 *)monster + 0x18) >= limits[((u8 *)monster)[0x11]]) {
            u32 *level_thresholds;
            u32 next_level_exp;
            level_monster = monster;
            level_thresholds = limits;
            do {
                func_800A1D4C(level_monster, 0);
                next_level_exp = level_thresholds[((u8 *)monster)[0x11]];
                level_monster = monster;
            } while (*(u32 *)((u8 *)monster + 0x18) >= next_level_exp);
        } else {
            level_monster = monster;
        }
        ASM_USE_NV(level_monster); /* MATCH: Keep both threshold arms' argument assignments live. */
        if (((u8 *)monster)[0x49] != 0) {
            return;
        }
        *(s32 *)((u8 *)monster + 0x48) = func_800A9230(monster);
        return;
    } while (++attempt < 0x10);
}
