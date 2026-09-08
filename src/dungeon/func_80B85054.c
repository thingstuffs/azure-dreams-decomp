#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_80B85054_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80B85054_0;   /* obj in func_80B85054 */

typedef struct S_80B85054_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80B85054_1;   /* work in func_80B85054 */

typedef struct S_80B85054_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80B85054_2;   /* part_a in func_80B85054 */

typedef struct S_80B85054_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80B85054_3;   /* part_b in func_80B85054 */

typedef struct S_80B85054_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
} S_80B85054_4;   /* actor in func_80B85054 */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_80158A30[];
extern M2C_UNK D_80158E5C;
extern u8 D_8015BD0C[];
extern u8 D_8015BD4C[];

/* Allocates a dungeon object and initializes its flags, parts, and actor state. */
void *func_80B85054(s16 spawn_flags, s8 part_byte_24, s8 part_byte_25, s16 part_value)
{
    s32 kind;
    S_80B85054_1 *work = 0;
    void *obj;
    S_80B85054_2 *part_a;
    S_80B85054_3 *part_b;
    S_80B85054_4 *actor;
    s32 flags_or_roll;
    s32 secondary_flags;
    register s8 saved_byte_24 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 saved_part_value;
    register s8 saved_byte_25 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *object_arg;
    void *part_arg;

    saved_byte_24 = part_byte_24;
    saved_part_value = part_value;
    saved_byte_25 = part_byte_25;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80B85054_0 *)obj)->unk_10 = D_80158A30;
        work->unk_13 = 0xD;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_80B85054_0 *)obj)->unk_08;
        part_a->unk_0A = saved_part_value;
        part_b = ((S_80B85054_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = saved_byte_25;
        actor = work;
        part_b->unk_2C = D_8015BD0C;
        part_b->unk_24 = saved_byte_24;

        if (kind == 1) {
            flags_or_roll = work->unk_14 | 0x6000;
            secondary_flags = work->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        flags_or_roll = work->unk_14 | 0x2000;
        secondary_flags = work->unk_1C | 0x2000;
write_kind:
        work->unk_14 = flags_or_roll;
        work->unk_1C = secondary_flags;
        goto post_kind;

normal_kind:
        object_arg = obj;
        if (((spawn_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                part_arg = part_a;
                ASM_KEEP(object_arg);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                flags_or_roll = func_800A6D30();
                object_arg = obj;
                if (!(flags_or_roll & 1)) {
                    goto init_actor;
                }
                work->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_8015BD4C;
                goto post_kind;
            }
        }
        goto init_actor;

post_kind:
        object_arg = obj;
init_actor:
        func_800A9C18(object_arg, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80158E5C;
        actor->unk_A4 = -1;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
