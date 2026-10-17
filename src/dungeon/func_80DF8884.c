/* Relink of matched dungeon/func_80DE6884; every changed retail word is a paired relocation. */
#define dungeonCreateFourDirectionalEffects func_80162084
#include "modules/dungeon_ovl_e0365c.h"
extern void func_80161F8C(void *, void *, void *);
extern s32 func_800644B8(s32);
extern s32 rand(void);

void func_80162084(void *owner_arg, void *motion_arg, void *origin_arg) {
    u16 offsets[3];
    s32 effect_index;
    E_80174084_S_80DE6884_5 *owner;
    E_80174084_M2C_UNK *effect_data;
    E_80174084_S_80DE6884_0 *origin;
    void *render_config;
    E_80174084_S_80DE6884_2 *render_data;
    E_80174084_S_80DE6884_4 *motion;
    E_80174084_S_80DE6884_1 *effect;

    origin = origin_arg;
    offsets[2] = 0;
    offsets[1] = 0;
    offsets[0] = 0;
    owner = owner_arg;
    resolveRecordOrientationOrFallback(origin->unk_08, origin, (s16 *)offsets, 0);
    effect_index = 0;
    effect_data = (E_80174084_M2C_UNK *)((u32)func_80161F8C);
    do {
        effect = func_8003FC64(0x212);
        if (effect != NULL) {
            render_config = &D_800DEA68;
            render_data = effect->unk_0C;
            effect->unk_10 = effect_data;
            render_data->unk_0E = 0x60;
            render_data->unk_0D = 0x60;
            render_data->unk_0C = 0x60;
            render_data->unk_14 = set_flags(render_data->unk_14, 0xC);
            render_data->unk_10 = set_flags(render_data->unk_10, 0x20);
            func_8003DB94(render_data, render_config, 0);
            func_800478B8(render_data);
            render_data->unk_1A = rand() % 0x1000;
            render_data->unk_1E = 0x1000;
            render_data->unk_1C = 0x1000;
            func_8004491C(effect, func_80045340);
            motion = effect->unk_08;
            *(E_80174084_S_80DE6884_3 *)motion = *(E_80174084_S_80DE6884_3 *)motion_arg;
            motion->unk_00.at02.v = offset_coord(motion->unk_00.at02.v, offsets[0]);
            motion->unk_04.at02.v = offset_coord(motion->unk_04.at02.v, offsets[1]);
            motion->unk_08.at02.v = offset_coord(motion->unk_08.at02.v, offsets[2]);
            motion->unk_0C = (s32)((func_80064584(owner->unk_2A) >> 4) << 0xB);
            motion->unk_10 = (s32)((func_800644B8(owner->unk_2A) >> 4) << 0xB);
            motion->unk_14 = 0x9C40;
        }
        effect_index += 1;
    } while (effect_index < 4);
}

/* MECHANISM: the 24-byte motion block is one aggregate copy from motion_arg (movstrsi leaves its fourth
   word in a1, which the one-argument trig call never reads); the small u16 helpers keep the loop at 88
   real insns so loop.c does not hoist the 0x60 colour constant into a callee-saved register. */
