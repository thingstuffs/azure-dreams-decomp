#ifndef FRONTEND_SETTINGS_H
#define FRONTEND_SETTINGS_H
/* Prototypes of the functions defined in src/frontend/settings/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/transition_slots.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "frontend/settings/controller_body.h"

typedef struct SettingsEffectBlock {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} SettingsEffectBlock;

/* Two four-word copies followed by two final words, forty bytes in total. */
typedef struct SettingsEffectTable {
    SettingsEffectBlock blocks[2];
    s32 tail[2];
} SettingsEffectTable;

/* Per-sprite state, countdown and selection index for the settings effect children. */
typedef struct SettingsEffectObjectBody {
    /* 0x00 */ void *owner;
    /* 0x04 */ u8 pad_04[4];
    /* 0x08 */ s16 state;
    /* 0x0A */ u16 ticks;
    /* 0x0C */ s16 index;
} SettingsEffectObjectBody;

/* Object sampled by the settings synchronization callback. */
typedef struct SettingsSyncChildObjectBody {
    u8 pad_00[0x20];
    /* 0x20 */ s16 kind;
    /* 0x22 */ u8 pad_22[2];
    /* 0x24 */ s16 position_value;
    /* 0x26 */ u16 flags;
} SettingsSyncChildObjectBody;

typedef struct SettingsSyncObjectBody {
    /* 0x00 */ s16 state;
    /* 0x02 */ u8 pad_02[2];
    /* 0x04 */ SettingsSyncChildObjectBody *child;
    /* 0x08 */ s32 color;
    /* 0x0C */ s16 position_y;
    /* 0x0E */ s16 position_delta;
    /* 0x10 */ s16 width;
    /* 0x12 */ s16 height;
    /* 0x14 */ s16 value;
    /* 0x16 */ u16 flags;
} SettingsSyncObjectBody;

/* Controller body for the settings color and rotation effect. */
typedef struct SettingsVisualEffectBody {
    /* 0x00 */ void *owner;
    /* 0x04 */ s32 color;
    /* 0x08 */ s16 phase;
    /* 0x0A */ u16 ticks;
    /* 0x0C */ u8 pad_0C[2];
    /* 0x0E */ s16 angle;
} SettingsVisualEffectBody;

/* Settings screen body created by initialize_settings_screen and read by its callbacks. */
typedef struct Menu {
    /* 0x00 */ TransitionSlot fade;
    /* 0x08 */ s16 state;
    /* 0x0A */ s16 timer;
    /* 0x0C */ s16 row;
    /* 0x0E */ s16 color_channels[3];
    /* 0x14 */ u16 shade;
    /* 0x16 */ u16 flags;
} SettingsScreenBody;

/* The settings screen copies each 0x30-byte label into its callback node. */
typedef struct ColorEffect {
    s16 state;
    u16 timer;
    s32 text;
    u8 pad_08[4];
    SettingsScreenBody *owner;
    s32 color;
    s16 x;
    u16 y;
    s16 style;
    s16 font;
    u16 flags;
    u8 pad_1E[2];
    s32 selector;
    u32 active;
    u8 pad_28[8];
} ColorEffect;

/* Display entry body shared by the settings table callbacks.  The allocator copies
 * a 40-byte payload; the callbacks use its source, packed value, result and index. */
typedef struct MainTitleValueEntry {
    s16 flags;
    u8 pad_02[2];
    SettingsScreenBody *owner;
    s32 color;
    s16 x, y;
    s16 width, height;
    s16 style, shading;
    s32 index;
    u8 pad_1C[0xC];
} MainTitleValueEntry;

struct MainTitleValueEntry;
struct Obj;
struct SettingsPositionPair;

/* build_settings_sprite_tiles.c */
s32 build_settings_sprite_tiles(SettingsScreenBody *node_data, ObjectPosition *scroll_state);

/* create_settings_controller.c */
void create_settings_controller(void);

/* create_settings_sprite_object.c */
void *create_settings_sprite_object(struct SettingsPositionPair *position, s32 object_value, s32 render_value, SettingsScreenBody *extra_value);

/* handle_settings_menu_input.c */
void handle_settings_menu_input(SettingsScreenBody *menu);

/* create_settings_color_effect.c */
void create_settings_color_effect(void (*update)(ColorEffect *), const ColorEffect *data);

/* create_settings_value_entry.c */
void create_settings_value_entry(void (*update)(MainTitleValueEntry *), const MainTitleValueEntry *data);

/* initialize_settings_screen.c */
void initialize_settings_screen(void);

/* update_color_channel_entry.c */
void update_color_channel_entry(MainTitleValueEntry *entry);

/* load_signed_state.c */
void update_settings_color_cycle(struct ColorEffect *effect);

/* update_volume_slider_entry.c */
void update_volume_slider_entry(struct MainTitleValueEntry *entry);

/* update_packed_color_entry.c */
void update_packed_color_entry(MainTitleValueEntry *dest);

/* remove_value_entry_with_marked_source.c */
void remove_value_entry_with_marked_source(MainTitleValueEntry *entry);

/* queue_settings_sprite_grid.c */
s32 queue_settings_sprite_grid(struct Obj *entry, ObjectPosition *position);

/* update_settings_effect.c */
void update_settings_effect(SettingsVisualEffectBody *effect);

/* update_settings_effect_color.c */
void update_settings_effect_color(struct ColorEffect *effect);

/* update_settings_effect_object.c */
void update_settings_effect_object(SettingsEffectObjectBody *object, ObjectPosition *motion, SpriteFrameState *sprite);
void sync_settings_object_with_child(SettingsSyncObjectBody *object);

/* update_settings_menu_animation.c */
void update_settings_menu_animation(SettingsMenuBody *obj, ObjectPosition *position);

/* update_settings_phase_motion.c */
void update_settings_phase_motion(SettingsEffectObjectBody *state, ObjectPosition *motion, SpriteFrameState *update_data);


/* Remove a callback object when its linked owner is marked. */
struct SettingsOwnerLinkedBody;
void remove_record_with_marked_owner(struct SettingsOwnerLinkedBody *body);
void remove_effect_with_marked_owner(ColorEffect *body);

#endif
