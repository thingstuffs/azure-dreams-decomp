#ifndef FRONTEND_SETTINGS_H
#define FRONTEND_SETTINGS_H
/* Prototypes of the functions defined in src/frontend/settings/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

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
    /* 0x0E */ union { s16 s; u16 u; } angle;
} SettingsVisualEffectBody;

/* Display entry body shared by the settings table callbacks.  The allocator copies
 * a 40-byte payload; the callbacks use its source, packed value, result and index. */
typedef struct MainTitleValueEntry {
    /* 0x00 */ u8 pad_00[4];
    /* 0x04 */ void *value_data;
    /* 0x08 */ s32 packed_components;
    /* 0x0C */ u8 pad_0C[4];
    /* 0x10 */ s16 value;
    /* 0x12 */ u8 pad_12[2];
    /* 0x14 */ u16 attribute;
    /* 0x16 */ u8 pad_16[2];
    /* 0x18 */ s32 value_index;
    /* 0x1C */ u8 pad_1C[0xC];
} MainTitleValueEntry;

struct ColorEffect;
struct ColorRampEffect;
struct MainTitleValueEntry;
struct Menu;
struct Motion;
struct Obj;
struct S_7FDD3A2C_1;
struct State;

/* build_settings_sprite_tiles.c */
s32 build_settings_sprite_tiles(void *node_data, void *scroll_state);

/* create_settings_controller.c */
void create_settings_controller(void);

/* create_type.c */
void *create_type(struct S_7FDD3A2C_1 *position, s32 object_value, s32 render_value, s32 extra_value);

/* handle_settings_menu_input.c */
void handle_settings_menu_input(struct Menu *menu);

/* initialize_and_submit_record.c */
void initialize_and_submit_record(s32 value, void *data);

/* initialize_available.c */
void initialize_available(s32 value, void *data);

/* initialize_settings_screen.c */
void initialize_settings_screen(void);

/* load_indexed.c */
void load_indexed(void *entry);

/* load_signed_state.c */
void update_settings_color_cycle(struct ColorEffect *effect);

/* load_table.c */
void load_table(struct MainTitleValueEntry *entry);

/* pack_three_capped_components_and_flag.c */
void pack_three_capped_components_and_flag(void *dest);

/* propagate_record_high_bit.c */
void propagate_record_high_bit(void *record);

/* queue_settings_sprite_grid.c */
s32 queue_settings_sprite_grid(u8 *entry_data, u8 *scroll_data);

/* update_settings_effect.c */
void update_settings_effect(SettingsVisualEffectBody *effect);

/* update_settings_effect_color.c */
void update_settings_effect_color(struct ColorRampEffect *effect);

/* update_settings_effect_object.c */
void update_settings_effect_object(SettingsEffectObjectBody *object, void *motion, void *sprite);
void sync_object_with_sub_object(SettingsSyncObjectBody *object);

/* update_settings_menu_animation.c */
void update_settings_menu_animation(struct Obj *obj, s32 *position);

/* update_settings_phase_motion.c */
void update_settings_phase_motion(struct State *state, struct Motion *motion, void *update_data);


/* Remove a callback object when its linked owner is marked. */
void remove_record_with_marked_owner(void *body);
void remove_effect_with_marked_owner(void *body);

#endif
