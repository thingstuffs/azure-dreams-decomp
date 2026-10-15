#include "modules/dungeon_town_map.h"

void func_8008BB50(town_map_7FFEE3F0_Actor *actor) {
    town_map_7FFEE3F0_SubStruct *sub = actor->sub;

    sub->unk8 += 0x200;
    if ((s16)actor->sub->unk8 > 0) {
        actor->sub->unk8 = 0;
        actor->unk68 = (void *)func_8008BC58;
        actor->unk64 = D_800CFC70[actor->unk66];
        actor->unk6C = D_800CFC7C[actor->unk66];
    }
}
