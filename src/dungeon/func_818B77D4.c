#include "shared/object_node.h"
#include "modules/dungeon_ovl_18d6800.h"
#include "common.h"









extern s32 rand(void);

/* Creates an object from source data and payload, initializing two fields randomly. */
void func_80024FD4(B28_818B77D4_Arg0818B77D4 *source, B28_818B77D4_Arg1818B77D4 *payload) {
    B28_818B77D4_Obj818B77D4 *obj;
    B28_818B77D4_Inner818B77D4 *state;
    u16 source_value;

    obj = (B28_818B77D4_Obj818B77D4 *)func_8003FC64(0x212);
    if (obj != 0) {
        obj->unk10 = dungeonCycleSevenColorFade;
        state = &obj->unk20;
        state->unk0 = source->unk0;
        state->unk6 = 0;
        source_value = source->unk12;
        state->unkA = 0x30;
        state->unk8 = source_value;
        state->unkC = rand() % 0x1000;
        state->unkE = rand() % 0x1000;
        state->unk10 = source->unk18;
        *(B28_818B77D4_Arg1818B77D4 *)obj->unk8 = *payload;
        func_8004491C(obj, dungeonDrawTwoRadialEffectBands);
    }
}
