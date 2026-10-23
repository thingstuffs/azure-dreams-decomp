#ifndef SHARED_DUNGEON_DELAY_VIEWS_H
#define SHARED_DUNGEON_DELAY_VIEWS_H
#include "common.h"
#include "m2c_compat.h"
/* One shared game-view inventory for the delayed-effect producers and callbacks. */
/* Parent work for the delayed targeted effect at node +0x20. Child callbacks
 * set the activity word while the parent waits for its last particles to fade. */
typedef struct DelayedTargetEffect {
    u8 *owner;
    struct { u16 flags; } *animation;
    u8 pad_08;
    u8 variant;
    union { s16 s; u16 u; } state;
    u8 pad_0C[0x44];
    union { s16 s; u16 u; } timer;
    union { s16 s; u16 u; } child_activity;
} DelayedTargetEffect;

/* Position/motion prefix of delayed particle nodes, reserved by allocate_list_node.
 * advance_delayed_fading_sprite adds the horizontal motion increments after registration. */
typedef struct {
    s32 f0; /* world X in 16.16 units */
    s32 f4; /* world Y in 16.16 units */
    s32 f8; /* world height in 16.16 units */
    s32 fC; /* X increment per motion update, in 16.16 world units */
    s32 f10; /* Y increment per motion update, in 16.16 world units */
} DelayPosition;

/* Object flags immediately before delayed-effect work, initialized by allocate_list_node.
 * brighten_accelerate_and_fade_effect uses the two-byte [-1] view on completion. */
typedef struct DelayStatusPrefix {
    u16 unk_00; /* object flags; bit 0x8000 requests retirement */
} DelayStatusPrefix;   /* the 0x2 bytes before r_arg0 in func_800247D8, addressed as r_arg0[-1] */

/* Delayed-effect work at node +0x20, reserved by allocate_list_node.
 * brighten_accelerate_and_fade_effect advances its brightness, rising and fade phases. */
typedef struct DelayParticle {
    void * unk_00; /* owner work pointer; its +0x52 child-activity bit is set during updates */
    u8 pad_04[0x44];
    u16 unk_48; /* phase countdown in update ticks; reset to 16 before the rising phase */
    union {
        u16 u;
        s16 s;
        struct { u8 low, high; } bytes;
    } fade_step; /* per-update red/green decrement; blue loses twice its low byte */
    union { u16 u; s16 s; } unk_4C; /* effect phase: 0 brighten, 1 rise and emit children, 2 fade */
} DelayParticle;   /* r_arg0 in func_800247D8 */

/* Owner-work flag slice referenced by delayed particles; no separate allocation.
 * Delayed particle callbacks mark the owner while they are active. */
typedef struct DelayOwner {
    u8 pad_00[0x52];
    u16 unk_52; /* child-activity flags; each delayed child update sets bit 0x8000 */
} DelayOwner;   /* temp_v1 in func_800247D8 */

/* Color slice of an allocator-owned sprite part used by the rising/fading effect.
 * brighten_accelerate_and_fade_effect changes the three modulation channels together. */
typedef struct DelaySpriteColor {
    u8 pad_00[0xC];
    union {
        struct { u8 v; /* red modulation byte */ } at00;
        struct { s32 v; /* whole color/command word, cleared at effect completion */ } at00u;
        struct { u8 pad[0x1]; u8 v; /* green modulation byte */ } at01;
        struct { u8 pad[0x2]; u8 v; /* blue modulation byte */ } at02;
    } color; /* packed little-endian RGB modulation and primitive command byte */
} DelaySpriteColor;   /* arg2 in func_800247D8 */

/* Position/vertical-motion slice of the rising effect, reserved by allocate_list_node.
 * brighten_accelerate_and_fade_effect increases vertical velocity by 0x8000 per rising update. */
typedef struct DelayMotion {
    s32 unk_00; /* world X in 16.16 units, copied into emitted children */
    s32 unk_04; /* world Y in 16.16 units, copied into emitted children */
    s32 unk_08; /* world height in 16.16 units */
    u8 pad_0C[0x8];
    s32 unk_14; /* height increment per update, in 16.16 world units */
} DelayMotion;   /* arg1 in func_800247D8 */

/* Header/work slice of delayed child particles allocated by allocate_list_node.
 * brighten_accelerate_and_fade_effect installs their callback and links them to the owner. */
struct SpriteFrameState;

typedef struct DelayObject {
    u8 pad_00[0x8];
    void * unk_08; /* child position/motion part pointer */
    void * unk_0C; /* child sprite part pointer */
    void (*unk_10)(void *, DelayPosition *, struct SpriteFrameState *); /* child update callback, set to advance_delayed_fading_sprite */
    u8 pad_14[0xC];
    void * unk_20; /* owner work pointer stored at the beginning of the child payload */
} DelayObject;   /* temp_v0_4 in func_800247D8 */

typedef struct DelayMotionZ {
    u8 pad_00[0x8];
    s32 unk_08;
} DelayMotionZ;   /* child in func_800247D8 */

/* Sprite part initialized for children emitted by brighten_accelerate_and_fade_effect.
 * allocate_list_node reserves it; the delayed callback animates and fades it. */
typedef struct DelaySprite {
    u8 * unk_00; /* selected sprite-source entry */
    s8 unk_04; /* source entry index; initialized to zero */
    s8 unk_05; /* animation delay/rate byte; initialized to zero */
    u8 pad_06[0x2];
    s32 unk_08; /* command/attachment source copied from source entry +4 */
    s32 unk_0C; /* packed little-endian RGB modulation and primitive command byte */
    s16 unk_10; /* texture-page blend override; child initialization selects 0x20 */
    u8 pad_12[0x2];
    u16 unk_14; /* sprite status/render flags */
    u8 pad_16[0x6];
    s16 unk_1C; /* horizontal scale; 0x1000 = 1.0 */
    s16 unk_1E; /* vertical scale; 0x1000 = 1.0 */
} DelaySprite;   /* temp_s0 in func_800247D8 */


/* Timer/phase slice of delayed child work at node +0x20.
 * brighten_accelerate_and_fade_effect initializes it for advance_delayed_fading_sprite. */
typedef struct DelayParticleTimers {
    u8 pad_00[0x48];
    s16 unk_48; /* registration delay in update ticks, initialized to 0..3 */
    s16 unk_4A; /* red/green fade step per update; blue loses twice this value */
    s16 unk_4C; /* child phase: 0 registration delay, 1 move/animate/fade */
} DelayParticleTimers;   /* temp_v1_3 in func_800247D8 */

/* Horizontal position/velocity slice of delayed child particles.
 * allocate_list_node reserves it and brighten_accelerate_and_fade_effect seeds the motion. */
typedef struct DelayVelocity {
    s32 unk_00; /* world X in 16.16 units */
    s32 unk_04; /* world Y in 16.16 units */
    u8 pad_08[0x4];
    s32 unk_0C; /* X increment per update, in 16.16 world units */
    s32 unk_10; /* Y increment per update, in 16.16 world units */
} DelayVelocity;   /* ((DelayObject *)temp_v0_4)->unk_08 in func_800247D8 */


#endif
