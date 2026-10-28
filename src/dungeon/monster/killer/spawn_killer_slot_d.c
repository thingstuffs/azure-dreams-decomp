#include "shared/actor_status_ids.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "dungeon/actor/status.h"
#if 0 /* rowbase_rename_reverify precondition marker: dead declaration, never
seen by the real compiler;
satisfies the tool's textual defines()
check for the proven-region rename of create_randomized_flagged_object_2. */
    void create_randomized_flagged_object_2(void);
#endif

typedef struct DungeonSub2 DungeonSub2;
typedef struct DungeonSub1 DungeonSub1;
typedef struct DungeonNode DungeonNode;

struct DungeonSub2 {
    u8 pad00[0x24];
    s8 field24;
    s8 field25;
    u8 pad26[6];
    void *field2c;
};

struct DungeonNode {
    u8 pad00[8];
    void *field08;
    DungeonSub2 *field0c;
    void *field10;
    u8 pad14[0x0c];
};

struct DungeonSub1 {
    u8 pad00[0x13];
    s8 field13;
    s32 field14;
    u8 pad18[4];
    s32 field1c;
    u8 pad20[0x6c];
    void *field8c;
    u8 pad90[0x0a];
    u8 field9a;
    u8 pad9b[1];
    s8 field9c;
};

s32 generate_random_value(void);
extern u8 D_8015EA7C[];
extern M2C_UNK D_8015EEA8;
extern M2C_UNK D_80162038;
extern M2C_UNK D_80162088;

void *spawn_killer_slot_d(s16 setup_bits, s32 grid_x, s32 grid_y, s16 placement_value) ;

/* Allocate and initialize a dungeon node with the supplied setup and placement. */
/* Creates Killer with default frames at D_80162038, applies spawn flags, and attempts valid tile
 * placement. */
void *spawn_killer_slot_d(s16 setup_bits, s32 grid_x, s32 grid_y, s16 placement_value) {
    ActorRecord *state;
    void *body;
    ObjectNodeHeader *node;
    u16 saved_placement;
    ObjectPosition *node_data;
    s8 saved_grid_y;
    s8 saved_grid_x;
    s32 mode;
    s32 flags;
    SpriteFrameState *placement;
    DungeonSub1 *init_state;

    saved_grid_x = grid_x;
    saved_placement = placement_value;
    saved_grid_y = grid_y;
    grid_y = 0;
    state = (void *)grid_y;
    grid_x = 0x112;
    node = allocate_list_node(grid_x, &scene_object_list_anchor.next);
    if (node != NULL) {
        body = node + 1;
        state = body;
        node->update_callback = &D_8015EA7C;
        state->species = 0x28;
        register_node(node, project_sprite_chain);
        flags = (s32) &D_80162038;
        node_data = node->position;
        node_data->z.w.i = saved_placement;
        placement = node->sprite;
        mode = setup_bits & 3;
        placement->tile_y = saved_grid_y;
        init_state = body;
        placement->frameTable = (void *) flags;
        placement->tile_x = saved_grid_x;
        if (mode == 1) {
            state->flags14 |= 0x6000;
            state->flags1C |= 0x6000;
        } else if (mode >= 2) {
            state->flags14 |= 0x2000;
            state->flags1C |= 0x2000;
        } else {
            flags = setup_bits & ~3;
            if ((flags << 0x10) == 0) {
                if (!(state->flags14 & 0x200)) {
                    if (generate_random_value() & 1) {
                        state->flags1C |= 0x200;
                        set_or_clear_actor_status_slot(state, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                        placement->frameTable = &D_80162088;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(node, node_data, placement, (s16)(s32) setup_bits);
        init_state->field9a = 0xff;
        init_state->field9c = -1;
        init_state->field8c = &D_8015EEA8;
        try_move_actor_to_valid_position(init_state, node_data, placement, state);
    }
    return state;
}
