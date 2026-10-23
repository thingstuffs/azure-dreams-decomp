#ifndef SHARED_DUNGEON_TRAIL_VIEWS_H
#define SHARED_DUNGEON_TRAIL_VIEWS_H
#include "common.h"
#include "shared/gpu_packets.h"
/* Partial trail-effect and GPU views; offsets and access widths bind to retail. */
/* Spell trail controller at node +0x20, seeded by create_actor_spell_effect.
 * This overlay advances it through launch, travel/emission, hit and cleanup phases. */
typedef struct TrailEffectState {
    void *caster; /* caster actor work pointer */
    u16 *launch_flags; /* launch-context flags pointer; bit 0x80 permits launch */
    u8 pad_08[1];
    u8 spell_variant; /* spell variant byte passed to apply_attack_power_and_element_effects */
    s16 phase; /* trail phase: 0 launch wait, 1 travel, 2 emit, 3 hit, 4 delay, 5 cleanup */
    u8 pad_0C[0x44];
    u16 phase_ticks; /* phase/travel countdown in update ticks; travel lasts 12 ticks per tile */
    s16 child_flags; /* child-activity flags; bit 0x8000 postpones controller cleanup for this update */
} TrailEffectState;

/* Pooled position part used by trail effects and several monster movement callbacks.
 * allocate_list_node reserves it; the trail callback initializes planar motion from the caster tile. */
typedef struct TrailMotion {
    union {
        s32 unk_00; /* complete signed 16.16 X coordinate */
        struct {
            u8 pad_00[2];
            u16 unk_02; /* integer X bits passed to terrain queries */
        } unk_02;
    } x; /* world X in 16.16 units */
    union {
        s32 unk_04; /* complete signed 16.16 Y coordinate */
        struct {
            u8 pad_04[2];
            u16 unk_06; /* integer Y bits passed to terrain queries */
        } unk_06;
    } y; /* world Y in 16.16 units */
    u8 pad_08[2];
    s16 z; /* signed integer terrain/actor height, in world units */
    s32 velocity_x; /* X increment per position update, in 16.16 world units */
    s32 velocity_y; /* Y increment per position update, in 16.16 world units */
    s32 unk_14; /* actor callbacks: vertical velocity; trail callback: angle seed advanced by 0x100 per update */
} TrailMotion;

/* Caster/target slice borrowed from actor work by the spell trail controller.
 * The trail callback selects a target actor and records its map tile. */
typedef struct TrailActor {
    u8 pad_00[0x2A];
    u16 unk_2A; /* caster facing angle for the heading scan; 0x1000 units per turn */
    u8 pad_2C[0x34];
    void *unk_60; /* target actor work pointer returned by the heading scan, or zero */
    u8 pad_64[0xE];
    u8 unk_72; /* target map column, interpreted as signed when calculating travel distance */
    u8 unk_73; /* target map row, interpreted as signed when calculating travel distance */
} TrailActor;

/* Part-pointer slice of a pooled actor node; allocate_list_node fills the position and sprite pointers.
 * The trail controller reaches this header by subtracting 0x20 from caster work. */
typedef struct TrailObject {
    u8 pad_00[8];
    void *unk_08; /* position/motion part pointer */
    void *unk_0C; /* sprite/frame part pointer */
} TrailObject;

/* Sprite tile/status slice borrowed from the caster and target node parts.
 * The trail controller reads it to choose travel distance and the offscreen hit shortcut. */
typedef struct TrailSprite {
    u8 pad_00[0x14];
    u16 unk_14; /* sprite status/render flags; bit 0x8000 participates in the offscreen hit shortcut */
    u8 pad_16[0xE];
    u8 unk_24; /* map column in 64-world-unit tiles */
    u8 unk_25; /* map row in 64-world-unit tiles */
} TrailSprite;

/* Header/leading-work view of trail child nodes allocated with flags 0x201.
 * The trail controller installs update_flickering_effect_vertices and supplies the parent work pointer. */
typedef struct TrailSpawnedObject {
    u8 pad_00[0x10];
    s32 unk_10; /* child update callback, installed as update_flickering_effect_vertices */
    u8 pad_14[0xC];
    void *unk_20; /* parent trail-controller work pointer stored at payload +0 */
} TrailSpawnedObject;

/* Initialization view of trail child work at pooled node +0x20.
 * The spell trail callback seeds it for update_flickering_effect_vertices, whose fuller view is DungeonObj. */
typedef struct TrailParticleData {
    u8 pad_00[4];
    s32 unk_04; /* initial child X in 16.16 world units */
    s32 unk_08; /* initial child Y in 16.16 world units */
    s32 unk_0C; /* vertical motion offset in 16.16 units, initially zero */
    s32 unk_10; /* initial X increment per update, copied from the trail motion */
    s32 unk_14; /* initial Y increment per update, copied from the trail motion */
    s32 unk_18; /* initial vertical-offset increment, -3 in 16.16 units */
    s32 unk_1C; /* saved copy of the initial X motion increment */
    s32 unk_20; /* saved copy of the initial Y motion increment */
    s32 unk_24; /* saved copy of the initial vertical-offset increment */
    u8 pad_28[0x24];
    s16 unk_4C; /* initial vertex-rotation angle, randomized to 0..0xFFF */
    u16 unk_4E; /* initial orbit angle copied from the trail angle seed */
    u16 unk_50; /* initial terrain height reference, in integer world units */
    u16 unk_52; /* initial phase countdown copied from the controller */
    s16 unk_54; /* target/blend selector: initially -1 without a target, zero with a target */
    s16 unk_56; /* initial child phase, parent trail phase minus one */
} TrailParticleData;

typedef struct TrailHeightView {
    u8 pad_00[0xA];
    u16 unk_0A;
} TrailHeightView;

/* One transformed point inside caller-owned trail child work.
 * update_flickering_effect_vertices moves these integer coordinates during the final fade. */
typedef struct {
    u16 x; /* integer world X bits of the transformed point */
    u16 y; /* integer world Y bits of the transformed point */
    u16 z; /* integer world height bits of the transformed point */
    u16 pad;
} DungeonVertex;

/* Interior view of the four transformed points in a trail child; no separate allocation.
 * update_flickering_effect_vertices uses it to shift the points during the fade. */
typedef struct {
    u8 pad[0x10];
    DungeonVertex v[4]; /* four transformed integer world-coordinate points, each with an eight-byte stride */
} DungeonVertexBlock;

/* Interior trail-child view used while moving the transformed points after the rise.
 * update_flickering_effect_vertices borrows it from the same DungeonObj work allocation. */
typedef struct {
    u8 pad[0x18];
    DungeonVertexBlock block; /* view whose four world-coordinate points begin at child work +0x28 */
} DungeonFinalView;

typedef struct DungeonObj DungeonObj;

/* Full callback view of a spell trail child allocated by the trail controller with flags 0x201.
 * update_flickering_effect_vertices moves, colors and transforms the four points rendered as jittered triangles. */
struct DungeonObj {
    DungeonObj *parent; /* parent trail-controller work; each child update sets its +0x52 activity bit */
    s32 x; /* child X in 16.16 world units */
    s32 y; /* child Y in 16.16 world units */
    s32 z; /* vertical motion offset in 16.16 units; transform height uses twice its integer half */
    s32 dx; /* X motion increment per update, in 16.16 world units */
    s32 dy; /* Y motion increment per update, in 16.16 world units */
    s32 dz; /* vertical-offset increment per update, in 16.16 units; accelerated by 0x1700 */
    u8 pad1C[0x0C];
    u16 vx0; /* vertex 0 X, transformed in place from local offsets to integer world coordinates */
    u16 vy0; /* vertex 0 Y, transformed in place from local offsets to integer world coordinates */
    u16 vr0; /* vertex 0 height, seeded with 0..15 jitter before the in-place transform */
    u16 pad2E;
    u16 vx1; /* vertex 1 X, transformed in place from local offsets to integer world coordinates */
    u16 vy1; /* vertex 1 Y, transformed in place from local offsets to integer world coordinates */
    u16 vr1; /* vertex 1 height, seeded with 0..15 jitter before the in-place transform */
    u16 pad36;
    u16 vx2; /* vertex 2 X, transformed in place from local offsets to integer world coordinates */
    u16 vy2; /* vertex 2 Y, transformed in place from local offsets to integer world coordinates */
    u16 vr2; /* vertex 2 height, seeded with 0..15 jitter before the in-place transform */
    u16 pad3E;
    u16 vx3; /* vertex 3 X, transformed in place from local offsets to integer world coordinates */
    u16 vy3; /* vertex 3 Y, transformed in place from local offsets to integer world coordinates */
    u16 vr3; /* vertex 3 height, seeded with 0..15 jitter before the in-place transform */
    u16 pad46;
    u8 red; /* red modulation byte, randomized during rise and reduced by one quarter during fade */
    u8 green; /* green modulation byte, randomized during rise and reduced by one quarter during fade */
    u8 blue; /* blue modulation byte, randomized during rise and reduced by one quarter during fade */
    u8 pad4B;
    u16 angle; /* vertex rotation angle, masked to 0..0xFFF each update */
    u16 angle2; /* orbit angle for the sine/cosine position offset; advanced by 0x100 per rising update */
    u16 height; /* terrain height reference resampled beneath the child, in integer world units */
    u16 timer; /* phase countdown in updates; a negative prior value advances the phase */
    s16 aux; /* target/blend control: negative skips the hit pause; positive selects render blend mode 1 */
    s16 state; /* child phase; 0 drifts, phases below 2 rise/transform, 2 fades, 3 retires */
};

/* Stack vertex-transform request filled by update_flickering_effect_vertices.
 * transform_rotated_vertices reads its rotations, translation and count and transforms the point array in place. */
typedef struct {
    void *p0; /* source vertex array; the trail callback supplies the child points at +0x28 */
    void *p4; /* destination vertex array; equal to p0 for the in-place trail transform */
    s16 h8; /* first rotation component, initialized to zero for the trail transform */
    s16 hA; /* second rotation component, initialized to zero for the trail transform */
    u16 angle; /* third rotation component, copied from the child angle */
    s16 padE;
    s16 x; /* integer world X translation, including the orbit offset */
    s16 y; /* integer world Y translation, including the orbit offset */
    u16 height; /* integer height translation: terrain reference plus twice the child vertical offset */
    s16 pad16;
    s16 type; /* vertex count supplied to the transform; four for trail children */
    s16 pad1A;
} LocalPacket;

/* Twenty-byte flat triangle allocated at the frame packet cursor by draw_jittered_triangle_trails.
 * Each of the four child points produces one jittered screen-space triangle. */
typedef struct TrailTriangle {
    u32 unk_00; /* DMA chain address/count word */
    s32 unk_04; /* packed RGB/command word copied from the child before primitive setup */
    s16 unk_08; /* vertex 0 jittered screen X, in pixels */
    s16 unk_0A; /* vertex 0 jittered screen Y, in pixels */
    s16 unk_0C; /* vertex 1 jittered screen X, in pixels */
    s16 unk_0E; /* vertex 1 jittered screen Y, in pixels */
    s16 unk_10; /* vertex 2 jittered screen X, in pixels */
    s16 unk_12; /* vertex 2 jittered screen Y, in pixels */
} TrailTriangle;   /* packet1 in func_80024A1C */

/* Color/blend slice borrowed from a trail child by draw_jittered_triangle_trails.
 * The child updater supplies the channels and blend-control value. */
typedef struct TrailRenderItem {
    u8 pad_00[0x48];
    s32 unk_48; /* packed red/green/blue bytes copied to the flat triangle color word */
    u8 pad_4C[0x8];
    s16 unk_54; /* blend selector: positive uses GPU blend mode 1, otherwise mode 3 */
} TrailRenderItem;   /* item in func_80024A1C */

/* Depth-indexed view into the current frame ordering table; the renderer borrows the draw context.
 * draw_jittered_triangle_trails offsets the base by depth * 4 before using +0xB0. */
typedef struct TrailOrderEntry {
    u8 pad_00[0xB0];
    u32 unk_B0; /* ordering-table tag at draw context +0xB0 + depth * 4 */
} TrailOrderEntry;   /* entry in func_80024A1C */

/* Leading tag of a twelve-byte draw-mode packet allocated by draw_jittered_triangle_trails. */
typedef struct TrailDrawMode {
    u32 unk_00; /* DMA chain address/count word, linked ahead of the triangle at the same depth */
} TrailDrawMode;   /* packet0 in func_80024A1C */

/* Eight-byte slice immediately before trail work; register_node initializes its chain link.
 * The [-1] view reaches the owning node header at +0x18. */
typedef struct TrailChainPrefix {
    s32 unk_00; /* next registered node header address, or zero at the end of the render chain */
    u8 pad_04[0x4];
} TrailChainPrefix;   /* the 0x8 bytes before outer in func_80024A1C, addressed as outer[-1] */




#endif
