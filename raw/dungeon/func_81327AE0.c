#include "common.h"

typedef void (*Callback)(void *, void *, void *, void *);

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern void func_800353F4();
extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s32 func_800BCB04();
extern void func_8016F534() __attribute__((noreturn));
extern void func_8016F580() __attribute__((noreturn));
extern void func_8016F5A4() __attribute__((noreturn));
extern void func_8016F610() __attribute__((noreturn));
extern void func_8016F6A8() __attribute__((noreturn));
extern void func_8016F6C0() __attribute__((noreturn));
extern void func_8016F740() __attribute__((noreturn));
extern void func_8016F764() __attribute__((noreturn));

extern u16 D_80013714;
extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 *D_800E3D7C;
extern u8 D_800F8BBC[9];
extern u8 D_8016F78C[9];
extern Callback D_80174AD4[];

void func_8016F2E0(void *a0, void *a1, void *a2)
{
    register void *arg0 ASM_REG("$18") = a0;
    register void *arg1 ASM_REG("$20") = a1;
    register void *arg2 ASM_REG("$19") = a2;
    register void *actor ASM_REG("$17") = arg0;
    s32 old_direction;
    register s32 direction_copy ASM_REG("$21");
    Callback callback;
    s32 floor;
    s16 actor_height;
    u16 actor_height_u;
    register s32 direction_check ASM_REG("$2");
    register s32 direction_value ASM_REG("$3");
    register u8 *tile_slot ASM_REG("$2");
    register u8 *direction_slot ASM_REG("$2");
    register u16 return_flags ASM_REG("$2");
    register u16 flags ASM_REG("$3");
    register u16 new_flags ASM_REG("$2");
    s32 previous_direction;
    s32 tile_map;
    s32 i;
    u8 *slot;
    void *node;
    void *record;

    if (FIELD(arg0, s32, 0x14) & 0x00800000) {
        FIELD(arg0, s32, 0x14) &= 0xFF7FFFFF;
        func_800353F4(&D_800F8BBC);
        FIELD(arg0, u8, 0x6D) = 0;
        FIELD(arg0, u8, 0x9B) = 0;
        FIELD(arg0, u8, 0x71) &= 0x7F;
    }

    if (D_80013714 & 8) {
        i = 1;
        slot = D_800E3D7C + 4;
        do {
            node = FIELD(slot, void *, 0xAC);
            if (node != 0) {
                record = FIELD(node, void *, -0x14);
                FIELD(record, u16, 0x14) &= 0xFFBF;
            }
            i--;
            slot -= 4;
        } while (i >= 0);
    }

    if (D_80083462 & 0x2000) {
        callback = FIELD(arg0, Callback, 0x8C);
        if (callback == (Callback)&D_8016F78C) {
            callback(arg0, arg1, arg2, actor);
            func_8016F764();
            return;
        }
        FIELD(actor, u8, 0x71) &= 0x7F;
        func_8016F764();
        return;
    }

    old_direction = FIELD(actor, volatile u8, 0x6D);
    old_direction = (old_direction << 24) >> 24;
    if (func_800A9E70(arg0, arg1, arg2, actor) != 0) {
        return;
    }

    {
        Callback callback2 = FIELD(arg0, Callback, 0x8C);
        if (callback2 != 0) {
            callback2(arg0, arg1, arg2, actor);
        }
    }
    D_80174AD4[FIELD(arg0, u8, 0x9A)](arg0, arg1, arg2, actor);

    ASM_KEEP(old_direction);
    direction_check = (s16)old_direction;
    if (direction_check != FIELD(actor, s8, 0x6D)) {
        func_800AA36C(arg0, arg1, arg2, actor);
    }

    flags = FIELD(arg2, u16, 0x14);
    new_flags = flags & 0x8000;
    if (new_flags == 0) {
        old_direction = ((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7;
        previous_direction = FIELD(arg0, s16, 0x94);
        ASM_SCHED_BARRIER();
        direction_value = old_direction;
        ASM_KEEP(old_direction);
        direction_copy = old_direction;
        if (previous_direction != direction_value) {
            tile_map = FIELD(arg2, s32, 0x2C);
            if (tile_map != 0) {
                tile_slot = (u8 *)tile_map + direction_value;
                ASM_KEEP(tile_slot);
                func_80047738(arg2,
                    *tile_slot,
                    FIELD(arg2, s8, 4));
            }
            FIELD(arg0, s16, 0x94) = old_direction;
        }

        direction_slot = D_8006CCF8 + direction_copy;
        ASM_KEEP(direction_slot);
        if (*direction_slot != 0) {
            return_flags = FIELD(arg2, u16, 0x14);
            return_flags |= 1;
            ASM_TAILSLOT_PIN(return_flags);
            func_8016F534();
            return;
        }

        FIELD(arg2, volatile u16, 0x14) &= 0xFFFE;
        if (!(FIELD(actor, s32, 0x1C) & 0x20)) {
            if (!(FIELD(arg2, volatile u16, 0x14) & 0x40)) {
                func_800478B8(arg2);
                func_8016F580();
                return;
            }
        } else {
            FIELD(arg2, volatile u16, 0x14) |= 0x7000;
        }

        func_800A020C(FIELD(actor, s32, 0x1C), (u8 *)arg2 + 0xC);
        func_8016F5A4();
        return;
    }

    new_flags = flags & 0x0800;
    if (new_flags != 0) {
        new_flags = flags & 0x8FFF;
    } else {
        new_flags = flags | 0x7000;
    }
    FIELD(arg2, u16, 0x14) = new_flags;

    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);

    if (FIELD(arg0, u16, 0x98) & 8) {
        FIELD(arg0, u8, 0x9D) = 0;
        func_8016F610();
        return;
    }

    FIELD(arg1, s32, 0x14) += FIELD(arg0, s8, 0x9D) * 0x14000;
    FIELD(arg0, volatile u8, 0x9D)++;
    FIELD(arg0, s32, 0x90) += FIELD(arg1, s32, 0x14);

    if (!(FIELD(arg0, volatile u16, 0x98) & 4)) {
        floor = func_800BCB04(FIELD(arg1, u16, 2),
                              FIELD(arg1, u16, 6),
                              (s16)(FIELD(actor, u16, 0x88) - 0x20));
        if ((s16)floor < 0x200) {
            actor_height = FIELD(actor, s16, 0x88);
            actor_height_u = FIELD(actor, u16, 0x88);
            if (FIELD(arg0, s16, 0x92) + actor_height < (s16)floor) {
                FIELD(actor, s32, 0x1C) &= 0xF7FFFFFF;
                func_8016F6C0(actor_height_u, floor, actor_height);
                return;
            }
            if ((s16)floor >= actor_height) {
                FIELD(arg0, s32, 0x90) = 0;
                func_8016F6A8(actor_height_u, floor, actor_height);
                return;
            }

            FIELD(arg0, s16, 0x92) = floor - actor_height_u;
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(actor, s32, 0x1C) |= 0x08000000;
            FIELD(arg0, u8, 0x9D) = 0;

            if (FIELD(actor, s32, 0x1C) & 0x40000000) {
                FIELD(actor, s32, 0x1C) &= 0xBFFFFFFF;
                floor = func_800BCB04((FIELD(arg2, u8, 0x24) << 6) | 0x20,
                                      (FIELD(arg2, u8, 0x25) << 6) | 0x20,
                                      (s16)(FIELD(actor, u16, 0x88) - 0x20));
                FIELD(arg0, s16, 0x92) += FIELD(actor, u16, 0x88) - floor;
                FIELD(actor, u16, 0x88) = floor;
                func_8016F740();
                return;
            }
            goto finish;
        }
    }

    FIELD(actor, s32, 0x1C) &= 0xF7FFFFFF;

finish:
    FIELD(arg1, s16, 0xA) = FIELD(actor, u16, 0x88) + FIELD(arg0, u16, 0x92);
    FIELD(arg2, u16, 0x14) |= 0x40;
    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    ASM_KEEP(actor);
    ASM_KEEP(direction_copy);
}
