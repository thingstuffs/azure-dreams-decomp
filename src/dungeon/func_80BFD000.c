#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_80BFD000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 * unk_10;
} S_80BFD000_0;   /* temp_v0 in func_8015E878 */

typedef struct S_80BFD000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80BFD000_1;   /* var_s0 in func_8015E878 */

typedef struct S_80BFD000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80BFD000_2;   /* temp_s4 in func_8015E878 */

typedef struct S_80BFD000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80BFD000_3;   /* temp_s2 in func_8015E878 */

typedef struct S_80BFD000_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80BFD000_4;   /* actor in func_8015E878 */






extern u8 D_8015EA58[];
void *func_8003FD64();
s32 func_8004491C();
s16 func_800A48F0();
s32 func_800A6D30();
void func_800A9C18();
s32 func_800AA36C();
extern M2C_UNK D_8015F014;
extern M2C_UNK D_8016220C;
extern M2C_UNK D_8016225C;

/* Create a dungeon actor and initialize its placement, flags, and behavior. */
void *func_8015E878(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_value) {
    s32 unused_byte_neg_ba0;
    s32 unused_byte_21d8;
    s32 kind_or_bits;
    S_80BFD000_1 *actor_state = NULL;
    void *object;
    S_80BFD000_3 *placement;
    S_80BFD000_2 *attributes;
    S_80BFD000_4 *actor;
    s8 saved_x;
    s16 saved_value;
    s8 saved_y;
    s32 flags_14;
    s32 flags_1c;
    void *query_object;
    void *query_attributes;

    saved_x = tile_x;
    saved_value = spawn_value;
    saved_y = tile_y;
    unused_byte_21d8 = (s32) *(s8 *)0x21D8;
    unused_byte_neg_ba0 = (s32) *(s8 *)-0xBA0;
    object = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (object != NULL) {
        actor_state = object + 0x20;
        actor = actor_state;
        ((S_80BFD000_0 *)object)->unk_10 = D_8015EA58;
        actor_state->unk_13 = 0x10;
        func_8004491C(object, func_80045340);
        attributes = ((S_80BFD000_0 *)object)->unk_08;
        attributes->unk_0A = saved_value;
        placement = ((S_80BFD000_0 *)object)->unk_0C;
        kind_or_bits = spawn_flags & 3;
        placement->unk_25 = saved_y;
        placement->unk_2C = &D_8016220C;
        placement->unk_24 = saved_x;
        if (kind_or_bits == 1) {
            flags_14 = actor_state->unk_14 | 0x6000;
            flags_1c = actor_state->unk_1C | 0x6000;
            actor_state->unk_14 = flags_14;
            actor_state->unk_1C = flags_1c;
        } else if (kind_or_bits >= 2) {
            flags_14 = actor_state->unk_14 | 0x2000;
            flags_1c = actor_state->unk_1C | 0x2000;
            actor_state->unk_14 = flags_14;
            actor_state->unk_1C = flags_1c;
        } else {
            if (((spawn_flags & ~3) << 0x10) == 0) {
                query_object = object;
                if (!(actor_state->unk_14 & 0x200)) {
                    query_attributes = attributes;
                    kind_or_bits = func_800A6D30();
                    if (kind_or_bits & 1) {
                        func_800A48F0(actor_state, 1, (func_800A6D30() & 0x3F) | 0x20);
                        placement->unk_2C = &D_8016225C;
                    }
                }
            }
        }
        func_800A9C18(object, attributes, placement, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8015F014;
        actor_state->unk_1C = (s32) (actor_state->unk_1C | 0x40000);
        actor->unk_92 = -0x20;
        func_800AA36C(actor, attributes, placement, actor_state);
    }
    return actor_state;
}
