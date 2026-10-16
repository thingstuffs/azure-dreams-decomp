/* Relink of matched dungeon/func_80CE7794; every changed retail word is a paired relocation. */
#define dungeonUpdateGrowingBouncingEffect func_8015EF94
#include "modules/dungeon_ovl_7f469800_p01.h"

/* Updates effect motion, handles collisions, grows the sprite, and flags expiration. */
void func_8015EF94(void *effect, void *position, void *sprite)
{
    s32 height;
    u16 frame_count;
    u16 scale_x;
    u16 scale_y;
    u16 ticks_left;

    ((T_80170F94_S_80170F94_0 *)position)->unk_00.at00.v += ((T_80170F94_S_80170F94_1 *)effect)->unk_40;
    ((T_80170F94_S_80170F94_1 *)effect)->unk_40 += ((T_80170F94_S_80170F94_1 *)effect)->unk_4C;
    if (dungeonCheckLeftTileAndCenterHeight(((T_80170F94_S_80170F94_0 *)position)->unk_00.at02.v,
                      ((T_80170F94_S_80170F94_0 *)position)->unk_04.at02.v,
                      ((T_80170F94_S_80170F94_0 *)position)->unk_08.at02.v) << 16) {
        ((T_80170F94_S_80170F94_0 *)position)->unk_00.at00.v -= ((T_80170F94_S_80170F94_1 *)effect)->unk_40;
        ((T_80170F94_S_80170F94_1 *)effect)->unk_40 = 0;
        ((T_80170F94_S_80170F94_1 *)effect)->unk_4C = 0;
    }

    ((T_80170F94_S_80170F94_0 *)position)->unk_04.at00.v += ((T_80170F94_S_80170F94_1 *)effect)->unk_44;
    ((T_80170F94_S_80170F94_1 *)effect)->unk_44 += ((T_80170F94_S_80170F94_1 *)effect)->unk_50;
    if (dungeonCheckLeftTileAndCenterHeight(((T_80170F94_S_80170F94_0 *)position)->unk_00.at02.v,
                      ((T_80170F94_S_80170F94_0 *)position)->unk_04.at02.v,
                      ((T_80170F94_S_80170F94_0 *)position)->unk_08.at02.v) << 16) {
        ((T_80170F94_S_80170F94_0 *)position)->unk_04.at00.v -= ((T_80170F94_S_80170F94_1 *)effect)->unk_44;
        ((T_80170F94_S_80170F94_1 *)effect)->unk_44 = 0;
        ((T_80170F94_S_80170F94_1 *)effect)->unk_50 = 0;
    }

    ((T_80170F94_S_80170F94_0 *)position)->unk_08.at00.v += ((T_80170F94_S_80170F94_1 *)effect)->unk_48;
    ((T_80170F94_S_80170F94_1 *)effect)->unk_48 += ((T_80170F94_S_80170F94_1 *)effect)->unk_54;
    height = ((T_80170F94_S_80170F94_0 *)position)->unk_08.at02.v;
    if (func_800BCB04(((T_80170F94_S_80170F94_0 *)position)->unk_00.at02.v,
                      ((T_80170F94_S_80170F94_0 *)position)->unk_04.at02.v,
                      (s16)(((T_80170F94_S_80170F94_0 *)position)->unk_08.at02u.v - 4)) - 0x10 < height) {
        ((T_80170F94_S_80170F94_1 *)effect)->unk_48 = 0;
        ((T_80170F94_S_80170F94_0 *)position)->unk_08.at02.v = func_800BCB04(
            ((T_80170F94_S_80170F94_0 *)position)->unk_00.at02.v, ((T_80170F94_S_80170F94_0 *)position)->unk_04.at02.v,
            (s16)(((T_80170F94_S_80170F94_0 *)position)->unk_08.at02u.v - 4)) - 0x11;
        ((T_80170F94_S_80170F94_0 *)position)->unk_08.at00u.v = 0;
        if (((T_80170F94_S_80170F94_1 *)effect)->unk_0E == 0) {
            ((T_80170F94_S_80170F94_1 *)effect)->unk_0E = 1;
            ((T_80170F94_S_80170F94_1 *)effect)->unk_18.s = 0;
        }
    }

    frame_count = ((T_80170F94_S_80170F94_1 *)effect)->unk_1A + 1;
    ((T_80170F94_S_80170F94_1 *)effect)->unk_1A = frame_count;
    if ((frame_count & 3) == 0) {
        func_800478B8(sprite);
    }

    scale_x = ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v + 100;
    ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v = scale_x;
    if (scale_x > 0x1000) {
        ((Rec_D_80082E80 *)sprite)->unk_1C.at00_u16.v = 0x1000;
    }

    scale_y = ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v + 100;
    ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v = scale_y;
    if (scale_y > 0x1000) {
        ((Rec_D_80082E80 *)sprite)->unk_1C.at02_u16.v = 0x1000;
    }

    ticks_left = ((T_80170F94_S_80170F94_1 *)effect)->unk_18.u - 1;
    ((T_80170F94_S_80170F94_1 *)effect)->unk_18.u = ticks_left;
    if ((s16)ticks_left <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }

    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
