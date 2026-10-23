#include "common.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad_00[0x12];
    s16 state;
    u8 pad_14[4];
    s16 timer;
    u8 pad_1A[2];
    s16 phase;
} Entity;

typedef struct {
    u8 pad_00[2];
    s16 x;
    u8 pad_04[2];
    s16 y;
    u8 pad_08[2];
    u16 z;
} Actor;

typedef struct {
    s16 values[8];
} __attribute__((packed)) PhaseHeights;

extern PhaseHeights D_80164A54;
extern u8 *beldo_actor_nodes;
extern u16 dungeon_camera_targets[4];
extern s16 beldo_camera_rotation[4];
extern s16 beldo_camera_position[4];

extern void set_camera_targets(void *, void *, s32);
extern void queue_view_slot(s32);
extern s16 get_player_relative_point_octant(void *);

/*
 * Moves the encounter camera between Beldo and the player, selecting view angles by relative
 * octant and timed phases.
 */
void update_encounter_camera_focus(Entity *entity) {
    PhaseHeights heights = D_80164A54;
    Actor *actor = *(Actor * *)&((ObjectNodeHeader *)beldo_actor_nodes)->position;
    s16 phase_slot;
    s16 height_slot;
    s32 state = entity->state;
    void *focus_arg;
    void *offset_arg;
    s32 transition_ticks;
    u16 previous_state;

    switch (state) {
    case 0:
    {
        GameWork *globals;

        entity->timer = 0;
        entity->phase = 2;
        entity->state++;
        beldo_camera_rotation[0] = dungeon_camera_targets[0];
        beldo_camera_rotation[1] = dungeon_camera_targets[1];
        beldo_camera_rotation[2] = dungeon_camera_targets[2] - 0x600;
        beldo_camera_position[0] = actor->x;
        beldo_camera_position[1] = actor->y - 0x100;
        beldo_camera_position[2] = actor->z;
        globals = &g_game_work;
        globals->view.slot[2].callback = 0;
        globals->view.slot[0].callback = 0;
        queue_view_slot(1);
        queue_view_slot(0);
        set_camera_targets(beldo_camera_position, beldo_camera_rotation, 0xA);
        return;
    }

    case 1:
        entity->timer++;
        if (entity->timer < 0x28) {
            return;
        } else {
            focus_arg = beldo_camera_position;
            offset_arg = beldo_camera_rotation;
            previous_state = entity->state;
            transition_ticks = 0x14;
            entity->timer = 0;
            entity->state = previous_state + 1;
            set_camera_targets(focus_arg, offset_arg, transition_ticks);
            return;
        }

    case 2:
        entity->timer++;
        if (entity->timer < 0x28) {
            return;
        }
        focus_arg = 0;
        offset_arg = dungeon_camera_targets;
        previous_state = entity->state;
        transition_ticks = 0xA;

        entity->timer = 0;
        entity->state = previous_state + 1;
        set_camera_targets(focus_arg, offset_arg, transition_ticks);
        return;

    case 4:
    {
        s32 y_sum;
        GameWork *globals;

        entity->timer = 0;
        entity->state++;
        phase_slot = get_player_relative_point_octant(actor);
        height_slot = phase_slot + 3;
        beldo_camera_rotation[0] = dungeon_camera_targets[0];
        beldo_camera_rotation[1] = dungeon_camera_targets[1];
        if (height_slot >= 8) {
            height_slot = phase_slot - 5;
        }
        beldo_camera_rotation[2] = heights.values[height_slot] * 0x200;
        beldo_camera_position[0] = ((s32)(actor->x + view_reference_entity.x.w.i)) / 2;
        y_sum = actor->y + view_reference_entity.y.w.i;
        beldo_camera_position[1] = y_sum / 2;
        beldo_camera_position[2] = actor->z;
        globals = &g_game_work;
        globals->view.slot[2].callback = 0;
        globals->view.slot[0].callback = 0;
        queue_view_slot(1);
        queue_view_slot(0);
        set_camera_targets(beldo_camera_position, beldo_camera_rotation, 0xA);
        return;
    }

    case 6:
    {
        s32 y_sum;
        GameWork *globals;

        entity->timer = 0;
        entity->state++;
        phase_slot = get_player_relative_point_octant(actor);
        height_slot = phase_slot + 2;
        beldo_camera_rotation[0] = dungeon_camera_targets[0];
        beldo_camera_rotation[1] = dungeon_camera_targets[1];
        if (height_slot >= 8) {
            height_slot = phase_slot - 6;
        }
        beldo_camera_rotation[2] = heights.values[height_slot] * 0x200;
        beldo_camera_position[0] = ((s32)(actor->x + view_reference_entity.x.w.i)) / 2;
        y_sum = actor->y + view_reference_entity.y.w.i;
        beldo_camera_position[1] = y_sum / 2;
        beldo_camera_position[2] = actor->z;
        globals = &g_game_work;
        globals->view.slot[2].callback = 0;
        globals->view.slot[0].callback = 0;
        queue_view_slot(1);
        queue_view_slot(0);
        set_camera_targets(beldo_camera_position, beldo_camera_rotation, 2);
        break;
    }

    case 20:
    {
        s32 y_sum;
        GameWork *globals;

        if ((entity->timer & 0xF) == 0) {
            height_slot = get_player_relative_point_octant(actor);
            beldo_camera_rotation[0] = dungeon_camera_targets[0];
            beldo_camera_rotation[1] = dungeon_camera_targets[1];
            entity->phase++;
            height_slot += entity->phase;
            if (height_slot >= 8) {
                height_slot -= 8;
            }
            beldo_camera_rotation[2] = heights.values[height_slot] * 0x200;
            beldo_camera_position[0] = ((s32)(actor->x + view_reference_entity.x.w.i)) / 2;
            y_sum = actor->y + view_reference_entity.y.w.i;
            beldo_camera_position[1] = y_sum / 2;
            beldo_camera_position[2] = actor->z;
            globals = &g_game_work;
            globals->view.slot[2].callback = 0;
            globals->view.slot[0].callback = 0;
            queue_view_slot(1);
            queue_view_slot(0);
            set_camera_targets(beldo_camera_position, beldo_camera_rotation, 4);
        }
    }

        entity->timer++;
        if (entity->timer >= 0x79) {
            entity->timer = 0;
            entity->phase = 0;
            entity->state++;
        }

    case 21:
    default:
        break;
    }
}
