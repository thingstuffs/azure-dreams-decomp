#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_80B73054_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80B73054_0;   /* obj in func_80B73054 */

typedef struct S_80B73054_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80B73054_1;   /* work in func_80B73054 */

typedef struct S_80B73054_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80B73054_2;   /* part_a in func_80B73054 */

typedef struct S_80B73054_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80B73054_3;   /* part_b in func_80B73054 */

typedef struct S_80B73054_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
} S_80B73054_4;   /* actor in func_80B73054 */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8016AA30[];
extern M2C_UNK D_8016AE5C;
extern u8 D_8016DD0C[];
extern u8 D_8016DD4C[];

/* Creates a dungeon actor and initializes its parts and state from the spawn flags. */
void *func_80B73054(s16 spawn_flags, s8 tile_x, s8 tile_y, s16 part_value)
{
    s32 kind;
    void *obj;
    S_80B73054_2 *part_a;
    S_80B73054_3 *part_b;
    S_80B73054_1 *work;
    S_80B73054_4 *actor;
    s32 state_bits;
    s32 next_state_bits;
    register s8 saved_x ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 saved_value;
    register s8 saved_y ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *init_obj;
    void *saved_part;

    work = 0;
    saved_x = tile_x;
    saved_value = part_value;
    saved_y = tile_y;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80B73054_0 *)obj)->unk_10 = D_8016AA30;
        work->unk_13 = 0xD;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_80B73054_0 *)obj)->unk_08;
        part_a->unk_0A = saved_value;
        part_b = ((S_80B73054_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = saved_y;
        actor = work;
        part_b->unk_2C = D_8016DD0C;
        part_b->unk_24 = saved_x;

        if (kind == 1) {
            state_bits = work->unk_14 | 0x6000;
            next_state_bits = work->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        state_bits = work->unk_14 | 0x2000;
        next_state_bits = work->unk_1C | 0x2000;
write_kind:
        work->unk_14 = state_bits;
        work->unk_1C = next_state_bits;
        goto post_kind;

normal_kind:
        init_obj = obj;
        if (((spawn_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                saved_part = part_a;
                ASM_KEEP(init_obj);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                state_bits = func_800A6D30();
                init_obj = obj;
                if (!(state_bits & 1)) {
                    goto init_parts;
                }
                work->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_8016DD4C;
                goto post_kind;
            }
        }
        goto init_parts;

post_kind:
        init_obj = obj;
init_parts:
        func_800A9C18(init_obj, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8016AE5C;
        actor->unk_A4 = -1;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
