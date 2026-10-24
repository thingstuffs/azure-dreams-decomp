#ifndef SHARED_ITEM_MENU_H
#define SHARED_ITEM_MENU_H
#include "common.h"
#include "shared/timed_stream.h"
#include "shared/gpu_packets.h"
#include "shared/object_node.h"


/* Exact access views shared across registered binary consumers. */
/* Three signed parameters passed to the item-menu lifecycle handlers. */
/* Leading work words of an item-menu object allocated by create_item_menu_object.
 * start_item_menu_object_processing passes them to the menu reset and child-release handlers. */
typedef struct ItemMenuParameters {
    int field0; /* primary menu object header passed to the retirement/reset handler */
    int field4; /* child object header scheduled for linked-entry release, or zero */
    int field8; /* auxiliary display object whose update callback is replaced for completion */
} ItemMenuParameters;

/* Three-word item-menu scene state rooted at D_80110EB8. */
/* Town item-menu scene request words rooted at item_menu_scene_state.
 * The state-selection wrappers store the request value and select phases 3, 5 or 7. */
typedef struct ItemMenuSceneState {
    int unk0;
    int unk4;
    int unk8; /* menu scene phase; the request wrappers set 3, 5 or 7 */
} ItemMenuSceneState;

/* Item-menu selection delay status, limit and counter words. */
/* Caller-owned item-menu selection-delay work, updated by tick_item_menu_selection_delay.
 * The cursor transition runs before the counter advances and the delay status is cleared. */
typedef struct ItemMenuDelayState {
    int unk0; /* the display payload's per-update callback slot: change_item_menu_selection installs tick_item_menu_selection_delay here and tick clears it when the prior counter reaches the limit */
    int unk4; /* selection-delay duration and interpolation denominator, in update ticks */
    int unk8; /* elapsed selection-delay updates; incremented once per tick */
} ItemMenuDelayState;

/* Signed flag word at +0x1C of the shop record. */
typedef struct ItemMenuFlagsView {
    unsigned char pad_00[0x1C];
    int unk_1C;
} ItemMenuFlagsView;

/* Second 16-byte record of one item-menu display part (realloc_field_0_buffer bank B).
 * Word +0 is the part's packed colour word (update_item_menu_selection stores D_800891F4 there and
 * fade_color_to_gray eases it toward grey); x/y are the part's screen offsets. */
typedef struct ItemMenuPartPosition {
    int color; /* packed red/green/blue/code word */
    unsigned char pad_04[0x4];
    short x; /* horizontal screen offset */
    short y; /* vertical screen offset */
} ItemMenuPartPosition;

/* One item-menu display part (realloc_field_0_buffer bank A, 16-byte records). The item-menu object
 * keeps a pointer to an array of 40 part pointers (allocated by load_actor_display_resource):
 * parts 0-3 are the panel slots, 4 and 5 the selection cursor pair, 6-35 the item rows,
 * 38 and 39 the side indicators. */
typedef struct ItemMenuPart {
    void *handler; /* what the part draws: slot handler data, the panel packet, an item label object or indicator data; null hides it */
    ItemMenuPartPosition *position;
    DisplayPositionWords *vector; /* shared display vector; load_actor_display_resource points every part at the object's */
    struct ItemMenuPart *next; /* draw chain built by link_item_menu_object_entries */
} ItemMenuPart;

/* Leading words of the item-menu state that owns an item-menu object (the payload of the node
 * create_item_menu_object allocates; ItemMenuParameters views the same three leading words). */
typedef struct ItemMenuState {
    struct ObjectNodeHeader *menu_object; /* item-menu object node from create_item_menu_child_object */
    void *display_controller; /* selected-entry display controller, or null */
    void *dual_buffer_object; /* create_dual_buffer_object result */
    unsigned char pad_0C[0x4];
    int page; /* current page of ten entries */
    int last_page; /* (count - 1) / 10 */
    int position; /* selected entry index */
    int count; /* entry count */
    void **entries; /* listed item records (4-byte id/kind records) */
} ItemMenuState;

/* Node whose payload is an ItemMenuState (create_item_menu_object). */
typedef struct ItemMenuStateNode {
    ObjectNodeHeader header;
    ItemMenuState state;
} ItemMenuStateNode;

/* 16-byte display block copied from display_block_defaults; initialize_item_menu_linked_blocks then
 * sets x/y to -60, depth to 0x200 and mode to 4. */
typedef struct ItemMenuDisplayBlock {
    int unk_00;
    short unk_04;
    short ramp; /* 0..0x1000 opening ramp written by advance_item_menu_step; handler objects start at 0x1000 */
    short x;
    short y;
    short depth;
    unsigned char unk_0E;
    unsigned char mode;
} ItemMenuDisplayBlock;

/* Link block the item-menu object's node addresses as its sprite part (node->sprite); it points at
 * the object's display block and display position (initialize_item_menu_linked_blocks). */
typedef struct ItemMenuDisplayLinks {
    int unk_00;
    ItemMenuDisplayBlock *display;
    DisplayPositionWords *position;
} ItemMenuDisplayLinks;

/* Item-menu object: the payload of the node create_item_menu_child_object allocates. */
typedef struct ItemMenuObject {
    /* 0x00 */ ItemMenuState *menu; /* owning menu's state (owner node + 0x20) */
    /* 0x04 */ void *saved_update; /* node update callback saved while the selected-entry check runs */
    /* 0x08 */ int open_step; /* opening ramp step, 0..6 (advance_item_menu_step) */
    /* 0x0C */ int repeat_delay; /* held-direction repeat counter */
    /* 0x10 */ int enabled;
    /* 0x14 */ unsigned int page_flags; /* bit 0: no next page, bit 1: no previous page */
    /* 0x18 */ ItemMenuStateNode *owner; /* owning menu node */
    /* 0x1C */ FrameState cursor; /* selection cursor colour stream */
    /* 0x28 */ unsigned char panel[0x48]; /* two-colour panel packet (initialize_item_menu_panel_rectangle) */
    /* 0x70 */ ItemMenuDisplayBlock display;
    /* 0x80 */ DisplayPositionWords display_position;
    /* 0x8C */ DisplayPositionWords part_vector; /* shared by all parts (ItemMenuPart.vector) */
    /* 0x98 */ ItemMenuDisplayLinks links; /* node->sprite */
    /* 0xA4 */ ItemMenuPart *chain; /* head of the part draw chain */
    /* 0xA8 */ ItemMenuPart **parts; /* 40 part pointers */
    /* 0xAC */ unsigned short *allocations[8]; /* null-terminated buffer list (release_null_terminated_entries): part table, part banks, position banks */
} ItemMenuObject;

/* Node whose payload is an ItemMenuObject (create_item_menu_child_object). */
typedef struct ItemMenuObjectNode {
    ObjectNodeHeader header;
    ItemMenuObject menu;
} ItemMenuObjectNode;

/* The node that carries an item-menu object; callbacks receive the payload. */
#define ITEM_MENU_OBJECT_NODE(object) ((ItemMenuObjectNode *)((unsigned char *)(object) - sizeof(ObjectNodeHeader)))

#endif
