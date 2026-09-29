#include "common.h"

typedef struct S_52CE0_Rect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} S_52CE0_Rect;

typedef struct S_52CE0 {
    s16 state;
    s16 timer;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
} S_52CE0;

typedef struct S_52CE0_Pos {
    s32 x;
    s32 y;
} S_52CE0_Pos;

typedef struct S_52CE0_Ent {
    u8 pad0[0x14];
    u16 flags;
} S_52CE0_Ent;

extern void func_80052774(s16 a0, s16 a1, s16 a2, s16 a3);
extern void MoveImage(S_52CE0_Rect *rect, s32 x, s32 y);

/* Advance the entity animation, moving its position and copying image rows in VRAM. */
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
            func_80052774(anim->unk10, anim->unkC + 15, anim->unkE, 0);
        }
        break;
    case 1:
        anim->unk10 += 6;
        if (anim->timer >= 16) {
            anim->timer = 0;
            anim->state++;
        }
        func_80052774(anim->unk10, anim->unkC + 15, anim->unkE, 0);
        break;
    case 2:
        anim->unk10 += 6;
        anim->unkA += 8;
        if (anim->timer >= 0x30) {
            anim->timer = 0;
            anim->state++;
        }
        position->x = anim->unkA << 16;
        func_80052774(anim->unk10, anim->unkC + 15, anim->unkE, 0);
        break;
    case 3:
        if (anim->timer >= 0x50) {
            anim->timer = 0;
            anim->state++;
        }
        func_80052774(anim->unk10, anim->unkC + 15, anim->unkE, 0);
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
                func_80052774(anim->unk10, anim->unkC - row_offset, anim->unkE,
                              anim->timer + anim->unk4 * 2);
            } else {
                anim->timer = 0;
                anim->unk4 = 0;
                anim->state++;
            }
        } else {
            row_offset = anim->unk4 - 15;
            func_80052774(anim->unk10, anim->unkC - row_offset, anim->unkE,
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
