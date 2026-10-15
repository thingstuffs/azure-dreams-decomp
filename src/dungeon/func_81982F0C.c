#include "modules/dungeon_ovl_19a332c.h"

void *func_8002470C(s16 x, s16 y, s16 z, s16 heading, s16 count)
{
    ovl_19a332c_81982F0C_Object *particle = 0;
    s16 base_angle = (s16)heading;
    s32 remaining = count;

    while (remaining > 0) {
        particle = (ovl_19a332c_81982F0C_Object *)func_8003FC64(0x202);
        if (particle != 0) {
            s32 angle_offset;
            s32 move_angle;
            ovl_19a332c_81982F0C_S_8002470C_0 *motion;
            ovl_19a332c_81982F0C_S_8002470C_1 *sprite;
            u8 *extra;

            particle->callback = func_800245F8;
            func_8004491C(particle, func_80045340);
            motion = particle->dst;
            motion->unk_02 = (s16)x;
            motion->unk_06 = (s16)y;
            motion->unk_0A = (s16)(z + 0x10);

            angle_offset = (s16)((rand() & 0x7FF) - 0x400);
            angle_offset -= 0x800;
            move_angle = base_angle + angle_offset;
            motion->unk_0C = func_80064584(move_angle) << 6;
            motion->unk_10 = func_800644B8(move_angle) << 6;
            motion->unk_14 =
                (rand() & 0x1FFFF) - 0x10000;

            sprite = particle->sprite;
            sprite->unk_1E = 0x1000;
            sprite->unk_1C = 0x1000;
            sprite->unk_0C = 0x808080;
            func_8003DB94(sprite, D_80026AB0, rand() & 7);

            extra = (u8 *)particle + 0x20;
            ((ovl_19a332c_81982F0C_S_8002470C_2 *)extra)->unk_30 = (s16)((rand() & 7) + 0x10);
            ((ovl_19a332c_81982F0C_S_8002470C_2 *)extra)->unk_36 = (s16)heading;
        }
        remaining--;
    }
    return particle;
}
