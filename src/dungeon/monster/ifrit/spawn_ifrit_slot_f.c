#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

#include "shared/entity.h"

typedef struct S_FUNC_80A23000_BODY_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_FUNC_80A23000_BODY_0;   /* object in queue_projected_point_primitives_2 */

typedef struct S_FUNC_80A23000_BODY_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_FUNC_80A23000_BODY_1;   /* work in queue_projected_point_primitives_2 */

typedef struct S_FUNC_80A23000_BODY_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_FUNC_80A23000_BODY_2;   /* part_a in queue_projected_point_primitives_2 */

typedef struct S_FUNC_80A23000_BODY_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_FUNC_80A23000_BODY_3;   /* part_b in queue_projected_point_primitives_2 */

typedef struct S_FUNC_80A23000_BODY_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_FUNC_80A23000_BODY_4;   /* actor in queue_projected_point_primitives_2 */

extern void *allocate_list_node();
extern void register_node();
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();

extern u8 D_8016AA58[];
extern u8 D_8016E820[];
extern u8 D_8016E860[];
void func_8016AE84(void *controller, void *context, void *entity, ActorRecord *actor_state);

/* Creates an Ifrit actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *queue_projected_point_primitives_2(s16 mask, s16 value_24_input, s16 value_25_input, s16 value_0A_input)
{
    s32 kind;
    void *object;
    S_FUNC_80A23000_BODY_2 *part_a;
    SpriteFrameState *part_b;
    S_FUNC_80A23000_BODY_1 *work;
    S_FUNC_80A23000_BODY_4 *actor;
    s32 value_14;
    s32 value_1C;
    s16 value_0A;

    work = 0;
    value_0A = value_0A_input;
    object = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (object != 0) {
        work = (u8 *)object + 0x20;
        ((S_FUNC_80A23000_BODY_0 *)object)->unk_10 = D_8016AA58;
        work->unk_13 = MONSTER_IFRIT;
        register_node(object, project_sprite_chain);

        part_a = ((S_FUNC_80A23000_BODY_0 *)object)->unk_08;
        part_a->unk_0A = value_0A;
        part_b = ((S_FUNC_80A23000_BODY_0 *)object)->unk_0C;
        kind = mask & 3;
        part_b->unk_25 = value_25_input;
        actor = work;
        part_b->frameTable = D_8016E820;
        part_b->unk_24 = value_24_input;

        if (kind == 1) {
            value_14 = work->unk_14 | 0x6000;
            value_1C = work->unk_1C | 0x6000;
            work->unk_14 = value_14;
            work->unk_1C = value_1C;
        } else if (kind >= 2) {
            value_14 = work->unk_14 | 0x2000;
            value_1C = work->unk_1C | 0x2000;
            work->unk_14 = value_14;
            work->unk_1C = value_1C;
        } else if (((mask & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                value_14 = generate_random_value();
                if (value_14 & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_8016E860;
                }
            }
        }
        initialize_actor_sprite_and_animation(((void *)(object)), part_a, part_b, mask);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &func_8016AE84;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
