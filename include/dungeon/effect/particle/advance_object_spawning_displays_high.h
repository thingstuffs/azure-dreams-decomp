#ifndef DUNGEON_OVL_1960800_H
#define DUNGEON_OVL_1960800_H

struct ObjectNodeHeader;
typedef struct S_8003DF74_Vec SpriteAttachmentVector;
#include "shared/dungeon_effect_views.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "dungeon/effect/particle.h"
#include "sdk/libgte.h"
typedef struct S_81940800_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_81940800_1;
typedef struct S_81940800_2 {
    u8 pad_00[0x46];
    s16 unk_46;
} S_81940800_2;
typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} Rect16;
typedef struct {
    Rect16 rect[8];
} RectTable;
typedef struct {
    u32 word[3];
} __attribute__((packed)) PackedVec3;
typedef struct {
    u32 word[4];
} __attribute__((packed)) PackedBlock;
typedef struct {
    u32 word[4];
} AlignedBlock;
typedef struct {
    u8 pad0[6];
    s16 field6;
    void *vector;
    u8 red;
    u8 green;
    u8 blue;
    u8 padF;
    u8 pad10[4];
    u16 flags;
    u8 pad16[6];
    s16 scaleY;
    s16 scaleX;
} Display;
typedef struct Copy12 {
    s32 word[3];
} __attribute__((packed)) Copy12;
typedef struct {
    u8 pad0[6];
    s16 field6;
    void *ptr8;
    u8 byteC;
    u8 byteD;
    u8 byteE;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} Part;
typedef struct RotatingCountdownSpriteBody {
    u8 pad_00[0x2A];
    s16 ticks_remaining;
} RotatingCountdownSpriteBody;

/* The minigame consumer keeps this legacy spelling while the dungeon body uses the full type. */
typedef DisplaySpawnerEffectBody S_800243D8_0;

typedef struct S_800243D8_1_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800243D8_1_pre;
typedef struct Scratch800244E4 {
    u16 x;
    u16 y;
    u16 z;
    u8 pad06[0x12];
    u8 *cursor;         /* next free packet */
    u8 pad1C[4];
    u32 *ot;            /* ordering table */
    u8 pad24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad98[0x28];
    u32 index;          /* ordering table slot */
} Scratch800244E4;
typedef struct {
    unsigned char pad_00[0x32];
    s16 timer;
} Entity;
typedef struct {
    unsigned char pad_00[8];
    s32 position;
} State;
typedef struct {
    u8 pad[0x2A];
    s16 timer;
} DungeonObject;
typedef struct {
    s32 words[3];
} __attribute__((packed)) Packed12;
typedef struct PackedSpriteEffectBody {
    u8 pad_00[0x2A];
    s16 remaining;
} PackedSpriteEffectBody;
typedef struct S_800249F0_2_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800249F0_2_pre;
typedef struct {
    u8 bytes[12];
} __attribute__((packed)) EffectPacked12;
void select_record_entry_and_value(void *state, void *entries, short index);
void draw_transformed_sprite_with_clip_rect(void *, void *, void *, s32, s32);
extern s16 tint_particle_effect_updated;
extern PackedVec3 tint_particle_sprite_data;
void fade_tinted_display_sprite(FreeSlotDisplayEffectBody *effect, void *unused, void *primitive);
void spawn_free_slot_display_effect(DisplaySpawnerEffectBody *owner);
void create_free_slot_display_spawner(void *source, void *unused_position, void *unused_sprite);
s32 draw_brightness_scaled_point_chain(PointRecord *first_point, ObjectPosition *first_position);
void lower_timed_effect_position(Entity *entity, State *state);
void spawn_lowering_effect_under_parent(struct ObjectNodeHeader *source, s32 state_14_value, s32 state_08_value, s32 state_32_value, s16 x_offset, s16 y_offset, s16 z_offset);
void expand_rotating_countdown_sprite(RotatingCountdownSpriteBody *countdown_state, ObjectPosition *unused, SpriteFrameState *animation_state);
void advance_timed_effect_animation(DungeonObject *object, s32 unused, void *handlerContext);
void decrement_object_counter(PackedSpriteEffectBody *object);
void *create_packed_sprite_effect(void *source, ObjectPosition *unused_1, SpriteFrameState *unused_2, void *packed_data, s32 render_param, s32 render_x, s32 render_y, s32 render_mode);
/* Work at node +0x20 for advance_actor_tint_particle_sequence. Attachment
 * coordinates are returned by get_sprite_attachment_vector; the previous and
 * midpoint copies seed the particles between successive attachment positions. */
typedef struct TintParticleSequence {
    u8 pad_00[4];
    struct { u16 flags; } *animation;
    u8 variant;
    u8 pad_09;
    u16 state;
    u16 attachment_x;
    u16 attachment_y;
    u16 attachment_z;
    s16 previous_x;
    s16 previous_y;
    s16 previous_z;
    s16 midpoint_x;
    s16 midpoint_y;
    s16 midpoint_z;
    u8 pad_1E[2];
    s16 timer;
    u8 pad_22[4];
    s16 facing;
    u8 pad_28[2];
    u16 tick;
    u8 pad_2C[0x38];
    void *display_a;
    void *display_b;
} TintParticleSequence;

void advance_actor_tint_particle_sequence(TintParticleSequence *effect, ObjectPosition *effect_pos, SpriteFrameState *effect_data);

#endif
