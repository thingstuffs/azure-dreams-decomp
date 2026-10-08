#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80FDB000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FDB000_0;   /* created in func_801708A8 */

typedef struct S_80FDB000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_80FDB000_1;   /* result in func_801708A8 */

typedef struct S_80FDB000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FDB000_2;   /* position in func_801708A8 */

typedef struct S_80FDB000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80FDB000_3;   /* part_b in func_801708A8 */

typedef struct S_80FDB000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FDB000_4;   /* actor in func_801708A8 */


extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800A48F0();
extern s32 func_800A6D30();
extern void func_800A9C18();
extern void func_800AA36C();

extern u8 D_80170A7C[];
extern u8 D_80170EA8[];
extern u8 D_80174038[];
extern u8 D_80174088[];
extern void *func_801708A8(s16, s32, s32, s32);
extern u8 D_801712B8[];
extern u8 D_801712E4[];
extern u8 D_80171264[];
extern u8 D_801711F4[];
extern u8 D_801711E4[];
extern u8 D_801712A8[];
extern u8 D_80172AC4[];
extern u8 D_80172ABC[];
extern u8 D_80172AB4[];
extern u8 D_80172ACC[];
extern u8 D_80172A74[];
extern u8 D_80172A6C[];
extern u8 D_80172A64[];

void *func_801708A8(s16 flags, s32 kind_id, s32 variant, s32 spawn_value)
;

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
void *func_801708A8(s16 flags, s32 kind_id, s32 variant, s32 spawn_value)
{
    void *result = 0;
    void *created;
    void *position;
    S_80FDB000_3 *part_b;
    S_80FDB000_4 *actor;
    s32 left;
    s32 right;
    s16 saved_kind_id;
    s32 saved_spawn;
    s16 saved_variant;
    s16 original_flags;
    void *call_a0;
    void *call_a1;
    s32 kind;

    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    created = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    original_flags = flags;
    if (created != 0) {
        result = (u8 *)created + 0x20;
        ((S_80FDB000_0 *)created)->unk_10 = D_80170A7C;
        ((S_80FDB000_1 *)result)->unk_13 = 0x28;
        func_8004491C(created, func_80045340);

        position = ((S_80FDB000_0 *)created)->unk_08;
        ((S_80FDB000_2 *)position)->unk_0A = saved_spawn;
        part_b = ((S_80FDB000_0 *)created)->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = saved_variant;
        actor = result;
        part_b->unk_2C = D_80174038;
        part_b->unk_24 = saved_kind_id;

        if (kind == 1) {
            ((S_80FDB000_1 *)result)->unk_14 |= 0x6000;
            ((S_80FDB000_1 *)result)->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            ((S_80FDB000_1 *)result)->unk_14 |= 0x2000;
            ((S_80FDB000_1 *)result)->unk_1C |= 0x2000;
        } else {
            call_a0 = created;
            if (((flags & ~3) << 16) == 0) {
                if (!(((S_80FDB000_1 *)result)->unk_14 & 0x200)) {
                    call_a1 = position;
                    if (func_800A6D30() & 1) {
                        ((S_80FDB000_1 *)result)->unk_1C |= 0x200;
                        func_800A48F0(result, 1,
                            (func_800A6D30() & 0x3F) | 0x20);
                        part_b->unk_2C = D_80174088;
                    }
                }
            }
        }

        func_800A9C18(created, position, part_b,
            (s16)original_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = D_80170EA8;
        func_800AA36C(actor, position,
            part_b, result);
    }

    return result;
}
