#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    u32 words[3];
} __attribute__((packed)) Packet12;

extern s32 func_8003F270(void);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_80170D28(void *, s32, s32, s32, s32, s32, s32);
extern void func_80170F2C(void *, s32, s32, s32, s32, s32, s32);

extern s32 D_80045340;
extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170850[];
extern void *D_80170868[];
extern u8 D_80171080[];
extern s32 D_801719DC;
extern u8 D_80174634[];
extern Packet12 D_80174694;

void func_801732C4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const state_keep[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4, &&state_5
    };
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    register u8 *selection ASM_REG("$17");
    register s32 special ASM_REG("$19");
    u8 state;
    u8 next_state;
    void *active;

    special = 0;
    state = FIELD(arg0, u8, 0x9B);
    if ((u32)state >= 6) {
        goto end;
    }
    (void)state_keep;
    goto *D_80170850[state];

state_0:
    if (FIELD(arg3, u32, 0x1C) & 0x2000) {
        u32 dispatch;

        dispatch = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
        if (dispatch >= 7) {
            goto kind_default;
        }
        (void)kind_keep;
        goto *D_80170868[dispatch];

kind_5:
        special = 1;
        goto kind_3;
kind_6:
        special = 1;
        goto kind_2;
kind_7:
        special = 1;
        goto kind_1;
    }

    {
        s32 type;

        type = FIELD(arg3, u16, 0x46) & 0x3FFF;
        if (type == 2) {
            goto kind_2;
        }
        if (type < 3) {
            selection = 0;
            if (type == 1) {
                goto normal_kind_1;
            }
            goto selection_ready;
        }
        if (type != 3) {
            selection = 0;
            goto selection_ready;
        }
    }

kind_3:
    selection = (u8 *)arg3 + 0xE;
    goto selection_ready;
kind_2:
    selection = (u8 *)arg3 + 0xB;
    goto selection_ready;
normal_kind_1:
    ASM_KEEP(selection);
kind_1:
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
        s32 special_test;

        special_test = special;
        ASM_KEEP(special_test);
        if (special_test != 0) {
            active = D_800814A8;
            FIELD(arg3, void *, 0x60) = active;
            goto copy_active_coords;
        }
    }
    ASM_KEEP(selection);

    {
        u8 item;
        u8 *item_table;

        item_table = D_8006DE24;
        item = *selection;
        if (item_table[item * 20 + 0x12] == 2) {
            active = FIELD(arg3, void *, 0x60);
            if (active != 0) {
                register u8 *linked ASM_REG("$3");

copy_active_coords:
                linked = FIELD(active, void *, -0x14);
                ASM_KEEP(linked);
                FIELD(arg3, u8, 0x72) = FIELD(linked, u8, 0x24);
                FIELD(arg3, u8, 0x73) = FIELD(linked, u8, 0x25);
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            active = func_800A05A4(
                arg3, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(arg3, s16, 0x2A), 0x10);
            FIELD(arg3, void * volatile, 0x60) = active;
            ASM_KEEP(active);
            dx = FIELD(arg3, s8, 0x72);
            dy = FIELD(arg3, s8, 0x73);
            if (dx < 0) {
                dx = -dx;
            }
            if (dy < 0) {
                dy = -dy;
            }
            FIELD(arg3, u8, 0x72) = dx;
            FIELD(arg3, u8, 0x73) = dy;
        }
    }

invoke_item:
    if (func_800A94A0(arg3, selection, special, (u8 *)arg0 + 0x98) == 0) {
        goto end;
    }
    goto increment_state;

empty_selection:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    D_8008346C = 0;
    FIELD(D_800814A8, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = &D_801719DC;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    goto end;

state_1:
    if (func_8003F270()) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        goto end;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x703);

state_2:
    {
        u16 flags;
        s16 timer;

        flags = FIELD(arg2, u16, 0x14);
        if (flags & 0x8000) {
            next_state = FIELD(arg0, u8, 0x9B);
            FIELD(arg0, u16, 0x96) = 0;
            goto increment_state_loaded;
        }
        if (FIELD(arg2, s8, 4) == 2 && (flags & 0x1000)) {
            FIELD(arg2, u16, 0x14) = flags | 0x800;
            FIELD(arg0, u16, 0x96) = 0x16;
        }
        if (FIELD(arg2, s8, 4) < 2) {
            goto end;
        }
        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if (timer <= 0) {
            FIELD(arg0, u16, 0x96) = 0;
            FIELD(arg0, u8, 0x9B)++;
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
        }
        if (FIELD(arg0, s16, 0x96) < 7) {
            goto particle_done;
        }
    }

    special = 0;
state_2_particles:
    {
        s32 color;
        register s32 x ASM_REG("$17");
        register s32 y ASM_REG("$16");
        s16 z;

        special++;
        color = (func_80069EF8() & 0xFF) | 0x80;
        x = func_80069EF8();
        x &= 0x7F;
        x -= 0x40;
        x = (s16)x;
        y = func_80069EF8();
        y &= 0x7F;
        y -= 0x40;
        y = (s16)y;
        z = (func_80069EF8() & 0x7F) - 0x40;
        func_80170D28((u8 *)arg0 - 0x20, 0, 0x00C0C0C0,
                      color, x, y, z);
        if ((u16)special < 5) {
            goto state_2_particles;
        }
    }

particle_done:
    {
        void *object;
        u8 *object_base;
        void *transform;
        void *display;
        u16 timer;
        u16 flags;

        timer = FIELD(arg0, u16, 0x96);
        if (!(timer & 1) || (s16)timer < 0x13) {
            goto end;
        }
        object = func_8003FC64(0x212);
        if (object == 0) {
            goto end;
        }
        object_base = (u8 *)object + 0x20;
        FIELD(object_base, s16, 0x1A) = 0x19;
        FIELD(object_base, s16, 0x1C) = 0x19;
        FIELD(object, void *, 0x10) = D_80171080;
        func_8004491C(object, &D_80045340);
        transform = FIELD(object, void *, 8);
        FIELD(transform, u16, 2) = FIELD(arg1, u16, 2);
        FIELD(transform, u16, 6) = FIELD(arg1, u16, 6);
        FIELD(transform, u16, 0xA) = FIELD(arg1, u16, 0xA) - 0x60;
        display = FIELD(object, void *, 0xC);
        FIELD(object, Packet12, 0x48) = D_80174694;
        FIELD(display, void *, 8) = (u8 *)object + 0x48;
        FIELD(display, s16, 0x10) = 0x40;
        FIELD(display, s16, 0x1E) = 0x32C8;
        FIELD(display, s16, 0x1C) = 0x32C8;
        FIELD(display, s16, 6) = 0x64;
        FIELD(display, s32, 0x0C) = 0;
        flags = FIELD(display, u16, 0x14);
        FIELD(display, u16, 0x14) = flags | 0xC;
        FIELD(object_base, u8, 4) = 0x80;
        FIELD(object_base, u8, 3) = 0x80;
        FIELD(object_base, u8, 2) = 0x80;
    }
    goto end;

state_3:
    if ((FIELD(arg2, s8, 4) == 5 &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        FIELD(arg0, u16, 0x96) = 0x14;
        FIELD(arg0, u16, 0x98) |= 0x80;
        FIELD(arg0, u8, 0x9B)++;
        special = 0;
state_3_particles:
        {
            s32 color;

            special++;
            color = (func_80069EF8() & 0xFF) | 0x80;
            func_80170F2C((u8 *)arg0 - 0x20, 0, 0x00C0C0C0,
                          color, 0, 0, 0);
        }
        if ((u16)special >= 20) {
            goto end;
        }
        goto state_3_particles;
    }
    goto end;

state_4:
    {
        s16 timer;

        if (D_8008346C == 0) {
            FIELD(arg0, u16, 0x96) = 0;
        }
        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if (timer > 0 && !(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto end;
        }
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
increment_state:
        next_state = FIELD(arg0, u8, 0x9B);
increment_state_loaded:
        next_state++;
        FIELD(arg0, u8, 0x9B) = next_state;
        goto end;
    }

state_5:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto end;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    if (FIELD(arg2, u8 *, 0x2C) != D_80174634) {
        u8 *table;
        s32 index;
        s32 prior_a4;

        table = D_80174634;
        FIELD(arg2, u8 *, 0x2C) = table;
        index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
        func_80047784(arg2, table[index], 2);
        FIELD(arg2, u8, 5) = 1;
        prior_a4 = FIELD(arg0, s32, 0xA4);
        FIELD(arg0, u16, 0xA6) = 0;
        FIELD(arg0, u16, 0xB8) = 0;
        FIELD(arg0, s32, 0xAC) = 0;
        FIELD(arg0, s32, 0xB0) = 0;
        FIELD(arg0, s32, 0xA8) = prior_a4;
    }
    {
        u8 *global;

        global = (u8 *)&D_80083460;
        if (FIELD(global, s32, 0x0C) != 0) {
            goto end;
        }
        FIELD(global, u16, 0x0A)--;
        FIELD(arg0, void *, 0x8C) = &D_801719DC;
        func_800A4ACC(arg3);
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u8, 0x6D)--;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A56E0(0xB4);
    }

end:
    return;
}
