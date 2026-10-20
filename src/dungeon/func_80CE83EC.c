#include "dungeon/monster/troll/troll_flash_effects.h"

/* Creates a render object at the supplied position with an optional owner offset. */
void create_tracked_attachment_sprite(void *attachment, T_80171BEC_S_80171BEC_3 *base_position)
{
    T_80171BEC_Offset3 offset;
    void *object;
    T_80171BEC_S_80171BEC_1 *render;
    void *owner;
    T_80171BEC_S_80171BEC_2 *position;

    object = allocate_list_node(0x212, ((s32 *)&D_80083498.next));
    if (object != 0) {
        ((T_80171BEC_S_80171BEC_0 *)object)->unk_40 = attachment;
        ((T_80171BEC_S_80171BEC_0 *)object)->unk_10 = &update_tracked_attachment_sprite;
        register_node(object, project_sprite_chain);

        render = ((T_80171BEC_S_80171BEC_0 *)object)->unk_0C;
        render->unk_10 = 0x20;
        render->unk_06 = 8;
        render->unk_14 |= 0xC;

        position = ((T_80171BEC_S_80171BEC_0 *)object)->unk_08;
        position->unk_00.at00.v = base_position->unk_00;
        position->unk_04.at00.v = base_position->unk_04;
        position->unk_08.at00.v = base_position->unk_08;

        owner = ((T_80171BEC_S_80171BEC_4_pre *)attachment)[-1].unk_00;
        if (resolve_record_orientation_or_fallback(((T_80171BEC_S_80171BEC_5 *)owner)->unk_08, owner, &offset, 0) != 0) {
            position->unk_00.at02.v += offset.x;
            position->unk_04.at02.v += offset.y;
            position->unk_08.at02.v += offset.z;
        }

        render = ((T_80171BEC_S_80171BEC_0 *)object)->unk_0C;
        render->unk_1E = 0x800;
        render->unk_1C = 0x800;
        render->unk_0E = 0x80;
        render->unk_0D = 0x80;
        render->unk_0C = 0x80;
        *(T_80171BEC_Packed3 *)((u8 *)object + 0x44) = D_80175EE8;
        render->unk_08 = (u8 *)object + 0x44;
    }
}

