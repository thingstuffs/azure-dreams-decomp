#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad24[0x24];
    u8 x;
    u8 y;
    s8 kind;
} Entity;

s32 func_8009FB34();
extern u8 D_800E3548[];
extern u8 D_800E36C8[];

typedef struct S_800A6E8C_0 {
    u8 unk_00;
    u8 unk_01;
} S_800A6E8C_0;   /* var_s2 in func_800A6E8C */

typedef struct S_800A6E8C_1 {
    u8 unk_00;
    u8 unk_01;
} S_800A6E8C_1;   /* var_s3 in func_800A6E8C */

/* Finds the nearest matching entry in the entity's region and writes its coordinates. */
u32 func_800A6E8C(Entity *entity, s32 filter, s16 *out_x, s16 *out_y) {
    s32 match_id;
    s32 best_index;
    s32 index;
    s32 y_is_larger;
    register s32 filter_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 match_type ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 filter_or_addr ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 delta_x;
    s32 delta_y;
    s32 scaled_right;
    s32 scaled_left;
    register s32 distance_y ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 distance_x;
    register s32 distance ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 best_distance ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 entry_x;
    u8 entry_y;
    u8 *base;
    u8 *entry_filter;
    u8 *entry_position;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (entity->kind < 0) {
        return 0;
    }
    best_distance = 0x100;
    best_index = -1;
    index = 0x3F;
    filter_or_addr = filter & 0xFF;
    ASM_KEEP(filter_or_addr);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    match_id = filter_or_addr;
    filter_value = filter << 0x10;
    match_type = filter_value >> 0x18;
    base = D_800E36C8;
    entry_position = base + 0x2F4;
    base = D_800E3548;
    entry_filter = base + 0xFC;
    do {
        filter_value = ((S_800A6E8C_0 *)entry_filter)->unk_01;
        filter_or_addr = match_id;
        ASM_KEEP(filter_or_addr);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        if ((filter_value == filter_or_addr) && ((match_type == 0) || (((S_800A6E8C_0 *)entry_filter)->unk_00 == match_type))) {
            entry_x = ((S_800A6E8C_1 *)entry_position)->unk_00;
            entry_y = ((S_800A6E8C_1 *)entry_position)->unk_01;
            if ((s16)func_8009FB34(entry_x, entry_y) == entity->kind) {
                delta_x = entry_x - entity->x;
                distance_x = delta_x;
                if (delta_x < 0) {
                    distance_x = 0 - distance_x;
                }
                scaled_left = distance_x << 0x10;
                delta_y = entry_y - entity->y;
                distance_y = delta_y;
                if (delta_y < 0) {
                    distance_y = 0 - distance_y;
                }
                scaled_right = distance_y << 0x10;
                y_is_larger = scaled_left < scaled_right;
                distance = distance_x;
                if (y_is_larger != 0) {
                    distance = distance_y;
                }
                scaled_left = best_distance << 0x10;
                scaled_right = distance << 0x10;
                if (scaled_right < scaled_left) {
                    best_distance = distance_x;
                    if (y_is_larger != 0) {
                        best_distance = distance_y;
                    }
                    filter_or_addr = (s32)out_x;
                    ASM_KEEP(filter_or_addr);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    *(s16 *)filter_or_addr = (s16) entry_x;
                    filter_or_addr = (s32)out_y;
                    ASM_KEEP(filter_or_addr);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    best_index = index;
                    *(s16 *)filter_or_addr = (s16) entry_y;
                }
            }
        }
        entry_position -= 0xC;
        index -= 1;
        entry_filter -= 4;
    } while (index >= 0);
    return (u32) ~((s16)best_index) >> 0x1F;
}
