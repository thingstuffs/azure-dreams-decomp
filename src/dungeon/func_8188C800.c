#include "modules/dungeon_ovl_18ac800.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"



#ifdef __mips__
#endif





/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol func_80024000).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_18ac800_entry)(u8 *, u8 *, u8 *) = func_80024050;

static __inline__ s32 align_effect_coord(s32 coord)
{
    return ((coord << 6) + 32) & 0xFFE0;
}

/* Updates a moving effect through initialization, travel, impact, and fading. */
void func_80024050(u8 *self, u8 *motion, u8 *part)
{
    u8 *owner;
    u8 *base;
    u8 *record;
    u8 *tail_page0;
    u8 *tail_page1;
    s32 velocity;
    register s32 state;
    s32 scratch[4];
    u32 color;
    u32 init_flags;
    u32 init_size;
    u8 *effect_params;

    owner = ((MovingEffectState *)self)->unk_00;
    state = ((MovingEffectState *)self)->unk_0A.s;
    base = owner - 32;
    record = ((MovingObject *)base)->unk_08;
    switch (state) {
    case 0:
        color = 0x00808080;
        init_flags = 0x01000340;
        init_size = 0x00200020;
        effect_params = D_80026484;
        ((MovingSprite *)part)->unk_0C.at00.v = color;
        ((MovingSprite *)part)->unk_1E = 0x555;
        ((MovingSprite *)part)->unk_1C = 0x555;
        ((MovingSprite *)part)->unk_08 = D_80026490;
        ((SignedWordView *)D_80026470)->unk_00 = 0;
        ((SignedHalfView *)D_80026474)->unk_00 = 0;
        ((UnsignedWordView *)D_80026476)->unk_00 = 0;
        ((UnsignedHalfView *)D_800265C0)->unk_00 = 0;
        ((UnsignedByteView *)D_800265C4)->unk_00 = 0;
        {
            u16 owner_flags = ((MovingActor *)owner)->unk_2A;
            *(u16 *)D_80026484 = 0x1010;
            ((MovingParameter *)effect_params)->unk_08 = 0;
            ((MovingEffectState *)self)->unk_16.u = (owner_flags >> 9) & 7;
        }
        scratch[2] = init_flags;
        scratch[3] = init_size;
        func_800B835C(effect_params - 12, scratch + 2, 1, 0);
        ((MovingEffectState *)self)->unk_0A.u++;
    case 1:
        if (func_8003DF74(((MovingSpriteFlags *)(((MovingObject *)base)->unk_0C))->unk_08,
                          ((MovingObject *)base)->unk_0C, scratch, 0) == 0) {
            if (!(((MovingSpriteFlags *)(((MovingObject *)base)->unk_0C))->unk_14 & 0x8000)) {
                break;
            }
        }
        ((MovingMotion *)motion)->unk_00.at02.v = ((MovingPosition *)record)->unk_02;
        ((MovingMotion *)motion)->unk_04.at02.v = ((MovingPosition *)record)->unk_06;
        if (((MovingSpriteFlags *)(((MovingObject *)base)->unk_0C))->unk_14 & 0x8000) {
            u16 height = ((MovingPosition *)record)->unk_0A - 64;
            ((MovingMotion *)motion)->unk_08.at02.v = height;
            ((MovingEffectState *)self)->unk_30.at02.v = height;
        } else {
            u16 height = ((MovingPosition *)record)->unk_0A + ((OriginOffsetView *)scratch)->unk_04;
            ((MovingMotion *)motion)->unk_08.at02.v = height;
            ((MovingEffectState *)self)->unk_30.at02.v = height;
        }
        if (!(((MovingAnimationFlags *)(((MovingEffectState *)self)->unk_04))->unk_00 & 0x80)) {
            break;
        }
        if (!(((MovingEffectState *)self)->unk_12 & 4)) {
            func_8004491C(self - 32, func_80045340);
            ((MovingSprite *)part)->unk_10 = 32;
            ((MovingSprite *)part)->unk_0C.at02.v = 128;
            ((MovingSprite *)part)->unk_0C.at01.v = 128;
            ((MovingSprite *)part)->unk_0C.at00u.v = 128;
            ((MovingSprite *)part)->unk_14 |= 0xC;
            ((MovingEffectState *)self)->unk_12 |= 4;
        }
        {
            u8 *target = ((MovingActor *)owner)->unk_60.p;
            if (target != 0) {
                u8 *target_part = ((MovingTarget_pre *)target)[-1].unk_00;
                ((MovingEffectState *)self)->unk_0C = ((MovingTargetPosition *)target_part)->unk_02;
                ((MovingEffectState *)self)->unk_0E = ((MovingTargetPosition *)target_part)->unk_06;
                ((MovingEffectState *)self)->unk_10.u = ((MovingTargetPosition *)target_part)->unk_0A -
                                          D_800DDC40[0];
                {
                    u8 *target_record = ((MovingActor_pre *)owner)[-1].unk_00;
                    u8 x = ((MovingTile *)target_record)->unk_24 +
                           ((u8 *)dirStepX)[((MovingEffectState *)self)->unk_16.s * 2];
                    ((MovingEffectState *)self)->unk_1C.at02.v = x;
                    ((MovingEffectState *)self)->unk_20.at00.v = x;
                    {
                        u8 y = ((MovingTile *)target_record)->unk_25 +
                               ((u8 *)dirStepY)[((MovingEffectState *)self)->unk_16.s * 2];
                        ((MovingEffectState *)self)->unk_1C.at03.v = y;
                        ((MovingEffectState *)self)->unk_20.at01.v = y;
                    }
                    {
                        s32 owner_coord = ((MovingActor *)owner)->unk_70.at02.v;
                        s32 record_coord =
                            ((MovingTile *)target_record)->unk_24;
                        s32 tile_distance;
                        if (owner_coord == record_coord) {
                            owner_coord = ((MovingActor *)owner)->unk_70.at03.v;
                            record_coord = ((MovingTile *)target_record)->unk_25;
                        }
                        tile_distance = owner_coord - record_coord;
                        tile_distance = abs(tile_distance);
                        ((MovingEffectState *)self)->unk_14 = tile_distance + 1;
                    }
                }
            } else {
                ((MovingEffectState *)self)->unk_14 = 8;
                ((MovingEffectState *)self)->unk_0C = ((MovingMotion *)motion)->unk_00.at02.v;
                ((MovingEffectState *)self)->unk_0E = ((MovingMotion *)motion)->unk_04.at02.v;
                ((MovingEffectState *)self)->unk_10.u = ((MovingActor *)owner)->unk_88 - 80;
            }
        }
        ((MovingMotion *)motion)->unk_0C.at02.v =
            (*(s16 *)((u8 *)((u8 *)dirStepX) + ((MovingEffectState *)self)->unk_16.s * 2)) * 8;
        ((MovingMotion *)motion)->unk_10.at02.v =
            (*(s16 *)((u8 *)((u8 *)dirStepY) + ((MovingEffectState *)self)->unk_16.s * 2)) * 8;
        ((MovingEffectState *)self)->unk_0A.u++;
        break;

    case 2:
    {
        s32 position;
        s32 adjusted;
        velocity = ((MovingMotion *)motion)->unk_0C.at00.v;
        position = (*(s32 *)((u8 *)motion + 0));
        position += velocity;
        (*(s32 *)((u8 *)motion + 0)) = position;
        adjusted = ((MovingMotion *)motion)->unk_0C.at00.v;
        position = adjusted >> 4;
        adjusted += position;
        velocity = abs(adjusted);
        ((MovingMotion *)motion)->unk_0C.at00.v = adjusted;
        if (velocity > 0x200000) {
            s32 limit = -0x200000;
            if (adjusted > 0) {
                limit = 0x200000;
            }
            ((MovingMotion *)motion)->unk_0C.at00.v = limit;
        }
    }
        {
            s32 position;
            s32 adjusted;
            velocity = ((MovingMotion *)motion)->unk_10.at00.v;
            position = (*(s32 *)((u8 *)motion + 4));
            position += velocity;
            (*(s32 *)((u8 *)motion + 4)) = position;
            adjusted = ((MovingMotion *)motion)->unk_10.at00.v;
            position = adjusted >> 4;
            adjusted += position;
            velocity = abs(adjusted);
            ((MovingMotion *)motion)->unk_10.at00.v = adjusted;
            if (velocity > 0x200000) {
                s32 limit = -0x200000;
                if (adjusted > 0) {
                    limit = 0x200000;
                }
                ((MovingMotion *)motion)->unk_10.at00.v = limit;
            }
        }
        {
            s32 height = ((MovingEffectState *)self)->unk_30.at00.v;
            s32 height_step = (((s32)((MovingEffectState *)self)->unk_10.s << 16) - height) >> 4;
            ((MovingEffectState *)self)->unk_30.at00.v = height + height_step;
        }
        {
            s32 height = ((MovingMotion *)motion)->unk_08.at00.v;
            s32 height_step = (((s32)((MovingEffectState *)self)->unk_10.s << 16) - height) >> 4;
            ((MovingMotion *)motion)->unk_08.at00.v = height + height_step;
        }
        ((MovingMotion *)motion)->unk_08.at00.v += func_800644B8((s32)((MovingEffectState *)self)->unk_18.s
            << 7) << 6;
        func_8002495C(motion, part);
        {
            s32 x = ((MovingMotion *)motion)->unk_00.at02u.v;
            if (x < 0) {
                x += 63;
            }
            ((MovingEffectState *)self)->unk_1C.at02.v = x >> 6;
            {
                s32 y = ((MovingMotion *)motion)->unk_04.at02u.v;
                if (y < 0) {
                    y += 63;
                }
                ((MovingEffectState *)self)->unk_1C.at03.v = y >> 6;
            }
        }
        if (((MovingEffectState *)self)->unk_20.at00u.v == ((MovingEffectState *)self)->unk_1C.at02u.v) {
            break;
        }
        if (((MovingActor *)owner)->unk_60.p2 != 0) {
            if ((((MovingActor *)owner)->unk_70.at00.v & 0xFFFF0000) ==
                (((MovingEffectState *)self)->unk_1C.at00.v & 0xFFFF0000)) {
                s32 snap_x = ((MovingActor *)owner)->unk_70.at02.v;
                s32 snap_y;
                snap_x <<= 6;
                snap_x += 32;
                ((MovingMotion *)motion)->unk_00.at02.v = snap_x;
                snap_y = ((MovingActor *)owner)->unk_70.at03.v;
                snap_y <<= 6;
                snap_y += 32;
                ((MovingMotion *)motion)->unk_04.at02.v = snap_y;
                ((MovingMotion *)motion)->unk_08.at02.v = ((MovingEffectState *)self)->unk_10.u;
                func_8002495C(motion, part);
                {
                    u8 *target = ((MovingActor *)owner)->unk_60.p;
                    u16 next_state = ((MovingEffectState *)self)->unk_0A.u + 1;
                    u16 height = ((MovingTarget *)target)->unk_88;
                    ((MovingEffectState *)self)->unk_0A.u = next_state;
                    ((MovingHeight *)D_800269C8)->unk_00 = height;
                }
                break;
            }
        }

        {
            u8 old_x = ((MovingEffectState *)self)->unk_1C.at02.v;
            s16 steps_left = ((MovingEffectState *)self)->unk_14 - 1;
            u8 old_y = ((MovingEffectState *)self)->unk_1C.at03.v;
            ((MovingEffectState *)self)->unk_14 = steps_left;
            ((MovingEffectState *)self)->unk_20.at00.v = old_x;
            ((MovingEffectState *)self)->unk_20.at01.v = old_y;
            if (steps_left != 0) {
                s32 x = align_effect_coord(((MovingEffectState *)self)->unk_1C.at02p.v);
                s32 height = ((MovingEffectState *)self)->unk_30.at02u.v;
                s32 y;
                y = align_effect_coord(((MovingEffectState *)self)->unk_1C.at03u.v);
                if ((func_800A45D8(x, y, height) << 16) == 0) {
                    break;
                }
            }
        }
        ((MovingEffectState *)self)->unk_0A.u = 16;
        break;

    case 3:
        func_80065F90(((MovingMotion *)motion)->unk_0C.at02.v,
            ((MovingMotion *)motion)->unk_10.at02.v);
        ((MovingEffectState *)self)->unk_2C.i =
            func_800262AC(((MovingMotion *)motion)->unk_00.at02u.v,
                ((MovingMotion *)motion)->unk_04.at02u.v,
                          ((MovingMotion *)motion)->unk_08.at02u.v);
        if (((MovingEffectState *)self)->unk_2C.i == 0) {
            break;
        }
        if (((MovingActor *)owner)->unk_60.p2 != 0) {
            func_800A56E0(0x300);
        }
        ((MovingEffectState *)self)->unk_0A.u++;
    case 4:
        ((MovingSprite *)part)->unk_0C.at00u.v -= ((MovingSprite *)part)->unk_0C.at00u.v >> 2;
        ((MovingSprite *)part)->unk_0C.at01.v -= ((MovingSprite *)part)->unk_0C.at01.v >> 2;
        ((MovingSprite *)part)->unk_0C.at02.v -= ((MovingSprite *)part)->unk_0C.at02.v >> 2;
        if (!(((MovingSpawnFlags *)(((MovingEffectState *)self)->unk_2C.p))->unk_1E & 0x8000)) {
            break;
        }
        if (((MovingActor *)owner)->unk_60.p2 != 0) {
            func_80026404(((MovingActor *)owner)->unk_60.p2, ((MovingEffectState *)self)->unk_09,
                owner);
        }
        dungeonStatus.unk_0C = 0;
        ((MovingEffectState_pre *)self)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        break;

    case 16:
        ((MovingMotion *)motion)->unk_00.at00.v += ((MovingMotion *)motion)->unk_0C.at00.v;
        ((MovingMotion *)motion)->unk_04.at00.v += ((MovingMotion *)motion)->unk_10.at00.v;
        {
            s32 height_step = ((s32)((MovingEffectState *)self)->unk_10.s << 16) -
                        ((MovingMotion *)motion)->unk_08.at00.v;
            height_step >>= 4;
            ((MovingMotion *)motion)->unk_08.at00.v += height_step;
        }
        ((MovingSprite *)part)->unk_0C.at00u.v -= ((MovingSprite *)part)->unk_0C.at00u.v >> 1;
        ((MovingSprite *)part)->unk_0C.at01.v -= ((MovingSprite *)part)->unk_0C.at01.v >> 1;
        ((MovingSprite *)part)->unk_0C.at02.v -= ((MovingSprite *)part)->unk_0C.at02.v >> 1;
        func_8002495C(motion, part);
        if (((MovingSprite *)part)->unk_0C.at00u.v < 2) {
            ((MovingEffectState *)self)->unk_0A.u++;
        }
        break;

    case 17:
        if (D_80026472.value.s != 0) {
            break;
        }
        dungeonStatus.unk_0C = 0;
        ((MovingEffectState_pre *)self)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
    {
        u16 frame = ((MovingEffectState *)self)->unk_18.u;
        D_80026472.value.u = 0;
        ((MovingEffectState *)self)->unk_18.u = frame + 1;
    }
}
