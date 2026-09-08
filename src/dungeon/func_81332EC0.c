#include "common.h"

#ifndef NULL
#define NULL ((void *)0)
#endif


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_800353F4();
extern void func_80042B68();
extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern void func_800A48F0();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s32 func_800BCB04();
extern void func_80169FC0() __attribute__((noreturn));
extern void func_8016A158() __attribute__((noreturn));
extern void func_8016A17C() __attribute__((noreturn));
extern void func_8016A1E8() __attribute__((noreturn));
extern void func_8016A280() __attribute__((noreturn));
extern void func_8016A298() __attribute__((noreturn));
extern void func_8016A318() __attribute__((noreturn));
extern void D_8016A36C();

extern u16 D_80013714;
extern s16 D_80083228;
extern u16 D_80083462;
extern s16 D_8008346A;
extern u8 *D_800E3D7C;
extern Callback D_80173B94[];
extern u8 D_80173DDC[];


typedef struct S_80169EC0_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80169EC0_0;   /* scan in func_80169EC0 */

typedef struct S_80169EC0_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80169EC0_1_pre;   /* the 0x14 bytes before entry in func_80169EC0, addressed as entry[-1] */

typedef struct S_80169EC0_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80169EC0_2;   /* record in func_80169EC0 */

typedef struct S_80169EC0_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80169EC0_3;   /* actor in func_80169EC0 */

typedef struct S_80169EC0_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80169EC0_4;   /* data in func_80169EC0 */

typedef struct S_80169EC0_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80169EC0_5;   /* motion in func_80169EC0 */

/* Updates actor callbacks, facing, movement, and terrain height. */
void func_80169EC0(void *owner_arg, void *motion_arg, void *data_arg)
{
    void *owner = owner_arg;
    void *motion = motion_arg;
    register void *data ASM_REG("$19") = data_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *actor ASM_REG("$16") = owner;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 initial_state ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s16 facing ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register u32 state_bits ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    Callback special_callback;
    Callback update_callback;
    s32 terrain_height;
    s32 actor_flags;
    s32 slot_index;
    u8 *slot_ptr;
    void *slot_entry;
    S_80169EC0_2 *slot_record;
    u16 status;
    u16 height;
    s16 signed_height;

    if ((*(u8 *)((u8 *)owner + (0xB1))) == 0 &&
        !(D_80013714 & 1) && D_8008346A == 0) {
        (*(u8 *)((u8 *)owner + (0xB1))) = 1;
        func_800353F4(D_80173DDC);
        (*(u8 *)((u8 *)owner + (0x6D))) = 0;
        (*(u8 *)((u8 *)owner + (0x9B))) = 0;
    }

    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */

    if (D_80013714 & 8) {
        slot_index = 1;
        slot_ptr = D_800E3D7C + 4;
        do {
            slot_entry = ((S_80169EC0_0 *)slot_ptr)->unk_AC;
            if (slot_entry != NULL) {
                slot_record = ((S_80169EC0_1_pre *)slot_entry)[-1].unk_00;
                slot_record->unk_14 &= 0xFFBF;
            }
            slot_index--;
            slot_ptr -= 4;
        } while (slot_index >= 0);
    }

    if ((*(u8 *)((u8 *)owner + (0xB0))) == 1) {
        u32 page;
        func_800A48F0(actor, 7, 1);
        page = 0x80080000;
        ASM_PAGEBASE_PIN(page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80169FC0();
        return;
    }

    func_80042B68(actor, 7);
    if (D_80083462 & 0x2000) {
        special_callback = (*(Callback *)((u8 *)owner + (0x8C)));
        if (special_callback == (Callback)D_8016A36C) {
            special_callback(owner, motion, data, actor);
            return;
        } else {
            ((S_80169EC0_3 *)actor)->unk_71 &= 0x7F;
            return;
        }
    }

    {
        register void *call_owner ASM_REG("$4") = owner;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register void *call_motion ASM_REG("$5") = motion;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register void *call_data ASM_REG("$6") = data;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

        state_bits = ((S_80169EC0_3 *)actor)->unk_6D.u;
        state_bits <<= 24;
        ASM_KEEP_NV(state_bits);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        initial_state = (s32)state_bits >> 24;
        if (func_800A9E70(call_owner, call_motion, call_data, actor) != 0) {
            return;
        }
    }

    update_callback = (*(Callback *)((u8 *)owner + (0x8C)));
    if (update_callback != NULL) {
        update_callback(owner, motion, data, actor);
    }
    D_80173B94[(*(u8 *)((u8 *)owner + (0x9A)))](owner, motion, data, actor);
    if (initial_state != ((S_80169EC0_3 *)actor)->unk_6D.s) {
        func_800AA36C(owner, motion, data, actor);
    }

    status = ((S_80169EC0_4 *)data)->unk_14;
    if (!(status & 0x8000)) {
        register s32 facing_angle ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u16 frame_status;
        u16 cleared_status;
        facing_angle = D_80083228 + ((S_80169EC0_3 *)actor)->unk_2A + 0x100;
        facing = (facing_angle >> 9) & 7;
        if ((*(s16 *)((u8 *)owner + (0x94))) != facing) {
            u8 *facing_steps = ((S_80169EC0_4 *)data)->unk_2C;
            if (facing_steps != NULL) {
                func_80047738(data, facing_steps[facing], ((S_80169EC0_4 *)data)->unk_04);
            }
            (*(s16 *)((u8 *)owner + (0x94))) = facing;
        }

        frame_status = ((S_80169EC0_4 *)data)->unk_14;
        cleared_status = frame_status & 0xFFFE;
        ((S_80169EC0_4 *)data)->unk_14 = cleared_status;
        if (!(((S_80169EC0_3 *)actor)->unk_1C & 0x20)) {
            if (!(frame_status & 0x40)) {
                func_800478B8(data);
                func_8016A158();
                return;
            }
        } else {
            ((S_80169EC0_4 *)data)->unk_14 = cleared_status | 0x7000;
        }
        func_800A020C(((S_80169EC0_3 *)actor)->unk_1C, (u8 *)data + 0xC);
        func_8016A17C();
        return;
    }

    ((S_80169EC0_4 *)data)->unk_14 = (status & 0x800) ?
                            (status & 0x8FFF) : (status | 0x7000);

    ((S_80169EC0_5 *)motion)->unk_00.at00.v += ((S_80169EC0_5 *)motion)->unk_0C;
    ((S_80169EC0_5 *)motion)->unk_04.at00.v += ((S_80169EC0_5 *)motion)->unk_10;
    if ((*(u16 *)((u8 *)owner + (0x98))) & 8) {
        (*(u8 *)((u8 *)owner + (0x9D))) = 0;
        func_8016A1E8();
        return;
    }

    ((S_80169EC0_5 *)motion)->unk_14 += (*(s8 *)((u8 *)owner + (0x9D))) * 0x14000;
    (*(u8 *)((u8 *)owner + (0x9D)))++;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    (*(s32 *)((u8 *)owner + (0x90))) += ((S_80169EC0_5 *)motion)->unk_14;

    if ((*(u16 *)((u8 *)owner + (0x98))) & 4) {
        goto clear_movement_flag;
    }
    terrain_height = func_800BCB04(((S_80169EC0_5 *)motion)->unk_00.at02.v, ((S_80169EC0_5 *)motion)->unk_04.at02.v,
                           (s16)(((S_80169EC0_3 *)actor)->unk_88.u - 0x20));
    if ((s16)terrain_height >= 0x200) {
        goto clear_movement_flag;
    }
    signed_height = ((S_80169EC0_3 *)actor)->unk_88.s;
    height = ((S_80169EC0_3 *)actor)->unk_88.u;
    if ((*(s16 *)((u8 *)owner + (0x92))) + signed_height < (s16)terrain_height) {
        ((S_80169EC0_3 *)actor)->unk_1C &= 0xF7FFFFFF;
        func_8016A298(height, terrain_height, signed_height);
        return;
    }
    if ((s16)terrain_height >= signed_height) {
        (*(s32 *)((u8 *)owner + (0x90))) = 0;
        func_8016A280(height, terrain_height, signed_height);
        return;
    }
    (*(s16 *)((u8 *)owner + (0x92))) = terrain_height - height;
    ((S_80169EC0_5 *)motion)->unk_14 = 0;
    ((S_80169EC0_3 *)actor)->unk_1C |= 0x08000000;
    (*(u8 *)((u8 *)owner + (0x9D))) = 0;
    actor_flags = ((S_80169EC0_3 *)actor)->unk_1C;
    if (actor_flags & 0x40000000) {
        ((S_80169EC0_3 *)actor)->unk_1C = actor_flags & 0xBFFFFFFF;
        terrain_height = func_800BCB04((((S_80169EC0_4 *)data)->unk_24 << 6) | 0x20,
                               (((S_80169EC0_4 *)data)->unk_25 << 6) | 0x20,
                               (s16)(((S_80169EC0_3 *)actor)->unk_88.u - 0x20));
        (*(s16 *)((u8 *)owner + (0x92))) += ((S_80169EC0_3 *)actor)->unk_88.u - terrain_height;
        ((S_80169EC0_3 *)actor)->unk_88.u = terrain_height;
        func_8016A318();
        return;
    }
    goto finish;

clear_movement_flag:
    ((S_80169EC0_3 *)actor)->unk_1C &= 0xF7FFFFFF;

finish:
    ((S_80169EC0_5 *)motion)->unk_0A = (*(s8 *)((u8 *)owner + (0xAA))) +
                              (((S_80169EC0_3 *)actor)->unk_88.u +
                               (*(u16 *)((u8 *)owner + (0x92))));
    ((S_80169EC0_4 *)data)->unk_14 |= 0x40;
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(facing);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
}
