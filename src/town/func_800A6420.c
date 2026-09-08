#include "common.h"

typedef struct S_800A3B80_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800A3B80_0;   /* town in func_800A3B80 */

typedef struct S_800A3B80_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x3];
    u8 unk_0F;
} S_800A3B80_1;   /* arg2_temp in func_800A3B80 */

typedef struct S_800A3B80_2 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A3B80_2;   /* arg2_data in func_800A3B80 */

typedef struct S_800A3B80_3 {
    s16 unk_00;
    u8 pad_02[0x4];
    u8 unk_06;
    u8 pad_07[0x5];
    s16 unk_0C;
} S_800A3B80_3;   /* arg0 in func_800A3B80 */

typedef struct S_800A3B80_4 {
    void * unk_00;
} S_800A3B80_4;   /* global_base in func_800A3B80 */

typedef struct S_800A3B80_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800A3B80_5;   /* end_town in func_800A3B80 */



typedef struct TownGlobals {
    void *root;
    u8 pad04[0xC4];
    u16 angle;
} TownGlobals;

typedef struct Scratch {
    u8 pad00[0x20];
    void *data20;
    u8 pad24[0x4C];
    s16 data70;
    s16 data72;
    u8 pad74[4];
    s16 data78;
    s16 data7A;
    u8 pad7C[4];
    s16 data80;
    s16 data82;
    u8 pad84[4];
    s16 data88;
    s16 data8A;
    u8 pad8C[0x8C];
    void *data118;
} Scratch;

extern TownGlobals D_80083160;
extern u16 D_80100D88;
extern u16 D_80100D8A;

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void *func_800A41D8(void *, void *, void *, void *, s32);

s32 func_800A3B80(S_800A3B80_3 *arg0, s32 unused, void *arg2)
{
    Scratch *scratch;
    s32 coord_y;
    s32 coord_x;
    s32 calc;
    register s32 adjusted ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 *global_base;
    void *town;
    void *root;
    void *next_root;
    S_800A3B80_5 *end_town;
    S_800A3B80_1 *arg2_temp;
    S_800A3B80_2 *arg2_data;
    u16 origin_y;
    u16 origin_x;
    s32 positive;
    s32 negative;
    s32 next_angle;
    s32 initial_adjusted;

    scratch = (Scratch *)0x1F800000;
    global_base = (u8 *)&D_80083160;
    town = D_80083160.root;
    root = ((S_800A3B80_0 *)town)->unk_8D0;
    scratch->data20 = (u8 *)town + 0x8B0;
    origin_y = D_80100D88;
    origin_x = D_80100D8A;
    arg2_temp = arg2;
    arg2_data = arg2_temp->unk_08;
    scratch->data118 = arg2_data;
    arg2_temp->unk_0F = arg2_data->unk_01;

    initial_adjusted = arg0->unk_06;
    result = D_80083160.angle;
    initial_adjusted += 0xC00;
    result = (result + 0x80) & 0xF00;
    initial_adjusted -= result;
    adjusted = initial_adjusted;
    negative = adjusted;
    positive = adjusted;
    ASM_KEEP(adjusted);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    adjusted = (s16)adjusted;
    calc = func_80064584(adjusted) * 6;
    coord_y = calc - origin_y;
    calc = func_800644B8(adjusted) * 6;
    coord_x = calc - origin_x;

positive_store_first:
    scratch->data80 = coord_y;
    scratch->data70 = coord_y;
    result = coord_x << 16;
    adjusted = result >> 16;
    if (arg0->unk_0C != 0) {
        calc = adjusted - (func_800644B8(((s32)(positive << 16) >> 14) +
                                         (arg0->unk_00 << 5)) >> 1);
    } else {
        calc = adjusted + (func_800644B8(((s32)(positive << 16) >> 14) +
                                         (arg0->unk_00 << 5)) >> 1);
    }
    result = positive + 0x80;
    positive = result;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    next_angle = (s16)result;
    scratch->data82 = calc;
    scratch->data72 = calc;
    adjusted = func_80064584(next_angle) * 6;
    adjusted -= origin_y;
    coord_y = adjusted;
    calc = func_800644B8(next_angle) * 6;
    scratch->data88 = adjusted;
    scratch->data78 = adjusted;
    calc -= origin_x;
    coord_x = calc;
    calc <<= 16;
    adjusted = calc >> 16;
    if (arg0->unk_0C != 0) {
        result = adjusted - (func_800644B8((next_angle * 4) +
                                           (arg0->unk_00 << 5)) >> 1);
    } else {
        result = adjusted + (func_800644B8((next_angle * 4) +
                                           (arg0->unk_00 << 5)) >> 1);
    }
    {
        void *call_object;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        void *call_arg2;
        void *call_scratch;
        void *call_root;
        call_object = arg0;
        call_scratch = scratch;
        call_arg2 = arg2;
        call_root = root;
        scratch->data8A = result;
        scratch->data7A = result;
        next_root = func_800A41D8(call_object, call_arg2, call_scratch,
                                  call_root, 0);
    }
    if (next_root == 0) {
        goto negative_begin;
    }
    root = next_root;

    scratch->data80 = coord_y;
    scratch->data70 = coord_y;
    result = coord_x << 16;
    adjusted = result >> 16;
    if (arg0->unk_0C != 0) {
        calc = adjusted - (func_800644B8(((s32)(positive << 16) >> 14) +
                                         (arg0->unk_00 << 5)) >> 1);
    } else {
        calc = adjusted + (func_800644B8(((s32)(positive << 16) >> 14) +
                                         (arg0->unk_00 << 5)) >> 1);
    }
    result = positive + 0x80;
    positive = result;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    next_angle = (s16)result;
    scratch->data82 = calc;
    scratch->data72 = calc;
    adjusted = func_80064584(next_angle) * 6;
    adjusted -= origin_y;
    coord_y = adjusted;
    calc = func_800644B8(next_angle) * 6;
    scratch->data88 = adjusted;
    scratch->data78 = adjusted;
    calc -= origin_x;
    coord_x = calc;
    calc <<= 16;
    adjusted = calc >> 16;
    if (arg0->unk_0C != 0) {
        result = adjusted - (func_800644B8((next_angle * 4) +
                                           (arg0->unk_00 << 5)) >> 1);
    } else {
        result = adjusted + (func_800644B8((next_angle * 4) +
                                           (arg0->unk_00 << 5)) >> 1);
    }
    {
        void *call_object;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        void *call_arg2;
        void *call_scratch;
        void *call_root;
        call_object = arg0;
        call_scratch = scratch;
        call_arg2 = arg2;
        call_root = root;
        scratch->data8A = result;
        scratch->data7A = result;
        next_root = func_800A41D8(call_object, call_arg2, call_scratch,
                                  call_root, 1);
    }
    if (next_root != 0) {
        root = next_root;
        goto positive_store_first;
    }

negative_begin:
    adjusted = (s16)negative;
    calc = func_80064584(adjusted) * 6;
    coord_y = calc - origin_y;
    calc = func_800644B8(adjusted) * 6;
    coord_x = calc - origin_x;

negative_store_first:
    scratch->data88 = coord_y;
    scratch->data78 = coord_y;
    result = coord_x << 16;
    adjusted = result >> 16;
    if (arg0->unk_0C != 0) {
        calc = adjusted - (func_800644B8(((s32)(negative << 16) >> 14) +
                                         (arg0->unk_00 << 5)) >> 1);
    } else {
        calc = adjusted + (func_800644B8(((s32)(negative << 16) >> 14) +
                                         (arg0->unk_00 << 5)) >> 1);
    }
    result = negative - 0x80;
    negative = result;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    next_angle = (s16)result;
    scratch->data8A = calc;
    scratch->data7A = calc;
    adjusted = func_80064584(next_angle) * 6;
    adjusted -= origin_y;
    coord_y = adjusted;
    calc = func_800644B8(next_angle) * 6;
    scratch->data80 = adjusted;
    scratch->data70 = adjusted;
    calc -= origin_x;
    coord_x = calc;
    calc <<= 16;
    adjusted = calc >> 16;
    if (arg0->unk_0C != 0) {
        result = adjusted - (func_800644B8((next_angle * 4) +
                                           (arg0->unk_00 << 5)) >> 1);
    } else {
        result = adjusted + (func_800644B8((next_angle * 4) +
                                           (arg0->unk_00 << 5)) >> 1);
    }
    {
        void *call_object;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        void *call_arg2;
        void *call_scratch;
        void *call_root;
        call_object = arg0;
        call_scratch = scratch;
        call_arg2 = arg2;
        call_root = root;
        scratch->data82 = result;
        scratch->data72 = result;
        next_root = func_800A41D8(call_object, call_arg2, call_scratch,
                                  call_root, 1);
    }
    if (next_root == 0) {
        goto done;
    }
    root = next_root;

    scratch->data88 = coord_y;
    scratch->data78 = coord_y;
    result = coord_x << 16;
    adjusted = result >> 16;
    if (arg0->unk_0C != 0) {
        calc = adjusted - (func_800644B8(((s32)(negative << 16) >> 14) +
                                         (arg0->unk_00 << 5)) >> 1);
    } else {
        calc = adjusted + (func_800644B8(((s32)(negative << 16) >> 14) +
                                         (arg0->unk_00 << 5)) >> 1);
    }
    result = negative - 0x80;
    negative = result;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    next_angle = (s16)result;
    scratch->data8A = calc;
    scratch->data7A = calc;
    adjusted = func_80064584(next_angle) * 6;
    adjusted -= origin_y;
    coord_y = adjusted;
    calc = func_800644B8(next_angle) * 6;
    scratch->data80 = adjusted;
    scratch->data70 = adjusted;
    calc -= origin_x;
    coord_x = calc;
    calc <<= 16;
    adjusted = calc >> 16;
    if (arg0->unk_0C != 0) {
        result = adjusted - (func_800644B8((next_angle * 4) +
                                           (arg0->unk_00 << 5)) >> 1);
    } else {
        result = adjusted + (func_800644B8((next_angle * 4) +
                                           (arg0->unk_00 << 5)) >> 1);
    }
    {
        void *call_object;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        void *call_arg2;
        void *call_scratch;
        void *call_root;
        call_object = arg0;
        call_scratch = scratch;
        call_arg2 = arg2;
        call_root = root;
        scratch->data82 = result;
        scratch->data72 = result;
        next_root = func_800A41D8(call_object, call_arg2, call_scratch,
                                  call_root, 0);
    }
    if (next_root != 0) {
        root = next_root;
        goto negative_store_first;
    }

done:
    end_town = ((S_800A3B80_4 *)global_base)->unk_00;
    end_town->unk_8D0 = root;
    return 0;
}
