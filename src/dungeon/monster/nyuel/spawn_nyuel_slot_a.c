#include "modules/dungeon_ovl_bdb094.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_bdb094.h"

/* Creates a Nyuel actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
Func80BBB094PartC *func_8014C894(s32 spawn_flags, s16 attr_a, s32 attr_b, s32 attr_c)
{
    Func80BBB094PartC *result = 0;
    unsigned long slot1;
    s16 arg2Reg;
    register Func80BBB094PartC *resultAlias;
    Func80BBB094Object *obj;
    Func80BBB094PartA *partA;
    s16 savedArg0;
    SpriteFrameState *partB;
    s32 mode;
    s32 flag;
    s32 randomTest;
    slot1 = (unsigned long)attr_c;
    arg2Reg = attr_b;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    savedArg0 = spawn_flags;
    if (obj != 0) {
        result = &obj->unk20;
        result->unk13 = 14;
        register_node(obj, project_sprite_chain);

        partA = obj->unk8;
        partA->unkA = (s32)slot1;
        slot1 = (unsigned long)obj->unkC;
        partB = (Func80BBB094PartB *)slot1;
        partB->unk_24 = attr_a;
        partB->unk_25 = arg2Reg;
        resultAlias = result;

        mode = spawn_flags & 3;
        if (mode == 1) {
            result->unk8C = D_8014CE9C;
            result->unk14 |= 0x6000;
            result->unk1C |= 0x6000;
            partB->frameTable = D_80150ED8;
        } else if (mode >= 2) {
            result->unk8C = D_8014CE9C;
            result->unk14 |= 0x2000;
            result->unk1C |= 0x2000;
            partB->frameTable = D_80150ED8;
        } else {
            spawn_flags = (s16)(spawn_flags & -4);
            if (spawn_flags == 0) {
                flag = result->unk14 & 0x200;
                if (flag == 0) {
                    randomTest = generate_random_value() & 1;
                    if (randomTest != 0) {
                        s32 random = generate_random_value();

                        set_or_clear_actor_status_slot(result, 1, (random & 0x3F) | 0x20);
                        partB->frameTable = D_80150F00;
                    }
                } else {
                }
                resultAlias->unk8C = (void *)D_8014CE9C;
                partB->frameTable = D_80150ED8;
            } else {
                result->unk8C = (void *)D_8014CE9C;
                partB->frameTable = D_80150ED8;
            }
        }

        obj->unk10 = D_8014CA98;
        initialize_actor_sprite_and_animation(obj, partA, partB, savedArg0);

        resultAlias->unk9A = 0xFF;
        resultAlias->unk9C = -1;
        try_move_actor_to_valid_position(resultAlias, partA, partB, result);
    }
    return result;
}
