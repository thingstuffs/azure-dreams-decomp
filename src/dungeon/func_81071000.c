/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_FUNC_81071000_BODY_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_FUNC_81071000_BODY_0;   /* temp_v0 in FUNC_81071000_BODY */

typedef struct S_FUNC_81071000_BODY_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x78];
    u16 unk_98;
} S_FUNC_81071000_BODY_1;   /* var_s0 in FUNC_81071000_BODY */

typedef struct S_FUNC_81071000_BODY_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_FUNC_81071000_BODY_2;   /* temp_s4 in FUNC_81071000_BODY */

typedef struct S_FUNC_81071000_BODY_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_FUNC_81071000_BODY_3;   /* temp_s2 in FUNC_81071000_BODY */

typedef struct S_FUNC_81071000_BODY_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0xD];
    s16 unk_AA;
} S_FUNC_81071000_BODY_4;   /* temp_s5 in FUNC_81071000_BODY */

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
void func_80158A10(void) __attribute__((noreturn));
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80158AA4;
extern M2C_UNK D_80158F68;
extern M2C_UNK D_8015BFB8;
extern M2C_UNK D_8015C000;

#ifdef __mips__
static const u32 func_81071000_prefix_a[] __asm__("func_81071000")
    __attribute__((used, section(".text.func_81071000"), aligned(4))) = {
    0x80158898, 0x80158AA4, 0x80159394, 0x80159394,
    0x80159394, 0x801593C0, 0x80159340, 0x80159340,
    0x80159340, 0x801592EC, 0x80159324, 0x801593C0,
    0x801593C0, 0x80159384, 0x8015AAF0, 0x8015AAE8,
    0x8015AAE0, 0x8015AAF8, 0x8015AAA0, 0x8015AA98,
    0x8015AA90,
};
static const u32 func_81071000_prefix_b[]
    __attribute__((used, section(".text.func_81071000"), aligned(4))) = {
    0x97824081, 0x8E828582, 0x40819482, 0x85828282,
    0x93829282, 0x92828582, 0x44818B82, 0,
    0,
};
static const u32 func_81071000_prefix_c[]
    __attribute__((used, section(".text.func_81071000"), aligned(4))) = {
    0x8015BCBC, 0x8015BD60, 0x8015BDD8, 0x8015BE10,
    0x8015BCBC, 0x8015BD60, 0x8015BDD8, 0x8015BE70,
};
__asm__(".globl func_81071000\n"
        ".type func_81071000,@function\n"
        ".size func_81071000,676");
#define FUNC_81071000_BODY func_81071000_body
#define FUNC_81071000_ATTR __attribute__((used, section(".text.func_81071000")))
#else
#define FUNC_81071000_BODY func_81071000
#define FUNC_81071000_ATTR
#endif

/* Allocate a dungeon object and initialize its placement, flags, and behavior. */
FUNC_81071000_ATTR void *FUNC_81071000_BODY(s16 spawn_flags, s8 x, s8 y, s16 config_value) {
    S_FUNC_81071000_BODY_1 *object_state;
    s32 mode_or_roll;
    u16 state_flags;
    S_FUNC_81071000_BODY_3 *placement;
    S_FUNC_81071000_BODY_2 *config;
    S_FUNC_81071000_BODY_4 *behavior;
    void *object;
    register s8 saved_x ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 saved_config_value;
    register s8 saved_y ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *init_object;
    void *init_config;

    object_state = NULL;
    saved_x = x;
    saved_config_value = config_value;
    saved_y = y;
    object = func_8003FD64(0x112, &D_80083498);
    if (object == NULL) {
        goto done;
    }
    {
        object_state = object + 0x20;
        ((S_FUNC_81071000_BODY_0 *)object)->unk_10 = &D_80158AA4;
        object_state->unk_13 = 0x2B;
        func_8004491C(object, &D_80045340);
        config = ((S_FUNC_81071000_BODY_0 *)object)->unk_08;
        config->unk_0A = saved_config_value;
        placement = ((S_FUNC_81071000_BODY_0 *)object)->unk_0C;
        mode_or_roll = spawn_flags & 3;
        placement->unk_25 = saved_y;
        behavior = object_state;
        placement->unk_2C = &D_8015BFB8;
        placement->unk_24 = saved_x;
        if (mode_or_roll == 1) {
            state_flags = object_state->unk_98;
            object_state->unk_14 = (s32) (object_state->unk_14 | 0x6000);
            object_state->unk_98 = (u16) (state_flags | 0x4000);
            object_state->unk_1C = (s32) (object_state->unk_1C | 0x6000);
            func_80158A10();
        }
        if (mode_or_roll >= 2) {
            state_flags = object_state->unk_98;
            object_state->unk_14 = (s32) (object_state->unk_14 | 0x2000);
            object_state->unk_98 = (u16) (state_flags | 0x4000);
            object_state->unk_1C = (s32) (object_state->unk_1C | 0x2000);
            func_80158A10();
        }
        init_object = object;
        if (((spawn_flags & ~3) << 0x10) == 0) {
            if (!(object_state->unk_14 & 0x200)) {
                init_config = config;
                mode_or_roll = func_800A6D30();
                init_object = object;
                if (!(mode_or_roll & 1)) {
                    goto init_state;
                }
                object_state->unk_1C = (s32) (object_state->unk_1C | 0x200);
                func_800A48F0(object_state, 1, (func_800A6D30() & 0x3F) | 0x20);
                placement->unk_2C = &D_8015C000;
                goto select_init_object;
            }
        }
        goto init_state;
select_init_object:
        init_object = object;
init_state:
        func_800A9C18(init_object, config, placement, spawn_flags);
        behavior->unk_9A = 0xFF;
        behavior->unk_9C = -1;
        behavior->unk_8C = &D_80158F68;
        placement->unk_14 = (u16) (placement->unk_14 | 0xC);
        behavior->unk_AA = (s16) ((u16) object_state->unk_14 & 7);
        func_800AA36C(behavior, config, placement, object_state);
    }
done:
    return object_state;
}
