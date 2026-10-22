#include "common.h"
#include "shared/monster_ids.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"



typedef struct S_80170890_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80170890_1;   /* work in create_flagged_dungeon_actor_object */

typedef struct S_80170890_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x13];
    s16 unk_B0;
} S_80170890_4;   /* actor in create_flagged_dungeon_actor_object */

typedef struct S_80170890_5 {
    u16 unk_00;
} S_80170890_5;   /* (u8 *)(((index + count) << 2) + (u32)table) + 6 in create_flagged_dungeon_actor_object */

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s32);
extern void func_800672D8(void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern s32 D_80045340;
extern u8 D_80170AE8[];
extern u8 D_80176460[];
#include "dungeon/monster/cyclone.h"
extern u8 D_80171094[];
extern u8 D_801764B8[];

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
/* Creates Cyclone with frames at D_80176460, loads a palette row from D_801764B8, and attempts tile
 * placement. */
void *create_flagged_dungeon_actor_object(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    ObjectNodeHeader *obj;
    void *work = 0;
    ObjectPosition *part_a;
    SpriteFrameState *part_b;
    S_80170890_4 *actor;
    s32 kind;
    s32 left;
    s32 right;
    s8 saved_kind_id = kind_id;
    s16 saved_spawn = spawn_value;
    s8 saved_variant = variant;

    obj = allocate_list_node(274, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->unk_10 = D_80170AE8;
        ((S_80170890_1 *)work)->unk_13 = MONSTER_CYCLONE;
        register_node(obj, &D_80045340);

        part_a = obj->position;
        part_a->z.w.i = saved_spawn;
        part_b = obj->sprite;
        kind = flags & 3;
        part_b->unk_25 = saved_variant;
        part_b->unk_24 = saved_kind_id;
        actor = work;
        part_b->frameTable = D_80176460;

        if (kind == 1) {
            left = ((S_80170890_1 *)work)->unk_14 | 0x6000;
            right = ((S_80170890_1 *)work)->unk_1C | 0x6000;
            ((S_80170890_1 *)work)->unk_14 = left;
            ((S_80170890_1 *)work)->unk_1C = right;
        } else if (kind >= 2) {
            left = ((S_80170890_1 *)work)->unk_14 | 0x2000;
            right = ((S_80170890_1 *)work)->unk_1C | 0x2000;
            ((S_80170890_1 *)work)->unk_14 = left;
            ((S_80170890_1 *)work)->unk_1C = right;
        } else {
            if (((flags & ~3) << 16) == 0) {
                if (!(((S_80170890_1 *)work)->unk_14 & 0x200)) {
                    if (generate_random_value() & 1) {
                        set_or_clear_actor_status_slot(work, 1,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = cyclone_direction_frames;
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(obj, part_a, part_b, (s16)flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = D_80171094;
        ((S_80170890_1 *)work)->unk_1C |= 0x00040000;
        actor->unk_92 = -32;

        {
            u8 *cursor = (*(u8 ** *)&part_b->source);
            s32 count = 0;
            s32 index;
            u16 packet[4];
            u8 *table;
            s16 value;

            while (1) {
                index = count << 1;
                if (!(*cursor & 0x20)) {
                    break;
                }
                cursor += 12;
                count += 1;
            }
            table = (*(u8 ** *)&part_b->source);
            value = (((S_80170890_5 *)((u8 *)(((index + count) << 2) + (u32)table) + 6))->unk_00 >> 6) - 1;
            packet[1] = value;
            actor->unk_B0 = value << 6;
            packet[2] = 256;
            packet[0] = 0;
            packet[3] = 1;
            func_800672D8(packet, D_801764B8);
            try_move_actor_to_valid_position(actor, part_a, part_b, work);
        }
    }
    return work;
}
