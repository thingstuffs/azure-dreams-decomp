#include "common.h"

typedef struct { u8 unk0; u8 unk1; s8 unk2; u8 unk3; } FuncData;
typedef struct { u8 pad[0x1C]; s32 flags; } FuncState;

extern void *func_8003AD08();
extern void *func_80099194();
extern void *func_800992A8();
extern void *func_800992E8();
extern u8 *D_800DD720;
extern s32 D_800DD72C[];
extern s32 D_800DD784[];
extern FuncState *D_800E3D7C;

/* Appends formatted data with type-specific affixes and a numeric value to the buffer. */
u8 *func_80099368(FuncData *data, u8 *buffer) {
    s32 prefix_id;
    s32 suffix_id;
    s32 value;
    u8 prefix_kind;
    u8 suffix_kind;
    u8 kind;
    u8 *unused_cursor;
    u8 *format;
    u8 *value_end;
    u8 *out;

    out = buffer;
    if (!(D_800E3D7C->flags & 0x10)) {
        prefix_kind = data->unk1;
        prefix_id = D_800DD72C[prefix_kind];
        if ((prefix_id != 0) && ((prefix_kind != 0xF) || (data->unk0 < 0xEU))) {
            out = func_80099194(prefix_id, out, out);
        }
    }
    out = func_800992E8(data, out, out);
    if (D_800E3D7C->flags & 0x10) {
        goto return_out;
    }
    suffix_kind = data->unk1;
    suffix_id = D_800DD784[suffix_kind];
    if ((suffix_id != 0) && ((suffix_kind != 0xF) || (data->unk0 < 0xEU))) {
        out = func_80099194(suffix_id, out, out);
    }
    kind = data->unk1;
    switch (kind) {
    case 4:
        if (!(data->unk3 & 0x80)) {
            format = D_800DD720;
            value = data->unk2;
            *out++ = *format++;
            *out = *format++;
            value_end = func_8003AD08(value, out + 1, out);
            out = value_end;
            *out++ = *format++;
            *out++ = *format++;
        }
        break;
    case 14:
    case 18:
    case 19:
    case 21:
        break;
    default:
        if (!(data->unk3 & 0x80)) {
            value = data->unk2;
            if (value != 0) {
                out = func_800992A8(value, out, out);
                if (value < 0) value = -value;
                out = func_8003AD08(value, out, out);
            }
        }
        break;
    }
return_out:
    return out;
}
