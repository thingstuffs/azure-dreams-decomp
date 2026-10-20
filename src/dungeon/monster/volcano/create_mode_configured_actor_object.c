#include "dungeon/monster/volcano/create_mode_configured_actor_object.h"
#include "dungeon/monster/volcano/create_mode_configured_actor_object.h"

void *create_mode_configured_actor_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    void *result = NULL;
    void *root;
    void *position;
    s16 held_flags;
    s32 kind;
    s8 saved_a;
    s16 saved_c;
    s8 saved_b;

    {
        void *arg3_part;
        void *arg2_work;

        saved_a = attr_a;
        saved_c = attr_c;
        saved_b = attr_b;
        root = allocate_list_node(0x112, &D_80083498);
        held_flags = spawn_flags;
        if (root != NULL) {
            result = (u8 *)root + 0x20;
            ((S_8016A800_0 *)result)->unk_13 = 0x1C;
            register_node(root, project_sprite_chain);

            position = ((S_8016A800_1 *)root)->unk_08;
            kind = spawn_flags & 3;
            ((S_8016A800_2 *)position)->unk_0A = saved_c;
            arg3_part = ((S_8016A800_1 *)root)->unk_0C;
            ((S_8016A800_3 *)arg3_part)->unk_24 = saved_a;
            ((S_8016A800_3 *)arg3_part)->unk_25 = saved_b;
            arg2_work = result;

            if (kind == 1) {
                ((S_8016A800_0 *)result)->unk_8C = func_8016AE5C;
                ((S_8016A800_0 *)result)->unk_14 |= 0x6000;
                ((S_8016A800_0 *)result)->unk_1C |= 0x6000;
                ((S_8016A800_3 *)arg3_part)->unk_2C = D_8016E510;
            } else {
                if (kind >= 2) {
                    ((S_8016A800_0 *)result)->unk_8C = func_8016AE5C;
                    ((S_8016A800_0 *)result)->unk_14 |= 0x2000;
                    ((S_8016A800_0 *)result)->unk_1C |= 0x2000;
                    ((S_8016A800_3 *)arg3_part)->unk_2C = D_8016E510;
                } else {
                    if ((s16)(spawn_flags & ~3) == 0) {
                        if (!(((S_8016A800_0 *)result)->unk_14 & 0x200)) {
                            spawn_flags = generate_random_value();
                            if (spawn_flags & 1) {
                                set_or_clear_actor_status_slot(result, 1, (generate_random_value() & 0x3F) | 0x20);
                                ((S_8016A800_3 *)arg3_part)->unk_2C = D_8016E538;
                            }
                        }
                        ((S_8016A800_4 *)((void *)arg2_work))->unk_8C = func_8016AE5C;
                        ((S_8016A800_3 *)arg3_part)->unk_2C = D_8016E510;
                    } else {
                        ((S_8016A800_0 *)result)->unk_8C = func_8016AE5C;
                        ((S_8016A800_3 *)arg3_part)->unk_2C = D_8016E510;
                    }

                }
            }
            ((S_8016A800_1 *)root)->unk_10 = func_8016AA58;
            initialize_actor_sprite_and_animation(root, position, arg3_part, (s16)held_flags);
            ((S_8016A800_4 *)((void *)arg2_work))->unk_9A = 0xFF;
            ((S_8016A800_4 *)((void *)arg2_work))->unk_9C = -1;
            try_move_actor_to_valid_position(arg2_work, position, arg3_part, result);
        }
    }
    return result;
}
