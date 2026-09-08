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

/* Emits segments in both angular directions and updates the town output pointer. */
s32 func_800A3B80(S_800A3B80_3 *object, s32 unused, void *context)
{
    Scratch *scratch;
    s32 coord_y;
    s32 coord_x;
    s32 coord_value;
    register s32 angle_or_coord ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 *global_base;
    void *town;
    void *output;
    void *next_output;
    S_800A3B80_5 *end_town;
    S_800A3B80_1 *context_view;
    S_800A3B80_2 *context_data;
    u16 origin_y;
    u16 origin_x;
    s32 forward_angle;
    s32 reverse_angle;
    s32 next_angle;
    s32 start_angle;

    scratch = (Scratch *)0x1F800000;
    global_base = (u8 *)&D_80083160;
    town = D_80083160.root;
    output = ((S_800A3B80_0 *)town)->unk_8D0;
    scratch->data20 = (u8 *)town + 0x8B0;
    origin_y = D_80100D88;
    origin_x = D_80100D8A;
    context_view = context;
    context_data = context_view->unk_08;
    scratch->data118 = context_data;
    context_view->unk_0F = context_data->unk_01;

    start_angle = object->unk_06;
    result = D_80083160.angle;
    start_angle += 0xC00;
    result = (result + 0x80) & 0xF00;
    start_angle -= result;
    angle_or_coord = start_angle;
    reverse_angle = angle_or_coord;
    forward_angle = angle_or_coord;
    ASM_KEEP(angle_or_coord);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    angle_or_coord = (s16)angle_or_coord;
    coord_value = func_80064584(angle_or_coord) * 6;
    coord_y = coord_value - origin_y;
    coord_value = func_800644B8(angle_or_coord) * 6;
    coord_x = coord_value - origin_x;

forward_segment:
    scratch->data80 = coord_y;
    scratch->data70 = coord_y;
    result = coord_x << 16;
    angle_or_coord = result >> 16;
    if (object->unk_0C != 0) {
        coord_value = angle_or_coord -
            (func_800644B8(((s32)(forward_angle << 16) >> 14) +
                           (object->unk_00 << 5)) >> 1);
    } else {
        coord_value = angle_or_coord +
            (func_800644B8(((s32)(forward_angle << 16) >> 14) +
                           (object->unk_00 << 5)) >> 1);
    }
    result = forward_angle + 0x80;
    forward_angle = result;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    next_angle = (s16)result;
    scratch->data82 = coord_value;
    scratch->data72 = coord_value;
    angle_or_coord = func_80064584(next_angle) * 6;
    angle_or_coord -= origin_y;
    coord_y = angle_or_coord;
    coord_value = func_800644B8(next_angle) * 6;
    scratch->data88 = angle_or_coord;
    scratch->data78 = angle_or_coord;
    coord_value -= origin_x;
    coord_x = coord_value;
    coord_value <<= 16;
    angle_or_coord = coord_value >> 16;
    if (object->unk_0C != 0) {
        result = angle_or_coord -
            (func_800644B8((next_angle * 4) + (object->unk_00 << 5)) >> 1);
    } else {
        result = angle_or_coord +
            (func_800644B8((next_angle * 4) + (object->unk_00 << 5)) >> 1);
    }
    scratch->data8A = result;
    scratch->data7A = result;
    next_output = func_800A41D8(object, context, scratch, output, 0);
    if (next_output == 0) {
        goto reverse_begin;
    }
    output = next_output;

    scratch->data80 = coord_y;
    scratch->data70 = coord_y;
    result = coord_x << 16;
    angle_or_coord = result >> 16;
    if (object->unk_0C != 0) {
        coord_value = angle_or_coord -
            (func_800644B8(((s32)(forward_angle << 16) >> 14) +
                           (object->unk_00 << 5)) >> 1);
    } else {
        coord_value = angle_or_coord +
            (func_800644B8(((s32)(forward_angle << 16) >> 14) +
                           (object->unk_00 << 5)) >> 1);
    }
    result = forward_angle + 0x80;
    forward_angle = result;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    next_angle = (s16)result;
    scratch->data82 = coord_value;
    scratch->data72 = coord_value;
    angle_or_coord = func_80064584(next_angle) * 6;
    angle_or_coord -= origin_y;
    coord_y = angle_or_coord;
    coord_value = func_800644B8(next_angle) * 6;
    scratch->data88 = angle_or_coord;
    scratch->data78 = angle_or_coord;
    coord_value -= origin_x;
    coord_x = coord_value;
    coord_value <<= 16;
    angle_or_coord = coord_value >> 16;
    if (object->unk_0C != 0) {
        result = angle_or_coord -
            (func_800644B8((next_angle * 4) + (object->unk_00 << 5)) >> 1);
    } else {
        result = angle_or_coord +
            (func_800644B8((next_angle * 4) + (object->unk_00 << 5)) >> 1);
    }
    scratch->data8A = result;
    scratch->data7A = result;
    next_output = func_800A41D8(object, context, scratch, output, 1);
    if (next_output != 0) {
        output = next_output;
        goto forward_segment;
    }

reverse_begin:
    angle_or_coord = (s16)reverse_angle;
    coord_value = func_80064584(angle_or_coord) * 6;
    coord_y = coord_value - origin_y;
    coord_value = func_800644B8(angle_or_coord) * 6;
    coord_x = coord_value - origin_x;

reverse_segment:
    scratch->data88 = coord_y;
    scratch->data78 = coord_y;
    result = coord_x << 16;
    angle_or_coord = result >> 16;
    if (object->unk_0C != 0) {
        coord_value = angle_or_coord -
            (func_800644B8(((s32)(reverse_angle << 16) >> 14) +
                           (object->unk_00 << 5)) >> 1);
    } else {
        coord_value = angle_or_coord +
            (func_800644B8(((s32)(reverse_angle << 16) >> 14) +
                           (object->unk_00 << 5)) >> 1);
    }
    result = reverse_angle - 0x80;
    reverse_angle = result;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    next_angle = (s16)result;
    scratch->data8A = coord_value;
    scratch->data7A = coord_value;
    angle_or_coord = func_80064584(next_angle) * 6;
    angle_or_coord -= origin_y;
    coord_y = angle_or_coord;
    coord_value = func_800644B8(next_angle) * 6;
    scratch->data80 = angle_or_coord;
    scratch->data70 = angle_or_coord;
    coord_value -= origin_x;
    coord_x = coord_value;
    coord_value <<= 16;
    angle_or_coord = coord_value >> 16;
    if (object->unk_0C != 0) {
        result = angle_or_coord -
            (func_800644B8((next_angle * 4) + (object->unk_00 << 5)) >> 1);
    } else {
        result = angle_or_coord +
            (func_800644B8((next_angle * 4) + (object->unk_00 << 5)) >> 1);
    }
    scratch->data82 = result;
    scratch->data72 = result;
    next_output = func_800A41D8(object, context, scratch, output, 1);
    if (next_output == 0) {
        goto done;
    }
    output = next_output;

    scratch->data88 = coord_y;
    scratch->data78 = coord_y;
    result = coord_x << 16;
    angle_or_coord = result >> 16;
    if (object->unk_0C != 0) {
        coord_value = angle_or_coord -
            (func_800644B8(((s32)(reverse_angle << 16) >> 14) +
                           (object->unk_00 << 5)) >> 1);
    } else {
        coord_value = angle_or_coord +
            (func_800644B8(((s32)(reverse_angle << 16) >> 14) +
                           (object->unk_00 << 5)) >> 1);
    }
    result = reverse_angle - 0x80;
    reverse_angle = result;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    next_angle = (s16)result;
    scratch->data8A = coord_value;
    scratch->data7A = coord_value;
    angle_or_coord = func_80064584(next_angle) * 6;
    angle_or_coord -= origin_y;
    coord_y = angle_or_coord;
    coord_value = func_800644B8(next_angle) * 6;
    scratch->data80 = angle_or_coord;
    scratch->data70 = angle_or_coord;
    coord_value -= origin_x;
    coord_x = coord_value;
    coord_value <<= 16;
    angle_or_coord = coord_value >> 16;
    if (object->unk_0C != 0) {
        result = angle_or_coord -
            (func_800644B8((next_angle * 4) + (object->unk_00 << 5)) >> 1);
    } else {
        result = angle_or_coord +
            (func_800644B8((next_angle * 4) + (object->unk_00 << 5)) >> 1);
    }
    scratch->data82 = result;
    scratch->data72 = result;
    next_output = func_800A41D8(object, context, scratch, output, 0);
    if (next_output != 0) {
        output = next_output;
        goto reverse_segment;
    }

done:
    end_town = ((S_800A3B80_4 *)global_base)->unk_00;
    end_town->unk_8D0 = output;
    return 0;
}
