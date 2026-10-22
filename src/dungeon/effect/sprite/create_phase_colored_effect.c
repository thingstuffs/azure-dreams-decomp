#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"

typedef struct S_818BD52C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818BD52C_0;   /* node in create_phase_colored_effect */

typedef struct S_818BD52C_1 {
    s32 unk_00;
    u8 pad_04[0x14];
    void * unk_18;
} S_818BD52C_1;   /* arg0 in create_phase_colored_effect */

typedef struct S_818BD52C_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
} S_818BD52C_2;   /* base in create_phase_colored_effect */

typedef struct S_818BD52C_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BD52C_4;   /* coords in create_phase_colored_effect */

typedef struct S_818BD52C_5 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818BD52C_5;   /* ((S_818BD52C_1 *)arg0)->unk_18 in create_phase_colored_effect */

#define NORETURN

typedef struct {
    s32 word[6];
} Copy24;

extern void select_record_entry_and_value();
extern s32 rand();
extern void register_node();

extern u8 D_80024BB0[];
extern u8 D_800DEC70[];

/* Creates an effect node with phase-based color, random rotation, and offset coordinates. */
void *create_phase_colored_effect(S_818BD52C_1 *owner, void *source_coords, s32 phase_index, s32 effect_param)
{
    s32 scaled_color;
    s32 color_level;
    s32 phase_half;
    s32 random_angle;
    s32 phase;
    s16 phase_bit;
    s16 phase_half_s16;
    SpriteFrameState *part;
    S_818BD52C_2 *base;
    S_818BD52C_4 *coords;
    ObjectNodeHeader *node;
    s32 end_z;

    node = allocate_flagged_object_node(0x212);
    if (node != 0) {
        node->unk_10 = D_80024BB0;
        base = (u8 *)node + 0x20;
        ((S_818BD52C_0 *)node)->unk_20 = owner->unk_00;
        base->unk_04 = 0;
        base->unk_06 = 0x10;

        scaled_color = entity_height_offsets[((S_818BD52C_5 *)(owner->unk_18))->unk_13] * 3;
        if (scaled_color < 0) {
            scaled_color += 3;
        }
        phase = (s16)(phase_index + 1);
        color_level = scaled_color >> 2;
        base->unk_0A = color_level;
        base->unk_08 = color_level;
        base->unk_0C = effect_param;

        part = node->sprite;
        part->color.c.r = (phase / 4) * 0x80;
        phase_half = phase / 2;
        phase_half_s16 = phase_half;
        phase_bit = phase_half_s16 % 2;
        part->color.c.g = phase_bit * 0x80;
        phase_bit = phase - (phase_half * 2);
        part->color.c.b = phase_bit * 0x80;
        part->clut = 0x7DCF;
        part->flags |= 0xC;
        part->tpage_abr |= 0x20;
        part->flags |= 0x100;
        select_record_entry_and_value(part, D_800DEC70, 0);

        random_angle = rand();
        part->angle_z = random_angle % 0x1000;
        part->scale_y = 0xC00;
        part->scale_x = 0xC00;
        register_node(node, project_sprite_chain);

        coords = node->position;
        *(Copy24 *)coords = *(Copy24 *)source_coords;
        coords->unk_0C = coords->unk_00;
        coords->unk_10 = coords->unk_04;
        coords->unk_14 = coords->unk_08;
        end_z = coords->unk_14 + ((u32)base->unk_0A << 16);
        coords->unk_14 = end_z;
        return node;
    }
    return node;
}
