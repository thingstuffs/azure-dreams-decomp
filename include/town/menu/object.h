#ifndef TOWN_MENU_OBJECT_H
#define TOWN_MENU_OBJECT_H
/* Prototypes of the functions defined in src/town/menu/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "town/menu/object_setup.h"
#include "shared/dungeon_effect_views.h"
#include "shared/dungeon_moving_views.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_source.h"
#include "shared/vector.h"

struct Rec_D_80082D58;
struct DoorProjectionChild;
struct EmoteCallbackObject;
struct S_func_800A9F90;
struct SpriteFrameState;
struct TownObject;
struct DoorDisplayBody;
struct ObjectPosition;
struct LitMeshSprite;
struct TownObjectRecord;

typedef void (*DoorDisplayCallback)(struct DoorDisplayBody *, struct ObjectPosition *, struct LitMeshSprite *);

/* The door creates this child and stores its own body, position and active flag.
 * The initializer replaces callback with the rotation update for this part. */
typedef struct DoorDisplayBody {
    DoorDisplayCallback callback;
    u8 pad_04[0xC];
    struct TownObjectRecord *owner;
    struct ObjectPosition *origin;
    u8 pad_18[8];
    s16 part_index;
    u8 pad_22[0x1E];
    u8 *active_flag;
} DoorDisplayBody;

/* Body finalized when its bounds check or countdown expires. */
typedef struct BoundsExpiryObject {
    /* 0x00 */ u8 pad_00[0x6C];
    /* 0x6C */ u16 timer;
    /* 0x6E */ u8 pad_6E[0x2A];
    /* 0x98 */ u8 *linked_flag;
} BoundsExpiryObject;

/* allocate_and_initialize_display_object_g01137.c */
struct ObjectNodeHeader *allocate_and_initialize_display_object(struct TownObjectRecord *owner, u8 *active_flag, ObjectPosition *origin, s32 part_index, DoorDisplayCallback update,
    DoorDisplayCallback initialize);
s32 create_display_object_series(struct TownObjectRecord *owner, u8 *active_flag, ObjectPosition *origin, s32 count);
void run_callback_until_state_clears(DoorDisplayBody *object, ObjectPosition *position, struct LitMeshSprite *mesh);
void initialize_directional_object_state(DoorDisplayBody *object, ObjectPosition *placement, struct LitMeshSprite *state);
void copy_directional_value(DoorDisplayBody *object, ObjectPosition *unused, struct LitMeshSprite *mesh);
struct ObjectNodeHeader *create_default_display_object(struct TownObjectRecord *owner, u8 *active_flag, ObjectPosition *origin, s32 part_index);

struct DoorTransitionEffect;

/* create_shaded_primitive_object.c */
ObjectNodeHeader *create_shaded_primitive_object(struct DoorTransitionEffect *parent, s32 index, struct ObjectPosition *unused_origin);

/* create_positioned_sprite_object_g01142.c */
ObjectNodeHeader *create_emote_sprite_object(IntVector3 *position, EmoteObjectCallback on_ground, SpriteSourceEntry *graphic_id);
void load_emote_launch_velocity(struct EmoteCallbackObject *object, ObjectPosition *output, struct SpriteFrameState *unused);
void invoke_emote_object_callback(struct EmoteCallbackObject *object, ObjectPosition *motion, struct SpriteFrameState *sprite);
void advance_emote_motion(struct EmoteCallbackObject *object, ObjectPosition *motion, struct SpriteFrameState *unused);
void advance_position_and_handle_ground_contact(struct EmoteCallbackObject *entity, ObjectPosition *motion, struct SpriteFrameState *sprite);

/* create_preset_sprite_object.c */
ObjectNodeHeader *create_preset_sprite_object(IntVector3 *position);

/* create_timed_effect_object.c */
void create_timed_effect_object(struct TownObjectRecord *owner, ObjectPosition *position, struct SpriteFrameState *source);

/* decrement_callback_object_timer.c */
void decrement_callback_object_timer(struct S_func_800A9F90 *self, ObjectPosition *expiry_arg);

/* retire_object_on_check_or_timeout.c */
void retire_object_on_check_or_timeout(BoundsExpiryObject *object, ObjectPosition *position);

/* initialize_effect_object.c */
void initialize_effect_object(struct TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context);

/* initialize_object_items_in_reverse.c */
s32 initialize_object_items_in_reverse(struct DoorTransitionEffect *object, struct ObjectPosition *origin, s32 item_count);

/* initialize_timed_scale_object.c */
void initialize_timed_scale_object(struct TownObjectRecord *object, ObjectPosition *state, struct SpriteFrameState *context);

/* render_shaded_object_primitive.c */
void render_shaded_object_primitive(struct DoorProjectionChild *object, ObjectPosition *coords, struct SpriteFrameState *primitive);

/* swap_catalog_paired_entries.c */

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"

#endif
