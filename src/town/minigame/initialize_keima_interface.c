#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/slus_callbacks.h"
#include "engine/runtime.h"
#include "engine/util.h"

typedef struct {
    s32 v[5];
} Word5;

typedef struct {
    s32 v[8];
} Word8;

typedef struct {
    s32 v[4];
} Word4;

typedef struct {
    s32 w0;
    s32 w4;
} __attribute__((packed)) Packed8;

typedef struct {
    s16 h0;
    s16 pad2;
    void *p4;
    s32 w8;
    s16 hC;
    s16 hE;
    s16 h10;
    s16 h12;
    s16 h14;
    s16 h16;
    s32 pad18[4];
} Init40;

typedef struct {
    s16 h0;
    s16 pad2;
    void *p4;
    void *p8;
    void *pC;
    s32 w10;
    s16 h14;
    s16 h16;
    s16 h18;
    s16 h1A;
    s16 h1C;
    s16 pad1E;
    s32 pad20[4];
} Init10;

#define AT(type, base, off) (*(type *)((u8 *)(base) + (off)))

extern Word5 D_80020100[];
extern Word8 D_80020114[];
extern Word4 D_80020134[];
extern Packed8 D_80020144[];
extern u8 D_800218E4[];
extern u8 D_80022484[];
extern u8 D_800225F0[];
extern u8 D_80023158[];
extern u8 D_80023260[];
extern u8 D_80023A00[];
extern u8 D_80023C80[];
extern Packed8 D_80024310[];
extern u8 D_80046398[];
extern u8 D_800F15E4[];

extern void func_8002108C();
extern void func_80021120();
extern u8 D_80022FD8[];
extern void func_80023DA0();
extern void select_record_entry_and_value();
extern u8 *allocate_list_node();
extern void register_node();
extern s16 query_lowered_transform_position();

/* Initializes the interface owner, widgets, and sprite objects. */
s32 initialize_keima_interface(void) {
    u8 *owner = 0;
    Init10 widget_init;
    Init40 panel_init;
    Word5 widget_data = D_80020100[0];
    Word8 sprite_frames = D_80020114[0];
    Word4 sprite_images = D_80020134[0];
    ObjectNodeHeader *obj;
    SpriteFrameState *sprite;
    u8 *child_data;
    s32 *timer;
    s32 index;
    s32 template_page;

    set_resident_bit(0x58D);
    set_resident_bit(0x58E);
    set_packed_2bit_flag(0xE, 0);

    obj = allocate_list_node(1, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        owner = ((u8 *)obj) + 0x20;
        AT(s16, owner, 0x2E) = 0x2D;
        obj->unk_10 = D_800218E4;
    }
    AT(void *, ((u8 *)(&scene_object_list_anchor)), 0x74) = owner;
    func_80023DA0(owner);

    panel_init.hC = 0x10;
    panel_init.hE = 0x10;
    panel_init.h10 = 0x68;
    panel_init.h12 = 0x40;
    panel_init.h14 = 2;
    panel_init.h16 = 1;
    panel_init.w8 = 0x404040;
    panel_init.h0 = 0;
    panel_init.p4 = owner;
    func_80021120(D_80022484, &panel_init);

    {
        index = 3;
        panel_init.hC = -2;
        panel_init.hE = -2;
        panel_init.h14 = 0;
        panel_init.h16 = 0;
        do {
            panel_init.w8 = (0x80 << (index * 8)) & 0xFFFFFF;
            panel_init.p4 = owner + index * 4;
            func_80021120(D_80023C80, &panel_init);
            index--;
        } while (index >= 0);
    }

    {
        s32 widget_index;
        Init10 *widget_params;
        widget_init.h14 = 0x14;
        widget_init.h18 = 3;
        widget_init.h1C = 0;
        widget_init.h1A = 0x7C80;
        widget_init.w10 = 0x808080;
        widget_init.h0 = 0;
        widget_init.pC = owner;
        widget_index = 4;
        widget_params = &widget_init;
        do {
            u8 *widget_handler;
            Init10 *widget_args;
            widget_handler = D_800225F0;
            widget_args = widget_params;
            widget_init.h16 = widget_index * 0xC + 0x14;
            widget_init.p4 = (void *)((s32 *)&widget_init)[0x16 + widget_index];
            func_8002108C(widget_handler, widget_args);
            widget_index--;
        } while (widget_index >= 0);
    }

    widget_init.h14 = 0x3C;
    timer = (s32 *)0x800135B4;
    if (*timer == 0) {
        *timer = 0x258;
    }
    AT(u16, owner, 0x38) = *(u16 *)timer;
    index = 4;
    do {
        Packed8 *text_buffer = &D_80024310[index];
        *text_buffer = D_80020144[0];
        AT(s8, text_buffer, 7) = 0;
        widget_init.h16 = index * 0xC + 0x14;
        widget_init.p4 = text_buffer;
        widget_init.p8 = owner + 0x30 + index * 2;
        func_8002108C(D_80022FD8, &widget_init);
        index--;
    } while (index >= 0);

    {
        s32 sprite_index = 7;
        s32 handler_page = (s32)0x80020000;
        u8 *sprite_handler;
        SpriteFrameState *grid_sprite;
        sprite_handler = D_80023158;
        sprite = (u8 *)0x1000;
        do {
            obj = (u8 *)allocate_flagged_object_node(0x136);
            if (obj != 0) {
                register_node(obj, D_80046398);
                grid_sprite = *(u8 * *)&obj->sprite;
                obj->unk_10 = sprite_handler;
                grid_sprite->color.word = 0x808080;
                grid_sprite->scale_x = (s16)sprite;
                grid_sprite->scale_y = (s16)sprite;
                grid_sprite->unk_20 = (s16)sprite;
                grid_sprite->source = sprite_frames.v[sprite_index];
                AT(s32, AT(u8 *, obj, 8), 0) = ((sprite_index >> 2) << 22) + 0x0FE00000;
                AT(s32, AT(u8 *, obj, 8), 4) = ((sprite_index % 4) << 22) + 0x03E00000;
                AT(s32, AT(u8 *, obj, 8), 8) = 0;
                AT(void *, obj, 0x20) = owner;
            }
            sprite_index--;
        } while (sprite_index >= 0);
    }

    index = 3;
    do {
        obj = (u8 *)allocate_flagged_object_node(0x136);
        if (obj != 0) {
            register_node(obj, project_sprite_chain);
            sprite = *(u8 * *)&obj->sprite;
            obj->unk_10 = D_80023158;
            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            sprite->color.word = 0x808080;
            select_record_entry_and_value(sprite, (void *)sprite_images.v[index], 0);
            sprite->clut = 0xFFC0;
            AT(s32, AT(u8 *, obj, 8), 0) = ((index >> 2) << 22) + 0x0FD00000;
            AT(s32, AT(u8 *, obj, 8), 4) = ((index % 4) << 22) + 0x04100000;
            AT(s32, AT(u8 *, obj, 8), 8) = 0xFF600000;
            AT(void *, obj, 0x20) = owner;
        }
        index--;
    } while (index >= 0);

    {
        u8 *new_obj;
        TileObject *sprite_state;
        index = 2;
        do {
            new_obj = allocate_list_node(0x136, ((u8 *)(&scene_object_list_anchor)));
            AT(void *, owner + index * 4, 0x20) = new_obj;
            obj = new_obj;
            if (obj != 0) {
                obj->unk_10 = D_80023260;
                register_node(obj, project_sprite_chain);
                sprite = *(u8 * *)&obj->sprite;
                AT(s32, AT(u8 *, obj, 8), 0) = 0x10000000;
                AT(s32, AT(u8 *, obj, 8), 4) = (index << 22) + 0x04200000;
                child_data = ((u8 *)obj) + 0x20;
                AT(s16, AT(u8 *, obj, 8), 0xA) = query_lowered_transform_position(obj->position);
                AT(s16, sprite, 0x1E) = 0x1000;
                AT(s16, sprite, 0x1C) = 0x1000;
                sprite_state = &reference_tile_object;
                sprite->unk_28 = AT(s32, sprite_state, 0x28);
                AT(s16, child_data, 0x2A) = 0x800;
                select_record_entry_and_value(sprite, D_800F15E4, 0);
                sprite->color.word = 0x808080;
                sprite->clut = (index + 1) * 4;
                AT(void *, obj, 0x20) = owner;
                AT(s16, child_data, 0x24) = index + 1;
            }
            index--;
        } while (index >= 0);
    }

    obj = allocate_list_node(0x136, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        obj->unk_10 = D_80023A00;
        register_node(obj, project_sprite_chain);
        sprite = *(u8 * *)&obj->sprite;
        AT(s32, AT(u8 *, obj, 8), 0) = 0x10000000;
        AT(s32, AT(u8 *, obj, 8), 4) = 0x03E00000;
        child_data = ((u8 *)obj) + 0x20;
        template_page = query_lowered_transform_position(obj->position);
        AT(s16, AT(u8 *, obj, 8), 0xA) = template_page;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->unk_28 = reference_tile_object.render_attributes;
        AT(s16, child_data, 0x2A) = 0x800;
        select_record_entry_and_value(sprite, D_800F15E4, 0);
        sprite->color.word = 0x808080;
        AT(void *, obj, 0x20) = owner;
    }
    return 0;
}
