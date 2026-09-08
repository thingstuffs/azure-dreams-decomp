/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80DA1000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80DA1000_0;   /* temp_v0 in BODY_NAME */

typedef struct S_80DA1000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80DA1000_1;   /* var_s0 in BODY_NAME */

typedef struct S_80DA1000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80DA1000_2;   /* temp_s4 in BODY_NAME */

typedef struct S_80DA1000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80DA1000_3;   /* temp_s2 in BODY_NAME */

typedef struct S_80DA1000_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80DA1000_4;   /* temp_s5 in BODY_NAME */


#ifdef __mips__
static const u32 bank_words[] __asm__("func_80DA1000")
    __attribute__((section(".text.func_80DA1000"), aligned(4))) = {
    0x8015E874, 0x8015EA3C, 0x8015F208, 0x8015F208,
    0x8015F208, 0x8015F234, 0x8015F1B4, 0x8015F1B4,
    0x8015F1B4, 0x8015F144, 0x8015F134, 0x8015F234,
    0x8015F234, 0x8015F1F8, 0x8016098C, 0x80160984,
    0x8016097C, 0x80160994, 0x8016093C, 0x80160934,
    0x8016092C, 0x95824081, 0x85829382, 0x40818482,
    0x99828882, 0x8E829082, 0x93828F82, 0x93828982,
    0x2E004481,
};
__asm__(".globl func_80DA1000\n"
        ".size func_80DA1000,572");
#define BODY_NAME func_80DA1074
#define BODY_ATTR __attribute__((used, section(".text.func_80DA1000")))
#else
#define BODY_NAME func_80DA1000
#define BODY_ATTR
#endif

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
void *func_8015E954(void) __attribute__((noreturn));
void *func_8015E9C0(void) __attribute__((noreturn));
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8015EA3C;
extern M2C_UNK D_8015EE68;
extern M2C_UNK D_8016186C;

void *BODY_NAME(s16 spawn_flags, s8 grid_x, s8 grid_y, s16 type_id) BODY_ATTR;
/* Allocates an entity and initializes its type, placement, flags, and callbacks. */
void *BODY_NAME(s16 spawn_flags, s8 grid_x, s8 grid_y, s16 type_id) {
    s32 global_byte;
    s32 unused_slot;
    s32 spawn_mode;
    S_80DA1000_3 *placement;
    S_80DA1000_2 *type_data;
    void *object;
    S_80DA1000_4 *entity_data;
    S_80DA1000_1 *entity = NULL;
    register s8 saved_x ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s8 saved_y ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 saved_type;
    void *object_arg;
    void *type_arg;

    M2C_ERROR(/* Read from unset register $t0 */) | 0x4481;
    saved_x = grid_x;
    saved_type = type_id;
    saved_y = grid_y;
    global_byte = (s32) *(s8 *)-0x56D4;
    object = func_8003FD64(0x112, &D_80083498);
    if (object != NULL) {
        entity = object + 0x20;
        ((S_80DA1000_0 *)object)->unk_10 = &D_8015EA3C;
        entity->unk_13 = 0x1A;
        func_8004491C(object, &D_80045340);
        type_data = ((S_80DA1000_0 *)object)->unk_08;
        type_data->unk_0A = saved_type;
        placement = ((S_80DA1000_0 *)object)->unk_0C;
        spawn_mode = spawn_flags & 3;
        placement->unk_25 = saved_y;
        entity_data = entity;
        placement->unk_2C = &D_8016186C;
        placement->unk_24 = saved_x;
        if (spawn_mode == 1) {
            s32 flags_14;
            s32 flags_1c;

            flags_14 = entity->unk_14 | 0x6000;
            flags_1c = entity->unk_1C | 0x6000;
            ASM_KEEP(flags_14);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ASM_TAILSLOT_PIN(flags_1c);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            return func_8015E954();
        }
        if (spawn_mode >= 2) {
            entity->unk_14 = (s32) (entity->unk_14 | 0x2000);
            entity->unk_1C = (s32) (entity->unk_1C | 0x2000);
            func_8015E9C0();
        }
        object_arg = object;
        if (((spawn_flags & ~3) << 0x10) == 0) {
            if (!(entity->unk_14 & 0x200)) {
                type_arg = type_data;
                if (func_800A6D30() & 1) {
                    entity->unk_1C = (s32) (entity->unk_1C | 0x200);
                    func_800A48F0(entity, 1, (func_800A6D30() & 0x3F) | 0x20);
                }
            }
        }
        func_800A9C18(object, type_data, placement, spawn_flags);
        entity_data->unk_9A = 0xFF;
        entity_data->unk_9C = -1;
        entity_data->unk_8C = &D_8015EE68;
        func_800AA36C(entity_data, type_data, placement, entity);
    }
    return entity;
}
