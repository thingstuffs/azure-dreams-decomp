#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u32 words[3];
} __attribute__((packed)) LocalPacket;

typedef struct {
    u8 bytes[0x12];
    u8 kind;
    u8 pad;
} LocalItemInfo;

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

extern s32 D_80045340;
extern LocalItemInfo D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170850[];
extern u8 D_80171030[];
extern u8 D_801716F4[];
extern u8 D_80175554[];
extern u8 D_80175594[];
extern u8 D_801755CC[];
extern LocalPacket D_801755D4;

void func_801731C8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    u8 *selection;
    s32 special;
    s32 next_state;
    s32 state;
    void *active;

    special = 0;
    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto end;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_0:
    if (FIELD(arg3, u32, 0x1C) & 0x2000) {
        u32 dispatch;

        dispatch = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
        if (dispatch >= 7) {
            goto kind_default;
        }
        (void)kind_keep;
        goto *D_80170850[dispatch];

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
        register s32 special_test ASM_REG("$2");

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

        item = *selection;
        if (D_8006DE24[item].kind == 2) {
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
    FIELD(arg0, u16, 0x96) = 0x11;
    {
        u8 *table;
        s32 index;

        table = D_801755CC;
        FIELD(arg2, u8 *, 0x2C) = table;
        index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
        func_80047784(arg2, table[index], 0);
    }
    next_state = FIELD(arg0, u8, 0x9B) + 1;
    FIELD(arg0, u8, 0x9B) = next_state;
    goto state_1_done;

empty_selection:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    D_8008346C = 0;
    FIELD(D_800814A8, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = D_801716F4;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    goto end;

state_1:
    if (func_8003F270()) {
state_1_done:
        FIELD(arg2, u16, 0x14) |= 0x800;
        goto end;
    }
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x703);

state_2:
    {
        s16 timer;

        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if (timer <= 0 || (FIELD(arg2, u16, 0x14) & 0xE000)) {
            FIELD(arg0, u16, 0x98) |= 0x80;
            FIELD(arg0, u8, 0x9B)++;
            FIELD(arg2, u16, 0x14) |= 0x800;
            FIELD(arg0, u16, 0x96) = 0xF;
        }
        if (FIELD(arg0, s16, 0x96) == 8) {
            u8 *table;
            s32 index;

            table = D_80175594;
            FIELD(arg2, u8 *, 0x2C) = table;
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
            index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
            func_80047784(arg2, table[index], 0);
        }
        if (FIELD(arg0, s16, 0x96) < 2) {
            goto end;
        }
    }

    {
        register s16 counter ASM_REG("$19");
        register s16 next_counter ASM_REG("$2");
        u8 *handler;
        register s32 low_color ASM_REG("$18");
        s32 high_color;

        counter = 0;
        handler = D_80171030;
        low_color = 0x20;
        high_color = 0xE0;
        ASM_KEEP(counter);
        do {
            void *object;

            object = func_8003FC64(0x212);
            if (object == 0) {
                goto null_counter;
            }
            ASM_KEEP(object);
            {
                void *part;
                register s32 random ASM_REG("$3");
                register s32 selector ASM_REG("$4");

                FIELD(object, s16, 0x22) = 8;
                FIELD(object, void *, 0x10) = handler;
                func_8004491C(object, &D_80045340);
                part = FIELD(object, void *, 0x0C);
                FIELD(part, s16, 0x10) = low_color;
                FIELD(part, u16, 0x14) |= 0xC;

                part = FIELD(object, void *, 8);
                {
                    s32 coord_random;
                    s32 coord;

                    coord_random = func_80069EF8();
                    coord = FIELD(arg1, u16, 2);
                    coord -= 0x20;
                    FIELD(part, s16, 2) = coord + (coord_random & 0x3F);
                }
                {
                    s32 coord_random;
                    s32 coord;

                    coord_random = func_80069EF8();
                    coord = FIELD(arg1, u16, 6);
                    coord -= 0x20;
                    FIELD(part, s16, 6) = coord + (coord_random & 0x3F);
                }
                FIELD(part, s16, 0xA) =
                    FIELD(arg1, u16, 0xA) - (func_80069EF8() & 0x1F) - 0x30;

                part = FIELD(object, void *, 0x0C);
                {
                    register s32 initial_color ASM_REG("$2");

                    FIELD(part, s16, 0x1E) = 0x200;
                    FIELD(part, s16, 0x1C) = 0x200;
                    ASM_KEEP(part);
                    initial_color = 0x80;
                    ASM_KEEP(initial_color);
                    FIELD(part, u8, 0x0E) = initial_color;
                    FIELD(part, u8, 0x0D) = initial_color;
                    FIELD(part, u8, 0x0C) = initial_color;
                }
                *(LocalPacket *)((u8 *)object + 0x40) = D_801755D4;
                FIELD(part, void *, 8) = (u8 *)object + 0x40;

                random = func_80069EF8() & 3;
                selector = random;
                ASM_KEEP(random);
                ASM_KEEP(selector);
                if (selector == 0) {
                    goto null_counter;
                }
                ASM_KEEP(part);
                FIELD(part, s16, 0x12) = random + 0x7DC6;
                FIELD(part, u16, 0x14) |= 0x100;
                switch (selector) {
                    case 1:
                        FIELD(part, u8, 0x0C) = high_color;
                        FIELD(part, u8, 0x0E) = low_color;
                        FIELD(part, u8, 0x0D) = low_color;
                        break;
                    case 2:
                        FIELD(part, u8, 0x0E) = high_color;
                        FIELD(part, u8, 0x0C) = low_color;
                        FIELD(part, u8, 0x0D) = low_color;
                        break;
                    case 3:
                        FIELD(part, u8, 0x0D) = high_color;
                        FIELD(part, u8, 0x0E) = low_color;
                        FIELD(part, u8, 0x0C) = low_color;
                        break;
                }
            }
            next_counter = counter + 1;
            goto assign_counter;
null_counter:
            next_counter = counter + 1;
assign_counter:
            counter = next_counter;
            ASM_KEEP(next_counter);
counter_test:
            ;
        } while ((s16)next_counter < 1);
    }
    goto end;

state_3:
    {
        u8 *global;
        s16 timer;

        global = (u8 *)&D_80083460;
        if (FIELD(global, s32, 0x0C) == 0) {
            FIELD(arg0, u16, 0x96) = 0;
        }
        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if (timer <= 0) {
            FIELD(arg0, u16, 0x96) = 0;
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
        }
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto end;
        }
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        if (FIELD(arg2, u8 *, 0x2C) != D_80175554) {
            u8 *table;
            s32 index;

            table = D_80175554;
            FIELD(arg2, u8 *, 0x2C) = table;
            index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
            func_80047784(arg2, table[index], 0);
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
        }
        if (FIELD(global, s32, 0x0C) != 0) {
            goto end;
        }
        FIELD(global, u16, 0x0A)--;
        FIELD(arg0, void *, 0x8C) = D_801716F4;
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
