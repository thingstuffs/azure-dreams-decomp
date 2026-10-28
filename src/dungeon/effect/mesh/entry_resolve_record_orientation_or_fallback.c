#include "common.h"
#include "dungeon/effect/mesh.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "engine/scene.h"

typedef struct S_81976850_0 {
    void * unk_00;
    void * unk_04;
    void * unk_08;
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
    union { s16 s; u16 u; } unk_0E;   /* accessed as both */
    u16 unk_10;
} S_81976850_0;   /* arg0 in func_81976850 */

typedef struct S_81976850_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_81976850_1;   /* source in func_81976850 */


   /* coords in func_81976850 */

typedef struct S_81976850_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_81976850_4;   /* arg2 in func_81976850 */

typedef struct S_81976850_5 {
    s32 unk_00;
    s32 unk_04;
} S_81976850_5;   /* target in func_81976850 */

typedef struct S_81976850_7 {
    void * unk_00;
} S_81976850_7;   /* (void *)index in func_81976850 */

typedef struct S_81976850_8 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_81976850_8;   /* ((S_81976850_0 *)arg0)->unk_00 in func_81976850 */

typedef struct S_81976850_9 {
    u16 unk_00;
} S_81976850_9;   /* ((S_81976850_0 *)arg0)->unk_08 in func_81976850 */

typedef struct S_81976850_10 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81976850_10;   /* ((S_81976850_0 *)arg0)->unk_04 in func_81976850 */


typedef struct Vec16 {
    s16 x;
    s16 y;
    s16 z;
} Vec16;

extern u8 *actor_direction_sprites;

extern void register_node(void *, void *);
extern s32 rsin(s32);

/* Follow the source, then brighten and move to the target over ten frames. */
void follow_source_then_seek_target(void *effect, ObjectPosition *motion, void *visual)
{
    Vec16 delta;
    void *source;
    MovingPosition *source_pos;
    S_81976850_5 *target_pos;
    ActorRecord *scene;
    void *object;
    s32 z_offset;
    s32 table_entry;
    s16 state;
    s16 frames_left;
    u16 source_z;
    u8 brightness;

    state = ((S_81976850_0 *)effect)->unk_0C.s;
    switch (state) {
    case 0:
        object = (u8 *)effect - 0x20;
        register_node(object, project_sprite_chain);
        ((S_81976850_0 *)effect)->unk_0C.u++;
        /* Fall through to follow the source on the initialization frame. */

    case 1:
        source = ((S_81976850_8 *)(((S_81976850_0 *)effect)->unk_00))->unk_0C;
        if ((((S_81976850_1 *)source)->unk_14 & 0x8000) ||
            resolve_record_orientation_or_fallback(((S_81976850_1 *)source)->unk_08, source, &delta, 0)) {
            source_pos = ((S_81976850_8 *)(((S_81976850_0 *)effect)->unk_00))->unk_08;
            motion->x.w.i = source_pos->x;
            motion->y.w.i = source_pos->y;
            source_z = source_pos->z;
            motion->z.w.i = source_z;

            if (!(((S_81976850_1 *)source)->unk_14 & 0x8000)) {
                *(u16 *)&motion->x.w.i += delta.x;
                *(u16 *)&motion->y.w.i += delta.y;
                *(u16 *)&motion->z.w.i += delta.z;
            } else {
                motion->z.w.i = source_z - 0x20;
            }
        }

        if (((S_81976850_9 *)(((S_81976850_0 *)effect)->unk_08))->unk_00 & 0x80) {
            ((S_81976850_0 *)effect)->unk_0E.s = 10;
            ((S_81976850_0 *)effect)->unk_0C.u++;
        }
        break;

    case 2:
        brightness = ((S_81976850_4 *)visual)->unk_0E + 8;
        ((S_81976850_4 *)visual)->unk_0E = brightness;
        ((S_81976850_4 *)visual)->unk_0D = brightness;
        ((S_81976850_4 *)visual)->unk_0C = brightness;

        target_pos = ((S_81976850_10 *)(((S_81976850_0 *)effect)->unk_04))->unk_08;
        motion->velocity_x = target_pos->unk_00;
        (motion->velocity_y) = target_pos->unk_04;

        scene = primary_actor_record;
        motion->velocity_z =
            (scene->ground_height - 0x50) << 16;

        table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + scene->facing + 0x100) >> 7) & 0x1C;
        table_entry += (s32)actor_direction_sprites;
        if (resolve_record_orientation_or_fallback(
                ((S_81976850_7 *)((void *)table_entry))->unk_00,
                &reference_tile_object,
                &delta,
                0) != 0) {
            motion->velocity_x += delta.x << 16;
            motion->velocity_y += delta.y << 16;
            motion->velocity_z += delta.z << 16;
        }

        motion->x.v +=
            (motion->velocity_x - motion->x.v) /
            ((S_81976850_0 *)effect)->unk_0E.s;

        motion->y.v +=
            (motion->velocity_y - motion->y.v) /
            ((S_81976850_0 *)effect)->unk_0E.s;

        z_offset = rsin(((S_81976850_0 *)effect)->unk_0E.s * 0xAA) << 7;
        motion->z.v +=
            (motion->velocity_z - motion->z.v) /
            ((S_81976850_0 *)effect)->unk_0E.s - z_offset;

        frames_left = ((S_81976850_0 *)effect)->unk_0E.u - 1;
        ((S_81976850_0 *)effect)->unk_0E.s = frames_left;
        if (frames_left <= 0) {
            motion->x.v = motion->velocity_x;
            motion->y.v = motion->velocity_y;
            motion->z.v = motion->velocity_z;
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }

        break;
    default:
        break;
    }
    ((S_81976850_0 *)effect)->unk_10++;
    ((S_81976850_4 *)visual)->unk_1A += 0x300;
}
