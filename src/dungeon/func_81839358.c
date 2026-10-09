#include "modules/dungeon_ovl_1858800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"



/* Updates effect motion and advances its timed sprite animation. */
void func_80024B58(void *effect, void *motion, void *sprite) {
    s32 state;
    s32 rounded_x;
    s32 rounded_y;
    s32 vel_y;
    s32 vel_z;
    s32 pos_x;
    s32 vel_x;
    s32 sprite_word;
    s32 timer_shift;
    u8 red_level;
    s32 timer;
    u16 sprite_scale;
    u8 green_blue;
    void *owner;

    pos_x = ((ProjectileMotion *)motion)->unk_00.s;
    vel_x = ((ProjectileMotion *)motion)->unk_0C;
    vel_y = ((ProjectileMotion *)motion)->unk_10;
    vel_z = ((ProjectileMotion *)motion)->unk_14;
    ((ProjectileMotion *)motion)->unk_00.s = pos_x + vel_x;
    ((ProjectileMotion *)motion)->unk_04.s = (s32) (((ProjectileMotion *)motion)->unk_04.s + vel_y);
    ((ProjectileMotion *)motion)->unk_08.s = (s32) (((ProjectileMotion *)motion)->unk_08.s + vel_z);
    owner = ((ProjectileParticle *)effect)->unk_00;
    ((ProjectileOwnerFlags *)owner)->unk_10 = (s32) (((ProjectileOwnerFlags *)owner)->unk_10 | 0x8000);
    rounded_x = ((ProjectileMotion *)motion)->unk_00.h.unk_02;
    if ((rounded_x / 64) == ((ProjectileParticle *)effect)->unk_04) {
        rounded_y = ((ProjectileMotion *)motion)->unk_04.h.unk_06;
        if ((rounded_y / 64) == ((ProjectileParticle *)effect)->unk_06) {
            ((ProjectileMotion *)motion)->unk_14 = 0;
            ((ProjectileMotion *)motion)->unk_10 = 0;
            ((ProjectileMotion *)motion)->unk_0C = 0;
        }
    }
    state = ((ProjectileParticle *)effect)->unk_4C.s;
    timer = ((ProjectileParticle *)effect)->unk_48 - 1;
    ((ProjectileParticle *)effect)->unk_48 = timer;
    switch (state) {
    case 0:
        timer_shift = timer << 0x10;
        if (timer_shift > 0) {
            return;
        }
        func_8004491C(effect - 0x20, func_80045340);
        ((ProjectileParticle *)effect)->unk_4C.u = ((ProjectileParticle *)effect)->unk_4C.u + 1;
        return;
    case 1:
        func_800478B8(sprite);
        if (((ProjectileSprite *)sprite)->unk_14 & 0x6000) {
            ((ProjectileSprite *)sprite)->unk_04 = 0;
            ((ProjectileSprite *)sprite)->unk_05 = 0;
        }
        if (((ProjectileSprite *)sprite)->unk_0C.at00.v <= ((ProjectileParticle *)effect)->unk_4A) {
            ((ProjectileMotion *)motion)->unk_0C = (s32) (((ProjectileMotion *)motion)->unk_0C * 5);
            ((ProjectileMotion *)motion)->unk_10 = (s32) (((ProjectileMotion *)motion)->unk_10 * 5);
            ((ProjectileMotion *)motion)->unk_14 = (s32) (((ProjectileMotion *)motion)->unk_14 * 8);
            ((ProjectileSprite *)sprite)->unk_1E = 0xC00U;
            ((ProjectileSprite *)sprite)->unk_1C = 0xC00U;
            ((ProjectileSprite *)sprite)->unk_0C.at00u.v = ((ProjectileSprite *)sprite)->unk_0C.at00u.v * 4;
            if (((ProjectileParticle *)effect)->unk_48 & 1) {
                ((ProjectileSprite *)sprite)->unk_00 = D_800DEC70;
                sprite_word = ((SpriteSourceEntry *)D_800DEC70)->unk_04;
            } else {
                ((ProjectileSprite *)sprite)->unk_00 = &D_800DED28;
                sprite_word = ((SpriteSourceEntry *)(&D_800DED28))->unk_04;
            }
            ((ProjectileSprite *)sprite)->unk_04 = 0;
            ((ProjectileSprite *)sprite)->unk_05 = 0;
            ((ProjectileSprite *)sprite)->unk_08 = sprite_word;
            ((ProjectileParticle *)effect)->unk_4C.u = ((ProjectileParticle *)effect)->unk_4C.u + 1;
        } else {
            sprite_scale = ((ProjectileSprite *)sprite)->unk_1E - 0x200;
            ((ProjectileSprite *)sprite)->unk_1E = sprite_scale;
            ((ProjectileSprite *)sprite)->unk_1C = sprite_scale;
            ((ProjectileSprite *)sprite)->unk_0C.at00.v = (u8) (((ProjectileSprite *)sprite)->unk_0C.at00.v
                - (u8) ((ProjectileParticle *)effect)->unk_4A);
            green_blue = ((ProjectileSprite *)sprite)->unk_0C.at02.v - ((s32) ((u16) ((ProjectileParticle *)effect)->unk_4A
                << 0x10) >> 0x12);
            ((ProjectileSprite *)sprite)->unk_0C.at02.v = green_blue;
            ((ProjectileSprite *)sprite)->unk_0C.at01.v = green_blue;
        }
                        /* fall through */
    case 2:
        func_800478B8(sprite);
        if (((ProjectileSprite *)sprite)->unk_14 & 0x6000) {
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((EffectStatusPrefix *)effect)[-1].unk_00 | 0x8000);
            objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
        }
        break;
    default:
        return;
    }
}
/* Historic per-row note: The natural 0x20 frame follows from three held arguments and explicit state CFG labels.
   Zero-arg noreturn dispatchers plus a guarded $v0 tail-slot pointer reproduce all five retail tails.
   Volatile ordered initial loads, direct scalar RMWs, and a comparison-local memory fence close scheduling. */
