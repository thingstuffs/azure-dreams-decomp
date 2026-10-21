#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_80126890_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
    void * unk_20;
} S_80126890_0;   /* node in allocate_and_initialize_node_2 */


extern void register_node(void *, void *);
extern void release_null_terminated_entries(void *);
extern void SD_Call(s32);
extern void initialize_catalog_glyph_cache(void);
extern s32 initialize_catalog_display_nodes(void *);
extern void initialize_catalog_state(void *);

extern s32 dungeon_menu_tag;
extern s8 animation_tick_scale;
extern s32 D_80126704;

/* Allocates and initializes a node for the supplied data, returning null on failure. */
static void *allocate_and_initialize_node_2(void *data) {
    void *node;
    void *payload;

    node = allocate_flagged_object_node(0);
    if (node != 0) {
        ((S_80126890_0 *)node)->unk_20 = data;
        payload = (u8 *)node + 0x20;
        if (initialize_catalog_display_nodes(payload) != 0) {
            animation_tick_scale = 1;
            initialize_catalog_glyph_cache();
            ((S_80126890_0 *)node)->unk_0C = (u8 *)node + 0x68;
            initialize_catalog_state(payload);
            register_node(node, &dungeon_menu_tag);
            ((S_80126890_0 *)node)->unk_10 = &D_80126704;
            SD_Call(0x701);
        } else {
            release_null_terminated_entries((u8 *)node + 0x7C);
            ((S_80126890_0 *)node)->unk_1E |= 0x8000;
            object_flag_block.flags |= 0x8000;
            node = 0;
        }
    }
    return node;
}
