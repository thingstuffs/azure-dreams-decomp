/* Relink of matched dungeon/func_80C429A0; every changed retail word is a paired relocation. */
#define updateOrbitHeightAndFadeEffect func_8015C1A0
#include "modules/dungeon_ovl_7f511800_p04.h"
extern void func_8015C06C(void *, void *, void *);
extern s32 rand(void);
extern s32 func_800644B8(s32);

/* Update the effect's orbit and height, fade its color, and mark it for removal when its life expires. */
void func_8015C1A0(void *effect, EntityRec *position, Rec_D_80082E80 *primitive) {
    s16 life;
    s16 angle;
    s16 next_life;

    angle = ((T_801741A0_S_801741A0_0 *)effect)->unk_1E - 0x12C;
    ((T_801741A0_S_801741A0_0 *)effect)->unk_1E = (u16) angle;
    position->x.v = (s32) (((T_801741A0_S_801741A0_0 *)effect)->unk_40 + (func_80064584(angle) * 0x280));
    position->y.v = (s32) (((T_801741A0_S_801741A0_0 *)effect)->unk_44
        + (func_800644B8((s16) ((T_801741A0_S_801741A0_0 *)effect)->unk_1E) * 0x280));
    position->z.v = (s32) (position->z.v + 0xFFF60000);
    func_800478B8(primitive);
    if ((((T_801741A0_S_801741A0_0 *)effect)->unk_1A < 0x11) && (((T_801741A0_S_801741A0_0 *)effect)->unk_20 == 0) && !(rand() & 0xF)) {
        func_8015C06C(effect, position, primitive);
    }
    life = ((T_801741A0_S_801741A0_0 *)effect)->unk_1A;
    if (life < 0xA) {
        primitive->unk_0C.at00_s8.v = (s8) ((((T_801741A0_S_801741A0_0 *)effect)->unk_00 * life) / 9);
        primitive->unk_0C.at01_s8.v = (s8) ((((T_801741A0_S_801741A0_0 *)effect)->unk_01 * ((T_801741A0_S_801741A0_0 *)effect)->unk_1A) / 9);
        primitive->unk_0C.at02_s8.v = (s8) ((((T_801741A0_S_801741A0_0 *)effect)->unk_02 * ((T_801741A0_S_801741A0_0 *)effect)->unk_1A) / 9);
    }
    next_life = (u16) ((T_801741A0_S_801741A0_0 *)effect)->unk_1A - 1;
    ((T_801741A0_S_801741A0_0 *)effect)->unk_1A = next_life;
    if ((next_life << 0x10) <= 0) {
        ((T_801741A0_S_801741A0_0_pre *)effect)[-1].unk_00 = (u16) (((T_801741A0_S_801741A0_0_pre *)effect)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags = (s32) (objectFlagBlock.flags | 0x8000);
    }
}
