#include "shared/entity.h"
#include "common.h"
#include "town/minigame.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
#include "engine/runtime.h"
#include "engine/util.h"
#include "town/minigame/object.h"
#include "town/minigame/state.h"

typedef struct TownDraw24 {
    s16 state;
    s16 delay;
    void *linked;
    u32 color;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 tpage_mode;
    u16 flags;
    u8 pad18[0x10];
} TownDraw24;

typedef struct TownDraw32 {
    s16 state;
    s16 delay;
    void *text;
    void *unk08;
    void *owner;
    u32 color;
    s16 x;
    s16 y;
    s16 blend_mode;
    s16 clut;
    s16 flags;
    s16 unk1E;
    u8 pad20[0x10];
} TownDraw32;

typedef struct TownData {
    u8 pad00[0x0C];
    u32 color;
    u8 pad10[0x0C];
    s16 angle1C;
    s16 angle1E;
} TownData;

typedef struct TownPart TownPart;
typedef struct TownObject TownObject;

struct TownPart {
    u8 pad00[4];
    TownObject *child;
    u8 pad08[0xA4];
    TownPart *root;
};

struct TownObject {
    u8 pad00[8];
    ObjectPosition *transform;
    TownData *data;
    void (*callback)(void *);
    u8 pad14[0x0C];
    TownPart part;
};

extern u8 D_8002017C[];
extern u8 D_80020260[];
extern u8 D_80020360[];

extern struct Box D_80026DC8;
extern void *D_80026EE0[];
extern void *D_80026F04[];
extern void *D_80026F08[];
extern s16 snowball_round_scores[];
extern s16 snowball_round_score_text[];
extern s32 D_800272C0[];
extern u8 D_800F2F28[];

#include "slus.h"

/* Initializes the town display objects, panel lines, and image tiles. */
/* The dispatcher passes four explicit zero arguments. */
s32 initialize_snowball_minigame(s32 unused_arg0, s32 unused_arg1, s32 unused_arg2, s32 unused_arg3)
{
    TownDraw32 tile;
    TownDraw24 draw;
    TownDraw24 *draw_ptr;
    TownPart *root_part;
    TownObject *object;
    TownPart *object_part;
    SpriteFrameState *object_data;
    s16 *filled_entry;
    s16 *zero_entry;
    void **images;
    s32 index;
    s32 initial_value;

    root_part = 0;
    SD_Call(0x704);
    set_resident_bit(0xA5);
    set_packed_2bit_flag(0x3D, root_part);
    set_packed_2bit_flag(0x3E, root_part);

    object = allocate_list_node(1, &scene_object_list_anchor.next);
    if (object != 0) {
        root_part = &object->part;
        object->callback = update_collection_cutscene_step;
    }

    object = allocate_list_node(0x136, &scene_object_list_anchor.next);
    root_part->child = object;
    if (object != 0) {
        object->callback = update_snowball_minigame_actor;
        register_node(object, project_sprite_chain);

        object_part = &object->part;
        object_data = object->data;
        object->transform->x.v = 0x03A00000;
        object->transform->y.v = 0x01E00000;
        object->transform->z.v = 0x00200000;
        object_part->root = root_part;
        object_data->scale_y = 0x1000;
        object_data->scale_x = 0x1000;
        select_record_entry_and_value(object_data, D_800F2F28, 0);
        object_data->color.word = 0x00808080;
        init_scene_node_mode_2(object_part, object->transform, &D_80026DC8);
    }

    index = 7;
    initial_value = 0x30;
    zero_entry = snowball_round_score_text;
    filled_entry = zero_entry + 7;
    zero_entry = snowball_round_scores;
    zero_entry += 7;
    do {
        *zero_entry = 0;
        *filled_entry = initial_value;
        filled_entry--;
        index--;
        zero_entry--;
    } while (index >= 0);

    draw_ptr = &draw;
    D_800272C0[0] = 0x3020;
    draw.x = 0x30;
    draw.y = 0xA0;
    draw.width = 0xE0;
    draw.height = 0x22;
    draw.tpage_mode = 2;
    draw.color = 0x404040;
    draw.state = 0;
    draw.delay = 0x10;
    draw.linked = root_part;
    draw.flags |= 3;
    create_menu_line_object(D_8002017C, draw_ptr);

    draw.x = 0x7A;
    draw.y = 0x40;
    draw.width = 0x50;
    draw.height = 0x10;
    draw.tpage_mode = 2;
    draw.color = 0;
    draw.state = 0;
    draw.delay = 0x10;
    draw.linked = root_part;
    draw.flags |= 0xFFFD;
    create_menu_line_object(D_80020260, draw_ptr);

    draw.y = 0xA2;
    draw.width = 1;
    draw.height = 0x1E;
    draw.tpage_mode = 0;
    draw.color = 0x808080;
    draw.state = 0;
    draw.linked = root_part;
    index = 8;
    do {
        draw.x = 0x60 + index * 0x10;
        create_menu_line_object(D_80020360, &draw);
        index--;
    } while (index >= 0);

    draw.x = 0x32;
    draw.y = 0xB0;
    draw.width = 0xDC;
    draw.height = 1;
    create_menu_line_object(D_80020360, &draw);

    tile.color = 0x808080;
    tile.x = 0x34;
    tile.y = 0xB6;
    tile.blend_mode = 3;
    tile.flags = 2;
    tile.clut = 0x7C80;
    tile.state = 0;
    tile.delay = 0x10;
    tile.owner = root_part;
    tile.text = D_80026F04[0];
    create_text_sprite_object(retire_delayed_scene_text_on_completion, &tile);

    {
        void **image_base = D_80026EE0;

        images = image_base;
    }
    tile.y = 0xA4;
    index = 8;
    do {
        tile.text = images[index];
        tile.x = 0x64 + index * 0x10;
        create_text_sprite_object(retire_delayed_scene_text_on_completion, &tile);
        index--;
    } while (index >= 0);

    tile.x = 0xF4;
    tile.y = 0xB6;
    tile.text = D_800272C0;
    create_text_sprite_object(tick_summed_scene_value_text, &tile);

    tile.x = 0x7E;
    tile.y = 0x44;
    tile.text = D_80026F08[0];
    create_text_sprite_object(retire_scene_text_after_terminal_phase, &tile);
    return 0;
}
