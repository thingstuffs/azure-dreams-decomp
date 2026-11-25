#include "dungeon/menu_cache_fusion.h"
#include "engine/graphics.h"
#include "engine/node/registration.h"
#include "shared/menu_display.h"

static const u8 cached_fusion_shade_phase[5][3] = {
    {0, 0, 0}, {0, 0, 1}, {0, 1, 2}, {1, 2, 0}, {2, 0, 0},
};

void shade_fusion_result(CachedFusionResult *result)
{
    s32 index;

    for (index = 0; index < 3; index++) {
        const u8 intensity = cached_fusion_shade_phase[result->phase][index];

        if (intensity == 1) {
            result->parts[index + 1].handler = card_selection_display_data;
            result->parts[index + 1].position->color.word = 0x00808080;
        } else if (intensity == 2) {
            result->parts[index + 1].handler = card_selection_display_data;
            result->parts[index + 1].position->color.word = 0x00404040;
        } else {
            result->parts[index + 1].handler = 0;
        }
    }
}

void update_fusion_result(CachedFusionResult *result)
{
    result->tick++;
    if (result->tick == 2) {
        result->tick = 0;
        result->phase = result->phase < 4 ? result->phase + 1 : 0;
        shade_fusion_result(result);
    }
}

void position_fusion_result(CachedFusionResult *result)
{
    result->parts[0].position->x = 4;
    result->parts[0].position->y = -44;
    result->parts[0].position->depth = 512;
    result->parts[3].position->x = 0;
    result->parts[2].position->x = 4;
    result->parts[1].position->x = 8;
}

/* The result constructor supplies four parts. Link them in draw order. */
s32 initialize_fusion_result_parts(CachedFusionResult *result, s32 count)
{
    ItemMenuPart *part = result->parts;
    s32 index;

    for (index = 0; index < count; index++) {
        StorageDisplayBlock *block = &result->blocks[index];
        s32 default_vector_x;

        block->words[0] = display_block_defaults.words[0];
        default_vector_x = display_vector_defaults.unk0;
        block->words[1] = display_block_defaults.words[1];
        block->words[2] = display_block_defaults.words[2];
        block->words[3] = display_block_defaults.words[3];
        part->position = (ItemMenuPartPosition *)block;
        result->vectors[index].unk0 = default_vector_x;
        result->vectors[index].unk4 = display_vector_defaults.unk4;
        result->vectors[index].unk8 = display_vector_defaults.unk8;
        part->vector = &result->vectors[index];
        part->next = part + 1;
        part++;
    }
    part[-1].next = 0;
    return 1;
}

ObjectNodeHeader *create_fusion_result(void)
{
    ObjectNodeHeader *node = allocate_flagged_object_node(0);

    if (node != 0) {
        CachedFusionResult *result = NODE_BODY(node);

        initialize_fusion_result_parts(result, 4);
        position_fusion_result(result);
        node->sprite = (SpriteFrameState *)result->parts;
        node->update_callback = update_fusion_result;
        register_node(node, draw_tinted_node_sprites_scratch);
    }
    return node;
}
