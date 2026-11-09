#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
/* cfail-repair: true-name warm-start */
#include "common.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
#include "dungeon/effect/particle.h"
#include "slus.h"


typedef struct S_801690D8_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801690D8_6;   /* arg0_work in create_eight_part_textured_ribbon */

typedef struct {
    u8 bytes[32];
} Copy32;

extern u8 ribbon_sprite_entries[3];
extern Copy32 D_801648DC;
extern u8 ribbon_vertices[96];

typedef struct S_801690D8_8 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x48];
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
} S_801690D8_8;

/* Creates eight effect segments with positions, colors, and vertex data. */
void create_eight_part_textured_ribbon(ActorRecord *source, void *origin, SpriteFrameState *unused, ObjectPosition *effect_position) {
    s32 direction_pairs[8];
    s32 segment;
    s32 trunc_bias;
    s32 prev_segment;
    s32 prev_base_x;
    s32 prev_base_y;
    s32 base_x;
    s32 base_y;
    s32 prev_tip_x;
    s32 prev_tip_y;
    s32 tip_x;
    s32 tip_y;
    SpriteFrameState *render_flags;
    ObjectPosition *position;
    SpriteFrameState *appearance;
    EightPartTexturedRibbonBody *effect;
    ObjectNodeHeader *object;
    S_801690D8_6 *heading_source;
    s32 *directions;
    u16 *side_direction;
    u8 *vertex_table;
    ObjectPosition *origin_pos;

    origin_pos = origin;
    heading_source = source;
    *(Copy32 *)direction_pairs = D_801648DC;
    segment = 0;
    directions = direction_pairs;
    trunc_bias = 0xFFFF;
    vertex_table = ribbon_vertices;
    do {
        object = allocate_flagged_object_node(0x12);
        effect = NODE_BODY(object);
        if (object != 0) {
            effect->unk_18 = 0xEU;
            if ((segment == 0) || (segment == 7)) {
                effect->unk_18 = 8U;
            }
            if ((segment == 1) || (segment == 6)) {
                effect->unk_18 = (u16) ((u16)effect->unk_18 - 4);
            }
            if ((segment == 2) || (segment == 5)) {
                effect->unk_18 = (u16) ((u16)effect->unk_18 - 2);
            }
            effect->unk_1A =  source->action_timer;
            effect->unk_1C = segment;
            effect->unk_1E = 0;
            effect->unk_24 = effect_position;
            object->update_callback = &update_animated_textured_ribbon;
            register_node(object, project_sprite_chain);
            render_flags = object->sprite;
            render_flags->tpage_abr = 0x20;
            render_flags->flags = (u16) (render_flags->flags | 0x8C);
            position = object->position;
            position->x.v = (s32) origin_pos->x.v;
            position->y.v = (s32) origin_pos->y.v;
            position->z.v = (s32) (origin_pos->z.v + 0xFFC80000);
            effect->unk_8A = 0U;
            effect->unk_84 = 0U;
            effect->unk_7E = 0U;
            effect->unk_78 = 0U;
            effect->unk_88 = 0U;
            effect->unk_82 = 0U;
            effect->unk_86 = 0U;
            effect->unk_80 = 0U;
            effect->unk_74 = (u16) ((*(s16 *)((u8 *)directions + ((((u16) heading_source->unk_2A
                >> 7) & 0x1C)))) * 0xF);
            effect->unk_7A = (u16) ((*(s16 *)((u8 *)directions + ((((u16) heading_source->unk_2A
                >> 7) & 0x1C)))) * 0xF);
            effect->unk_76 = (u16) ((s16) *(u16 *)(((s8 *) directions + (((u16) heading_source->unk_2A >> 7) & 0x1C))
                + 2) * 0xF);
            effect->unk_7C = (u16) ((s16) *(u16 *)(((s8 *) directions + (((u16) heading_source->unk_2A >> 7) & 0x1C))
                + 2) * 0xF);
            prev_segment = segment - 1;
            effect->unk_5C = (*(s16 *)((u8 *)directions + (((((s32) (heading_source->unk_2A << 0x10) >> 0x19)
                + 6) & 7) << 2))) * 0x3333;
            side_direction = (u16 *)((s8 *)directions + (((((s32) (heading_source->unk_2A << 0x10) >> 0x19) + 6) & 7)
                << 2));
            effect->unk_60 = (s32) ((s16) side_direction[1] * 0x3333);
            prev_tip_x = effect->unk_5C * prev_segment;
            if (prev_tip_x < 0) {
                prev_tip_x += trunc_bias;
            }
            effect->unk_7A = (u16) (effect->unk_7A + (prev_tip_x >> 0x10));
            prev_base_x = effect->unk_5C * prev_segment;
            if (prev_base_x < 0) {
                prev_base_x += trunc_bias;
            }
            prev_tip_y = effect->unk_60 * prev_segment;
            effect->unk_86 = (u16) (effect->unk_86 + (prev_base_x >> 0x10));
            if (prev_tip_y < 0) {
                prev_tip_y += trunc_bias;
            }
            prev_base_y = effect->unk_60 * prev_segment;
            effect->unk_7C = (u16) (effect->unk_7C + (prev_tip_y >> 0x10));
            if (prev_base_y < 0) {
                prev_base_y += trunc_bias;
            }
            tip_x = effect->unk_5C * segment;
            effect->unk_88 = (u16) (effect->unk_88 + (prev_base_y >> 0x10));
            if (tip_x < 0) {
                tip_x += trunc_bias;
            }
            base_x = effect->unk_5C * segment;
            effect->unk_74 = (u16) (effect->unk_74 + (tip_x >> 0x10));
            if (base_x < 0) {
                base_x += trunc_bias;
            }
            tip_y = effect->unk_60 * segment;
            effect->unk_80 = (u16) (effect->unk_80 + (base_x >> 0x10));
            if (tip_y < 0) {
                tip_y += trunc_bias;
            }
            base_y = effect->unk_60 * segment;
            effect->unk_76 = (u16) (effect->unk_76 + (tip_y >> 0x10));
            if (base_y < 0) {
                base_y += trunc_bias;
            }
            effect->unk_82 = (u16) (effect->unk_82 + (base_y >> 0x10));
            appearance = object->sprite;
            appearance->scale_y = 0x1000;
            appearance->scale_x = 0x1000;
            appearance->color.c.g = 0x60U;
            effect->unk_00 = (
                appearance->color.c.r = 0xF0U,
                appearance->color.c.b = 0xFFU,
                appearance->color.c.r);
            effect->unk_01 = (u8) appearance->color.c.g;
            effect->unk_02 = (u8) appearance->color.c.b;
            select_record_entry_and_value(appearance, &ribbon_sprite_entries, 0);
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_00 = effect->unk_80;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_02 = (u16) effect->unk_82;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_04 = (u16) effect->unk_84;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_06 = (u16) effect->unk_86;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_08 = (u16) effect->unk_88;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_0A = (u16) effect->unk_8A;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_54 = (u16) effect->unk_74;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_56 = (u16) effect->unk_76;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_58 = (u16) effect->unk_78;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_5A = (u16) effect->unk_7A;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_5C = (u16) effect->unk_7C;
            ((S_801690D8_8 *)(((effect->unk_1C * 0x60) + vertex_table)))->unk_5E = (u16) effect->unk_7E;
        }
        segment += 1;
    } while (segment < 8);
}
