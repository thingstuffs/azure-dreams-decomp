#include "common.h"
#include "shared/entity.h"


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
extern s32 update_object_and_clear_status_fields(void *);
extern void set_state_bytes_from_flags(s32 flags, u8 *state);
extern void create_colored_scaled_effect(StackRecord *);
extern void update_sine_pulse_color(StackRecord *);
extern s32 quantize_heading_to_sector(s16, s16);
extern s32 check_heading_past_half_sector(s16, s16);


typedef struct S_800A6684_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_800A6684_0;   /* arg2 in update_entity_sprite_and_effects */


/* Update the entity sprite and trigger effects when it crosses the height threshold. */
void update_entity_sprite_and_effects(void *entity, EntityRec *position, S_800A6684_0 *sprite)
{
    StackRecord effect_pos;
    s32 frame_index;
    s32 height_or_shade;

    (*(EntityCallback *)((u8 *)entity + 0x50))(entity, entity, position, sprite);
    if (!((*(u16 *)((u8 *)entity + -2)) & 0x8000)) {
        set_state_bytes_from_flags(update_object_and_clear_status_fields(position), entity);

        frame_index = quantize_heading_to_sector((*(s16 *)((u8 *)entity + 0x72)), (*(s16 *)((u8 *)entity + 0x64)));
        if ((*(s16 *)((u8 *)entity + 0x74)) != frame_index) {
            func_8003DB94(sprite, (*(void ** *)((u8 *)entity + 0x78))[frame_index], sprite->unk_04);
            (*(s16 *)((u8 *)entity + 0x74)) = frame_index;
        }

        if ((check_heading_past_half_sector((*(s16 *)((u8 *)entity + 0x72)), (*(s16 *)((u8 *)entity + 0x64))) << 0x10) != 0) {
            sprite->unk_14 |= 1;
        } else {
            sprite->unk_14 &= 0xFFFE;
        }
                   /* MATCH: keep the flags store before call argument setup. */
        func_800478B8(sprite);

        if (position->y.v <= 0x06500000 && (*(s32 *)((u8 *)entity + 0xA0)) > 0x06500000) {
            sprite->unk_0C = sprite->unk_0D = sprite->unk_0E = 0xFF;
            effect_pos.unk0 = position->x.v;
            effect_pos.unk4 = 0x06400000;
            effect_pos.unk8 = position->z.v - 0x00280000;
            create_colored_scaled_effect(&effect_pos);
        } else if (position->y.v > 0x06500000 && (*(s32 *)((u8 *)entity + 0xA0)) <= 0x06500000 &&
            (*(s32 *)((u8 *)entity + 0xA4)) <= 0x06500000) {
            sprite->unk_0C = sprite->unk_0D = sprite->unk_0E = 0xFF;
            effect_pos.unk0 = position->x.v;
            effect_pos.unk4 = 0x06600000;
            effect_pos.unk8 = position->z.v - 0x00280000;
            update_sine_pulse_color(&effect_pos);
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
        (*(s32 *)((u8 *)entity + 0xA0)) = position->y.v;
    }
}
