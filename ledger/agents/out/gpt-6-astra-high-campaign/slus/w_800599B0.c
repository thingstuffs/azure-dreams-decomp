#include "common.h"

typedef struct {
    /* 0x00 */ s32 f00;
    /* 0x04 */ s32 f04;
    /* 0x08 */ s8 pad08[8];
    /* 0x10 */ s32 f10;
    /* 0x14 */ s8 pad14[4];
    /* 0x18 */ s32 f18;
    /* 0x1C */ s32 f1C;
    /* 0x20 */ s32 f20;
    /* 0x24 */ s32 f24;
    /* 0x28 */ s8 pad28[4];
    /* 0x2C */ s32 f2C;
    /* 0x30 */ s8 pad30[8];
    /* 0x38 */ s32 f38;
    /* 0x3C */ s8 pad3C[4];
    /* 0x40 */ s32 f40;
    /* 0x44 */ s8 pad44[4];
    /* 0x48 */ u8 f48;
    /* 0x49 */ u8 f49;
    /* 0x4A */ u8 f4A;
    /* 0x4B */ s8 pad4B[5];
} Entity; /* 0x50 */

extern Entity D_80085FA8[];
extern s32 D_800869B4;
extern s32 D_800737C4;
extern s32 D_800737C8;
extern u8 *D_80085FA4;

extern void func_80058B70(void);
extern void func_800597A8(Entity *);
extern s32 func_80058A04(Entity *);
extern void func_80059814(Entity *);

/* Initialize playback slot offsets, timing, and state for the input format. */
s32 func_800599B0(void)
{
    u32 entity_index;
    Entity *entity;
    s32 offset;
    s32 length;
    u8 *length_cursor;
    u8 *data;
    s32 span;
    register s32 start ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 end;
    s32 default_value;
    s32 packed_default;
    s32 format;
    s32 mode;

    D_800737C4 = 0;
    D_800737C8 = 1;
    offset = 0;
    format = *D_80085FA4;
    if (format == 0x70) {
        D_800737C8 = 0;
    } else if (format == 0x4B) {
        D_800737C8 = 2;
    }
    func_80058B70();
    mode = D_800737C8;
    if (mode < 0) {
        goto done;
    }
    if (mode < 2) {
        goto init_entities;
    }
    if (mode == 2) {
        goto init_spans;
    }
    return 0;
init_entities:
    {
        entity_index = 0;
        if (D_800869B4 == 0) {
            goto done;
        }
        default_value = 0x68;
        entity = D_80085FA8;
        do {
            if (D_800737C8 == 1) {
                entity->f00 = offset + 1;
                entity->f24 = default_value;
                entity->f20 = default_value;
                func_800597A8(entity);
                offset = entity->f00;
            }
            entity->f04 = entity->f00;
            entity->f10 = func_80058A04(entity);
            entity->f48 = 0;
            entity->f4A = 0;
            entity->f49 = 0;
            entity->f2C = 0;
            entity->f40 = 0;
            if (D_800737C4 != 0) {
                func_80059814(entity);
            }
            entity++;
            entity_index++;
        } while (entity_index < (u32)D_800869B4);
        goto done;
    }
init_spans:
    offset = 0x50;
    data = D_80085FA4;
    entity_index = 0;
    if (D_800869B4 == 0) {
        goto done;
    }
    packed_default = 0x68;
    entity = D_80085FA8;
    length_cursor = data;
    do {
        entity->f00 = offset;
        length = *(u16 *)(length_cursor + 0x10);
        entity->f18 = length;
        ASM_KEEP_NV(length);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        span = length;
        ASM_KEEP_NV(span);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        entity->f24 = packed_default;
        entity->f20 = packed_default;
        start = entity->f00;
        end = start;
        ASM_USE2_NV(end, span);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        entity->f04 = start;
        entity->f38 = start;
        offset += length;
        end += span;
        entity->f1C = end;
        entity->f10 = func_80058A04(entity);
        entity->f48 = 0;
        entity->f4A = 0;
        entity->f49 = 0;
        entity->f2C = 0;
        entity->f40 = 0;
        if (D_800737C4 != 0) {
            func_80059814(entity);
        }
        entity++;
        length_cursor += 2;
        entity_index++;
    } while (entity_index < (u32)D_800869B4);
done:
    return 0;
}
