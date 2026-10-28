#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "engine/node.h"
#include "engine/graphics.h"

typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    u16 f4;
    u16 f6;
    u8 f8;
    u8 f9;
    u8 f10;
    u8 f11;
} S_80084478;

extern S_80084478 shaded_line_render_templates[16];
extern void update_shaded_line_effect(void);
struct ObjectPosition;
struct SpriteFrameState;

typedef struct {
    u8 pad0[8];
    S_80084478 *unk8;
    u32 unkC;
    u8 pad10[4];
    u16 unk14;
    u8 pad16[6];
    u16 unk1C;
    u16 unk1E;
} S_80052FE8_C;

typedef struct {
    u32 unk0;
    u32 unk4;
    u32 unk8;
} S_80052FE8_B;

typedef struct {
    ObjectNodeHeader header;
    u16 unk20;
    u16 unk22;
    u16 unk24;
    u8 pad26[2];
    s16 unk28;
    u8 pad2A[2];
    u16 unk2C;
    u16 unk2E;
} S_80052FE8;

/* Initialize the object callbacks, display entry, rendering defaults, and position. */
void init_shaded_line_effect(S_80052FE8 *object, s16 entry_index) {
    SpriteFrameState *render_state;
    ObjectPosition *position;
    u16 *state_fields;

    object->header.update_callback = update_shaded_line_effect;
    state_fields = &object->unk20;
    state_fields[0] = 0;
    state_fields[1] = 0;
    state_fields[2] = 0;
    state_fields[6] = 0;
    state_fields[7] = 0;
    state_fields[4] = entry_index;
    render_state = object->header.sprite;
    render_state->color.word = 0x808080;
    render_state->scale_y = 0x1000;
    render_state->scale_x = 0x1000;
    render_state->source = shaded_line_render_templates + entry_index;
    render_state->flags |= 0x80;
    register_node(&object->header, draw_linked_sprites);
    position = object->header.position;
    position->x.v = 0;
    position->y.v = 0;
    position->z.v = 0x600000;
}
