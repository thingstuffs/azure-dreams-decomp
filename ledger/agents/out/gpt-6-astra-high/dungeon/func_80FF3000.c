/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80FF3000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80FF3000_0;   /* temp_v0 in BODY_NAME */

typedef struct S_80FF3000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FF3000_1;   /* var_s0 in BODY_NAME */

typedef struct S_80FF3000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FF3000_2;   /* temp_s4 in BODY_NAME */

typedef struct S_80FF3000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80FF3000_3;   /* temp_s2 in BODY_NAME */

typedef struct S_80FF3000_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FF3000_4;   /* temp_s5 in BODY_NAME */


void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
extern void func_80158988(void) __attribute__((noreturn));
extern void func_80158A00(void) __attribute__((noreturn));
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80158A7C;
extern M2C_UNK D_80158EA8;
extern M2C_UNK D_8015C038;
extern M2C_UNK D_8015C088;

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80FF3000")
    __attribute__((section(".text.func_80FF3000"), aligned(4))) = {
    0x801588a8, 0x80158a7c, 0x801592b8, 0x801592b8,
    0x801592b8, 0x801592e4, 0x80159264, 0x80159264,
    0x80159264, 0x801591f4, 0x801591e4, 0x801592e4,
    0x801592e4, 0x801592a8, 0x8015aac4, 0x8015aabc,
    0x8015aab4, 0x8015aacc, 0x8015aa74, 0x8015aa6c,
    0x8015aa64, 0x89824081, 0x40819382, 0x93829082,
    0x83829982, 0x85828882, 0x7c818482, 0x90829582,
    0x00004481, 0x92824081, 0x96828582, 0x81828582,
    0x85828c82, 0x40818482, 0x94828982, 0x40819382,
    0x92829482, 0x85829582, 0x90824081, 0x97828f82,
    0x92828582, 0x65004481,
};
__asm__(".globl func_80FF3000\n"
        ".size func_80FF3000, 636");
#define BODY_NAME func_80FF30A8
#else
#define BODY_NAME func_80FF3000
#endif

void *BODY_NAME(s32, s8, s8, s16)
#ifdef __mips__
    __attribute__((section(".text.func_80FF3000")))
#endif
    ;

/* Allocates and initializes a dungeon object with flags and placement parameters. */
void *BODY_NAME(s32 init_flags, s8 pos_x, s8 pos_y, s16 init_value) {
    S_80FF3000_1 *object_state;
    void *object;
    register s16 saved_value ASM_REG("$18");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 saved_flags ASM_REG("$19");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    S_80FF3000_2 *base_data;
    register s8 saved_y ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s8 saved_x ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 setup_flags;
    s32 mode_or_flags;
    s32 config_value;
    S_80FF3000_3 *placement;
    S_80FF3000_4 *extended_state;

    saved_flags = init_flags;
    object_state = NULL;
    ASM_KEEP_NV(object_state);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_KEEP_NV(saved_flags);   /* MATCH pin: retail schedule: same instructions, different order without it */
    saved_x = pos_x;
    saved_value = init_value;
    saved_y = pos_y;
    object = func_8003FD64(0x112, &D_80083498);
    if (object != NULL) {
        setup_flags = saved_flags;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        object_state = object + 0x20;
        ((S_80FF3000_0 *)object)->unk_10 = &D_80158A7C;
        object_state->unk_13 = 0x28;
        func_8004491C(object, &D_80045340);
        config_value = (s32) &D_8015C038;
        base_data = ((S_80FF3000_0 *)object)->unk_08;
        base_data->unk_0A = saved_value;
        placement = ((S_80FF3000_0 *)object)->unk_0C;
        mode_or_flags = saved_flags & 3;
        placement->unk_25 = saved_y;
        extended_state = object_state;
        placement->unk_2C = (void *) config_value;
        placement->unk_24 = saved_x;
        if (mode_or_flags == 1) {
            config_value = object_state->unk_14;
            mode_or_flags = object_state->unk_1C;
            config_value |= 0x6000;
            mode_or_flags |= 0x6000;
            ASM_TAILSLOT_PIN(mode_or_flags);   /* MATCH pin: load-bearing for the whole function shape */
            ASM_KEEP(config_value);   /* MATCH pin: retail basic-block layout depends on it */
            func_80158988();
        }
        config_value = mode_or_flags < 2;
        if (!config_value) {
            config_value = object_state->unk_14;
            mode_or_flags = object_state->unk_1C;
            config_value |= 0x2000;
            mode_or_flags |= 0x2000;
            object_state->unk_14 = config_value;
            object_state->unk_1C = mode_or_flags;
            func_80158A00();
        }
        config_value = saved_flags & ~3;
        if ((config_value << 0x10) == 0) {
            if (!(object_state->unk_14 & 0x200)) {
                if (func_800A6D30() & 1) {
                    object_state->unk_1C = (s32) (object_state->unk_1C | 0x200);
                    func_800A48F0(object_state, 1, (func_800A6D30() & 0x3F) | 0x20);
                    placement->unk_2C = &D_8015C088;
                }
            }
        }
        func_800A9C18(object, base_data, placement, (s16)(s32) setup_flags);
        extended_state->unk_9A = 0xFF;
        extended_state->unk_9C = -1;
        extended_state->unk_8C = &D_80158EA8;
        func_800AA36C(extended_state, base_data, placement, object_state);
        return object_state;
    }
    return object_state;
}
