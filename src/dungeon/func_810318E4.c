#include "common.h"


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


typedef struct S_801730E4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801730E4_0;   /* arg0 in func_801730E4 */

typedef struct S_801730E4_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_801730E4_1_pre;   /* the 0x14 bytes before active in func_801730E4, addressed as active[-1] */

typedef struct S_801730E4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801730E4_2;   /* linked in func_801730E4 */

typedef struct S_801730E4_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801730E4_3;   /* arg2 in func_801730E4 */

typedef struct S_801730E4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801730E4_4;   /* arg1 in func_801730E4 */

typedef struct S_801730E4_5 {
    u8 pad_00[0x94];
    u16 unk_94;
    u16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
} S_801730E4_5;   /* part in func_801730E4 */

typedef struct S_801730E4_6 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_801730E4_6;   /* object in func_801730E4 */

typedef struct S_801730E4_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_801730E4_7;   /* target in func_801730E4 */

typedef struct S_801730E4_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_801730E4_8;   /* held_base in func_801730E4 */

typedef struct S_801730E4_9 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801730E4_9;   /* source in func_801730E4 */

typedef struct S_801730E4_10 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801730E4_10;   /* global in func_801730E4 */

void func_801730E4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const keepalive[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_default, &&kind_default, &&kind_default
    };
    u16 delta[3];
    s32 special;
    void *active;
    register u8 *linked ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u8 linked_x;
    u8 linked_y;
    u8 *selection;
    u8 *held_base;
    u8 state;

    special = 0;
    held_base = (u8 *)arg0 - 0x20;
    state = ((S_801730E4_0 *)arg0)->unk_9B;
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
    if ((*(u32 *)((u8 *)arg3 + 0x1C)) & 0x2000) {
        u32 kind;

        kind = ((*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF) - 1;
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

        kind = (*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF;
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

    ((S_801730E4_0 *)arg0)->unk_98 &= 0xFF7F;
    {
        s32 special_test = special;

        ASM_KEEP(special_test);   /* MATCH pin: retail basic-block layout depends on it */
        if (special_test != 0) {
            active = D_800814A8;
            (*(void * *)((u8 *)arg3 + 0x60)) = active;
        } else {
            if (D_8006DE24[*selection].type != 2) {
                goto create_active;
            }
            active = (*(void * *)((u8 *)arg3 + 0x60));
            if (active == 0) {
                goto active_ready;
            }
        }
    }
copy_active:
    linked = ((S_801730E4_1_pre *)active)[-1].unk_00;
    (*(u8 *)((u8 *)arg3 + 0x72)) = ((S_801730E4_2 *)linked)->unk_24;
    (*(u8 *)((u8 *)arg3 + 0x73)) = ((S_801730E4_2 *)linked)->unk_25;
    goto active_ready;

create_active:
    {
        s32 x;
        s32 y;

        active = func_800A05A4(
            arg3, ((S_801730E4_3 *)arg2)->unk_24, ((S_801730E4_3 *)arg2)->unk_25,
            (*(s16 *)((u8 *)arg3 + 0x2A)), 0x10);
        (*(void * volatile *)((u8 *)arg3 + 0x60)) = active;
        ASM_KEEP(active);   /* MATCH pin: keeps a statement from moving across a call/branch */
        x = (*(s8 *)((u8 *)arg3 + 0x72));
        y = (*(s8 *)((u8 *)arg3 + 0x73));
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        (*(u8 *)((u8 *)arg3 + 0x72)) = x;
        (*(u8 *)((u8 *)arg3 + 0x73)) = y;
    }

active_ready:
    if (func_800A94A0(arg3, selection, special, (u8 *)arg0 + 0x98) == 0) {
        return;
    }
    ((S_801730E4_0 *)arg0)->unk_96 = 10;
    ((S_801730E4_0 *)arg0)->unk_9B++;
    func_800A56E0(0x703);
    return;

empty_selection:
    ((S_801730E4_4 *)arg1)->unk_14 = 0;
    ((S_801730E4_4 *)arg1)->unk_10 = 0;
    ((S_801730E4_4 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_801730E4_3 *)arg2)->unk_24, ((S_801730E4_3 *)arg2)->unk_25);
    {
        void *active;

        active = D_800814A8;
        D_8008346C = 0;
        (*(u16 *)((u8 *)active + 0xA6))--;
    }
    func_800A4ACC(arg3);
    (*(u8 *)((u8 *)arg3 + 0x6D))--;
    ((S_801730E4_0 *)arg0)->unk_8C = &D_801714B8;
    (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
    (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
    (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
    return;

state_1:
    if (func_8003F270() != 0) {
        ((S_801730E4_3 *)arg2)->unk_14 |= 0x800;
        return;
    }
    ((S_801730E4_3 *)arg2)->unk_14 &= 0xF7FF;
    ((S_801730E4_0 *)arg0)->unk_96 = 10;
    ((S_801730E4_0 *)arg0)->unk_9B++;
    {
        u8 *object;

        object = func_8003FD64(0x112, D_80083498);
        if (object != 0) {
            u8 *part;
            u8 *target;
            void *source;
            u8 animation;

            part = object + 0x20;
            ((S_801730E4_5 *)part)->unk_96 = 0xF;
            ((S_801730E4_6 *)object)->unk_10 = &D_801708D4;
            ((S_801730E4_5 *)part)->unk_A8 = arg1;
            ((S_801730E4_5 *)part)->unk_94 = (*(u16 *)((u8 *)arg3 + 0x2A));
            target = ((S_801730E4_6 *)object)->unk_0C;
            *(Copy48 *)target = *(Copy48 *)arg2;
            ((S_801730E4_7 *)target)->unk_1E = 0x1000;
            ((S_801730E4_7 *)target)->unk_1C = 0x1000;
            ((S_801730E4_7 *)target)->unk_0E = 0x80;
            ((S_801730E4_7 *)target)->unk_0D = 0x80;
            ((S_801730E4_7 *)target)->unk_0C = 0x80;
            func_8004491C(object, &D_80045340);
            animation = D_801760FC[0];
            ((S_801730E4_7 *)target)->unk_2C = D_801760FC;
            func_80047784(target, animation, 0);
            ((S_801730E4_7 *)target)->unk_10 = 0x20;
            ((S_801730E4_7 *)target)->unk_12 = 0xFF80;
            ((S_801730E4_7 *)target)->unk_14 |= 0xC;

            source = ((S_801730E4_8 *)held_base)->unk_0C;
            target = ((S_801730E4_6 *)object)->unk_08;
            if (func_8003DE58(((S_801730E4_9 *)source)->unk_08, source, delta, 0) != 0) {
                ((S_801730E4_7 *)target)->unk_02 = ((S_801730E4_4 *)arg1)->unk_02;
                ((S_801730E4_7 *)target)->unk_06 = ((S_801730E4_4 *)arg1)->unk_06;
                ((S_801730E4_7 *)target)->unk_0A = ((S_801730E4_4 *)arg1)->unk_0A;
                ((S_801730E4_7 *)target)->unk_02 += delta[0];
                ((S_801730E4_7 *)target)->unk_06 += delta[1];
                ((S_801730E4_7 *)target)->unk_0A += delta[2];
            }
        }
    }

state_2:
    {
        u16 timer;

        timer = ((S_801730E4_0 *)arg0)->unk_96 - 1;
        ((S_801730E4_0 *)arg0)->unk_96 = timer;
        if ((s16)timer > 0 && !(((S_801730E4_3 *)arg2)->unk_14 & 0xE000)) {
            return;
        }
    }
    ((S_801730E4_0 *)arg0)->unk_98 |= 0x80;
    ((S_801730E4_0 *)arg0)->unk_9B++;
    return;

state_3:
    if ((((S_801730E4_3 *)arg2)->unk_04 == 2 &&
         (((S_801730E4_3 *)arg2)->unk_14 & 0x1000)) ||
        (((S_801730E4_3 *)arg2)->unk_14 & 0x8000)) {
        ((S_801730E4_3 *)arg2)->unk_14 |= 0x800;
        ((S_801730E4_0 *)arg0)->unk_96 = 0x14;
    }
    {
        u8 *global;
        u16 timer;

        global = (u8 *)&D_80083460;
        if (((S_801730E4_10 *)global)->unk_0C == 0) {
            ((S_801730E4_0 *)arg0)->unk_96 = 0;
        }
        timer = ((S_801730E4_0 *)arg0)->unk_96 - 1;
        ((S_801730E4_0 *)arg0)->unk_96 = timer;
        if ((s16)timer <= 0) {
            ((S_801730E4_0 *)arg0)->unk_96 = 0;
            ((S_801730E4_3 *)arg2)->unk_14 &= 0xF7FF;
        }
        if (!(((S_801730E4_3 *)arg2)->unk_14 & 0xE000)) {
            return;
        }

        ((S_801730E4_4 *)arg1)->unk_14 = 0;
        ((S_801730E4_4 *)arg1)->unk_10 = 0;
        ((S_801730E4_4 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_801730E4_3 *)arg2)->unk_24, ((S_801730E4_3 *)arg2)->unk_25);
        if (((S_801730E4_3 *)arg2)->unk_2C != D_8017609C) {
            s32 index;

            (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8017609C;
            index = ((D_80083228 + (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7;
            func_80047784(arg2, D_8017609C[index], 0);
            ((S_801730E4_3 *)arg2)->unk_14 &= 0xF7FF;
        }
        if (((S_801730E4_10 *)global)->unk_0C != 0) {
            return;
        }
        ((S_801730E4_10 *)global)->unk_0A--;
    }
    ((S_801730E4_0 *)arg0)->unk_8C = &D_801714B8;
    func_800A4ACC(arg3);
    (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
    (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
    (*(u8 *)((u8 *)arg3 + 0x6D))--;
    (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
    func_800A56E0(0xB4);
}
