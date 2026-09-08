#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_80ABF07C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80ABF07C_0;   /* obj in func_80ABF07C */

typedef struct S_80ABF07C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80ABF07C_1;   /* work in func_80ABF07C */

typedef struct S_80ABF07C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80ABF07C_2;   /* part_a in func_80ABF07C */

typedef struct S_80ABF07C_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80ABF07C_3;   /* part_b in func_80ABF07C */

typedef struct S_80ABF07C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80ABF07C_4;   /* actor in func_80ABF07C */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8014CA50[];
extern M2C_UNK D_8014CE7C;
extern u8 D_80150C3C[];
extern u8 D_80150C8C[];

/* Creates an actor and initializes its parts and flags for the selected kind. */
void *func_80ABF07C(s16 spawn_flags, s8 tile_x, s8 tile_y, s16 part_value)
{
    s32 kind;
    void *obj;
    S_80ABF07C_2 *part_a;
    S_80ABF07C_3 *part_b;
    S_80ABF07C_1 *work;
    S_80ABF07C_4 *actor;
    s32 flags_or_roll;
    s32 state_flags;
    register s8 saved_x ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 saved_value;
    register s8 saved_y ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *init_obj;
    void *init_part;

    work = 0;
    saved_x = tile_x;
    saved_value = part_value;
    saved_y = tile_y;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80ABF07C_0 *)obj)->unk_10 = D_8014CA50;
        work->unk_13 = 0x8;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_80ABF07C_0 *)obj)->unk_08;
        part_a->unk_0A = saved_value;
        part_b = ((S_80ABF07C_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = saved_y;
        actor = work;
        part_b->unk_2C = D_80150C3C;
        part_b->unk_24 = saved_x;

        if (kind == 1) {
            flags_or_roll = work->unk_14 | 0x6000;
            state_flags = work->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        flags_or_roll = work->unk_14 | 0x2000;
        state_flags = work->unk_1C | 0x2000;
write_kind:
        work->unk_14 = flags_or_roll;
        work->unk_1C = state_flags;
        goto post_kind;

normal_kind:
        init_obj = obj;
        if (((spawn_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                init_part = part_a;
                ASM_KEEP(init_obj);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                flags_or_roll = func_800A6D30();
                init_obj = obj;
                if (!(flags_or_roll & 1)) {
                    goto initialize_parts;
                }
                work->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_80150C8C;
                goto post_kind;
            }
        }
        goto initialize_parts;

post_kind:
        init_obj = obj;
initialize_parts:
        func_800A9C18(init_obj, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8014CE7C;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
