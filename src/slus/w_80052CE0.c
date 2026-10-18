#include "slus/jtbl_80052CE0.h"

void func_80052CE0(S_52CE0 *anim, S_52CE0_Pos *position, S_52CE0_Ent *entity)
{
    S_52CE0_Rect source_rect;
    s16 row_offset;
    s32 state_index;

    anim->timer++;
    state_index = anim->state;
    switch (state_index) {
    case 0:
        if (anim->unk6 == 1) {
            anim->timer = 0;
            anim->unk6 = 2;
            anim->state++;
            entity->flags &= 0xFF7F;
            position->x = anim->unkA << 16;
            position->y = anim->unkC << 16;
            draw_shaded_horizontal_line(anim->unk10, anim->unkC + 15, anim->unkE, 0);
        }
        break;
    case 1:
        anim->unk10 += 6;
        if (anim->timer >= 16) {
            anim->timer = 0;
            anim->state++;
        }
        draw_shaded_horizontal_line(anim->unk10, anim->unkC + 15, anim->unkE, 0);
        break;
    case 2:
        anim->unk10 += 6;
        anim->unkA += 8;
        if (anim->timer >= 0x30) {
            anim->timer = 0;
            anim->state++;
        }
        position->x = anim->unkA << 16;
        draw_shaded_horizontal_line(anim->unk10, anim->unkC + 15, anim->unkE, 0);
        break;
    case 3:
        if (anim->timer >= 0x50) {
            anim->timer = 0;
            anim->state++;
        }
        draw_shaded_horizontal_line(anim->unk10, anim->unkC + 15, anim->unkE, 0);
        break;
    case 4:
        anim->timer++;
        if (anim->timer >= 2) {
            anim->timer = 0;
            anim->unk4++;
            source_rect.x = 0x3C0;
            source_rect.y = (anim->unk8 + 1) * 16 - anim->unk4;
            source_rect.w = 0x3F;
            source_rect.h = 1;
            MoveImage(&source_rect, 0x380, (anim->unk8 + 1) * 16 - anim->unk4);
            if (anim->unk4 < 16) {
                row_offset = anim->unk4 - 15;
                draw_shaded_horizontal_line(anim->unk10, anim->unkC - row_offset, anim->unkE,
                              anim->timer + anim->unk4 * 2);
            } else {
                anim->timer = 0;
                anim->unk4 = 0;
                anim->state++;
            }
        } else {
            row_offset = anim->unk4 - 15;
            draw_shaded_horizontal_line(anim->unk10, anim->unkC - row_offset, anim->unkE,
                          anim->timer + anim->unk4 * 2);
        }
        break;
    case 5:
        if (anim->timer >= 0x50) {
            anim->timer = 0;
            anim->state++;
        }
        break;
    case 6:
        anim->unkA -= 8;
        if (anim->timer >= 0x30) {
            anim->timer = 0;
            anim->state++;
        }
        position->x = anim->unkA << 16;
        break;
    case 7:
        entity->flags |= 0x80;
        anim->state = 0;
        anim->timer = 0;
        anim->unk4 = 0;
        anim->unk6 = 0;
        anim->unkA = 0;
        anim->unkC = 0;
        anim->unkE = 0;
        anim->unk10 = 0;
        break;
    }
}
