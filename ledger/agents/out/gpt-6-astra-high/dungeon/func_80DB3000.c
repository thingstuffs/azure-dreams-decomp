/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80DB3000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80DB3000_0;   /* temp_v0 in BODY_NAME */

typedef struct S_80DB3000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80DB3000_1;   /* var_s0 in BODY_NAME */

typedef struct S_80DB3000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80DB3000_2;   /* temp_s4 in BODY_NAME */

typedef struct S_80DB3000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80DB3000_3;   /* temp_s2 in BODY_NAME */

typedef struct S_80DB3000_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80DB3000_4;   /* temp_s5 in BODY_NAME */


#ifdef __mips__
static const u32 bank_words[] __asm__("func_80DB3000")
    __attribute__((section(".text.func_80DB3000"), aligned(4))) = {
    0x8014C874, 0x8014CA3C, 0x8014D208, 0x8014D208,
    0x8014D208, 0x8014D234, 0x8014D1B4, 0x8014D1B4,
    0x8014D1B4, 0x8014D144, 0x8014D134, 0x8014D234,
    0x8014D234, 0x8014D1F8, 0x8014E98C, 0x8014E984,
    0x8014E97C, 0x8014E994, 0x8014E93C, 0x8014E934,
    0x8014E92C, 0x95824081, 0x85829382, 0x40818482,
    0x99828882, 0x8E829082, 0x93828F82, 0x93828982,
    0x00004481,
};
__asm__(".globl func_80DB3000\n"
        ".size func_80DB3000,572");
#define BODY_NAME func_80DB3074
#define BODY_ATTR __attribute__((used, section(".text.func_80DB3000")))
#else
#define BODY_NAME func_80DB3000
#define BODY_ATTR
#endif

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
void *func_8014C954(void) __attribute__((noreturn));
void *func_8014C9C0(void) __attribute__((noreturn));
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8014CA3C;
extern M2C_UNK D_8014CE68;
extern M2C_UNK D_8014F86C;

void *BODY_NAME(s16 spawn_flags, s8 grid_x, s8 grid_y, s16 property_value) BODY_ATTR;
/* Allocates and initializes a dungeon object with the supplied flags and placement. */
void *BODY_NAME(s16 spawn_flags, s8 grid_x, s8 grid_y, s16 property_value) {
    s32 global_byte;
    s32 unused_slot;
    s32 spawn_mode;
    S_80DB3000_3 *placement;
    S_80DB3000_2 *properties;
    void *object;
    S_80DB3000_4 *extended_state;
    S_80DB3000_1 *state = NULL;
    register s8 saved_x ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s8 saved_y ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s16 saved_property;
    void *call_object;
    void *call_properties;

    M2C_ERROR(/* Read from unset register $t0 */) | 0x4481;
    saved_x = grid_x;
    saved_property = property_value;
    saved_y = grid_y;
    global_byte = (s32) *(s8 *)-0x56D4;
    object = func_8003FD64(0x112, &D_80083498);
    if (object != NULL) {
        state = object + 0x20;
        ((S_80DB3000_0 *)object)->unk_10 = &D_8014CA3C;
        state->unk_13 = 0x1A;
        func_8004491C(object, &D_80045340);
        properties = ((S_80DB3000_0 *)object)->unk_08;
        properties->unk_0A = saved_property;
        placement = ((S_80DB3000_0 *)object)->unk_0C;
        spawn_mode = spawn_flags & 3;
        placement->unk_25 = saved_y;
        extended_state = state;
        placement->unk_2C = &D_8014F86C;
        placement->unk_24 = saved_x;
        if (spawn_mode == 1) {
            s32 flags_14;
            s32 flags_1c;

            flags_14 = state->unk_14 | 0x6000;
            flags_1c = state->unk_1C | 0x6000;
            ASM_KEEP(flags_14);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            ASM_TAILSLOT_PIN(flags_1c);   /* MATCH pin: load-bearing for the whole function shape */
            return func_8014C954();
        }
        if (spawn_mode >= 2) {
            state->unk_14 = (s32) (state->unk_14 | 0x2000);
            state->unk_1C = (s32) (state->unk_1C | 0x2000);
            func_8014C9C0();
        }
        call_object = object;
        if (((spawn_flags & ~3) << 0x10) == 0) {
            if (!(state->unk_14 & 0x200)) {
                call_properties = properties;
                if (func_800A6D30() & 1) {
                    state->unk_1C = (s32) (state->unk_1C | 0x200);
                    func_800A48F0(state, 1, (func_800A6D30() & 0x3F) | 0x20);
                }
            }
        }
        func_800A9C18(object, properties, placement, spawn_flags);
        extended_state->unk_9A = 0xFF;
        extended_state->unk_9C = -1;
        extended_state->unk_8C = &D_8014CE68;
        func_800AA36C(extended_state, properties, placement, state);
    }
    return state;
}
