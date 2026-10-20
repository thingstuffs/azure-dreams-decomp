#include "common.h"

typedef struct S_8004EEBC_Obj S_8004EEBC_Obj;

typedef struct S_8004F418_Node {
    struct S_8004F418_Node *next;
    u8 pad4[8];
    void *unkC;
    void (*unk10)(S_8004EEBC_Obj *);
    u8 pad14[10];
    u16 flags;
    u8 body[0x31C];
} S_8004F418_Node;

extern S_8004F418_Node D_80084138;
extern u8 D_801C9E40[0x10900];
extern u8 D_80027DD0[16];

extern void *find_active_list_node(void *);
extern void set_object_cleanup_flag(void *);
extern void *initialize_scene_object_in_buffer(s32, void *, s32);
extern void register_node(void *, void *);
extern void initialize_menu_backdrop_display_nodes(void *, s32);
extern void bzero(void *, s32);
extern void *link_menu_backdrop_display_nodes(void *);
extern void initialize_menu_backdrop_layout(void *, s32);
extern void update_menu_backdrop_variant(S_8004EEBC_Obj *);

/* Initialize or reset the shared node, link its owner and state, and select its active sub-object. */
void *create_or_reset_seven_entry_menu_backdrop(s32 owner, s32 state)
{
    S_8004F418_Node *node = &D_80084138;
    u8 *body = node->body;
    u8 *template_node;

    if (find_active_list_node(node) == 0) {
        node = initialize_scene_object_in_buffer(0, node, 0xCF);
        register_node(node, D_80027DD0);
    } else {
        set_object_cleanup_flag(node);
        node->flags &= 0x7FFF;
        bzero(body, 0x31C);
    }

    D_801C9E40[0x19] = 0;
    D_801C9E40[0x1A] = 0;
    D_801C9E40[0x1B] = 0;
    D_801C9E40[0x108ED] = 0;
    D_801C9E40[0x108EE] = 0;
    D_801C9E40[0x108EF] = 0;
    initialize_menu_backdrop_display_nodes(body, 7);

    template_node = body + 0x210;
    node->unkC = template_node;
    *(void **)(body + 0x21C) = link_menu_backdrop_display_nodes(body + 0x220);
    *(s32 *)(body + 4) = state;
    initialize_menu_backdrop_layout(body, owner);
    node->unk10 = update_menu_backdrop_variant;
    update_menu_backdrop_variant((S_8004EEBC_Obj *)body);
    return node;
}
