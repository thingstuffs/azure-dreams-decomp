#include "common.h"


extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_800BB044(void *);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170838[];
extern u8 D_80170F20[];
extern u8 D_801762C0[];


typedef struct S_80172798_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172798_0;   /* arg0 in func_80172798 */

typedef struct S_80172798_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172798_1_pre;   /* the 0x14 bytes before active in func_80172798, addressed as active[-1] */

typedef struct S_80172798_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172798_2;   /* linked in func_80172798 */

typedef struct S_80172798_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172798_3;   /* arg2 in func_80172798 */

typedef struct S_80172798_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172798_4;   /* arg1 in func_80172798 */

typedef struct S_80172798_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172798_5;   /* global in func_80172798 */

void func_80172798(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    u8 *selection;
    s32 special;
    u8 state;
    void *active;

    special = 0;
    state = ((S_80172798_0 *)arg0)->unk_9B;
    switch (state) {
    case 0:
        goto state_0;
    case 1:
        goto state_1;
    case 2:
        goto state_2;
    default:
        goto end;
    }

state_0:
    if ((*(u32 *)((u8 *)arg3 + 0x1C)) & 0x2000) {
        u32 dispatch;

        dispatch = ((*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF) - 1;
        if (dispatch >= 7) {
            goto kind_default;
        }
        (void)kind_keep;
        goto *D_80170838[dispatch];

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
        switch (type) {
        case 1:
            goto normal_kind_1;
        case 2:
            goto kind_2;
        case 3:
            goto kind_3;
        default:
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
    ((S_80172798_0 *)arg0)->unk_98 &= 0xFF7F;
    ASM_KEEP(selection);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    {
        s32 special_test;

        special_test = special;
        ASM_KEEP(special_test);   /* MATCH pin: retail delay-slot fill depends on it */
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
                register u8 *linked ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

copy_active_coords:
                linked = ((S_80172798_1_pre *)active)[-1].unk_00;
                (*(u8 *)((u8 *)arg3 + 0x72)) = ((S_80172798_2 *)linked)->unk_24;
                (*(u8 *)((u8 *)arg3 + 0x73)) = ((S_80172798_2 *)linked)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            active = func_800A05A4(
                arg3, ((S_80172798_3 *)arg2)->unk_24, ((S_80172798_3 *)arg2)->unk_25,
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
    func_800BB044(arg3);
    ((S_80172798_0 *)arg0)->unk_9B++;
    goto end;

empty_selection:
    ((S_80172798_4 *)arg1)->unk_14 = 0;
    ((S_80172798_4 *)arg1)->unk_10 = 0;
    ((S_80172798_4 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_80172798_3 *)arg2)->unk_24, ((S_80172798_3 *)arg2)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(arg3);
    (*(u8 *)((u8 *)arg3 + 0x6D))--;
    ((S_80172798_0 *)arg0)->unk_8C = D_80170F20;
    (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
    (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
    (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
    goto end;

state_1:
    if (func_8003F270()) {
        ((S_80172798_3 *)arg2)->unk_14 |= 0x800;
        goto end;
    }
    ((S_80172798_3 *)arg2)->unk_14 &= 0xF7FF;
    ((S_80172798_0 *)arg0)->unk_9B++;

state_2:
    if ((((S_80172798_3 *)arg2)->unk_04 == 7 &&
         (((S_80172798_3 *)arg2)->unk_14 & 0x1000)) ||
        (((S_80172798_3 *)arg2)->unk_14 & 0xE000)) {
        ((S_80172798_3 *)arg2)->unk_14 |= 0x800;
        ((S_80172798_0 *)arg0)->unk_96 = 1;
        ((S_80172798_0 *)arg0)->unk_98 |= 0x80;
    }
    {
        s16 timer;

        timer = ((S_80172798_0 *)arg0)->unk_96 - 1;
        ((S_80172798_0 *)arg0)->unk_96 = timer;
        if (timer <= 0) {
            ((S_80172798_0 *)arg0)->unk_96 = 0;
            ((S_80172798_3 *)arg2)->unk_14 &= 0xF7FF;
        }
    }
    if (!(((S_80172798_3 *)arg2)->unk_14 & 0xE000)) {
        goto end;
    }
    ((S_80172798_4 *)arg1)->unk_14 = 0;
    ((S_80172798_4 *)arg1)->unk_10 = 0;
    ((S_80172798_4 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_80172798_3 *)arg2)->unk_24, ((S_80172798_3 *)arg2)->unk_25);
    if (((S_80172798_3 *)arg2)->unk_2C != D_801762C0) {
        u8 *table;
        s32 index;

        table = D_801762C0;
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
        index = ((D_80083228 + (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7;
        func_80047784(arg2, table[index], 0);
    }
    {
        u8 *global;

        global = (u8 *)&D_80083460;
        if (((S_80172798_5 *)global)->unk_0C != 0) {
            goto end;
        }
        ((S_80172798_5 *)global)->unk_0A--;
        ((S_80172798_0 *)arg0)->unk_8C = D_80170F20;
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
