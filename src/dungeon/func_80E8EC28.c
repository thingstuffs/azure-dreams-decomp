#include "common.h"

typedef struct S_80174428_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x1A];
    s16 unk_88;
} S_80174428_0;   /* object in func_80174428 */

typedef struct S_80174428_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174428_1;   /* state in func_80174428 */

typedef struct S_80174428_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80174428_2;   /* actor in func_80174428 */

typedef struct S_80174428_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_80174428_3;   /* motion in func_80174428 */



extern u8 D_8006CCD8[9];
extern u8 D_8006CCE8[9];
extern s16 D_80081468[3];
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u16 D_80083460[6];
extern u8 D_801710F4[];
extern u8 D_80174EF8[];
extern u8 D_80174F00[];
extern u8 D_80174F58[];
extern u16 D_80174FC4[];
extern u16 D_80174FD4[];
extern void *D_801708F0[];

extern void func_80047784(void *, s32, s32);
extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern s16 func_800A4E2C(u8 *, u8 *);
extern void func_800A56E0(s32);
extern void func_800AA53C(void *);
extern void func_800AD594(void *, s32);
extern s16 func_800BCB04(s32, s32, s16);

#define state arg0
#define motion arg1
#define actor arg2
#define object arg3

void func_80174428(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&case_5
    };
    s32 ystep;
    s32 xstep;
    register s16 *xstep_ptr ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    u32 direction_offset;
    register u32 raw_direction ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s16 result;
    register s32 case4_result ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    register s32 case4_valid ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 counter ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *world;
    s16 *level;
    register void **jump_base ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u32 jump_offset;
    u32 state_id;
    register u32 state_valid ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    xstep_ptr = (s16 *)&D_8006CCD8;
    raw_direction = ((S_80174428_0 *)object)->unk_2A.s;
    direction_offset = raw_direction >> 8;
    direction_offset &= 0xE;
    state_id = ((S_80174428_1 *)state)->unk_9B;
    xstep_ptr = (s16 *)((u8 *)xstep_ptr + direction_offset);
    direction_offset += (u32)&D_8006CCE8;
    state_valid = state_id < 6;
    xstep = *xstep_ptr;
    ystep = *(s16 *)direction_offset;
    if (!state_valid) {
        return;
    }
    (void)jt_keep;
    jump_base = D_801708F0;
    jump_offset = state_id << 2;
    jump_offset = jump_offset + (u32)jump_base;
    goto **(void **)jump_offset;

case_0:
        func_8009A3D0(((S_80174428_2 *)actor)->unk_24, ((S_80174428_2 *)actor)->unk_25,
            (((S_80174428_0 *)object)->unk_1C & 0x2000) ? 0x300 : 0x3000);
        (*(u8 * *)((u8 *)actor + 0x2C)) = D_80174EF8;
        func_80047784(actor,
            D_80174EF8[((D_80083228 + ((S_80174428_0 *)object)->unk_2A.u + 0x100) >> 9) & 7], 0);
        ((S_80174428_3 *)motion)->unk_0C = (xstep << 19) + (xstep << 18);
        ((S_80174428_3 *)motion)->unk_10 = (ystep << 19) + (ystep << 18);
        ((S_80174428_1 *)state)->unk_96.s = 4;
        func_800A56E0(0x80E);
        ((S_80174428_1 *)state)->unk_9B++;
        if (!(((S_80174428_2 *)actor)->unk_14 & 0x8000)) {
            ((S_80174428_1 *)state)->unk_96.s--;
            if (((S_80174428_1 *)state)->unk_96.u > 0) {
                return;
            }
        }
        ((S_80174428_3 *)motion)->unk_10 = 0;
        ((S_80174428_3 *)motion)->unk_0C = 0;
        (*(u8 * *)((u8 *)actor + 0x2C)) = D_80174F58;
        func_80047784(actor,
            D_80174F58[((*(s16 *)(D_80082E80 + 0x3A8) +
                ((S_80174428_0 *)object)->unk_2A.u + 0x100) >> 9) & 7], 0);
        ((S_80174428_1 *)state)->unk_96.s = 0;
        ((S_80174428_3 *)motion)->unk_0C = (-xstep) << 18;
        ((S_80174428_3 *)motion)->unk_10 = (-ystep) << 18;
        goto advance_state;

case_1:
        if (!(((S_80174428_2 *)actor)->unk_14 & 0xE000)) {
            return;
        }
        ((S_80174428_3 *)motion)->unk_10 = 0;
        ((S_80174428_3 *)motion)->unk_0C = 0;
        (*(u8 * *)((u8 *)actor + 0x2C)) = D_80174F00;
        func_80047784(actor,
            D_80174F00[((D_80083228 + ((S_80174428_0 *)object)->unk_2A.u + 0x100) >> 9) & 7], 0);
        if (((S_80174428_0 *)object)->unk_1C & 0x2000) {
            ((S_80174428_1 *)state)->unk_96.s = 7;
            ((S_80174428_1 *)state)->unk_9B = 5;
            return;
        }
        ((S_80174428_0 *)object)->unk_2A.s &= 0xFFF;
        goto advance_state;

case_2: {
        u16 angle = ((S_80174428_0 *)object)->unk_2A.s;
        if ((((S_80174428_0 *)object)->unk_2A.u == 0x400) ||
            (((S_80174428_2 *)actor)->unk_14 & 0x8000)) {
            func_80047784(actor, 0x37, 0);
            goto advance_state;
        }
        if ((u32)(angle - 0x401) < 0x800) {
            ((S_80174428_0 *)object)->unk_2A.s = angle - 0x80;
            return;
        }
        ((S_80174428_0 *)object)->unk_2A.s = (angle + 0x80) & 0xFFF;
        return;
    }

case_3:
        ((S_80174428_2 *)actor)->unk_24 = (u8)xstep;
        ((S_80174428_2 *)actor)->unk_25 = (u8)ystep;
        goto advance_state;

case_4:
        if (!(((S_80174428_2 *)actor)->unk_14 & 0xE000)) {
            return;
        }
        func_80047784(actor, 0x38, 0);
        counter = 0x40;
        world = D_80082E80;
        level = D_80081468;
        ((S_80174428_1 *)state)->unk_96.s = 0;
        xstep = ((S_80174428_2 *)actor)->unk_24;
        ystep = ((S_80174428_2 *)actor)->unk_25;

        ASM_KEEP(counter);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        counter--;
case_4_check:
        if (counter <= 0) {
            goto case_3;
        }
        {
            case4_result = func_800A4E2C(actor + 0x24, actor + 0x25);
            counter--;
            if (case4_result < 0) {
                goto case_4_check;
            }
            counter++;
            if (case4_result != (s8)world[0x26]) {
                goto case_4_position;
            }
            counter--;
            if (*(s16 *)((u8 *)level + 6) >= 2) {
                goto case_4_check;
            }
            counter++;
case_4_position:
            case4_result = func_800BCB04((((S_80174428_2 *)actor)->unk_24 << 6) | 0x20,
                (((S_80174428_2 *)actor)->unk_25 << 6) | 0x20,
                (s16)(((S_80174428_3 *)motion)->unk_0A - 0x80));
            case4_valid = case4_result < 0x201;
            counter--;
            if (!case4_valid) {
                goto case_4_check;
            }
            goto advance_state;
        }

advance_state:
        ((S_80174428_1 *)state)->unk_9B++;
        return;

case_5:
    {
        ((S_80174428_2 *)actor)->unk_1C = D_80174FC4[((S_80174428_1 *)state)->unk_96.u];
        ((S_80174428_2 *)actor)->unk_1E = D_80174FD4[((S_80174428_1 *)state)->unk_96.u];
        if (((S_80174428_1 *)state)->unk_96.u == 4) {
            func_800A56E0(0x705);
        }
        if (!(((S_80174428_2 *)actor)->unk_14 & 0x8000)) {
            ((S_80174428_1 *)state)->unk_96.s++;
            if (((S_80174428_1 *)state)->unk_96.u < 8) {
                return;
            }
        }
        D_80083460[5]--;
        func_800AA53C(object);
        result = func_800BCB04((((S_80174428_2 *)actor)->unk_24 << 6) | 0x20,
            (((S_80174428_2 *)actor)->unk_25 << 6) | 0x20,
            (s16)(((S_80174428_3 *)motion)->unk_0A - 0x80));
        ((S_80174428_0 *)object)->unk_88 = result;
        ((S_80174428_2 *)actor)->unk_2C = D_80174F00;
        func_800AD594(object, 0x200);
        func_80047784(actor,
            ((S_80174428_2 *)actor)->unk_2C[((D_80083228 + ((S_80174428_0 *)object)->unk_2A.u + 0x100) >> 9) & 7], 0);
        func_8009A21C(((S_80174428_2 *)actor)->unk_24, ((S_80174428_2 *)actor)->unk_25,
            (((S_80174428_0 *)object)->unk_1C & 0x2000) ? 0x300 : 0x3000);
        func_800A2B04(motion, ((S_80174428_2 *)actor)->unk_24, ((S_80174428_2 *)actor)->unk_25);
        ((S_80174428_2 *)actor)->unk_1E = 0x1000;
        ((S_80174428_2 *)actor)->unk_1C = 0x1000;
        ((S_80174428_1 *)state)->unk_8C = D_801710F4;
        func_800A4ACC(object);
        ((S_80174428_0 *)object)->unk_6D = 0;
        ((S_80174428_0 *)object)->unk_46 &= 0x7FFF;
        return;
    }
}

#undef state
#undef motion
#undef actor
#undef object
