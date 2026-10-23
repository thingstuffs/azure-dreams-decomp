#ifndef TOWN_OVL_79DD70_H
#define TOWN_OVL_79DD70_H
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "town/minigame/pickup_data.h"

typedef struct { s32 words[22]; } Payload88;
typedef struct { s32 words[6]; } Initial24;
typedef void (*ObjectCallback)(void *, void *, void *);

typedef struct {
    s32 word00;
    u8 x;
    u8 y;
    u8 pad06[2];
    s32 image;
    u32 color;
    s32 word10;
    u16 flags;
    u8 pad16[6];
    s16 scale_x;
    s16 scale_y;
} RenderPart;

/* Bank-specific typed view of ObjectNodeHeader offsets 0x08, 0x0C and 0x10.
 * The allocator returns the shared base header; the constructor casts to this
 * view before using its initial-data, render and callback slots. */
typedef struct {
    u8 pad00[8];
    Initial24 *initial;
    RenderPart *render;
    ObjectCallback callback;
} Object;

struct RegistrationNode;
struct S_80045340_Entry;
extern s32 register_node(struct RegistrationNode *, s32 registration_id);
extern s32 func_8004491C(struct RegistrationNode *, s32 registration_id);
extern void configure_the_set_mode_n_1(void *, void *, void *);
extern u8 D_80020014[], minigame_source_bounds[];
extern s32 project_sprite_chain(void *, s32, struct S_80045340_Entry *, s32);
extern s32 func_80045340(void *, s32, struct S_80045340_Entry *, s32);
extern void update_bouncing_pickup(void *, void *, SpriteFrameState *);
extern s32 minigame_pickup_sprite_sources[];


#endif
