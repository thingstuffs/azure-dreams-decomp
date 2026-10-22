#ifndef SHARED_DUNGEON_PROJECTILE_VIEWS_H
#define SHARED_DUNGEON_PROJECTILE_VIEWS_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_source.h"
/* Partial game-object views jointly observed by projectile producers and callbacks.
 * Offsets and signed/unsigned access forms are retail constraints; sizes are views. */
/* Spell projectile work at object node +0x20; create_actor_spell_effect initializes its caster and context.
 * func_80024020 advances launch, travel, impact and cleanup phases. */
typedef struct ProjectileState {
    void *unk_00; /* caster actor work pointer, supplied by create_actor_spell_effect */
    void *unk_04; /* launch/action context; leading flags bit 0x80 releases the projectile */
    u8 pad_08[1];
    u8 unk_09; /* spell variant byte passed to apply_attack_power_and_element_effects */
    union { s16 s; u16 u; } unk_0A; /* projectile phase: 0 await launch, 1 delay, 2 travel, 3 impact, 4 unlink, 5 cleanup */
    union { s32 s; u16 u; } unk_0C; /* phase countdown in update ticks; also offsets the emitted particle trail */
    s32 unk_10; /* child-activity flags; bit 0x8000 postpones cleanup for this update */
    u8 pad_14[0x3C];
    union { s16 s; u16 u; } unk_50; /* travel/cleanup countdown, decremented once per projectile update */
} ProjectileState;

/* Position and velocity part of pooled projectile/particle nodes, reserved by allocate_list_node.
 * Projectile callbacks add the three velocity words to the 16.16 coordinates each update. */
typedef struct ProjectileMotion {
    union {
        s32 s; /* complete signed 16.16 X coordinate */
        struct { u8 pad_00[2]; s16 unk_02; /* signed integer X, divided by 64 for the tile column */ } h;
    } unk_00; /* world X in signed 16.16 units */
    union {
        s32 s; /* complete signed 16.16 Y coordinate */
        struct { u8 pad_04[2]; s16 unk_06; /* signed integer Y, divided by 64 for the tile row */ } h;
    } unk_04; /* world Y in signed 16.16 units */
    union {
        s32 s; /* complete signed 16.16 height */
        struct { u8 pad_08[2]; u16 unk_0A; /* integer height bits, passed to terrain queries */ } h;
    } unk_08; /* world height in 16.16 units */
    s32 unk_0C; /* X increment per update, in 16.16 world units */
    s32 unk_10; /* Y increment per update, in 16.16 world units */
    s32 unk_14; /* height increment per update, in 16.16 world units */
} ProjectileMotion;

/* Sprite-part view shared by projectile and particle callbacks; allocate_list_node reserves the part.
 * Projectile spawners initialize its source, color, blend mode and scales. */
typedef struct ProjectileSprite {
    void *unk_00; /* selected sprite-source entry */
    u8 unk_04; /* source entry index; reset to zero when restarting the particle animation */
    u8 unk_05; /* animation delay/rate byte; reset alongside the source index */
    u8 pad_06[2];
    void *unk_08; /* selected command/attachment source read from source entry +4 */
    union {
        struct { u8 v; /* red modulation byte, reduced by the particle fade step */ } at00;
        struct { s32 v; /* complete packed color/command word */ } at00u;
        struct { u8 pad[1]; u8 v; /* green modulation byte */ } at01;
        struct { u8 pad[2]; u8 v; /* blue modulation byte */ } at02;
    } unk_0C; /* packed little-endian RGB modulation and primitive command byte */
    s16 unk_10; /* texture-page blend override; replaces tpage bits 5..6 when nonzero */
    u8 pad_12[2];
    u16 unk_14; /* sprite status/render flags; particle callbacks test animation bits 0x6000 */
    u8 pad_16[6];
    u16 unk_1C; /* horizontal sprite scale; 0x1000 = 1.0 */
    u16 unk_1E; /* vertical sprite scale; 0x1000 = 1.0 */
    u8 pad_20[4];
    u8 unk_24; /* map column in 64-world-unit tiles */
    u8 unk_25; /* map row in 64-world-unit tiles */
} ProjectileSprite;

/* Caster/target slice of actor work, initialized through the actor constructors.
 * func_80024020 selects the target and stores its tile for the projectile and its particles. */
typedef struct ProjectileActor {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A; /* facing angle used for the heading scan; 0x1000 units per turn */
    u8 pad_2C[0x34];
    union { void *p; s32 s; } unk_60; /* target actor work pointer returned by scan_monster_along_heading, or zero */
    u8 pad_64[0x0E];
    union { s8 s; u8 u; } unk_72; /* target tile column; interpreted as signed when constructing the target position */
    union { s8 s; u8 u; } unk_73; /* target tile row; interpreted as signed when constructing the target position */
} ProjectileActor;

/* Object-header slice used by actor and projectile producers; allocate_list_node sets the part pointers.
 * Actor/effect constructors install the update callback at +0x10; work begins at node +0x20. */
typedef struct ProjectileObject {
    u8 pad_00[8];
    void *unk_08; /* position/motion part pointer, assigned by the node allocator */
    void *unk_0C; /* sprite/frame part pointer, assigned by the node allocator */
    void *unk_10; /* object update callback installed by the actor or effect constructor */
} ProjectileObject;

/* Particle work at node +0x20, initialized by func_80024020 after allocate_list_node.
 * update_timed_sprite_effect handles its registration delay, fade and final animation. */
typedef struct ProjectileParticle {
    void *unk_00; /* parent projectile work; the child sets its +0x10 activity bit 0x8000 */
    s16 unk_04; /* target tile column; reaching both tile coordinates stops particle motion */
    s16 unk_06; /* target tile row; reaching both tile coordinates stops particle motion */
    u8 pad_08[0x40];
    u16 unk_48; /* update countdown; initially a 0..3 tick registration delay */
    s16 unk_4A; /* red fade step/threshold; green and blue use one quarter of this step */
    union { s16 s; u16 u; } unk_4C; /* particle phase: 0 delay, 1 fade/shrink, 2 wait for animation completion */
} ProjectileParticle;

/* Leading flag halfword of the caller-supplied launch context; this view owns no allocation.
 * create_actor_spell_effect stores the context and func_80024020 waits on its bit 0x80. */
typedef struct AnimationFlags {
    u16 unk_00; /* launch-context flags; bit 0x80 permits projectile launch */
} AnimationFlags;

/* Completion-flag view of an object header initialized by allocate_list_node.
 * Projectile cleanup sets bit 0x8000 at node +0x1E. */
typedef struct ObjectStatusPrefix {
    u8 pad_00[0x1E];
    u16 unk_1E; /* object flags immediately before work at +0x20; bit 0x8000 requests retirement */
} ObjectStatusPrefix;

/* Stack target-position scratch in func_80024020; filled from the selected tile and terrain height. */
typedef struct {
    Fixed1616 x; /* target X in 16.16 units; integer part is tile column * 64 + 32 */
    Fixed1616 y; /* target Y in 16.16 units; integer part is tile row * 64 + 32 */
    Fixed1616 z; /* target height in 16.16 units; terrain result or caster fallback height minus 48 world units */
    s32 rx;
    s32 ry;
    s32 rz;
} ProjectileTargetTransform;

/* Stack integer world point projected by func_800248F8; the renderer fills it from the projectile position. */
typedef struct {
    s16 x; /* integer world X supplied to the projection routine */
    s16 y; /* integer world Y supplied to the projection routine */
    s16 z; /* integer world height; the renderer projects endpoints 28 units apart */
} SVECTOR;

/* Textured projectile quad allocated at the frame draw context packet cursor by func_800248F8.
 * Each packet occupies 0x28 bytes and is linked into the depth ordering table. */
typedef struct {
    u32 tag; /* DMA link/count word; low 24 bits link the ordering-table chain */
    u8 r0; /* red modulation byte, initialized to neutral 0x80 */
    u8 g0; /* green modulation byte, initialized to neutral 0x80 */
    u8 b0; /* blue modulation byte, initialized to neutral 0x80 */
    u8 code; /* GPU textured-quad primitive command byte */
    s16 x0; /* vertex 0 screen X, in pixels */
    s16 y0; /* vertex 0 screen Y, in pixels */
    u8 u0; /* vertex 0 texture U, in texels */
    u8 v0; /* vertex 0 texture V, in texels */
    u16 clut; /* GPU texture palette identifier */
    s16 x1; /* vertex 1 screen X, in pixels */
    s16 y1; /* vertex 1 screen Y, in pixels */
    u8 u1; /* vertex 1 texture U, in texels */
    u8 v1; /* vertex 1 texture V, in texels */
    u16 tpage; /* GPU texture-page and blend-mode bits */
    s16 x2; /* vertex 2 screen X, in pixels */
    s16 y2; /* vertex 2 screen Y, in pixels */
    u8 u2; /* vertex 2 texture U, in texels */
    u8 v2; /* vertex 2 texture V, in texels */
    u16 pad2;
    s16 x3; /* vertex 3 screen X, in pixels */
    s16 y3; /* vertex 3 screen Y, in pixels */
    u8 u3; /* vertex 3 texture U, in texels */
    u8 v3; /* vertex 3 texture V, in texels */
    u16 pad3;
} POLY_FT4;

/* Partial frame draw-context view selected through GameWork.draw_buffer; init_frame_buffers owns the backing contexts.
 * func_800248F8 allocates projectile quads through its packet cursor. */
typedef struct {
    u8 pad0[0xB0];
    u32 ot[0x208]; /* ordering-table words; projectile packets use depth-indexed entries beginning at +0xB0 */
    u8 pad8D0[0x8D0 - 0x8D0];
    u8 *next_prim; /* next free GPU packet byte, advanced by 0x28 per projectile quad */
} RenderContext;

/* Projectile render-work slice within the pooled object; func_800248F8 advances its texture frame. */
typedef struct {
    u8 pad0[0x52];
    s16 frame; /* texture frame index; incremented each draw and wrapped from 12 to 8 */
} RenderRecord;

/* Two-byte flags immediately before particle work, initialized by allocate_list_node.
 * update_timed_sprite_effect addresses this prefix with [-1] on completion. */
typedef struct EffectStatusPrefix {
    u16 unk_00; /* object flags; bit 0x8000 requests retirement */
} EffectStatusPrefix;
/* Parent-projectile activity word viewed by a spawned particle; no separate allocation.
 * func_80024020 consumes the bit written by update_timed_sprite_effect before cleanup. */
typedef struct ProjectileOwnerFlags {
    u8 pad_00[0x10];
    s32 unk_10; /* bit 0x8000 reports a child update and defers parent cleanup for one update */
} ProjectileOwnerFlags;
#endif
