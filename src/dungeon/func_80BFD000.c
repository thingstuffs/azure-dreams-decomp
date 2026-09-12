#include "common.h"
#include "m2c_compat.h"

typedef struct S_80BFD000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 * unk_10;
} S_80BFD000_0;   /* temp_v0 in BODY_NAME */

typedef struct S_80BFD000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80BFD000_1;   /* var_s0 in BODY_NAME */

typedef struct S_80BFD000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80BFD000_2;   /* temp_s4 in BODY_NAME */

typedef struct S_80BFD000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80BFD000_3;   /* temp_s2 in BODY_NAME */

typedef struct S_80BFD000_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80BFD000_4;   /* actor in BODY_NAME */


static const u32 func_8015E800_bank[] __asm__("func_8015E800")
    __attribute__((section(".text.func_8015E800"), aligned(4), used)) = {
    0x8015e878, 0x00000000, 0x8015f470, 0x8015f470,
    0x8015f470, 0x8015f49c, 0x8015f41c, 0x8015f41c,
    0x8015f41c, 0x8015f3e4, 0x8015f3e4, 0x8015f49c,
    0x8015f49c, 0x8015f460, 0x801606c0, 0x801606b8,
    0x801606b0, 0x801606c8, 0x80160670, 0x80160668,
    0x80160660, 0x00000000, 0x80161d4c, 0x80161d60,
    0x80161da4, 0x80161e84, 0x80161f58, 0x801620bc,
    0x80162158, 0x801621d8,
};

__asm__(".globl func_8015E800\n.size func_8015E800, 600");

#ifdef __mips__
#define BODY_NAME func_8015E878
#else
#define BODY_NAME func_8015E800
#endif

extern u8 D_80083498[];
extern u8 D_8015EA58[];
extern u8 D_80045340[];
void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
extern M2C_UNK D_8015F014;
extern M2C_UNK D_8016220C;
extern M2C_UNK D_8016225C;

/* Create a dungeon actor and initialize its placement, flags, and behavior. */
__attribute__((section(".text.func_8015E800")))
void *BODY_NAME(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_value) {
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
    register void *query_object ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    void *query_attributes;

    saved_x = tile_x;
    saved_value = spawn_value;
    saved_y = tile_y;
    unused_byte_21d8 = (s32) *(s8 *)0x21D8;
    unused_byte_neg_ba0 = (s32) *(s8 *)-0xBA0;
    object = func_8003FD64(0x112, D_80083498);
    if (object != NULL) {
        actor_state = object + 0x20;
        actor = actor_state;
        ((S_80BFD000_0 *)object)->unk_10 = D_8015EA58;
        actor_state->unk_13 = 0x10;
        func_8004491C(object, D_80045340);
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
            goto write_kind;
        }
        if (kind_or_bits < 2) {
            goto normal_path;
        }
        flags_14 = actor_state->unk_14 | 0x2000;
        flags_1c = actor_state->unk_1C | 0x2000;
write_kind:
        actor_state->unk_14 = flags_14;
        actor_state->unk_1C = flags_1c;
        goto common_path;
normal_path:
        if (((spawn_flags & ~3) << 0x10) == 0) {
            query_object = object;
            if (!(actor_state->unk_14 & 0x200)) {
                query_attributes = attributes;
                kind_or_bits = func_800A6D30(query_object);
                if (kind_or_bits & 1) {
                    func_800A48F0(actor_state, 1, (func_800A6D30(query_object) & 0x3F) | 0x20);
                    placement->unk_2C = &D_8016225C;
                }
            }
        }
common_path:
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
