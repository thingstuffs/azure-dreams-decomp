#include "shared/object_node.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_801267B8_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_801267B8_0;   /* obj in open_standalone_catalog */


s32 register_node();
void release_null_terminated_entries(u16 **entries);
short SD_Call(int flags);
void func_80064F00(s32, s32);
void func_80064F20(s32);
void initialize_catalog_glyph_cache();
s32 initialize_catalog_display_nodes();
void initialize_catalog_state();
int draw_tinted_node_sprites_scratch(void *forwarded_ptr, int unused_arg, void *second_ptr);
extern s8 animation_tick_scale;
extern s32 D_80126704;

/* Initializes the object's state and callbacks, or flags initialization failure. */
void open_standalone_catalog(void) {
    s32 obj_data;
    s32 global_flags;
    u16 object_flags;
    void *obj;

    obj = func_8003FC64(0);
    obj_data = (u8 *)obj + 0x20;
    if (obj != NULL) {
        if (initialize_catalog_display_nodes(obj_data) != 0) {
            animation_tick_scale = 1;
            initialize_catalog_glyph_cache();
            ((S_801267B8_0 *)obj)->unk_0C = (u8 *)obj + 0x68;
            initialize_catalog_state(obj_data);
            register_node(obj, &draw_tinted_node_sprites_scratch);
            ((S_801267B8_0 *)obj)->unk_10 = &D_80126704;
            g_game_work.view.projection_distance = 0x200;
            func_80064F20(0x200);
            func_80064F00(0xA0, 0x78);
            SD_Call(0x701);
            return;
        }
        release_null_terminated_entries((u8 *)obj + 0x7C);
        global_flags = object_flag_block.flags;
        object_flags = ((S_801267B8_0 *)obj)->unk_1E;
        ((S_801267B8_0 *)obj)->unk_1E = object_flags | 0x8000;
        object_flag_block.flags = global_flags | 0x8000;
    }
}
