#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node/allocation.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80D653B8_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x12];
    s16 unk_AA;
    u8 pad_AC[0x4];
    void * unk_B0;
} S_80D653B8_0;   /* work in create_anchored_directional_object */

typedef struct S_80D653B8_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_80D653B8_2;   /* object_data in create_anchored_directional_object */

typedef struct S_80D653B8_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80D653B8_3;   /* arg3 in create_anchored_directional_object */

   /* position in create_anchored_directional_object */

typedef struct S_80D653B8_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0xA];
    u16 unk_16;
} S_80D653B8_5;   /* arg1 in create_anchored_directional_object */

extern void register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern void project_sprite_chain(void);
extern void select_sprite_entry();

extern u8 D_800D6FEC[];
extern u8 baloon_anchored_frames[];

/* Creates an object from a template, selects its direction, and positions it at the anchor. */
/* Copies a sprite template into a timed Baloon effect, selects anchored directional frames, and links it
 * to the origin. */
void create_anchored_directional_object(void *unused, S_80D653B8_5 *anchor, S_80D653B8_2 *object_template,
                   S_80D653B8_3 *facing_source, s32 initial_value)
{
    ObjectNodeHeader *object;
    SpriteFrameState *object_data;
    ObjectPosition *position;
    S_80D653B8_0 *object_work;

    (void)unused;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != NULL) {
        object_work = (u8 *)object + 0x20;
        object_work->unk_96 = initial_value;
        object_work->unk_AA = initial_value;
        object->update_callback = D_800D6FEC;
        object_work->unk_B0 = anchor;
        object_data = object->sprite;
        *(S_80D653B8_2 *)object_data = *object_template;

        object_data->scale_y = 0x1000;
        object_data->scale_x = 0x1000;
        object_data->color.c.b = 0x80;
        object_data->color.c.g = 0x80;
        object_data->color.c.r = 0x80;
        object_data->tpage_abr = 0x20;
        object_data->clut = 0xFF80;
        object_data->depth_bias = -6;
        object_data->flags |= 0xC;
        register_node(object, project_sprite_chain);

        {
            u8 *direction_table = baloon_anchored_frames;

            object_data->frameTable = direction_table;
            select_sprite_entry(object_data,
                direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + facing_source->unk_2A + 0x100) >> 9) & 7],
                0);
        }

        position = object->position;
        position->x.w.i = anchor->unk_02;
        position->y.w.i = anchor->unk_06;
        position->z.w.i =
            anchor->unk_0A + anchor->unk_16;
    }
}
