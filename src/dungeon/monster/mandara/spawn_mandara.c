/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/sprite_frame_state.h"
typedef struct { u8 pad[6]; u16 count; } CountView;
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80FC9000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FC9000_0;   /* obj in func_801588A4 */

typedef struct S_80FC9000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FC9000_1;   /* work in func_801588A4 */

typedef struct S_80FC9000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FC9000_2;   /* pin_part_a in func_801588A4 */

typedef struct S_80FC9000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    u16 unk_AE;
} S_80FC9000_4;   /* pin_actor in func_801588A4 */

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void func_800673A0(s16 *, s32, s32);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern s32 generate_random_value(void);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern u8 D_80158B40[];
extern u8 D_80158F6C[];
extern u8 D_8015D258[];
extern u8 D_8015D298[];

void *func_801588A4(s32 input_value, s16 part_b_value, s16 part_b_value2, s16 part_a_value)

;

/* Creates a Mandara actor, initializes status and tile placement, and prepares sprite image rectangles. */
void *func_801588A4(s32 input_value, s16 part_b_value, s16 part_b_value2, s16 part_a_value)
{
    void *work;
    void *obj;
    s32 call_id;
    ObjectNodeHeader *call_target;
    SpriteFrameState *part_b;
    void *part_a;
    s16 saved_arg0;
    s32 kind;
    s32 left;
    s32 right;
    s32 index;
    s32 count;
    u16 actor_value;
    s32 double_index;
    s16 values[4];
    u8 *entry;
    s16 pin_arg1;
    s16 pin_arg3;
    void *pin_part_a;
    void *pin_actor;

    work = 0;
    call_id = 0x112;
    pin_arg1 = part_b_value;
    pin_arg3 = part_a_value;
    call_target = &scene_object_list_anchor;
    obj = allocate_list_node(call_id, call_target);
    saved_arg0 = (s16)input_value;
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80FC9000_0 *)obj)->unk_10 = D_80158B40;
        ((S_80FC9000_1 *)work)->unk_13 = 0x27;
        register_node(obj, project_sprite_chain);

        pin_part_a = ((S_80FC9000_0 *)obj)->unk_08;
        ((S_80FC9000_2 *)pin_part_a)->unk_0A = pin_arg3;
        part_b = ((S_80FC9000_0 *)obj)->unk_0C;
        kind = input_value & 3;
        part_b->unk_25 = part_b_value2;
        pin_actor = work;
        part_b->frameTable = D_8015D258;
        part_b->unk_24 = pin_arg1;
        if (kind == 1) {
            left = ((S_80FC9000_1 *)work)->unk_14 | 0x6000;
            right = ((S_80FC9000_1 *)work)->unk_1C | 0x6000;
            ((S_80FC9000_1 *)work)->unk_14 = left;
            ((S_80FC9000_1 *)work)->unk_1C = right;
        } else if (kind >= 2) {
            left = ((S_80FC9000_1 *)work)->unk_14 | 0x2000;
            right = ((S_80FC9000_1 *)work)->unk_1C | 0x2000;
            ((S_80FC9000_1 *)work)->unk_14 = left;
            ((S_80FC9000_1 *)work)->unk_1C = right;
        } else {
            if (((input_value = (s16)(input_value & ~3)) << 16) == 0) {
                if (!(((S_80FC9000_1 *)work)->unk_14 & 0x200)) {
                    if (generate_random_value() & 1) {
                        ((S_80FC9000_1 *)work)->unk_1C |= 0x200;
                        set_or_clear_actor_status_slot(work, 1,
                                      (generate_random_value() & 0x3F) |
                                      0x20);
                        part_b->frameTable = D_8015D298;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, pin_part_a, part_b, saved_arg0);
        index = 0;
        actor_value = part_b->clut;
        ((S_80FC9000_4 *)pin_actor)->unk_9A = 0xFF;
        ((S_80FC9000_4 *)pin_actor)->unk_9C = -1;
        ((S_80FC9000_4 *)pin_actor)->unk_8C = D_80158F6C;
        ((S_80FC9000_4 *)pin_actor)->unk_AE = actor_value;

        entry = *(u8 * *)&part_b->source;
        do {
            double_index = index << 1;
            if (*entry & 0x20) {
                entry += 12;
                index += 1;
            } else {
                break;
            }
        } while (1);
        count = ((CountView *)(*(u8 * *)&part_b->source + (double_index + index) * 4))->count >> 6;
        values[0] = 0;
        values[1] = count;
        values[2] = 0x100;
        values[3] = 1;
        func_800673A0(values, 0, count - 1);

        values[2] = 0x10;
        values[0] = 0x30;
        values[1] -= 1;
        do {
            func_800673A0(values, values[0] - 0x30, values[1]);
            values[0] += 0x40;
        } while (values[0] < 0x100);

        try_move_actor_to_valid_position(pin_actor, pin_part_a, part_b, work);
    }
    return work;
}
