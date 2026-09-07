#include "common.h"


typedef s32 M2C_UNK;

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800BB044(void *);
extern void func_80174BC8(void *, void *, void *);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170868[];
extern M2C_UNK D_80170E94;
extern u8 D_80175F10[8];


typedef struct S_801738B4_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801738B4_0;   /* arg0 in func_801738B4 */

typedef struct S_801738B4_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_801738B4_1_pre;   /* the 0x14 bytes before copy_object in func_801738B4, addressed as copy_object[-1] */

typedef struct S_801738B4_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801738B4_2;   /* entity in func_801738B4 */

typedef struct S_801738B4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801738B4_3;   /* arg1 in func_801738B4 */

typedef struct S_801738B4_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801738B4_4;   /* global in func_801738B4 */

void func_801738B4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *entity ASM_REG("$18") = arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *actor ASM_REG("$17") = arg3;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    static void *const keep_cases[] = {
        &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_5, &&case_6, &&case_7
    };
    u8 *item;
    s32 special;
    s32 state;
    s32 kind;
    u16 value;
    s32 x;
    s32 y;
    void *object;
    void *copy_object;
    register u8 *record ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *global;

    special = 0;
    state = ((S_801738B4_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    if ((*(u32 *)((u8 *)actor + 0x1C)) & 0x2000) {
        kind = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
        if ((u32)kind >= 7) {
            goto no_item;
        }
        (void)keep_cases;
        goto *D_80170868[kind];

case_7:
        special = 1;
        goto item_3;
case_6:
        special = 1;
        goto item_2;
case_5:
        special = 1;
        goto item_1;
    } else {
        kind = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
        if (kind == 2) {
            goto item_2;
        }
        if (kind < 3) {
            if (kind == 1) {
                goto item_1;
            }
            goto no_item;
        }
        if (kind == 3) {
            goto item_3;
        }
        goto no_item;
    }

case_3:
item_3:
    item = (u8 *)actor + 0x0E;
    goto have_item;
case_2:
item_2:
    item = (u8 *)actor + 0x0B;
    goto have_item;
case_1:
item_1:
    item = (u8 *)actor + 8;
    goto have_item;
case_4:
no_item:
    item = 0;

have_item:
    if (*item == 0) {
        goto empty_item;
    }

    ((S_801738B4_0 *)arg0)->unk_98 &= 0xFF7F;
    {
        s32 special_test = (special == 1);
        if (special_test) {
            copy_object = D_800814A8;
            (*(void * *)((u8 *)actor + 0x60)) = copy_object;
            goto copy_position_object;
        }
    }
    {
        u8 item_id;

        item_id = *item;
        if (D_8006DE24[item_id * 20 + 0x12] != 2) {
            goto spawn_object;
        }
    }
    copy_object = (*(void * *)((u8 *)actor + 0x60));
    if (copy_object == 0) {
        goto apply_item;
    }

copy_position_object:
    record = ((S_801738B4_1_pre *)copy_object)[-1].unk_00;
    (*(u8 *)((u8 *)actor + 0x72)) = record[0x24];
    (*(u8 *)((u8 *)actor + 0x73)) = record[0x25];
    goto call_item;

spawn_object:
    copy_object = func_800A05A4(actor,
        ((S_801738B4_2 *)entity)->unk_24,
        ((S_801738B4_2 *)entity)->unk_25,
        (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
    (*(void * volatile *)((u8 *)actor + 0x60)) = copy_object;
    ASM_USE(copy_object);   /* MATCH pin: keeps a statement from moving across a call/branch */
    x = (*(s8 *)((u8 *)actor + 0x72));
    y = (*(s8 *)((u8 *)actor + 0x73));
    if (x < 0) {
        x = -x;
    }
    if (y < 0) {
        y = -y;
    }
    (*(s8 *)((u8 *)actor + 0x72)) = x;
    (*(s8 *)((u8 *)actor + 0x73)) = y;

call_item:
apply_item:
    if (!func_800A94A0(actor, item, special, &((S_801738B4_0 *)arg0)->unk_98)) {
        goto epilogue;
    }
    func_800BB044(actor);
    ((S_801738B4_0 *)arg0)->unk_9B++;
    goto done;

empty_item:
    ((S_801738B4_3 *)arg1)->unk_14 = 0;
    ((S_801738B4_3 *)arg1)->unk_10 = 0;
    ((S_801738B4_3 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_801738B4_2 *)entity)->unk_24, ((S_801738B4_2 *)entity)->unk_25);
    object = D_800814A8;
    D_8008346C = 0;
    (*(u16 *)((u8 *)object + 0xA6))--;
    func_800A4ACC(actor);
    (*(u8 *)((u8 *)actor + 0x6D))--;
    ((S_801738B4_0 *)arg0)->unk_8C = &D_80170E94;
    (*(u8 *)((u8 *)actor + 0x73)) = 0;
    (*(u8 *)((u8 *)actor + 0x72)) = 0;
    (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
    goto done;

state_1:
    if (func_8003F270()) {
        ((S_801738B4_2 *)entity)->unk_14 |= 0x0800;
        goto done;
    }
    ((S_801738B4_2 *)entity)->unk_14 &= 0xF7FF;
    ((S_801738B4_0 *)arg0)->unk_9B++;

state_2:
    if ((((S_801738B4_2 *)entity)->unk_04 == 3 &&
         (((S_801738B4_2 *)entity)->unk_14 & 0x1000)) ||
        (((S_801738B4_2 *)entity)->unk_14 & 0xE000)) {
        func_80174BC8(arg0, arg1, entity);
        ((S_801738B4_0 *)arg0)->unk_9B++;
    }

state_3:
    if ((((S_801738B4_2 *)entity)->unk_04 == 4 &&
         (((S_801738B4_2 *)entity)->unk_14 & 0x1000)) ||
        (((S_801738B4_2 *)entity)->unk_14 & 0xE000)) {
        ((S_801738B4_2 *)entity)->unk_14 |= 0x0800;
        ((S_801738B4_0 *)arg0)->unk_96 = 1;
        ((S_801738B4_0 *)arg0)->unk_98 |= 0x0080;
    }

    value = ((S_801738B4_0 *)arg0)->unk_96 - 1;
    ((S_801738B4_0 *)arg0)->unk_96 = value;
    if ((s16)value <= 0) {
        ((S_801738B4_0 *)arg0)->unk_96 = 0;
        ((S_801738B4_2 *)entity)->unk_14 &= 0xF7FF;
    }
    if (!(((S_801738B4_2 *)entity)->unk_14 & 0xE000)) {
        goto epilogue;
    }

    ((S_801738B4_3 *)arg1)->unk_14 = 0;
    ((S_801738B4_3 *)arg1)->unk_10 = 0;
    ((S_801738B4_3 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_801738B4_2 *)entity)->unk_24, ((S_801738B4_2 *)entity)->unk_25);
    if (((S_801738B4_2 *)entity)->unk_2C != D_80175F10) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = D_80175F10;
        func_80047784(entity,
            D_80175F10[((D_80083228 + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7],
            0);
    }

    global = (u8 *)&D_80083460;
    if (((S_801738B4_4 *)global)->unk_0C != 0) {
        goto epilogue;
    }
    ((S_801738B4_4 *)global)->unk_0A--;
    ((S_801738B4_0 *)arg0)->unk_8C = &D_80170E94;
    func_800A4ACC(actor);
    (*(u8 *)((u8 *)actor + 0x73)) = 0;
    (*(u8 *)((u8 *)actor + 0x72)) = 0;
    (*(u8 *)((u8 *)actor + 0x6D))--;
    (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
    func_800A56E0(0xB4);

done:
epilogue:
    ASM_KEEP(actor);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(entity);   /* MATCH pin: retail schedule: same instructions, different order without it */
    return;
}
