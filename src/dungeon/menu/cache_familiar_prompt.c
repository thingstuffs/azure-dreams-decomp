#include "engine/sprite.h"
#include "engine/util.h"
#include "engine/texture.h"
#include "dungeon/menu_cache_familiar_prompt.h"
#include "dungeon/menu/state.h"
#include "slus.h"

static const u8 cached_action_draw_order[] __attribute__((aligned(4))) = {
    1, 0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 2, 19, 20, 21, 22, 23, 24, 26, 25, 27,
};
static const u8 cached_familiar_prompt_draw_order[] __attribute__((aligned(4))) = {
    1, 0, 21, 22, 23, 24, 26, 25, 27,
};

ItemMenuPart *link_cached_action_parts(ItemMenuPart **parts)
{
    return (ItemMenuPart *)build_reverse_indexed_chain((struct S_800491F4 **)parts, (u8 *)cached_action_draw_order, 27);
}

ItemMenuPart *link_familiar_prompt_parts(ItemMenuPart **parts)
{
    return (ItemMenuPart *)build_reverse_indexed_chain((struct S_800491F4 **)parts, (u8 *)cached_familiar_prompt_draw_order, 27);
}

/* Clear the five action labels before releasing the remaining part storage. */
void release_familiar_prompt_labels(ItemMenuPart **parts)
{
    s32 index;

    for (index = 9; index < 14; index++) {
        flag_optional_object_for_removal(parts[index]->handler);
    }
}

void release_familiar_prompt(CachedFamiliarPromptNode *node)
{
    if (node != 0) {
        u16 flags;
        s32 pending;
        CachedFamiliarPrompt *prompt = &node->prompt;

        release_familiar_prompt_labels(prompt->parts);
        release_null_terminated_entries(prompt->resources);
        flags = node->header.flags;
        pending = object_flag_block.flags;
        node->header.flags = flags | OBJECT_REMOVE_PENDING;
        object_flag_block.flags = pending | OBJECT_REMOVE_PENDING;
    }
}

void enable_familiar_prompt_input(CachedFamiliarPromptNode *node)
{
    node->prompt.input_enabled = 1;
}

void disable_familiar_prompt_input(CachedFamiliarPromptNode *node)
{
    node->prompt.input_enabled = 0;
}

void release_familiar_prompt_flow_children(CachedFamiliarPromptFlow *flow)
{
    release_familiar_prompt(flow->prompt);
    release_menu_entry_object(flow->actor_status);
    enqueue_script_message_command();
}

void start_familiar_prompt_close(CachedFamiliarPromptFlow *flow)
{
    if (flow != 0) {
        release_familiar_prompt_flow_children(flow);
        if (ensure_familiar_prompt_close(&flow->owner_link) == 0) {
            NODE_HEADER(flow)->update_callback = ensure_familiar_prompt_close;
        }
    }
}

void schedule_familiar_prompt_close(ObjectNodeHeader *node)
{
    set_dungeon_menu_flag_if_idle();
    node->update_callback = start_familiar_prompt_close;
}

/* Close the prompt and release its selection owner on the next update. */
void schedule_familiar_prompt_cleanup(ObjectNodeHeader *node)
{
    set_dungeon_menu_flag_if_idle();
    node->update_callback = finish_familiar_prompt_close;
}

ObjectNodeHeader *release_familiar_prompt_owner(ObjectNodeHeader *header)
{
    CachedFamiliarPromptFlowNode *node = (CachedFamiliarPromptFlowNode *)header;
    s32 pending;
    u16 flags;
    ObjectNodeHeader *owner;
    release_familiar_prompt_flow_children(&node->flow);
    flags = node->header.flags;
    pending = object_flag_block.flags;
    node->header.flags = flags | OBJECT_REMOVE_PENDING;
    owner = node->flow.owner_link.owner;
    object_flag_block.flags = pending | OBJECT_REMOVE_PENDING;
    return owner;
}

void finish_familiar_prompt_close(CachedFamiliarPromptFlow *flow)
{
    if (flow != 0) {
        release_familiar_prompt(flow->prompt);
        release_menu_entry_object(flow->actor_status);
        destroy_selection_menu_and_release_owner(flow->owner_link.owner);
        enqueue_script_message_command();
        NODE_HEADER(flow)->flags |= OBJECT_REMOVE_PENDING;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

MenuEntryObject *get_familiar_prompt_actor_status(ObjectNodeHeader *node)
{
    CachedFamiliarPromptFlow *flow = NODE_BODY(node);
    return flow->actor_status;
}

void enable_familiar_prompt_flow_input(ObjectNodeHeader *node)
{
    CachedFamiliarPromptFlow *flow = NODE_BODY(node);
    enable_familiar_prompt_input(flow->prompt);
}

void disable_familiar_prompt_flow_input(ObjectNodeHeader *node)
{
    CachedFamiliarPromptFlow *flow = NODE_BODY(node);
    disable_familiar_prompt_input(flow->prompt);
}

s32 find_familiar_prompt_actor(ActorRecord **actors, ActorRecord *actor, s32 count)
{
    s32 index;
    s32 selected = 0;

    for (index = 0; index < count; index++) {
        if (*actors == actor) {
            selected = index;
            break;
        }
        actors++;
    }
    return selected;
}

/* Allocate the draw-part pool and append the command buffer to its resources. */
s32 prepare_familiar_prompt(CachedFamiliarPrompt *prompt, s32 count)
{
    s32 ready = 0;
    u16 **resources = prompt->resources;

    prompt->parts = (ItemMenuPart **)rebuild_pointer_pool((s32 *)resources, count, 9);
    if (prompt->parts != 0) {
        prompt->packets = (void *)(unsigned long)(u32)append_allocated_node_body((s32 *)resources, 9);
        if (prompt->packets != 0) {
            prompt->part_common.unk0 = display_vector_defaults.unk0;
            prompt->part_common.unk4 = display_vector_defaults.unk4;
            prompt->part_common.unk8 = display_vector_defaults.unk8;
            set_menu_part_vectors(prompt->parts, &prompt->part_common, 27);
            ready = 1;
        }
    }
    return ready;
}

void configure_familiar_prompt_links(CachedFamiliarPrompt *prompt, ItemMenuDisplayLinks *links,
                                           StorageDisplayBlock *block, ItemMenuDisplayPosition *vector, CachedFamiliarPromptCoordinate x, CachedFamiliarPromptCoordinate y)
{
    s32 *words = display_block_defaults.words;
    DisplayPositionWords *defaults = &display_vector_defaults;
    s32 coordinate;

    block->words[0] = display_block_defaults.words[0];
    block->words[1] = words[1];
    block->words[2] = words[2];
    coordinate = display_vector_defaults.unk0;
    block->words[3] = words[3];
    vector->words.unk0 = coordinate;
    vector->words.unk4 = defaults->unk4;
    vector->words.unk8 = defaults->unk8;

    links->display = &block->display;
    links->position = vector;
    links->unk_00 = 0;
    links->display->x = x.coordinate;
    links->display->y = y.coordinate;
    links->display->depth = 512;
    links->display->mode = 4;
}

void setup_familiar_prompt(CachedFamiliarPrompt *prompt, ObjectNodeHeader *owner,
                                  ActorRecord *actor, s32 x, s32 y)
{
    CachedFamiliarPromptCoordinate horizontal, vertical;
    initialize_familiar_prompt_request(prompt, owner, actor);
    horizontal.coordinate = x;
    vertical.coordinate = y;
    configure_familiar_prompt_links(prompt, &prompt->links, &prompt->display,
                                           &prompt->position, horizontal, vertical);
    populate_familiar_prompt_parts(prompt, prompt->parts);
}
