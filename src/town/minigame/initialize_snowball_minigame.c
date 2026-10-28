#include "common.h"
#include "town/minigame.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct TownDraw24 {
    s16 unk00;
    s16 unk02;
    void *unk04;
    u32 unk08;
    s16 unk0C;
    s16 unk0E;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u16 flags;
    u8 pad18[0x10];
} TownDraw24;

typedef struct TownDraw32 {
    s16 unk00;
    s16 unk02;
    void *unk04;
    void *unk08;
    void *unk0C;
    u32 unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    u8 pad20[0x10];
} TownDraw32;

typedef struct TownTransform {
    s32 value[3];
} TownTransform;

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
    TownTransform *transform;
    TownData *data;
    void (*callback)(void *);
    u8 pad14[0x0C];
    TownPart part;
};

extern u8 D_8002017C[];
extern u8 D_80020260[];
extern u8 D_80020360[];
extern u8 D_800203F4[];
extern u8 D_80020488[];

extern u8 D_80026DC8[];
extern void *D_80026EE0[];
extern void *D_80026F04[];
extern void *D_80026F08[];
extern s16 D_800272A0[];
extern s16 D_800272B0[];
extern s32 D_800272C0[];
extern u8 D_800F2F28[];

extern void create_scene_object_with_48_byte_payload(void *, TownDraw32 *);
extern void create_scene_object_with_record_payload(void *, TownDraw24 *);
extern void set_resident_bit(s32);
#include "slus.h"
extern void func_8003E188(s32, void *);
extern void *allocate_list_node(s32, void *);
extern void register_node(TownObject *, void *);

extern void configure_the_set_mode_n_2(TownPart *, TownTransform *, void *);

/* Initializes the town display objects, panel lines, and image tiles. */
s32 initialize_snowball_minigame(void)
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
    func_8003E188(0x3D, root_part);
    func_8003E188(0x3E, root_part);

    object = allocate_list_node(1, &scene_object_list_anchor.next);
    if (object != 0) {
        root_part = &object->part;
        object->callback = count_entries_matching_search_path;
    }

    object = allocate_list_node(0x136, &scene_object_list_anchor.next);
    root_part->child = object;
    if (object != 0) {
        object->callback = update_snowball_minigame_actor;
        register_node(object, project_sprite_chain);

        object_part = &object->part;
        object_data = object->data;
        object->transform->value[0] = 0x03A00000;
        object->transform->value[1] = 0x01E00000;
        object->transform->value[2] = 0x00200000;
        object_part->root = root_part;
        object_data->scale_y = 0x1000;
        object_data->scale_x = 0x1000;
        select_record_entry_and_value(object_data, D_800F2F28, 0);
        object_data->color.word = 0x00808080;
        configure_the_set_mode_n_2(object_part, object->transform, D_80026DC8);
    }

    index = 7;
    initial_value = 0x30;
    zero_entry = D_800272B0;
    filled_entry = zero_entry + 7;
    zero_entry = D_800272A0;
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
    draw.unk0C = 0x30;
    draw.unk0E = 0xA0;
    draw.unk10 = 0xE0;
    draw.unk12 = 0x22;
    draw.unk14 = 2;
    draw.unk08 = 0x404040;
    draw.unk00 = 0;
    draw.unk02 = 0x10;
    draw.unk04 = root_part;
    draw.flags |= 3;
    create_scene_object_with_record_payload(D_8002017C, draw_ptr);

    draw.unk0C = 0x7A;
    draw.unk0E = 0x40;
    draw.unk10 = 0x50;
    draw.unk12 = 0x10;
    draw.unk14 = 2;
    draw.unk08 = 0;
    draw.unk00 = 0;
    draw.unk02 = 0x10;
    draw.unk04 = root_part;
    draw.flags |= 0xFFFD;
    create_scene_object_with_record_payload(D_80020260, draw_ptr);

    draw.unk0E = 0xA2;
    draw.unk10 = 1;
    draw.unk12 = 0x1E;
    draw.unk14 = 0;
    draw.unk08 = 0x808080;
    draw.unk00 = 0;
    draw.unk04 = root_part;
    index = 8;
    do {
        draw.unk0C = 0x60 + index * 0x10;
        create_scene_object_with_record_payload(D_80020360, &draw);
        index--;
    } while (index >= 0);

    draw.unk0C = 0x32;
    draw.unk0E = 0xB0;
    draw.unk10 = 0xDC;
    draw.unk12 = 1;
    create_scene_object_with_record_payload(D_80020360, &draw);

    tile.unk10 = 0x808080;
    tile.unk14 = 0x34;
    tile.unk16 = 0xB6;
    tile.unk18 = 3;
    tile.unk1C = 2;
    tile.unk1A = 0x7C80;
    tile.unk00 = 0;
    tile.unk02 = 0x10;
    tile.unk0C = root_part;
    tile.unk04 = D_80026F04[0];
    create_scene_object_with_48_byte_payload(D_800203F4, &tile);

    {
        void **image_base = D_80026EE0;

        images = image_base;
    }
    tile.unk16 = 0xA4;
    index = 8;
    do {
        tile.unk04 = images[index];
        tile.unk14 = 0x64 + index * 0x10;
        create_scene_object_with_48_byte_payload(D_800203F4, &tile);
        index--;
    } while (index >= 0);

    tile.unk14 = 0xF4;
    tile.unk16 = 0xB6;
    tile.unk04 = D_800272C0;
    create_scene_object_with_48_byte_payload(tick_summed_scene_value_text, &tile);

    tile.unk14 = 0x7E;
    tile.unk16 = 0x44;
    tile.unk04 = D_80026F08[0];
    create_scene_object_with_48_byte_payload(D_80020488, &tile);
    return 0;
}
