#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct Copy48 {
    u32 words[12];
} Copy48;

typedef struct ItemInfo {
    u8 pad00[0x12];
    u8 type;
    u8 pad13;
} ItemInfo;

extern s32 func_8003DE58(void *, void *, u16 *, s32);
extern s32 func_8003F270(void);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, u8, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);

extern s32 D_80045340;
extern ItemInfo D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern void *D_80170838[];
extern u8 D_801708D4;
extern u8 D_801714B8;
extern u8 D_8017609C[];
extern u8 D_801760FC[];

void func_801730E4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const keepalive[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_default, &&kind_default, &&kind_default
    };
    u16 delta[3];
    s32 special;
    void *active;
    register u8 *linked ASM_REG("$3");
    u8 linked_x;
    u8 linked_y;
    u8 *selection;
    u8 *held_base;
    u8 state;

    special = 0;
    held_base = (u8 *)arg0 - 0x20;
    state = FIELD(arg0, u8, 0x9B);
    switch (state) {
    case 0:
        goto state_0;
    case 1:
        goto state_1;
    case 2:
        goto state_2;
    case 3:
        goto state_3;
    default:
        return;
    }

state_0:
    if (FIELD(arg3, u32, 0x1C) & 0x2000) {
        u32 kind;

        kind = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
        if (kind >= 7) {
            goto kind_default;
        }
        (void)keepalive;
        goto *D_80170838[kind];

kind_3:
        special = 1;
        goto select_3;
kind_2:
        special = 1;
        goto select_2;
kind_1:
        special = 1;
        goto select_1;
    }

    {
        s32 kind;

        kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
        if (kind == 2) {
            goto select_2;
        }
        if (kind < 3) {
            if (kind == 1) {
                goto select_1;
            }
            selection = 0;
            goto selection_ready;
        }
        if (kind != 3) {
            selection = 0;
            goto selection_ready;
        }
    }

select_3:
    selection = (u8 *)arg3 + 0xE;
    goto selection_ready;
select_2:
    selection = (u8 *)arg3 + 0xB;
    goto selection_ready;
select_1:
    selection = (u8 *)arg3 + 8;
    goto selection_ready;
kind_default:
    selection = 0;

selection_ready:
    if (*selection == 0) {
        goto empty_selection;
    }

    FIELD(arg0, u16, 0x98) &= 0xFF7F;
    ASM_KEEP(selection);
    {
        register s32 special_test ASM_REG("$2") = special;

        ASM_KEEP(special_test);
        if (special_test != 0) {
            active = D_800814A8;
            FIELD(arg3, void *, 0x60) = active;
        } else {
            if (D_8006DE24[*selection].type != 2) {
                goto create_active;
            }
            active = FIELD(arg3, void *, 0x60);
            if (active == 0) {
                goto active_ready;
            }
        }
    }
copy_active:
    linked = FIELD(active, u8 *, -0x14);
    ASM_KEEP(linked);
    FIELD(arg3, u8, 0x72) = FIELD(linked, u8, 0x24);
    FIELD(arg3, u8, 0x73) = FIELD(linked, u8, 0x25);
    goto active_ready;

create_active:
    {
        s32 x;
        s32 y;

        active = func_800A05A4(
            arg3, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            FIELD(arg3, s16, 0x2A), 0x10);
        FIELD(arg3, void * volatile, 0x60) = active;
        ASM_KEEP(active);
        x = FIELD(arg3, s8, 0x72);
        y = FIELD(arg3, s8, 0x73);
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        FIELD(arg3, u8, 0x72) = x;
        FIELD(arg3, u8, 0x73) = y;
    }

active_ready:
    if (func_800A94A0(arg3, selection, special, (u8 *)arg0 + 0x98) == 0) {
        return;
    }
    FIELD(arg0, u16, 0x96) = 10;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x703);
    return;

empty_selection:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    {
        void *active;

        active = D_800814A8;
        D_8008346C = 0;
        FIELD(active, u16, 0xA6)--;
    }
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = &D_801714B8;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    return;

state_1:
    if (func_8003F270() != 0) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        return;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u16, 0x96) = 10;
    FIELD(arg0, u8, 0x9B)++;
    {
        u8 *object;

        object = func_8003FD64(0x112, D_80083498);
        if (object != 0) {
            u8 *part;
            u8 *target;
            void *source;
            u8 animation;

            part = object + 0x20;
            FIELD(part, u16, 0x96) = 0xF;
            FIELD(object, void *, 0x10) = &D_801708D4;
            FIELD(part, void *, 0xA8) = arg1;
            FIELD(part, u16, 0x94) = FIELD(arg3, u16, 0x2A);
            target = FIELD(object, u8 *, 0x0C);
            *(Copy48 *)target = *(Copy48 *)arg2;
            FIELD(target, u16, 0x1E) = 0x1000;
            FIELD(target, u16, 0x1C) = 0x1000;
            FIELD(target, u8, 0x0E) = 0x80;
            FIELD(target, u8, 0x0D) = 0x80;
            FIELD(target, u8, 0x0C) = 0x80;
            func_8004491C(object, &D_80045340);
            animation = D_801760FC[0];
            FIELD(target, void *, 0x2C) = D_801760FC;
            func_80047784(target, animation, 0);
            FIELD(target, u16, 0x10) = 0x20;
            FIELD(target, u16, 0x12) = 0xFF80;
            FIELD(target, u16, 0x14) |= 0xC;

            source = FIELD(held_base, void *, 0x0C);
            target = FIELD(object, u8 *, 8);
            if (func_8003DE58(FIELD(source, void *, 8), source, delta, 0) != 0) {
                FIELD(target, u16, 2) = FIELD(arg1, u16, 2);
                FIELD(target, u16, 6) = FIELD(arg1, u16, 6);
                FIELD(target, u16, 0xA) = FIELD(arg1, u16, 0xA);
                FIELD(target, u16, 2) += delta[0];
                FIELD(target, u16, 6) += delta[1];
                FIELD(target, u16, 0xA) += delta[2];
            }
        }
    }

state_2:
    {
        u16 timer;

        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if ((s16)timer > 0 && !(FIELD(arg2, u16, 0x14) & 0xE000)) {
            return;
        }
    }
    FIELD(arg0, u16, 0x98) |= 0x80;
    FIELD(arg0, u8, 0x9B)++;
    return;

state_3:
    if ((FIELD(arg2, s8, 4) == 2 &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        FIELD(arg0, u16, 0x96) = 0x14;
    }
    {
        u8 *global;
        u16 timer;

        global = (u8 *)&D_80083460;
        if (FIELD(global, s32, 0x0C) == 0) {
            FIELD(arg0, u16, 0x96) = 0;
        }
        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if ((s16)timer <= 0) {
            FIELD(arg0, u16, 0x96) = 0;
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
        }
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            return;
        }

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        if (FIELD(arg2, u8 *, 0x2C) != D_8017609C) {
            s32 index;

            FIELD(arg2, u8 *, 0x2C) = D_8017609C;
            index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
            func_80047784(arg2, D_8017609C[index], 0);
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
        }
        if (FIELD(global, s32, 0x0C) != 0) {
            return;
        }
        FIELD(global, u16, 0x0A)--;
    }
    FIELD(arg0, void *, 0x8C) = &D_801714B8;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_800A56E0(0xB4);
}
