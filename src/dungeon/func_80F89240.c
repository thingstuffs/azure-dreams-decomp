#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_8003F270(void);
extern void func_80047784(void *, u8, s16);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800DAE44(void *, s32);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern u8 D_80171138[];
extern u8 D_80174AD4[];


typedef struct S_80172A40_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_80172A40_0;   /* arg0 in func_80172A40 */

typedef struct S_80172A40_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 u; s8 s; } unk_72;   /* accessed as both */
    union { u8 u; s8 s; } unk_73;   /* accessed as both */
} S_80172A40_1;   /* arg3 in func_80172A40 */

typedef struct S_80172A40_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172A40_2_pre;   /* the 0x14 bytes before target in func_80172A40, addressed as target[-1] */

typedef struct S_80172A40_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172A40_3;   /* record in func_80172A40 */

typedef struct S_80172A40_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172A40_4;   /* arg2 in func_80172A40 */


typedef struct S_80172A40_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172A40_6;   /* status in func_80172A40 */

void func_80172A40(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const keepalive[] = {
        &&slot_one, &&slot_two, &&slot_three, &&slot_none,
        &&special_one, &&special_two, &&special_three
    };
    register void *owner ASM_REG("$19") = arg0;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *motion ASM_REG("$21") = arg1;   /* MATCH pin: keeps a constant in a register as retail does */
    register void *actor ASM_REG("$18") = arg2;   /* MATCH pin: keeps a statement from moving across a call/branch */
    void *object = arg3;
    s32 special;
    register u8 *selector ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 state;
    s32 kind;
    s32 special_copy;
    u8 *entry;
    u8 *entry_base;
    register void *target ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    void *record;
    s32 x;
    s32 y;
    s32 index;
    s32 item_id;
    u8 *status;

    ASM_KEEP_NV(owner);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP_NV(motion);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP_NV(actor);   /* MATCH pin: retail schedule: same instructions, different order without it */

#define arg0 owner
#define arg1 motion
#define arg2 actor
#define arg3 object

    state = ((S_80172A40_0 *)arg0)->unk_9B;
    special = 0;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        return;
    }
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    if (((S_80172A40_1 *)arg3)->unk_1C & 0x2000) {
        index = (((S_80172A40_1 *)arg3)->unk_46 & 0x3FFF) - 1;
        if ((u32)index >= 7U) {
            goto slot_none;
        }
        (void)keepalive;
        goto *(((void **)D_80170838)[index]);

special_one:
        special = 1;
        goto slot_three;
special_two:
        special = 1;
        goto slot_two;
special_three:
        special = 1;
        goto slot_one;
    }

    kind = ((S_80172A40_1 *)arg3)->unk_46 & 0x3FFF;
    if (kind == 2) {
        goto slot_two;
    }
    if (kind < 3) {
        if (kind == 1) {
            goto slot_one;
        }
        selector = 0;
        goto selected;
    }
    if (kind == 3) {
        goto slot_three;
    }
    selector = 0;
    goto selected;

slot_three:
    selector = (u8 *)arg3 + 0xE;
    goto selected;
slot_two:
    selector = (u8 *)arg3 + 0xB;
    goto selected;
slot_one:
    selector = (u8 *)arg3 + 8;
    goto selected;
slot_none:
    selector = 0;

selected:
    if (*selector != 0) {
        ((S_80172A40_0 *)arg0)->unk_98 &= 0xFF7F;

        special_copy = special;
        ASM_KEEP(special_copy);   /* MATCH pin: retail basic-block layout depends on it */
        if (special_copy) {
            target = D_800814A8;
            ((S_80172A40_1 *)arg3)->unk_60 = target;
            goto copy_record;
        }

        entry_base = D_8006DE24;
        item_id = *selector;
        entry = entry_base + item_id * 20;
        if (entry[0x12] == 2) {
            target = ((S_80172A40_1 *)arg3)->unk_60;
            if (target == 0) {
                goto move_setup;
            }
copy_record:
            record = ((S_80172A40_2_pre *)target)[-1].unk_00;
            ASM_KEEP(target);   /* MATCH pin: load-bearing for the whole function shape */
            ((S_80172A40_1 *)arg3)->unk_72.u = ((S_80172A40_3 *)record)->unk_24;
            ((S_80172A40_1 *)arg3)->unk_73.u = ((S_80172A40_3 *)record)->unk_25;
            goto move_setup;
        }

        ((S_80172A40_1 *)arg3)->unk_60 = func_800A05A4(
            arg3, ((S_80172A40_4 *)arg2)->unk_24, ((S_80172A40_4 *)arg2)->unk_25,
            ((S_80172A40_1 *)arg3)->unk_2A, 0x10);
        ASM_KEEP(object);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

        x = ((S_80172A40_1 *)arg3)->unk_72.s;
        y = ((S_80172A40_1 *)arg3)->unk_73.s;
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        ((S_80172A40_1 *)arg3)->unk_72.u = x;
        ((S_80172A40_1 *)arg3)->unk_73.u = y;

move_setup:
        if (func_800A94A0(arg3, selector, special,
                          (u16 *)((u8 *)arg0 + 0x98)) == 0) {
            return;
        }
        ((S_80172A40_4 *)arg2)->unk_14 &= 0xF7FF;
        func_800DAE44(arg1, 4);
        func_800A56E0(0x703);
        ((S_80172A40_0 *)arg0)->unk_96.u = 4;
        ((S_80172A40_0 *)arg0)->unk_9B++;
        ((S_80172A40_0 *)arg0)->unk_98 |= 8;
        ((S_80172A40_1 *)arg3)->unk_1C &= 0xF7FFFFFF;
        ((S_80172A40_1 *)arg3)->unk_1C &= 0xFFFBFFFF;
        return;
    }

    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((S_80172A40_4 *)arg2)->unk_24, ((S_80172A40_4 *)arg2)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(arg3);
    ((S_80172A40_1 *)arg3)->unk_6D.u--;
    ((S_80172A40_0 *)arg0)->unk_8C = D_80171138;
    ((S_80172A40_1 *)arg3)->unk_73.u = 0;
    ((S_80172A40_1 *)arg3)->unk_72.u = 0;
    ((S_80172A40_1 *)arg3)->unk_46 &= 0x7FFF;
    return;

state_one:
    if (func_8003F270() != 0) {
        ((S_80172A40_4 *)arg2)->unk_14 |= 0x800;
        return;
    }
    ((S_80172A40_4 *)arg2)->unk_14 &= 0xF7FF;
    ((S_80172A40_0 *)arg0)->unk_9B++;

state_two:
    ((S_80172A40_0 *)arg0)->unk_92 +=
        (-0x30 - ((S_80172A40_0 *)arg0)->unk_92) >> 3;
    ((S_80172A40_0 *)arg0)->unk_96.u--;
    if (((S_80172A40_0 *)arg0)->unk_96.s > 0) {
        if ((((S_80172A40_4 *)arg2)->unk_14 & 0xE000) == 0) {
            return;
        }
    }
    ((S_80172A40_0 *)arg0)->unk_98 |= 0x80;
    if ((((S_80172A40_4 *)arg2)->unk_14 & 0xE000) == 0) {
        return;
    }

    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((S_80172A40_4 *)arg2)->unk_24, ((S_80172A40_4 *)arg2)->unk_25);
    ((S_80172A40_0 *)arg0)->unk_98 &= 0xFFF7;
    ((S_80172A40_1 *)arg3)->unk_1C |= 0x08000000;
    ((S_80172A40_1 *)arg3)->unk_1C |= 0x00040000;

    if (((S_80172A40_4 *)arg2)->unk_2C != D_80174AD4) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174AD4;
        func_80047784(arg2,
                      D_80174AD4[((D_80083228 +
                                   ((S_80172A40_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                      ((S_80172A40_0 *)arg0)->unk_A0);
    }

    status = (u8 *)&D_80083460;
    if (((S_80172A40_6 *)status)->unk_0C != 0) {
        return;
    }
    ((S_80172A40_6 *)status)->unk_0A--;
    ((S_80172A40_4 *)arg2)->unk_14 &= 0xF7FF;
    ((S_80172A40_0 *)arg0)->unk_8C = D_80171138;
    func_800A4ACC(arg3);
    if (((S_80172A40_1 *)arg3)->unk_6D.s > 0) {
        ((S_80172A40_1 *)arg3)->unk_6D.u--;
    }
    ((S_80172A40_1 *)arg3)->unk_73.u = 0;
    ((S_80172A40_1 *)arg3)->unk_72.u = 0;
    ((S_80172A40_1 *)arg3)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);

#undef arg0
#undef arg1
#undef arg2
#undef arg3
}
