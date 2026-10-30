#include "shared/object_node.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "town/menu/catalog.h"
#include "engine/node.h"
#include "engine/graphics.h"

#ifndef NULL
#define NULL 0
#endif


void release_null_terminated_entries(u16 **entries);
short SD_Call(int flags);
void SetGeomOffset(s32, s32);
void SetGeomScreen(s32);
void initialize_catalog_glyph_cache(void);
extern s8 animation_tick_scale;
extern s32 D_80126704;

/* Initializes the object's state and callbacks, or flags initialization failure. */
void open_standalone_catalog(void) {
    CatalogDisplay *obj_data;
    s32 global_flags;
    u16 object_flags;
    ObjectNodeHeader *obj;

    obj = allocate_flagged_object_node(0);
    obj_data = ((void *)obj) + 0x20;
    if (obj != NULL) {
        if (initialize_catalog_display_nodes(obj_data) != 0) {
            animation_tick_scale = 1;
            initialize_catalog_glyph_cache();
            obj->sprite = (u8 *)obj + 0x68;
            initialize_catalog_state(obj_data);
            register_node(obj, &draw_tinted_node_sprites_scratch);
            obj->update_callback = &D_80126704;
            g_game_work.view.projection_distance = 0x200;
            SetGeomScreen(0x200);
            SetGeomOffset(0xA0, 0x78);
            SD_Call(0x701);
            return;
        }
        release_null_terminated_entries((u8 *)obj + 0x7C);
        global_flags = object_flag_block.flags;
        object_flags = obj->flags;
        obj->flags = object_flags | 0x8000;
        object_flag_block.flags = global_flags | 0x8000;
    }
}
