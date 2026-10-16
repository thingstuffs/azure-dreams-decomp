#include "modules/dungeon_ovl_191eef8.h"

void func_80024DB8(void **owner_ref, Row_818FF5B8_S_818FF5B8_4 *spawn_pos, Row_818FF5B8_S_818FF5B8_5 *appearance) {
    Row_818FF5B8_S_818FF5B8_2 *sprite;
    void *object;
    Row_818FF5B8_S_818FF5B8_0 *state;
    Row_818FF5B8_S_818FF5B8_3 *position;

    object = func_8003FC64(0x212);
    state = object + 0x20;
    if (object != NULL) {
        state->unk_2C = (void *) *owner_ref;
        state->unk_30 = (s32) ((Row_818FF5B8_S_818FF5B8_1 *)(*owner_ref))->unk_60;
        state->unk_34 = owner_ref;
        (*(M2C_UNK **)((u8 *)object + 0x10)) = &D_80024750;
        func_8004491C(object, func_80045340);
        sprite = (*(void **)((u8 *)object + 0xC));
        sprite->unk_10 = 0x20;
        sprite->unk_06 = 0;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        position = (*(void **)((u8 *)object + 8));
        position->unk_00 = (s32) spawn_pos->unk_00;
        position->unk_04 = (s32) spawn_pos->unk_04;
        position->unk_08 = (s32) spawn_pos->unk_08;
        sprite = (*(void **)((u8 *)object + 0xC));
        sprite->unk_1E = 0x800;
        sprite->unk_1C = 0x800;
        sprite->unk_0C = (u8) appearance->unk_0C;
        sprite->unk_0D = (u8) appearance->unk_0D;
        sprite->unk_0E = (u8) appearance->unk_0E;
        sprite->unk_1A = (s16) (0x1000 - appearance->unk_1A);
        *(Row_818FF5B8_Copy12 *)((u8 *)object + 0x40) = D_80025E64;
        sprite->unk_08 = (void *) (object + 0x40);
    }
}

