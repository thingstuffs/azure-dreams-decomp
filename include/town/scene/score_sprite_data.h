#ifndef TOWN_SCENE_SCORE_SPRITE_DATA_H
#define TOWN_SCENE_SCORE_SPRITE_DATA_H

#include "common.h"
#include "shared/minigame_body.h"
#include "shared/object_node.h"

/* The panel stores its address in the rising sprite's initial body. The sprite
 * copies that address to both children, which set the panel flag while shrinking. */
typedef struct RisingScorePanel {
    TownScoreCounterView *score;
    u8 work[0x48];
    u8 *resource;
    s16 mode;
    s16 timer;
    s16 progress;
    s16 column;
    u16 flags;
} RisingScorePanel;

typedef struct RisingScoreChild {
    RisingScorePanel *panel;
    s32 step_x;
} RisingScoreChild;

typedef struct RisingScorePanelNode {
    ObjectNodeHeader header;
    RisingScorePanel panel;
} RisingScorePanelNode;

/* Both text callbacks keep the same controller and text pointer in their bodies. */
typedef struct RisingScoreTextDisplay {
    s16 state;
    u8 pad_02[2];
    const char *text;
    s16 *value;
    TownScoreCounterView *controller;
    u32 color;
    s16 x;
    s16 y;
    s16 field_18;
    s16 field_1A;
} RisingScoreTextDisplay;

typedef struct RisingScoreFade {
    s16 state;
    u8 pad_02[2];
    TownScoreCounterView *controller;
    s32 color;
    s16 field_0C;
    s16 field_0E;
    s16 field_10;
    s16 field_12;
    s16 field_14;
    u16 flags;
} RisingScoreFade;

struct ObjectPosition;
struct SpriteFrameState;
/* Five words laid out by the panel before the sprite factory copies them.
 * The callback subsequently interprets these bytes as its mutable effect body. */
typedef struct RisingScoreSpawn {
    RisingScorePanel *root;
    u32 field_04;
    u32 field_08;
    u16 mode;
    u16 field_0E;
    u16 field_10;
} RisingScoreSpawn;
void advance_shop_item_panel(RisingScorePanel *object, struct ObjectPosition *position, struct SpriteFrameState *sprite);
void create_rising_score_sprite(const RisingScoreSpawn *init_data, s32 y_position);

void run_scheduled_three_actor_display(TownScoreCounterView *controller);
void set_record_flags_when_linked(RisingScoreTextDisplay *record);
void update_number_display_record(RisingScoreTextDisplay *record);

/* Source word of the frame entry selected by the bounce and slot-machine sprites. */
extern void *score_sprite_initial_value[];
/* The three kind-indexed sources in the Town score image table. */
extern void *score_object_images[3];
/* Address of the imported score-sprite draw callback at 0x8003C558. */
extern u8 score_sprite_draw_callback_address[];

#endif
