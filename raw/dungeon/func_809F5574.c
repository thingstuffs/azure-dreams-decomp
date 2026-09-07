#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, s32, s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, void *, s32, void *);
extern void func_800DAE44(void *, s32);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170838[];
extern void *D_80170880[];
extern u8 D_80171400[];
extern u8 D_80175140[];
extern u8 D_80175148[];
extern u8 D_80175168[];
extern u8 D_80175170[];

void func_80172D74(void *arg0, void *arg1, void *arg2, void *arg3)
{
    void *owner;
    void *part20;
    void *part28;
    u8 *slot;
    void *entity;
    s32 special;
    s32 xdir;
    s32 zdir;
    s32 next_state;
    register u8 state_value ASM_REG("$2");
    static void *const outer_keepalive[] = {
        &&state0, &&state1, &&state2, &&state3, &&state16
    };
    static void *const inner_keepalive[] = {
        &&kind1, &&kind2, &&kind3, &&kind4, &&kind5, &&kind6, &&kind7
    };

    special = 0;
    {
        u32 direction = ((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE;

        owner = FIELD(arg0, void *, 0xA4);
        part20 = (u8 *)owner + 0x20;
        xdir = *(s16 *)(&D_8006CCD8 + direction);
        zdir = *(s16 *)(&D_8006CCE8 + direction);
        part28 = (u8 *)owner + 0x28;
    }
    FIELD(arg0, u16, 0x96)--;
    {
        u8 dispatch = FIELD(arg0, u8, 0x9B);

        if ((u32)dispatch >= 17) {
            return;
        }
        (void)outer_keepalive;
        goto *D_80170838[dispatch];
    }

state0:
    if (FIELD(arg3, s32, 0x1C) & 0x2000) {
        s32 dispatch = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;

        if ((u32)dispatch >= 7) {
            goto kind4;
        }
        (void)inner_keepalive;
        goto *D_80170880[dispatch];
kind5:
        special = 1;
        goto kind3;
kind6:
        special = 1;
        goto kind2;
kind7:
        special = 1;
        goto kind1;
    }

    {
        s32 type = FIELD(arg3, u16, 0x46) & 0x3FFF;

        if (type == 2) {
            goto kind2;
        }
        if (type < 3) {
            if (type == 1) {
                goto kind1;
            }
            slot = 0;
            goto selected;
        }
        if (type == 3) {
            goto kind3;
        }
        slot = 0;
        goto selected;
    }

kind3:
    slot = (u8 *)arg3 + 0xE;
    goto selected;
kind2:
    slot = (u8 *)arg3 + 0xB;
    goto selected;
kind1:
    slot = (u8 *)arg3 + 8;
    goto selected;
kind4:
    slot = 0;

selected:
    if (*slot == 0) {
        goto empty_slot;
    }
    ASM_SCHED_BARRIER();
    FIELD(arg0, u16, 0x98) &= 0xFF7F;
    ASM_SCHED_BARRIER();
    {
        register s32 special_test ASM_REG("$2");

        special_test = special;
        ASM_KEEP(special_test);
        if (special_test != 0) {
            entity = D_800814A8;
            FIELD(arg3, void *, 0x60) = entity;
            goto have_entity;
        }
    }
    {
        u8 *item_defs = D_8006DE24;
        u8 item = *slot;

        if (item_defs[item * 20 + 0x12] == 2) {
            entity = FIELD(arg3, void *, 0x60);

            if (entity != 0) {
                register void *position ASM_REG("$3");

have_entity:
                position = FIELD(entity, void *, -0x14);
                ASM_KEEP(position);
                FIELD(arg3, u8, 0x72) = FIELD(position, u8, 0x24);
                FIELD(arg3, u8, 0x73) = FIELD(position, u8, 0x25);
            }
        } else {
            void *spawned;
            s32 x;
            s32 z;

            spawned = func_800A05A4(arg3,
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(arg3, s16, 0x2A), 0x10);
            FIELD(arg3, void *, 0x60) = spawned;
            ASM_SCHED_BARRIER();
            x = FIELD(arg3, s8, 0x72);
            z = FIELD(arg3, s8, 0x73);
            if (x < 0) {
                x = -x;
            }
            if (z < 0) {
                z = -z;
            }
            FIELD(arg3, s8, 0x72) = x;
            FIELD(arg3, s8, 0x73) = z;
        }
    }

ready_item:
    FIELD(part20, u16, 4) &= 0x7FFF;
    FIELD(part28, u8 *, 0x2C) = D_80175168;
    func_80047784(part28,
        D_80175168[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    if (!func_800A94A0(arg3, slot, special, (u8 *)arg0 + 0x98)) {
        return;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    func_800DAE44(arg1, 3);
    func_800A56E0(0x703);
    state_value = FIELD(arg0, u8, 0x9B);
    ASM_KEEP(state_value);
    FIELD(arg0, u16, 0x96) = 6;
    goto increment_state_loaded;

empty_slot:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    {
        void *entity = D_800814A8;

        D_8008346C = 0;
        FIELD(entity, u16, 0xA6)--;
    }
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, u8 *, 0x8C) = D_80171400;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    return;

state1:
    if (func_8003F270()) {
        FIELD(arg2, u16, 0x14) |= 0x0800;
        return;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;

state2:
    if (FIELD(arg0, s16, 0x96) > 0 &&
        !(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    FIELD(arg0, u16, 0x96) = 7;
    FIELD(arg0, u16, 0x98) |= 0x80;
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        next_state = 0x10;
        goto set_state;
    }

increment_state:
    state_value = FIELD(arg0, u8, 0x9B);
    ASM_KEEP(state_value);
increment_state_loaded:
    FIELD(arg0, u8, 0x9B) = state_value + 1;
    return;

state3:
    if (FIELD(arg0, s16, 0x96) < 4) {
        FIELD(arg1, s32, 0x0C) = -xdir << 18;
        FIELD(arg1, s32, 0x10) = -zdir << 18;
    }
    if (FIELD(arg0, s16, 0x96) > 0) {
        return;
    }
    next_state = 4;
    FIELD(arg0, u16, 0x96) = next_state;
    next_state = 0x10;
set_state:
    FIELD(arg0, u8, 0x9B) = next_state;
    return;

state16:
    {
        s32 coord = FIELD(arg2, u8, 0x24) << 6;
        s32 current = FIELD(arg1, s16, 2) - 0x20;

        FIELD(arg1, s32, 0x0C) = (coord - current) << 14;
    }
    {
        s32 coord = FIELD(arg2, u8, 0x25) << 6;
        s32 current = FIELD(arg1, s16, 6) - 0x20;

        FIELD(arg1, s32, 0x10) = (coord - current) << 14;
    }
    if (!(FIELD(part28, u16, 0x14) & 0x8000) &&
        FIELD(arg0, s16, 0x96) > 0) {
        return;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    {
        u8 *animation = FIELD(arg2, u8 *, 0x2C);
        u8 *next = D_80175140;

        if (animation != D_80175140) {
            u8 *alternate = D_80175148;

            if (animation != alternate && (FIELD(arg2, u16, 0x14) & 0x6000)) {
                FIELD(part20, u16, 4) |= 0x8000;
                FIELD(arg0, u16, 0xA8) = 0;
                if (FIELD(arg2, u8 *, 0x2C) == D_80175170) {
                    next = alternate;
                }
                FIELD(arg2, u8 *, 0x2C) = next;
                func_80047784(arg2,
                    next[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                    0);
            }
        }
    }
    {
        u8 *global = (u8 *)&D_80083460;

        if (FIELD(global, s32, 0xC) != 0) {
            return;
        }
        FIELD(global, u16, 0xA)--;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8 *, 0x8C) = D_80171400;
    func_800A4ACC(arg3);
    if (FIELD(arg3, s8, 0x6D) > 0) {
        FIELD(arg3, u8, 0x6D)--;
    }
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_800A56E0(0xB4);
}

/* MECHANISM: The true-space body naturally yields the 0x40 frame and s6/s7 held subobject bases.
   Fall-through barriers preserve the special-test move, load delays, and result-store schedule.
   The special CFG edge joins the position-copy block; short v0/v1 lives preserve pointer roles
   and carry the already-loaded state byte across the shared increment join. */
