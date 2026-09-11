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

/* Advances an item action through setup, animation, movement, and cleanup. */
void func_80172D74(void *action, void *motion, void *sprite, void *actor)
{
    void *owner;
    void *owner_flags;
    void *owner_sprite;
    u8 *item_slot;
    void *entity;
    s32 special_item;
    s32 step_x;
    s32 step_z;
    s32 next_state;
    register u8 state_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    static void *const state_labels[] = {
        &&state0, &&state1, &&state2, &&state3, &&state16
    };
    static void *const kind_labels[] = {
        &&kind1, &&kind2, &&kind3, &&kind4, &&kind5, &&kind6, &&kind7
    };

    special_item = 0;
    {
        u32 direction_index = ((u16)((S_80172D74_0 *)actor)->unk_2A >> 8) & 0xE;

        owner = ((S_80172D74_1 *)action)->unk_A4;
        owner_flags = (u8 *)owner + 0x20;
        step_x = *(s16 *)(&D_8006CCD8 + direction_index);
        step_z = *(s16 *)(&D_8006CCE8 + direction_index);
        owner_sprite = (u8 *)owner + 0x28;
    }
    ((S_80172D74_1 *)action)->unk_96.s--;
    {
        u8 state = ((S_80172D74_1 *)action)->unk_9B;

        if ((u32)state >= 17) {
            return;
        }
        (void)state_labels;
        goto *D_80170838[state];
    }

state0:
    if (((S_80172D74_0 *)actor)->unk_1C & 0x2000) {
        s32 kind_index = (((S_80172D74_0 *)actor)->unk_46 & 0x3FFF) - 1;

        if ((u32)kind_index >= 7) {
            goto kind4;
        }
        (void)kind_labels;
        goto *D_80170880[kind_index];
kind5:
        special_item = 1;
        goto kind3;
kind6:
        special_item = 1;
        goto kind2;
kind7:
        special_item = 1;
        goto kind1;
    }

    {
        s32 item_kind = ((S_80172D74_0 *)actor)->unk_46 & 0x3FFF;

        if (item_kind == 2) {
            goto kind2;
        }
        if (item_kind < 3) {
            if (item_kind == 1) {
                goto kind1;
            }
            item_slot = 0;
            goto selected;
        }
        if (item_kind == 3) {
            goto kind3;
        }
        item_slot = 0;
        goto selected;
    }

kind3:
    item_slot = (u8 *)actor + 0xE;
    goto selected;
kind2:
    item_slot = (u8 *)actor + 0xB;
    goto selected;
kind1:
    item_slot = (u8 *)actor + 8;
    goto selected;
kind4:
    item_slot = 0;

selected:
    if (*item_slot == 0) {
        goto empty_slot;
    }
    ((S_80172D74_1 *)action)->unk_98 &= 0xFF7F;
    {
        s16 special_test;

        special_test = special_item;
        if (special_test != 0) {
            entity = D_800814A8;
            ((S_80172D74_0 *)actor)->unk_60 = entity;
            goto have_entity;
        }
    }
    {
        u8 *item_defs = D_8006DE24;
        u8 item_id = *item_slot;

        if (item_defs[item_id * 20 + 0x12] == 2) {
            entity = ((S_80172D74_0 *)actor)->unk_60;

            if (entity != 0) {
                register void *position ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

have_entity:
                position = ((S_80172D74_2_pre *)entity)[-1].unk_00;
                ((S_80172D74_0 *)actor)->unk_72.s = ((S_80172D74_3 *)position)->unk_24;
                ((S_80172D74_0 *)actor)->unk_73.s = ((S_80172D74_3 *)position)->unk_25;
            }
        } else {
            void *spawned_entity;
            s32 x;
            s32 z;

            spawned_entity = func_800A05A4(actor,
                ((S_80172D74_4 *)sprite)->unk_24, ((S_80172D74_4 *)sprite)->unk_25,
                ((S_80172D74_0 *)actor)->unk_2A, 0x10);
            ((S_80172D74_0 *)actor)->unk_60 = spawned_entity;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            x = ((S_80172D74_0 *)actor)->unk_72.u;
            z = ((S_80172D74_0 *)actor)->unk_73.u;
            if (x < 0) {
                x = -x;
            }
            if (z < 0) {
                z = -z;
            }
            ((S_80172D74_0 *)actor)->unk_72.u = x;
            ((S_80172D74_0 *)actor)->unk_73.u = z;
        }
    }

ready_item:
    ((S_80172D74_5 *)owner_flags)->unk_04 &= 0x7FFF;
    (*(u8 * *)((u8 *)owner_sprite + 0x2C)) = D_80175168;
    func_80047784(owner_sprite,
        D_80175168[((D_80083228 + ((S_80172D74_0 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    if (!func_800A94A0(actor, item_slot, special_item, (u8 *)action + 0x98)) {
        return;
    }
    ((S_80172D74_4 *)sprite)->unk_14 &= 0xF7FF;
    func_800DAE44(motion, 3);
    func_800A56E0(0x703);
    state_value = ((S_80172D74_1 *)action)->unk_9B;
    ((S_80172D74_1 *)action)->unk_96.s = 6;
    goto increment_state_loaded;

empty_slot:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((S_80172D74_4 *)sprite)->unk_24, ((S_80172D74_4 *)sprite)->unk_25);
    {
        void *entity = D_800814A8;

        D_8008346C = 0;
        (*(u16 *)((u8 *)entity + 0xA6))--;
    }
    func_800A4ACC(actor);
    ((S_80172D74_0 *)actor)->unk_6D.s--;
    ((S_80172D74_1 *)action)->unk_8C = D_80171400;
    ((S_80172D74_0 *)actor)->unk_73.s = 0;
    ((S_80172D74_0 *)actor)->unk_72.s = 0;
    ((S_80172D74_0 *)actor)->unk_46 &= 0x7FFF;
    return;

state1:
    if (func_8003F270()) {
        ((S_80172D74_4 *)sprite)->unk_14 |= 0x0800;
        return;
    }
    ((S_80172D74_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_80172D74_1 *)action)->unk_9B++;

state2:
    if (((S_80172D74_1 *)action)->unk_96.u > 0 &&
        !(((S_80172D74_4 *)sprite)->unk_14 & 0xE000)) {
        return;
    }
    ((S_80172D74_1 *)action)->unk_96.s = 7;
    ((S_80172D74_1 *)action)->unk_98 |= 0x80;
    if (((S_80172D74_4 *)sprite)->unk_14 & 0x8000) {
        next_state = 0x10;
        goto set_state;
    }

increment_state:
    state_value = ((S_80172D74_1 *)action)->unk_9B;
increment_state_loaded:
    ((S_80172D74_1 *)action)->unk_9B = state_value + 1;
    return;

state3:
    if (((S_80172D74_1 *)action)->unk_96.u < 4) {
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = -step_x << 18;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = -step_z << 18;
    }
    if (((S_80172D74_1 *)action)->unk_96.u > 0) {
        return;
    }
    next_state = 4;
    ((S_80172D74_1 *)action)->unk_96.s = next_state;
    next_state = 0x10;
set_state:
    ((S_80172D74_1 *)action)->unk_9B = next_state;
    return;

state16:
    {
        s32 target_x = ((S_80172D74_4 *)sprite)->unk_24 << 6;
        s32 current_x = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20;

        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (target_x - current_x) << 14;
    }
    {
        s32 target_z = ((S_80172D74_4 *)sprite)->unk_25 << 6;
        s32 current_z = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;

        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (target_z - current_z) << 14;
    }
    if (!(((S_80172D74_7 *)owner_sprite)->unk_14 & 0x8000) &&
        ((S_80172D74_1 *)action)->unk_96.u > 0) {
        return;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((S_80172D74_4 *)sprite)->unk_24, ((S_80172D74_4 *)sprite)->unk_25);
    {
        u8 *animation = ((S_80172D74_4 *)sprite)->unk_2C;
        u8 *next_animation = D_80175140;

        if (animation != D_80175140) {
            u8 *alternate_animation = D_80175148;

            if (animation != alternate_animation && (((S_80172D74_4 *)sprite)->unk_14 & 0x6000)) {
                ((S_80172D74_5 *)owner_flags)->unk_04 |= 0x8000;
                ((S_80172D74_1 *)action)->unk_A8 = 0;
                if (((S_80172D74_4 *)sprite)->unk_2C == D_80175170) {
                    next_animation = alternate_animation;
                }
                (*(u8 * *)((u8 *)sprite + 0x2C)) = next_animation;
                func_80047784(sprite,
                    next_animation[((D_80083228 + ((S_80172D74_0 *)actor)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
        }
    }
    {
        u8 *global_state = (u8 *)&D_80083460;

        if (((S_80172D74_8 *)global_state)->unk_0C != 0) {
            return;
        }
        ((S_80172D74_8 *)global_state)->unk_0A--;
    }
    ((S_80172D74_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_80172D74_1 *)action)->unk_8C = D_80171400;
    func_800A4ACC(actor);
    if (((S_80172D74_0 *)actor)->unk_6D.u > 0) {
        ((S_80172D74_0 *)actor)->unk_6D.s--;
    }
    ((S_80172D74_0 *)actor)->unk_73.s = 0;
    ((S_80172D74_0 *)actor)->unk_72.s = 0;
    ((S_80172D74_0 *)actor)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);
}
