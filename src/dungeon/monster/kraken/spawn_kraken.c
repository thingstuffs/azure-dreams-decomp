#include "modules/dungeon_ovl_edb06c.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_edb06c.h"

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of spawn_flags select (or the random 0x20-mask variant), and run the two setup calls. */
void *spawn_kraken(s16 spawn_flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    void *work;
    s8 saved_kind_id;
    s8 saved_variant;
    void *obj;
    S_8016A86C_2 *part_a;
    SpriteFrameState *part_b;
    S_8016A86C_4 *actor;
    s32 left;
    s32 right;
    s16 saved_spawn_flags;
    void *current;
    S_8016A86C_8 *base;
    void *child_obj;
    S_8016A86C_7 *elem;
    s32 count;
    register s32 i;
    u32 elem_offset;
    s32 child_arg;
    u16 flags;
    u16 child_flags;
    u16 elem_flags;

    work = 0;
    saved_variant = variant;
    saved_spawn_flags = spawn_flags;
    obj = allocate_list_node(0x112, (saved_kind_id = kind_id, ((u8 *)(&D_80083498))));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8016A86C_0 *)obj)->unk_10 = func_8016AB64;
        ((S_8016A86C_1 *)work)->unk_13 = 0x21;
        register_node(obj, project_sprite_chain);
        actor = work;

        part_a = ((S_8016A86C_0 *)obj)->unk_08;
        part_a->unk_0A = spawn_value;
        part_b = ((S_8016A86C_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->frameTable = D_8016E18C;
        part_b->unk_24 = saved_kind_id;
        part_b->unk_25 = saved_variant;

        if (kind == 1) {
            left = ((S_8016A86C_1 *)work)->unk_14 | 0x6000;
            right = ((S_8016A86C_1 *)work)->unk_1C | 0x6000;
            ((S_8016A86C_1 *)work)->unk_14 = left;
            ((S_8016A86C_1 *)work)->unk_1C = right;
        } else if (kind >= 2) {
            left = ((S_8016A86C_1 *)work)->unk_14 | 0x2000;
            right = ((S_8016A86C_1 *)work)->unk_1C | 0x2000;
            ((S_8016A86C_1 *)work)->unk_14 = left;
            ((S_8016A86C_1 *)work)->unk_1C = right;
        } else {
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(((S_8016A86C_1 *)work)->unk_14 & 0x200)) {
                    left = generate_random_value();
                    if (left & 1) {
                        ((S_8016A86C_1 *)work)->unk_1C |= 0x200;
                        right = generate_random_value();
                        set_or_clear_actor_status_slot(work, 1, (right & 0x3F) | 0x20);
                        part_b->frameTable = D_8016E1CC;
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(obj, part_a, part_b, saved_spawn_flags);

        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = func_8016B1A4;
        ((S_8016A86C_1 *)work)->unk_1C |= 0x00040000;
        actor->unk_92 = -16;
        flags = actor->unk_98;
        actor->unk_A8 = 0;
        actor->unk_9E = 1;
        actor->unk_98 = flags | 0x4000;

        current = actor;
        count = 0;
        do {
            child_obj = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
            ((S_8016A86C_5 *)current)->unk_A4 = child_obj;
            if (child_obj != 0) {
                void *child;

                child = (u8 *)child_obj + 0x20;

                ((S_8016A86C_6 *)child)->unk_02 = 1;
                i = 0;
                base = current;
                elem_offset = 8;
                while (i < ((S_8016A86C_6 *)child)->unk_02) {
                    elem = (u8 *)child + elem_offset;
                    child_flags = ((S_8016A86C_6 *)child)->unk_04;
                    ((S_8016A86C_6 *)child)->unk_04 = child_flags | 0x8000;
                    child_arg = part_b->unk_28;
                    elem_flags = elem->unk_14;
                    elem->unk_10 = 96;
                    elem->unk_28 = child_arg;
                    elem->unk_14 = elem_flags | 0xC;

                    elem->unk_12 = *(s16 *)&part_b->clut - 128;
                    elem->unk_0C = ((u32)(0x00C0C0C0));
                    ((S_8016A86C_9 *)(base->unk_A4))->unk_10 = process_effect_block_entries;

                    select_sprite_entry(elem, 39, 0);
                    elem_offset += 48;
                    i++;
                    ((S_8016A86C_6 *)child)->unk_06 = 0;
                    texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(part_b, draw_sprite_effect_quads, 0);
                    ((S_8016A86C_6 *)child)->unk_98 = (u8 *)obj + 30;
                }
            }
            current = (u8 *)current + 4;
            count++;
        } while (count < actor->unk_9E);
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
