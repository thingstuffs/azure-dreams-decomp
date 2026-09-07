#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_801711DC(void *, s32, s32);
extern void func_8017145C(void *, s32);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_800E2348[];
extern u8 D_800E2388[8];
extern u8 D_800E2398[8];
extern void *D_80170850[];
extern u8 D_80170870[20];
extern s32 D_80171F1C;


typedef struct S_80173B08_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
} S_80173B08_0;   /* arg0 in func_80173B08 */

typedef struct S_80173B08_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80173B08_1_pre;   /* the 0x14 bytes before active in func_80173B08, addressed as active[-1] */

typedef struct S_80173B08_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173B08_2;   /* linked in func_80173B08 */



typedef struct S_80173B08_5 {
    u8 pad_00[0x3228];
    s16 unk_3228;
} S_80173B08_5;   /* (void *)page_entry in func_80173B08 */

typedef struct S_80173B08_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80173B08_6;   /* global in func_80173B08 */

void func_80173B08(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const state_keep[] = {
        &&state_0, &&state_1, &&state_2, &&state_3,
        &&state_4, &&state_5, &&state_6, &&state_7
    };
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    u8 *selection;
    register u8 *table ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
    u32 page_entry;
    s32 special;
    s16 counter;
    u8 state;
    void *active;

    special = 0;
    state = ((S_80173B08_0 *)arg0)->unk_9B;
    if ((u32)state >= 8) {
        goto end;
    }
    (void)state_keep;
    goto *D_80170850[state];

state_0:
    if ((*(u32 *)((u8 *)arg3 + 0x1C)) & 0x2000) {
        u32 dispatch;

        dispatch = ((*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF) - 1;
        if (dispatch >= 7) {
            goto kind_default;
        }
        (void)kind_keep;
        goto *(((void **)D_80170870)[dispatch]);

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
    ((S_80173B08_0 *)arg0)->unk_98 &= 0xFF7F;
    ASM_KEEP(special);   /* MATCH pin: keeps a constant in a register as retail does */
    {
        s32 special_test;

        special_test = special;
        ASM_KEEP(special_test);   /* MATCH pin: keeps a constant in a register as retail does */
        if (special_test != 0) {
            active = D_800814A8;
            (*(void * *)((u8 *)arg3 + 0x60)) = active;
            goto copy_active_coords;
        }
    }

    {
        u8 item;

        item = *selection;
        if (D_8006DE24[item * 20 + 0x12] == 2) {
            active = (*(void * *)((u8 *)arg3 + 0x60));
            if (active != 0) {
                register void *linked ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

copy_active_coords:
                linked = ((S_80173B08_1_pre *)active)[-1].unk_00;
                (*(u8 *)((u8 *)arg3 + 0x72)) = ((S_80173B08_2 *)linked)->unk_24;
                (*(u8 *)((u8 *)arg3 + 0x73)) = ((S_80173B08_2 *)linked)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            active = func_800A05A4(
                arg3, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25,
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
    if (func_800A94A0(arg3, selection, special,
                      (u8 *)arg0 + 0x98) == 0) {
        goto end;
    }
    ((S_80173B08_0 *)arg0)->unk_9B++;
    goto end;

empty_selection:
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(arg3);
    (*(u8 *)((u8 *)arg3 + 0x6D))--;
    ((S_80173B08_0 *)arg0)->unk_8C = &D_80171F1C;
    (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
    (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
    (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
    goto end;

state_1:
    if (func_8003F270()) {
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x800;
        goto end;
    }
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
    ((S_80173B08_0 *)arg0)->unk_9B++;
    func_800A56E0(0x703);

state_2:
    ((S_80173B08_0 *)arg0)->unk_9B++;
    ((S_80173B08_0 *)arg0)->unk_98 &= 0xFFF7;
    (*(u32 *)((u8 *)arg3 + 0x1C)) &= 0xFFFBFFFF;
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    ((Rec_D_80082E80 *)arg2)->unk_10.as_s16 = 0x20;
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0xC;

state_3:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        ((S_80173B08_0 *)arg0)->unk_9B = 7;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x6000;
        ((S_80173B08_0 *)arg0)->unk_98 |= 0x80;
        goto end;
    }
    {
        s16 floor;

        floor = func_800BCB04(((Rec_D_800E3D7C *)arg1)->unk_00.at02_u16.v,
                              ((Rec_D_800E3D7C *)arg1)->unk_04.at02_u16.v,
                              (s16)((*(u16 *)((u8 *)arg3 + 0x88)) - 0x20));
        if ((((S_80173B08_0 *)arg0)->unk_92.s -
             (s16)(floor - (*(u16 *)((u8 *)arg3 + 0x88)))) != 0) {
            goto end;
        }
    }
    table = D_800E2398;
    ((S_80173B08_0 *)arg0)->unk_96.u = 0;
    ((S_80173B08_0 *)arg0)->unk_9B++;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a constant in a register as retail does */
    page_entry = 0x80080000;
    goto update_table;

state_4:
    {
        s16 timer;

        timer = ((S_80173B08_0 *)arg0)->unk_96.u;
        ((S_80173B08_0 *)arg0)->unk_96.u = timer + 1;
        if (timer < 12 && !(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            goto end;
        }
    }
    ((S_80173B08_0 *)arg0)->unk_98 |= 0x80;
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x800;
    ((S_80173B08_0 *)arg0)->unk_96.u = 0x12;
    ((S_80173B08_0 *)arg0)->unk_9B++;
    counter = 0;
    do {
        func_801711DC((u8 *)arg0 - 0x20,
                      (*(s16 *)((u8 *)arg3 + 0x2A)), 0xE0E0E0);
        counter++;
    } while ((s16)counter < 3);
    goto end;

state_5:
    if (D_8008346C == 0) {
        ((S_80173B08_0 *)arg0)->unk_96.u = 0;
    }
    if (((S_80173B08_0 *)arg0)->unk_96.s >= 10) {
        counter = 0;
        do {
            func_801711DC((u8 *)arg0 - 0x20,
                          (*(s16 *)((u8 *)arg3 + 0x2A)), 0xE0E0E0);
            counter++;
        } while ((s16)counter < 3);
    }
    if ((u32)(((S_80173B08_0 *)arg0)->unk_96.u - 10) < 7) {
        register s32 next ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

        special = 0;
        do {
            s16 shifted;

            shifted = special;
            next = shifted;
            if (next != (*(s16 *)((u8 *)arg3 + 0x2A))) {
                counter = 0;
                do {
                    func_8017145C((u8 *)arg0 - 0x20, shifted);
                    counter++;
                } while ((s16)counter <= 0);
                next = special + 0x200;
            } else {
                next = special + 0x200;
            }
            special = next;
            ASM_KEEP(next);   /* MATCH pin: retail register colouring depends on it */
        } while ((s16)next < 0x1000);
    }
    {
        s16 timer;

        timer = ((S_80173B08_0 *)arg0)->unk_96.u - 1;
        ((S_80173B08_0 *)arg0)->unk_96.u = timer;
        if (timer > 0 && !(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            goto end;
        }
    }
    table = D_800E2388;
    ((S_80173B08_0 *)arg0)->unk_96.u = 0;
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
    {
        u16 flags;

        flags = ((S_80173B08_0 *)arg0)->unk_98;
        flags |= 8;
        ((S_80173B08_0 *)arg0)->unk_9B++;
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a constant in a register as retail does */
        page_entry = 0x80080000;
        ((S_80173B08_0 *)arg0)->unk_98 = flags;
    }
    goto update_table;

update_table:
    {
        ((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 = table;
        page_entry = (u32)(((((S_80173B08_5 *)((void *)page_entry))->unk_3228 +
                              (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7) +
                     (u32)table;
        func_80047784(arg2, *(u8 *)page_entry, 0);
    }
    goto end;

state_6:
    if (((S_80173B08_0 *)arg0)->unk_92.s >= -0x1F) {
        ((S_80173B08_0 *)arg0)->unk_92.u -= 4;
        goto end;
    }
    ((S_80173B08_0 *)arg0)->unk_9B++;

state_7:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto end;
    }
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 != D_800E2348) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_800E2348;
        func_80047784(
            arg2,
            D_800E2348[((D_80083228 + (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7],
            0);
        ((S_80173B08_0 *)arg0)->unk_9E = 0;
        ((S_80173B08_0 *)arg0)->unk_98 |= 8;
        (*(u32 *)((u8 *)arg3 + 0x1C)) |= 0x40000;
        ((S_80173B08_0 *)arg0)->unk_92.s = -0x20;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xFFF3;
    }
    {
        u8 *global;

        global = (u8 *)&D_80083460;
        if (((S_80173B08_6 *)global)->unk_0C != 0) {
            goto end;
        }
        ((S_80173B08_6 *)global)->unk_0A--;
        ((S_80173B08_0 *)arg0)->unk_8C = &D_80171F1C;
        func_800A4ACC(arg3);
    }
    (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
    (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
    (*(u8 *)((u8 *)arg3 + 0x6D))--;
    (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
    func_800A56E0(0xB4);

end:
    return;
}
