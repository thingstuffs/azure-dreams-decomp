#include "modules/dungeon_ovl_7e6b7800.h"

void func_8002455C(void *effect, void *position, void *sprite) {
    Row_8194CD5C_InputVector local_offset;
    Row_8194CD5C_OutputVector rotated_offset;
    s32 y_product;
    u16 scale;
    u8 brightness;
    void *counter_state;

    counter_state = ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_00;
    ((Row_8194CD5C_S_8002455C_1 *)counter_state)->unk_1A = (u16) (((Row_8194CD5C_S_8002455C_1 *)counter_state)->unk_1A + 1);
    ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2E = (u16) (((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2E + 0x100);
    ((Row_8194CD5C_S_8002455C_2 *)position)->unk_00.at00.v = (s32) ((Row_8194CD5C_S_8002455C_2 *)position)->unk_0C;
    ((Row_8194CD5C_S_8002455C_2 *)position)->unk_04.at00.v = (s32) ((Row_8194CD5C_S_8002455C_2 *)position)->unk_10;
    ((Row_8194CD5C_S_8002455C_2 *)position)->unk_08.at00.v = (s32) ((Row_8194CD5C_S_8002455C_2 *)position)->unk_14;
    local_offset.x = (s16) ((s32) ((func_800644B8((s16) ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2E)
        >> 4) * ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2C) >> 8);
    y_product = (func_80064584((s16) ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2E) >> 4) * ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2C;
    local_offset.z = 0;
    local_offset.y = (s16) (y_product >> 8);
    func_800649A0();
    func_80064B30(effect + 4, &local_offset, &rotated_offset);
    func_80064A40();
    ((Row_8194CD5C_S_8002455C_2 *)position)->unk_00.at02.v = (u16) (((Row_8194CD5C_S_8002455C_2 *)position)->unk_00.at02.v + rotated_offset.x);
    ((Row_8194CD5C_S_8002455C_2 *)position)->unk_04.at02.v = (u16) (((Row_8194CD5C_S_8002455C_2 *)position)->unk_04.at02.v + rotated_offset.y);
    ((Row_8194CD5C_S_8002455C_2 *)position)->unk_08.at02.v = (u16) (((Row_8194CD5C_S_8002455C_2 *)position)->unk_08.at02.v + rotated_offset.z);
    if (((Row_8194CD5C_S_8002455C_0 *)effect)->unk_30 != 0) {
        ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_30 = 0U;
    }
    brightness = ((Rec_D_80082E80 *)sprite)->unk_0C.at02_u8.v - 8;
    ((Rec_D_80082E80 *)sprite)->unk_0C.at02_u8.v = brightness;
    ((Rec_D_80082E80 *)sprite)->unk_0C.at01_u8.v = brightness;
    ((Rec_D_80082E80 *)sprite)->unk_0C.at00_u8.v = brightness;
    if (!(brightness & 0xFF) || (scale = ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v - 0x100,
        ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v = scale, ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v = scale,
        ((Rec_D_80082E80 *)sprite)->unk_1A.as_u16 = (u16) ((Row_8194CD5C_S_8002455C_0 *)effect)->unk_2E, func_800478B8(sprite),
        ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) != 0))) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((Row_8194CD5C_S_8002455C_0_pre *)effect)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags |= 0x8000;
    }
}
/* MECHANISM: Two six-byte vector aggregates force stack slots sp+0x10..0x14 and sp+0x18..0x1C,
   restoring the 0x30 frame and the s0/s1/s2-only save set.
   cdk -G0 plus a direct scalar D_800814A0 RMW removes the extra address addiu and closes the residue. */
