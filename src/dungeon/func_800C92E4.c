#include "common.h"

typedef void *(*SpawnFunc)(s32, s32, s32, s32);

typedef struct DungeonSlot {
    u8 unk0;
    u8 unk1;
    s8 count;
    u8 unk3;
} DungeonSlot;

typedef struct AreaRecord {
    u8 x;
    u8 unk1;
    u8 y;
    u8 unk3;
    u16 width;
    u16 height;
    u8 pad[12];
} AreaRecord;

typedef struct LocalScratch {
    u16 flags;
    u8 pad[6];
    u16 area_index;
} LocalScratch;

extern s32 D_800814A0;
extern u8 D_80082EA6;
extern s32 D_80083460;
extern u32 D_800835E4[];
extern u8 D_800E1C3A;
extern s8 D_800E2968;
extern s8 D_800E2970[];
extern u8 D_800E3648[];

extern s32 func_8003FA44(s32);
extern void func_800419EC(s32, s32);
extern void func_80042640(void *, s32);
extern void func_8004437C(s32, s32);
extern void SD_Call(s32);
extern void func_800997FC(void *);
extern s32 func_8009A350(s32, s32, s32, u16 *);
extern SpawnFunc func_800A0B94(s32, s32, s32);
extern void func_800A152C(s32, s32);
extern s32 func_800A1618(s32, s32);
extern void func_800A1D4C(void *, s32);
extern void func_800A56E0(s32);
extern s32 func_800A6D30(void);
extern s32 func_800A6DA4(s32, s32);

/* Spawns and levels monster den monsters, then advances the event delays and cleanup. */
void func_800CEA44(void *den_event) {
    register u8 *ctx ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    LocalScratch scratch;
    s16 state;
    u16 next_state;
    s32 tail_value;
    register s32 y ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 spawn_x;
    s32 area_x;
    register s32 entry_y ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 count ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 retries_left;
    s32 monster_level;
    s32 monster_type;
    s32 spawn_availability;
    u8 *area;
    u8 *monster_entry;
    void *monster;
    u32 *level_thresholds;
    u32 experience;
    u16 delay_timer;
    s32 random_value;

    ctx = den_event;
    state = *(s16 *)(ctx + 6);
    if (state == 0) {
        {
            u32 area_byte;
            register s32 area_raw ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            area_byte = D_80082EA6;
            area_raw = (s8)area_byte;
            scratch.area_index = area_raw;
            if ((s32)(area_byte << 24) < 0) {
                goto initial_done;
            }
        }

        count = ((DungeonSlot *)D_800E3648)[*(s16 *)(ctx + 0xC)].count;
        if (count < 0) {
            goto initial_done;
        }

spawn_loop:
        if (func_8003FA44(3) == 0) {
            goto spawn_failed;
        }

        random_value = func_800A6D30();
        {
            register u8 *global_base ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            global_base = (u8 *)&D_80083460;
            ASM_KEEP(global_base);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            monster_entry = *(u8 **)(global_base + 0x18) + (random_value & 0x1E);
            monster_type = monster_entry[0];
            monster_level = monster_entry[1];
        }
        spawn_availability = func_800A1618(monster_type, 1);
        if (spawn_availability != 0) {
            retries_left = 0xF;
            {
                register unsigned long area_raw ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                register s32 area_calc ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s32 area_offset;

                area_raw = scratch.area_index;
                ASM_KEEP(area_raw);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                area_calc = (s16)area_raw;
                ASM_KEEP(area_calc);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                area_offset = area_calc * sizeof(AreaRecord);
                do {
                    area_raw = (unsigned long)D_800E2970;
                } while (0);
                area = (u8 *)(area_offset + area_raw);
            }
retry_position:
            spawn_x = func_800A6DA4(0, (u16)(((AreaRecord *)area)->width - 1));
            y = func_800A6DA4(0, (u16)(((AreaRecord *)area)->height - 1));
            area_x = area[0];
            entry_y = area[2];
            spawn_x += area_x;
            y = entry_y + y;
            if (((s16)func_8009A350((u8)spawn_x - 1, (u8)y, 0,
                                    &scratch.flags) == 0) ||
                ((scratch.flags & 0xB700) != 0)) {
                retries_left--;
                if (retries_left >= 0) {
                    goto retry_position;
                }
            }

            if (retries_left >= 0) {
                s32 spawn_type;

                D_800E2968 = 1;
                spawn_type = monster_type;
                ASM_KEEP_NV(spawn_type);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
                monster = func_800A0B94(spawn_type, spawn_availability, 1)
                    (0, (u8)spawn_x, (u8)y, -0x400);
                if (monster != 0) {
                    func_800A152C(spawn_type, 1);
                    func_80042640(monster, spawn_type);
                    ((u8 *)monster)[0x43] = func_800A6D30();
                    ((u8 *)monster)[0x12] = 0;

                    {
                        register u32 *limits ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                        limits = D_800835E4;
                        experience = limits[monster_level];
                        limits++;
                        *(u32 *)((u8 *)monster + 0x18) = experience;
                        if (*(u32 *)((u8 *)monster + 0x18) >=
                            limits[((u8 *)monster)[0x11]]) {
                            level_thresholds = limits;
                            do {
                                func_800A1D4C(monster, 0);
                            } while (level_thresholds[((u8 *)monster)[0x11]] <=
                                     *(u32 *)((u8 *)monster + 0x18));
                        }
                    }
                    ((u8 *)monster)[0x9A] = 0x16;
                    *(s32 *)((u8 *)monster + 0x8C) = 0;
                    *(s32 *)((u8 *)monster + 0x1C) &= 0xF7FBFFFF;
                    *(u16 *)((u8 *)monster + 0x92) -= 0x200;
                }
            }
        }

        count--;
        if (count >= 0) {
            goto spawn_loop;
        }

initial_done:
        next_state = *(u16 *)(ctx + 6);
        tail_value = 10;
    } else {
        if (state != 1) {
            goto other_state;
        }
        delay_timer = *(u16 *)(ctx + 4) - 1;
        *(u16 *)(ctx + 4) = delay_timer;
        if ((s16)delay_timer >= 0) {
            return;
        }
        func_800997FC(&D_800E1C3A);
        func_800419EC(0xC, 0x18);
        func_800A56E0(0x602);
        next_state = *(u16 *)(ctx + 6);
        tail_value = 0x10;
    }
    do {
        *(u16 *)(ctx + 4) = tail_value;
    } while (0);
     /* MATCH: keep the timer store before the state increment. */
    *(u16 *)(ctx + 6) = next_state + 1;
    return;


spawn_failed:
    ((DungeonSlot *)D_800E3648)[*(s16 *)(ctx + 0xC)].count -= count;
    return;

other_state:
    delay_timer = *(u16 *)(ctx + 4) - 1;
    *(u16 *)(ctx + 4) = delay_timer;
    if ((s16)delay_timer < 0) {
        func_8004437C(0, 1);
        SD_Call(0x200);
        *(s32 *)(D_800E3648 + *(s16 *)(ctx + 0xC) * 4) = 0;
        {
            u8 *global_base = (u8 *)&D_80083460;

            *(u16 *)(global_base + 0xA) -= 1;
        }
        *(u16 *)(ctx - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
