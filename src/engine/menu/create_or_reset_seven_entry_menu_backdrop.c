#include "common.h"
#include "engine/menu.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "sdk/libc.h"

typedef struct S_8004F418_Node {
    struct S_8004F418_Node *next;
    u8 pad4[8];
    void *unkC;
    void (*unk10)(SevenEntryMenuBackdropBody *);
    u8 pad14[10];
    u16 flags;
    SevenEntryMenuBackdropBody body;
} S_8004F418_Node;

extern S_8004F418_Node menu_backdrop_node_storage;
extern u8 menu_backdrop_tag[16];

extern void *find_active_list_node(void *);
extern void *link_menu_backdrop_display_nodes(void *);

/* Initialize or reset the shared node, link its owner and state, and select its active sub-object. */
void *create_or_reset_seven_entry_menu_backdrop(s32 owner, s32 state)
{
    S_8004F418_Node *node = &menu_backdrop_node_storage;
    SevenEntryMenuBackdropBody *body = &node->body;
    u8 *template_node;

    if (find_active_list_node(node) == 0) {
        node = initialize_scene_object_in_buffer(0, node, 0xCF);
        register_node(node, menu_backdrop_tag);
    } else {
        set_object_cleanup_flag(node);
        node->flags &= 0x7FFF;
        bzero(body, 0x31C);
    }

    upper_draw_context[0x19] = 0;
    upper_draw_context[0x1A] = 0;
    upper_draw_context[0x1B] = 0;
    upper_draw_context[0x108ED] = 0;
    upper_draw_context[0x108EE] = 0;
    upper_draw_context[0x108EF] = 0;
    initialize_menu_backdrop_display_nodes(body, 7);

    template_node = (u8 *)body + 0x210;
    node->unkC = template_node;
    body->display_node_chain = link_menu_backdrop_display_nodes(&body->view.initializer.node_pointers[0]);
    body->state.value = state;
    initialize_menu_backdrop_layout(body, owner);
    node->unk10 = update_menu_backdrop_variant;
    update_menu_backdrop_variant(body);
    return node;
}
