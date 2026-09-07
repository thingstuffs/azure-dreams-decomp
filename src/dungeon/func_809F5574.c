#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172D74_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 s; s8 u; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80172D74_0;   /* arg3 in func_80172D74 */

typedef struct S_80172D74_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    void * unk_A4;
    u16 unk_A8;
} S_80172D74_1;   /* arg0 in func_80172D74 */

typedef struct S_80172D74_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172D74_2_pre;   /* the 0x14 bytes before entity in func_80172D74, addressed as entity[-1] */

typedef struct S_80172D74_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172D74_3;   /* position in func_80172D74 */

typedef struct S_80172D74_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172D74_4;   /* arg2 in func_80172D74 */

typedef struct S_80172D74_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80172D74_5;   /* part20 in func_80172D74 */


typedef struct S_80172D74_7 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80172D74_7;   /* part28 in func_80172D74 */

typedef struct S_80172D74_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172D74_8;   /* global in func_80172D74 */



extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, s32, s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, void *, s32, void *);
extern void func_800DAE44(void *, s32);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170838[];
extern void *D_80170880[];
extern u8 D_80171400[];
extern u8 D_80175140[];
extern u8 D_80175148[];
extern u8 D_80175168[];
extern u8 D_80175170[];

void func_80172D74(void *arg0, void *arg1, void *arg2, void *arg3)
{
    void *owner;
    void *part20;
    void *part28;
    u8 *slot;
    void *entity;
    s32 special;
    s32 xdir;
    s32 zdir;
    s32 next_state;
    register u8 state_value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    static void *const outer_keepalive[] = {
        &&state0, &&state1, &&state2, &&state3, &&state16
    };
    static void *const inner_keepalive[] = {
        &&kind1, &&kind2, &&kind3, &&kind4, &&kind5, &&kind6, &&kind7
    };

    special = 0;
    {
        u32 direction = ((u16)((S_80172D74_0 *)arg3)->unk_2A >> 8) & 0xE;

        owner = ((S_80172D74_1 *)arg0)->unk_A4;
        part20 = (u8 *)owner + 0x20;
        xdir = *(s16 *)(&D_8006CCD8 + direction);
        zdir = *(s16 *)(&D_8006CCE8 + direction);
        part28 = (u8 *)owner + 0x28;
    }
    ((S_80172D74_1 *)arg0)->unk_96.s--;
    {
        u8 dispatch = ((S_80172D74_1 *)arg0)->unk_9B;

        if ((u32)dispatch >= 17) {
            return;
        }
        (void)outer_keepalive;
        goto *D_80170838[dispatch];
    }

state0:
    if (((S_80172D74_0 *)arg3)->unk_1C & 0x2000) {
        s32 dispatch = (((S_80172D74_0 *)arg3)->unk_46 & 0x3FFF) - 1;

        if ((u32)dispatch >= 7) {
            goto kind4;
        }
        (void)inner_keepalive;
        goto *D_80170880[dispatch];
kind5:
        special = 1;
        goto kind3;
kind6:
        special = 1;
        goto kind2;
kind7:
        special = 1;
        goto kind1;
    }

    {
        s32 type = ((S_80172D74_0 *)arg3)->unk_46 & 0x3FFF;

        if (type == 2) {
            goto kind2;
        }
        if (type < 3) {
            if (type == 1) {
                goto kind1;
            }
            slot = 0;
            goto selected;
        }
        if (type == 3) {
            goto kind3;
        }
        slot = 0;
        goto selected;
    }

kind3:
    slot = (u8 *)arg3 + 0xE;
    goto selected;
kind2:
    slot = (u8 *)arg3 + 0xB;
    goto selected;
kind1:
    slot = (u8 *)arg3 + 8;
    goto selected;
kind4:
    slot = 0;

selected:
    if (*slot == 0) {
        goto empty_slot;
    }
    ((S_80172D74_1 *)arg0)->unk_98 &= 0xFF7F;
    {
        s32 special_test;

        special_test = special;
        ASM_KEEP(special_test);   /* MATCH pin: retail basic-block layout depends on it */
        if (special_test != 0) {
            entity = D_800814A8;
            ((S_80172D74_0 *)arg3)->unk_60 = entity;
            goto have_entity;
        }
    }
    {
        u8 *item_defs = D_8006DE24;
        u8 item = *slot;

        if (item_defs[item * 20 + 0x12] == 2) {
            entity = ((S_80172D74_0 *)arg3)->unk_60;

            if (entity != 0) {
                register void *position ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

have_entity:
                position = ((S_80172D74_2_pre *)entity)[-1].unk_00;
                ((S_80172D74_0 *)arg3)->unk_72.s = ((S_80172D74_3 *)position)->unk_24;
                ((S_80172D74_0 *)arg3)->unk_73.s = ((S_80172D74_3 *)position)->unk_25;
            }
        } else {
            void *spawned;
            s32 x;
            s32 z;

            spawned = func_800A05A4(arg3,
                ((S_80172D74_4 *)arg2)->unk_24, ((S_80172D74_4 *)arg2)->unk_25,
                ((S_80172D74_0 *)arg3)->unk_2A, 0x10);
            ((S_80172D74_0 *)arg3)->unk_60 = spawned;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            x = ((S_80172D74_0 *)arg3)->unk_72.u;
            z = ((S_80172D74_0 *)arg3)->unk_73.u;
            if (x < 0) {
                x = -x;
            }
            if (z < 0) {
                z = -z;
            }
            ((S_80172D74_0 *)arg3)->unk_72.u = x;
            ((S_80172D74_0 *)arg3)->unk_73.u = z;
        }
    }

ready_item:
    ((S_80172D74_5 *)part20)->unk_04 &= 0x7FFF;
    (*(u8 * *)((u8 *)part28 + 0x2C)) = D_80175168;
    func_80047784(part28,
        D_80175168[((D_80083228 + ((S_80172D74_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    if (!func_800A94A0(arg3, slot, special, (u8 *)arg0 + 0x98)) {
        return;
    }
    ((S_80172D74_4 *)arg2)->unk_14 &= 0xF7FF;
    func_800DAE44(arg1, 3);
    func_800A56E0(0x703);
    state_value = ((S_80172D74_1 *)arg0)->unk_9B;
    ((S_80172D74_1 *)arg0)->unk_96.s = 6;
    goto increment_state_loaded;

empty_slot:
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((S_80172D74_4 *)arg2)->unk_24, ((S_80172D74_4 *)arg2)->unk_25);
    {
        void *entity = D_800814A8;

        D_8008346C = 0;
        (*(u16 *)((u8 *)entity + 0xA6))--;
    }
    func_800A4ACC(arg3);
    ((S_80172D74_0 *)arg3)->unk_6D.s--;
    ((S_80172D74_1 *)arg0)->unk_8C = D_80171400;
    ((S_80172D74_0 *)arg3)->unk_73.s = 0;
    ((S_80172D74_0 *)arg3)->unk_72.s = 0;
    ((S_80172D74_0 *)arg3)->unk_46 &= 0x7FFF;
    return;

state1:
    if (func_8003F270()) {
        ((S_80172D74_4 *)arg2)->unk_14 |= 0x0800;
        return;
    }
    ((S_80172D74_4 *)arg2)->unk_14 &= 0xF7FF;
    ((S_80172D74_1 *)arg0)->unk_9B++;

state2:
    if (((S_80172D74_1 *)arg0)->unk_96.u > 0 &&
        !(((S_80172D74_4 *)arg2)->unk_14 & 0xE000)) {
        return;
    }
    ((S_80172D74_1 *)arg0)->unk_96.s = 7;
    ((S_80172D74_1 *)arg0)->unk_98 |= 0x80;
    if (((S_80172D74_4 *)arg2)->unk_14 & 0x8000) {
        next_state = 0x10;
        goto set_state;
    }

increment_state:
    state_value = ((S_80172D74_1 *)arg0)->unk_9B;
increment_state_loaded:
    ((S_80172D74_1 *)arg0)->unk_9B = state_value + 1;
    return;

state3:
    if (((S_80172D74_1 *)arg0)->unk_96.u < 4) {
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = -xdir << 18;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = -zdir << 18;
    }
    if (((S_80172D74_1 *)arg0)->unk_96.u > 0) {
        return;
    }
    next_state = 4;
    ((S_80172D74_1 *)arg0)->unk_96.s = next_state;
    next_state = 0x10;
set_state:
    ((S_80172D74_1 *)arg0)->unk_9B = next_state;
    return;

state16:
    {
        s32 coord = ((S_80172D74_4 *)arg2)->unk_24 << 6;
        s32 current = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v - 0x20;

        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = (coord - current) << 14;
    }
    {
        s32 coord = ((S_80172D74_4 *)arg2)->unk_25 << 6;
        s32 current = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v - 0x20;

        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = (coord - current) << 14;
    }
    if (!(((S_80172D74_7 *)part28)->unk_14 & 0x8000) &&
        ((S_80172D74_1 *)arg0)->unk_96.u > 0) {
        return;
    }
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((S_80172D74_4 *)arg2)->unk_24, ((S_80172D74_4 *)arg2)->unk_25);
    {
        u8 *animation = ((S_80172D74_4 *)arg2)->unk_2C;
        u8 *next = D_80175140;

        if (animation != D_80175140) {
            u8 *alternate = D_80175148;

            if (animation != alternate && (((S_80172D74_4 *)arg2)->unk_14 & 0x6000)) {
                ((S_80172D74_5 *)part20)->unk_04 |= 0x8000;
                ((S_80172D74_1 *)arg0)->unk_A8 = 0;
                if (((S_80172D74_4 *)arg2)->unk_2C == D_80175170) {
                    next = alternate;
                }
                (*(u8 * *)((u8 *)arg2 + 0x2C)) = next;
                func_80047784(arg2,
                    next[((D_80083228 + ((S_80172D74_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
        }
    }
    {
        u8 *global = (u8 *)&D_80083460;

        if (((S_80172D74_8 *)global)->unk_0C != 0) {
            return;
        }
        ((S_80172D74_8 *)global)->unk_0A--;
    }
    ((S_80172D74_4 *)arg2)->unk_14 &= 0xF7FF;
    ((S_80172D74_1 *)arg0)->unk_8C = D_80171400;
    func_800A4ACC(arg3);
    if (((S_80172D74_0 *)arg3)->unk_6D.u > 0) {
        ((S_80172D74_0 *)arg3)->unk_6D.s--;
    }
    ((S_80172D74_0 *)arg3)->unk_73.s = 0;
    ((S_80172D74_0 *)arg3)->unk_72.s = 0;
    ((S_80172D74_0 *)arg3)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);
}

/* MECHANISM: The true-space body naturally yields the 0x40 frame and s6/s7 held subobject bases.
   Fall-through barriers preserve the special-test move, load delays, and result-store schedule.
   The special CFG edge joins the position-copy block; short v0/v1 lives preserve pointer roles
   and carry the already-loaded state byte across the shared increment join. */
