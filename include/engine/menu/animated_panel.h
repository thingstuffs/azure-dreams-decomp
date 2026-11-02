#ifndef ENGINE_MENU_ANIMATED_PANEL_H
#define ENGINE_MENU_ANIMATED_PANEL_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/menu_display.h"
/* A sixteen-byte display link follows each block in the animated panel. */
typedef struct AnimatedPanelLink {
    s32 unk_00;
    void *self;
    void *parent;
    struct AnimatedPanelLink *next;
} AnimatedPanelLink;
typedef struct AnimatedPanelElement {
    MenuDisplayBlock block;
    AnimatedPanelLink link;
} AnimatedPanelElement;
/* Body initialized by window_create_animated_content_panel and init_menu_panel.
 * Integer resource-word views of the buffer remain separate at their boundary. */
typedef struct AnimatedMenuPanelBody {
    u16 flags;
    u8 pad_02[2];
    s16 target_x;
    s16 target_y;
    void *template_buffer;
    u8 pad_0C[8];
    s32 template_word;
    s32 resource_handle;
    s32 tag_values;
    AnimatedPanelElement elements[4];
    DisplayPositionWords vector;
} AnimatedMenuPanelBody;
typedef struct AnimatedMenuPanelNode {
    ObjectNodeHeader header;
    AnimatedMenuPanelBody body;
} AnimatedMenuPanelNode;
void menu_move_the_position_halfway_toward_target_position(AnimatedMenuPanelBody *position);
#endif
