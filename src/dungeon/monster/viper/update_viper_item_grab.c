#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"



typedef struct {
    Fixed1616 x;
    Fixed1616 y;
    u8 pad08[2];
    s16 height;
    s32 velocity_x;
    s32 velocity_y;
} Motion;

typedef struct {
    u8 pad00[0x8C];
    void (*callback)(void);
    u8 pad90[6];
    s16 timer;
    u8 pad98[3];
    u8 state;
    u8 pad9C[12];
    s16 saved_x;
    s16 saved_y;
} Entity;

typedef struct {
    u8 pad00[0x14];
    u16 flags;
    u8 pad16[0xE];
    u8 x_tile;
    u8 y_tile;
    u8 pad26[6];
    void (*callback)(void);
} Effect;

typedef struct {
    u8 bytes[4];
} PackedRecord __attribute__((packed));

typedef struct {
    u8 x;
    u8 y;
    u8 pad02[10];
} TileRecord;

typedef struct {
    u8 pad00[0x2A];
    u16 angle;
    u8 pad2C[0x1A];
    u16 flags;
    PackedRecord copy;
    u8 pad4C[0x21];
    s8 flag6D;
    u8 pad6E[0x1A];
    s16 height;
} Object;

typedef struct {
    u8 pad00[0x10];
    void (*callback)(void);
    u8 pad14[0xA7];
    u8 state;
} Spawned;

extern TileRecord dungeon_ground_item_positions[];
extern u8 D_80174A74[];
extern u8 D_80174AE4[];
extern u8 D_80174AEC[];
extern void *actor_update_node_cursor[];

extern s32 find_floor_item_at_world_position(s16, s16, s16);
extern Spawned *create_item_render_object(s32 parent, s32 sprite_source, s16 x, s32 y, s16 z);
extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern void select_sprite_entry(Effect *, u8, s32);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(Object *, s32);
extern void advance_status_timers(Object *);
extern void update_timed_effect_size_and_position(void);
extern void update_dungeon_actor_actions(void);
extern int abs(int);

/* Moves the entity forward, then returns it to its saved position and restores its callback. */
void update_viper_item_grab(Entity *entity, Motion *motion, Effect *effect, Object *object)
{
    s32 direction;
    s32 index;
    PackedRecord *record;
    PackedRecord *records;
    TileRecord *tile;
    TileRecord *tiles;
    Spawned *spawned;
    s32 distance;

    switch (entity->state) {
    case 0:
        direction = (object->angle >> 9) & 7;
        entity->saved_x = motion->x.w.i;
        entity->saved_y = motion->y.w.i;
        index = (s16)find_floor_item_at_world_position(effect->x_tile + dir_step_x[direction],
                                   effect->y_tile + dir_step_y[direction], object->height);
        records = ((PackedRecord *)dungeon_ground_items);
        record = &records[index];
        if (record->bytes[1] == 0x12) {
            object->copy = *record;
            tiles = dungeon_ground_item_positions;
            tile = &tiles[index];
            spawned = create_item_render_object((u8 *)entity - 0x20, record, (tile->x << 6) | 0x20,
                                    (tile->y << 6) | 0x20, motion->height);
            if (spawned != 0) {
                spawned->callback = update_timed_effect_size_and_position;
                spawned->state = 0;
            }
            record->bytes[0] = 0;
            record->bytes[1] = 0;
            update_map_cell_flags_with_item_limit(tile->x, tile->y, 0x800);
        }
        if (effect->flags & 0x8000) {
            entity->state = 3;
            entity->timer = 0;
            break;
        }
        motion->velocity_x = (dir_step_x[direction] << 16) + (dir_step_x[direction] << 15);
        motion->velocity_y = (dir_step_y[direction] << 16) + (dir_step_y[direction] << 15);
        effect->callback = (void (*)(void))D_80174AE4;
        select_sprite_entry(effect, D_80174AE4[((g_game_work.view.camera_rotation.parts.viewAngle + (s16)object->angle + 0x100) >> 9) & 7], 0);
        play_sound_if_enabled(0x51E);
        entity->timer = 2000;
        entity->state++;
        break;

    case 1:
        if ((effect->flags & 0x6000) && entity->timer >= 1001) {
            motion->velocity_x = 0;
            motion->velocity_y = 0;
            entity->timer = 10;
        }
        entity->timer--;
        if (entity->timer >= 0) {
            break;
        }
        effect->callback = (void (*)(void))D_80174AEC;
        select_sprite_entry(effect, D_80174AEC[((g_game_work.view.camera_rotation.parts.viewAngle + (s16)object->angle + 0x100) >> 9) & 7], 0);
        entity->timer = 2000;
        entity->state++;
        break;

    case 2:
        if ((effect->flags & 0x6000) && entity->timer >= 1001) {
            entity->timer = 12;
        }
        entity->timer--;
        if (entity->timer >= 0) {
            break;
        }
        index = (object->angle >> 9) & 7;
        motion->velocity_x = -dir_step_x[index] << 16;
        motion->velocity_y = -dir_step_y[index] << 16;
        effect->callback = (void (*)(void))D_80174A74;
        select_sprite_entry(effect, D_80174A74[((g_game_work.view.camera_rotation.parts.viewAngle + (s16)object->angle + 0x100) >> 9) & 7], 0);
        direction = abs(entity->saved_y - motion->y.w.i);
        distance = abs(entity->saved_x - motion->x.w.i);
        if (distance < direction) {
            distance = direction;
        }
        entity->timer = distance;
        entity->state++;
        break;

    case 3:
        entity->timer--;
        if (entity->timer > 0) {
            break;
        }
        motion->x.v = entity->saved_x << 16;
        motion->y.v = entity->saved_y << 16;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        spend_actor_mp(object, 0x100);
        entity->callback = update_dungeon_actor_actions;
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        advance_status_timers(object);
        if (object->flag6D == 0) {
            object->flags &= 0x7FFF;
        } else {
            actor_update_node_cursor[0] = (u8 *)object - 0x20;
        }
        break;
    }
}
