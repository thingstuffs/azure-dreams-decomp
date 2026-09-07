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
extern void func_80053DA8(s32);
extern void func_800997FC(void *);
extern s32 func_8009A350(s32, s32, s32, u16 *);
extern SpawnFunc func_800A0B94(s32, s32, s32);
extern void func_800A152C(s32, s32);
extern s32 func_800A1618(s32, s32);
extern void func_800A1D4C(void *, s32);
extern void func_800A56E0(s32);
extern s32 func_800A6D30(void);
extern s32 func_800A6DA4(s32, s32);
extern void func_800CED28(void);
extern void func_800CEDD8(void);

void func_800CEA44(void *arg0) {
    register u8 *ctx ASM_REG("$23");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    LocalScratch local;
    s16 state;
    register s32 y ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    s32 x;
    s32 entry_x;
    register s32 entry_y ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 count ASM_REG("$22");   /* MATCH pin: retail register colouring depends on it */
    s16 attempt;
    s32 variant;
    s32 type;
    s32 availability;
    u8 *entry;
    u8 *selection;
    void *object;
    u32 *loop_limits;
    u32 limit_value;
    u16 timer;
    s32 random;

    ctx = arg0;
    state = *(s16 *)(ctx + 6);
    if (state == 0) {
        {
            u32 area_byte;
            register s32 area_raw ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */

            area_byte = D_80082EA6;
            area_raw = (s8)area_byte;
            local.area_index = area_raw;
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

        random = func_800A6D30();
        {
            register u8 *global_base ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */

            global_base = (u8 *)&D_80083460;
            ASM_KEEP(global_base);   /* MATCH pin: retail delay-slot fill depends on it */
            selection = *(u8 **)(global_base + 0x18) + (random & 0x1E);
            type = selection[0];
            variant = selection[1];
        }
        availability = func_800A1618(type, 1);
        if (availability != 0) {
            attempt = 0xF;
            {
                register unsigned long area_raw ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
                register s32 area_calc ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
                s32 area_offset;

                area_raw = local.area_index;
                ASM_KEEP(area_raw);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                area_calc = (s16)area_raw;
                ASM_KEEP(area_calc);   /* MATCH pin: load-bearing for the whole function shape */
                area_offset = area_calc * sizeof(AreaRecord);
                ASM_KEEP(area_offset);   /* MATCH pin: retail schedule: same instructions, different order without it */
                area_raw = (unsigned long)D_800E2970;
                entry = (u8 *)(area_offset + area_raw);
            }
retry_position:
            x = func_800A6DA4(0, (u16)(((AreaRecord *)entry)->width - 1));
            y = func_800A6DA4(0, (u16)(((AreaRecord *)entry)->height - 1));
            entry_x = entry[0];
            entry_y = entry[2];
            x += entry_x;
            y = entry_y + y;
            if (((s16)func_8009A350((u8)x - 1, (u8)y, 0,
                                    &local.flags) == 0) ||
                ((local.flags & 0xB700) != 0)) {
                attempt--;
                if (attempt >= 0) {
                    goto retry_position;
                }
            }

            if (attempt >= 0) {
                s32 spawn_type;

                D_800E2968 = 1;
                spawn_type = type;
                ASM_KEEP_NV(spawn_type);   /* MATCH pin: retail keeps a computation the compiler would drop */
                object = func_800A0B94(spawn_type, availability, 1)
                    (0, (u8)x, (u8)y, -0x400);
                if (object != 0) {
                    func_800A152C(spawn_type, 1);
                    func_80042640(object, spawn_type);
                    ((u8 *)object)[0x43] = func_800A6D30();
                    ((u8 *)object)[0x12] = 0;

                    {
                        register u32 *limits ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

                        limits = D_800835E4;
                        limit_value = limits[variant];
                        limits++;
                        *(u32 *)((u8 *)object + 0x18) = limit_value;
                        if (*(u32 *)((u8 *)object + 0x18) >=
                            limits[((u8 *)object)[0x11]]) {
                            loop_limits = limits;
                            do {
                                func_800A1D4C(object, 0);
                            } while (loop_limits[((u8 *)object)[0x11]] <=
                                     *(u32 *)((u8 *)object + 0x18));
                        }
                    }
                    ((u8 *)object)[0x9A] = 0x16;
                    *(s32 *)((u8 *)object + 0x8C) = 0;
                    *(s32 *)((u8 *)object + 0x1C) &= 0xF7FBFFFF;
                    *(u16 *)((u8 *)object + 0x92) -= 0x200;
                }
            }
        }

        count--;
        if (count >= 0) {
            goto spawn_loop;
        }

initial_done:
        {
            register s32 tail_value ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

            (void)*(volatile u16 *)(ctx + 6);
            tail_value = 10;
            ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail delay-slot contents depend on it */
            func_800CED28();
        }
        return;
    }

    if (state == 1) {
        timer = *(u16 *)(ctx + 4) - 1;
        *(u16 *)(ctx + 4) = timer;
        if ((s16)timer >= 0) {
            return;
        }
        func_800997FC(&D_800E1C3A);
        func_800419EC(0xC, 0x18);
        func_800A56E0(0x602);
        *(u16 *)(ctx + 4) = 0x10;
        *(u16 *)(ctx + 6) += 1;
        func_800CEDD8();
        return;
    }

    goto other_state;

spawn_failed:
    ((DungeonSlot *)D_800E3648)[*(s16 *)(ctx + 0xC)].count -= count;
    func_800CEDD8();
    return;

other_state:
    timer = *(u16 *)(ctx + 4) - 1;
    *(u16 *)(ctx + 4) = timer;
    if ((s16)timer < 0) {
        func_8004437C(0, 1);
        func_80053DA8(0x200);
        *(s32 *)(D_800E3648 + *(s16 *)(ctx + 0xC) * 4) = 0;
        {
            u8 *global_base = (u8 *)&D_80083460;

            *(u16 *)(global_base + 0xA) -= 1;
        }
        *(u16 *)(ctx - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
