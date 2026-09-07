#include "common.h"


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


typedef struct S_801731C8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801731C8_0;   /* arg0 in func_801731C8 */

typedef struct S_801731C8_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801731C8_1_pre;   /* the 0x14 bytes before active in func_801731C8, addressed as active[-1] */

typedef struct S_801731C8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801731C8_2;   /* linked in func_801731C8 */

typedef struct S_801731C8_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801731C8_3;   /* arg2 in func_801731C8 */

typedef struct S_801731C8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801731C8_4;   /* arg1 in func_801731C8 */

typedef struct S_801731C8_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
} S_801731C8_5;   /* object in func_801731C8 */

typedef struct S_801731C8_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801731C8_6;   /* part in func_801731C8 */

typedef struct S_801731C8_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801731C8_7;   /* global in func_801731C8 */

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
    state = ((S_801731C8_0 *)arg0)->unk_9B;
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
    if ((*(u32 *)((u8 *)arg3 + 0x1C)) & 0x2000) {
        u32 dispatch;

        dispatch = ((*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF) - 1;
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

        type = (*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF;
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
    ((S_801731C8_0 *)arg0)->unk_98 &= 0xFF7F;
    {
        s32 special_test;

        special_test = special;
        ASM_KEEP(special_test);   /* MATCH pin: retail basic-block layout depends on it */
        if (special_test != 0) {
            active = D_800814A8;
            (*(void * *)((u8 *)arg3 + 0x60)) = active;
            goto copy_active_coords;
        }
    }

    {
        u8 item;

        item = *selection;
        if (D_8006DE24[item].kind == 2) {
            active = (*(void * *)((u8 *)arg3 + 0x60));
            if (active != 0) {
                register u8 *linked ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

copy_active_coords:
                linked = ((S_801731C8_1_pre *)active)[-1].unk_00;
                (*(u8 *)((u8 *)arg3 + 0x72)) = ((S_801731C8_2 *)linked)->unk_24;
                (*(u8 *)((u8 *)arg3 + 0x73)) = ((S_801731C8_2 *)linked)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            active = func_800A05A4(
                arg3, ((S_801731C8_3 *)arg2)->unk_24, ((S_801731C8_3 *)arg2)->unk_25,
                (*(s16 *)((u8 *)arg3 + 0x2A)), 0x10);
            (*(void * volatile *)((u8 *)arg3 + 0x60)) = active;
            ASM_KEEP(active);   /* MATCH pin: keeps a statement from moving across a call/branch */
            dx = (*(s8 *)((u8 *)arg3 + 0x72));
            dy = (*(s8 *)((u8 *)arg3 + 0x73));
            if (dx < 0) {
                dx = -dx;
            }
            if (dy < 0) {
                dy = -dy;
            }
            (*(u8 *)((u8 *)arg3 + 0x72)) = dx;
            (*(u8 *)((u8 *)arg3 + 0x73)) = dy;
        }
    }

invoke_item:
    if (func_800A94A0(arg3, selection, special, (u8 *)arg0 + 0x98) == 0) {
        goto end;
    }
    ((S_801731C8_0 *)arg0)->unk_96.u = 0x11;
    {
        u8 *table;
        s32 index;

        table = D_801755CC;
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
        index = ((D_80083228 + (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7;
        func_80047784(arg2, table[index], 0);
    }
    next_state = ((S_801731C8_0 *)arg0)->unk_9B + 1;
    ((S_801731C8_0 *)arg0)->unk_9B = next_state;
    goto state_1_done;

empty_selection:
    ((S_801731C8_4 *)arg1)->unk_14 = 0;
    ((S_801731C8_4 *)arg1)->unk_10 = 0;
    ((S_801731C8_4 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_801731C8_3 *)arg2)->unk_24, ((S_801731C8_3 *)arg2)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(arg3);
    (*(u8 *)((u8 *)arg3 + 0x6D))--;
    ((S_801731C8_0 *)arg0)->unk_8C = D_801716F4;
    (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
    (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
    (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
    goto end;

state_1:
    if (func_8003F270()) {
state_1_done:
        ((S_801731C8_3 *)arg2)->unk_14 |= 0x800;
        goto end;
    }
    ((S_801731C8_0 *)arg0)->unk_9B++;
    func_800A56E0(0x703);

state_2:
    {
        s16 timer;

        timer = ((S_801731C8_0 *)arg0)->unk_96.u - 1;
        ((S_801731C8_0 *)arg0)->unk_96.u = timer;
        if (timer <= 0 || (((S_801731C8_3 *)arg2)->unk_14 & 0xE000)) {
            ((S_801731C8_0 *)arg0)->unk_98 |= 0x80;
            ((S_801731C8_0 *)arg0)->unk_9B++;
            ((S_801731C8_3 *)arg2)->unk_14 |= 0x800;
            ((S_801731C8_0 *)arg0)->unk_96.u = 0xF;
        }
        if (((S_801731C8_0 *)arg0)->unk_96.s == 8) {
            u8 *table;
            s32 index;

            table = D_80175594;
            ((S_801731C8_3 *)arg2)->unk_2C = table;
            ((S_801731C8_3 *)arg2)->unk_14 &= 0xF7FF;
            index = ((D_80083228 + (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7;
            func_80047784(arg2, table[index], 0);
        }
        if (((S_801731C8_0 *)arg0)->unk_96.s < 2) {
            goto end;
        }
    }

    {
        s16 counter;
        s16 next_counter;
        u8 *handler;
        s32 low_color;
        s32 high_color;

        counter = 0;
        handler = D_80171030;
        low_color = 0x20;
        high_color = 0xE0;
        do {
            void *object;

            object = func_8003FC64(0x212);
            if (object == 0) {
                goto null_counter;
            }
            ASM_KEEP(object);   /* MATCH pin: retail keeps a computation the compiler would drop */
            {
                void *part;
                s32 random;
                register s32 selector ASM_REG("$4");   /* MATCH pin: retail keeps a computation the compiler would drop */

                ((S_801731C8_5 *)object)->unk_22 = 8;
                ((S_801731C8_5 *)object)->unk_10 = handler;
                func_8004491C(object, &D_80045340);
                part = ((S_801731C8_5 *)object)->unk_0C;
                ((S_801731C8_6 *)part)->unk_10 = low_color;
                ((S_801731C8_6 *)part)->unk_14 |= 0xC;

                part = ((S_801731C8_5 *)object)->unk_08;
                {
                    s32 coord_random;
                    s32 coord;

                    coord_random = func_80069EF8();
                    coord = ((S_801731C8_4 *)arg1)->unk_02;
                    coord -= 0x20;
                    ((S_801731C8_6 *)part)->unk_02 = coord + (coord_random & 0x3F);
                }
                {
                    s32 coord_random;
                    s32 coord;

                    coord_random = func_80069EF8();
                    coord = ((S_801731C8_4 *)arg1)->unk_06;
                    coord -= 0x20;
                    ((S_801731C8_6 *)part)->unk_06 = coord + (coord_random & 0x3F);
                }
                ((S_801731C8_6 *)part)->unk_08.at02.v =
                    ((S_801731C8_4 *)arg1)->unk_0A - (func_80069EF8() & 0x1F) - 0x30;

                part = ((S_801731C8_5 *)object)->unk_0C;
                {
                    s32 initial_color;

                    ((S_801731C8_6 *)part)->unk_1E = 0x200;
                    ((S_801731C8_6 *)part)->unk_1C = 0x200;
                    initial_color = 0x80;
                    ((S_801731C8_6 *)part)->unk_0E = initial_color;
                    ((S_801731C8_6 *)part)->unk_0D = initial_color;
                    ((S_801731C8_6 *)part)->unk_0C = initial_color;
                }
                *(LocalPacket *)((u8 *)object + 0x40) = D_801755D4;
                ((S_801731C8_6 *)part)->unk_08.at00.v = (u8 *)object + 0x40;

                random = func_80069EF8() & 3;
                selector = random;
                if (selector == 0) {
                    goto null_counter;
                }
                ASM_KEEP(part);   /* MATCH pin: retail keeps a computation the compiler would drop */
                ((S_801731C8_6 *)part)->unk_12 = random + 0x7DC6;
                ((S_801731C8_6 *)part)->unk_14 |= 0x100;
                switch (selector) {
                    case 1:
                        ((S_801731C8_6 *)part)->unk_0C = high_color;
                        ((S_801731C8_6 *)part)->unk_0E = low_color;
                        ((S_801731C8_6 *)part)->unk_0D = low_color;
                        break;
                    case 2:
                        ((S_801731C8_6 *)part)->unk_0E = high_color;
                        ((S_801731C8_6 *)part)->unk_0C = low_color;
                        ((S_801731C8_6 *)part)->unk_0D = low_color;
                        break;
                    case 3:
                        ((S_801731C8_6 *)part)->unk_0D = high_color;
                        ((S_801731C8_6 *)part)->unk_0E = low_color;
                        ((S_801731C8_6 *)part)->unk_0C = low_color;
                        break;
                }
            }
            next_counter = counter + 1;
            goto assign_counter;
null_counter:
            next_counter = counter + 1;
assign_counter:
            counter = next_counter;
            ASM_KEEP(next_counter);   /* MATCH pin: load-bearing for the whole function shape */
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
        if (((S_801731C8_7 *)global)->unk_0C == 0) {
            ((S_801731C8_0 *)arg0)->unk_96.u = 0;
        }
        timer = ((S_801731C8_0 *)arg0)->unk_96.u - 1;
        ((S_801731C8_0 *)arg0)->unk_96.u = timer;
        if (timer <= 0) {
            ((S_801731C8_0 *)arg0)->unk_96.u = 0;
            ((S_801731C8_3 *)arg2)->unk_14 &= 0xF7FF;
        }
        if (!(((S_801731C8_3 *)arg2)->unk_14 & 0xE000)) {
            goto end;
        }
        ((S_801731C8_4 *)arg1)->unk_14 = 0;
        ((S_801731C8_4 *)arg1)->unk_10 = 0;
        ((S_801731C8_4 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_801731C8_3 *)arg2)->unk_24, ((S_801731C8_3 *)arg2)->unk_25);
        if (((S_801731C8_3 *)arg2)->unk_2C != D_80175554) {
            u8 *table;
            s32 index;

            table = D_80175554;
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
            index = ((D_80083228 + (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7;
            func_80047784(arg2, table[index], 0);
            ((S_801731C8_3 *)arg2)->unk_14 &= 0xF7FF;
        }
        if (((S_801731C8_7 *)global)->unk_0C != 0) {
            goto end;
        }
        ((S_801731C8_7 *)global)->unk_0A--;
        ((S_801731C8_0 *)arg0)->unk_8C = D_801716F4;
        func_800A4ACC(arg3);
        (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
        (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
        (*(u8 *)((u8 *)arg3 + 0x6D))--;
        (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);
    }

end:
    return;
}
