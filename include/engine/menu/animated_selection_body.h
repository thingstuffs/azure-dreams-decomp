#ifndef ENGINE_MENU_ANIMATED_SELECTION_BODY_H
#define ENGINE_MENU_ANIMATED_SELECTION_BODY_H

#include "common.h"

struct ObjectNodeHeader;
struct ObjectPosition;
struct CardDisplayNode;

/* The menu sorts and relinks these pool nodes. Their sprite slots refer to
 * display records whose blocks supply X, Y, depth and shade. */
typedef struct AnimatedSelectionEntry {
    struct ObjectNodeHeader *next;
    struct ObjectNodeHeader **pprev;
    struct ObjectPosition *position;
    struct CardDisplayNode *display;
} AnimatedSelectionEntry;

/* The destructor releases three entries. The constructor queries their IDs at
 * +0x10 and fills the node slots according to the selected three-byte row. */
typedef struct AnimatedSelectionMenuBody {
    void (*animate)(struct AnimatedSelectionMenuBody *);
    AnimatedSelectionEntry *entries[3];
    s32 entry_ids[3];
    u8 pad_1C[4];
    s32 spacing;
    s32 count;
    s32 transition_frames;
    s32 transition_tick;
    s32 selected_index;
    s32 previous_index;
    s32 repeat_ticks;
} AnimatedSelectionMenuBody;

#endif
