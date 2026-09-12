#include "common.h"

typedef struct S_800A794C_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_800A794C_0;   /* object in func_800A794C */

typedef struct S_800A794C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800A794C_1;   /* position in func_800A794C */

typedef struct S_800A794C_2 {
    u8 pad_00[0x98];
    s32 unk_98;
    u8 pad_9C[0x4];
    s16 unk_A0;
    u8 pad_A2[0x8];
    s16 unk_AA;
    s16 unk_AC;
    s16 unk_AE;
} S_800A794C_2;   /* fields in func_800A794C */

typedef struct S_800A794C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800A794C_3;   /* state in func_800A794C */

extern void *func_800A8608(void *, void *, s32, s32, s32);

extern s32 D_80083498;
extern s32 D_800A77AC;
extern s32 D_80083460;

/* Create an object at the tile center, initialize its fields, and increment the object count. */
s32 func_800A794C(s32 tile_x, s32 tile_y, s32 height, s32 *payload_ptr,
                  s32 field_aa, s32 field_ac, s32 field_ae) {
    u8 *object;
    u8 *position;
    u8 *fields;
    u8 *state;
    s32 payload;
    s32 stored_ae;
    u16 object_count;
    s16 result;
    register u8 *callback ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    object = func_800A8608(&D_80083498, payload_ptr, 0, 0, 0);
#ifdef NON_MATCHING
    callback = (u8 *)&D_800A77AC;
#else
    callback = (u8 *)0x800A0000;
#endif
    if (object != 0) {
#ifndef NON_MATCHING
        ASM_KEEP(callback);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        callback += 0x77AC;
#endif
        ((S_800A794C_0 *)object)->unk_10 = callback;
        position = ((S_800A794C_0 *)object)->unk_08;
        ((S_800A794C_1 *)position)->unk_02 = (s16)((tile_x << 6) + 0x20);
        ((S_800A794C_1 *)position)->unk_06 = (s16)((tile_y << 6) + 0x20);
        ((S_800A794C_1 *)position)->unk_0A = height;

        fields = object + 0x20;
        payload = *payload_ptr;
        ((S_800A794C_2 *)fields)->unk_A0 = 4;
        ((S_800A794C_2 *)fields)->unk_AA = (s16)field_aa;
        ((S_800A794C_2 *)fields)->unk_AC = (s16)field_ac;
        stored_ae = field_ae;
        ((S_800A794C_2 *)fields)->unk_98 = payload;
        state = (u8 *)&D_80083460;
        ((S_800A794C_2 *)fields)->unk_AE = (s16)stored_ae;
        object_count = ((S_800A794C_3 *)state)->unk_0A;
        result = (s32)object;
        object_count++;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        ((S_800A794C_3 *)state)->unk_0A = object_count;
        return;
    }
    result = 0;
    return result;
}

