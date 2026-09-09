#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 padC;
    s32 pad10;
} StackRecord;

typedef void (*EntityCallback)(void *, void *, void *, void *);

extern void func_8003DB94(void *, void *, s8);
extern void func_800478B8(void *);
extern s32 func_80096FF4(void *);
extern void func_800970AC(s32, void *);
extern void func_800A6A94(StackRecord *);
extern void func_800A6B70(StackRecord *);
extern s32 func_800C2E1C(s16, s16);
extern s32 func_800C2F14(s16, s16);


typedef struct S_800A6684_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_800A6684_0;   /* arg2 in func_800A6684 */


/* Update the entity sprite and trigger effects when it crosses the height threshold. */
void func_800A6684(void *entity, Rec_D_800E3D7C *position, S_800A6684_0 *sprite)
{
    StackRecord effect_pos;
    s32 frame_index;
    register s32 above_height ASM_REG("$3"); /* MATCH: keep the shared height predicate in retail's v1 across both guards. */
    register s32 height_or_shade;
    u32 sprite_flags;

    (*(EntityCallback *)((u8 *)entity + 0x50))(entity, entity, position, sprite);
    if (!((*(u16 *)((u8 *)entity + -2)) & 0x8000)) {
        func_800970AC(func_80096FF4(position), entity);

        frame_index = func_800C2E1C((*(s16 *)((u8 *)entity + 0x72)), (*(s16 *)((u8 *)entity + 0x64)));
        if ((*(s16 *)((u8 *)entity + 0x74)) != frame_index) {
            func_8003DB94(sprite, (*(void ** *)((u8 *)entity + 0x78))[frame_index], sprite->unk_04);
            (*(s16 *)((u8 *)entity + 0x74)) = frame_index;
        }

        if ((func_800C2F14((*(s16 *)((u8 *)entity + 0x72)), (*(s16 *)((u8 *)entity + 0x64))) << 0x10) != 0) {
            sprite_flags = sprite->unk_14 | 1;
        } else {
            sprite_flags = sprite->unk_14 & 0xFFFE;
        }
        sprite->unk_14 = sprite_flags;
        ASM_SCHED_BARRIER();   /* MATCH: keep the flags store before call argument setup. */
        func_800478B8(sprite);

        height_or_shade = position->unk_04.at00_s32.v;
        above_height = height_or_shade > 0x06500000;
        if (!above_height && (*(s32 *)((u8 *)entity + 0xA0)) > 0x06500000) {
            sprite->unk_0C = sprite->unk_0D = sprite->unk_0E = 0xFF;
            effect_pos.unk0 = position->unk_00.at00_s32.v;
            effect_pos.unk4 = 0x06400000;
            effect_pos.unk8 = position->unk_08.at00_s32.v - 0x00280000;
            func_800A6A94(&effect_pos);
        } else if (above_height && (*(s32 *)((u8 *)entity + 0xA0)) <= 0x06500000 &&
            (*(s32 *)((u8 *)entity + 0xA4)) <= 0x06500000) {
            sprite->unk_0C = sprite->unk_0D = sprite->unk_0E = 0xFF;
            effect_pos.unk0 = position->unk_00.at00_s32.v;
            effect_pos.unk4 = 0x06600000;
            effect_pos.unk8 = position->unk_08.at00_s32.v - 0x00280000;
            func_800A6B70(&effect_pos);
        } else {
            height_or_shade = sprite->unk_0C - 8;
            sprite->unk_0C = height_or_shade;
            if ((u32)(height_or_shade & 0xFF) < 0x80U) {
                sprite->unk_0C = 0x80;
            }
            height_or_shade = sprite->unk_0D - 0x10;
            sprite->unk_0D = height_or_shade;
            if ((u32)(height_or_shade & 0xFF) < 0x80U) {
                sprite->unk_0D = 0x80;
            }
            sprite->unk_0E = sprite->unk_0D;
        }
        (*(s32 *)((u8 *)entity + 0xA4)) = (*(s32 *)((u8 *)entity + 0xA0));
        (*(s32 *)((u8 *)entity + 0xA0)) = position->unk_04.at00_s32.v;
    }
}
