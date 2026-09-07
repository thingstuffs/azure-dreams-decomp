#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u8 pad0[8];
    void *field8;
    void *fieldC;
    void *field10;
} DungeonObject;

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[2];
    u16 field6;
    u8 pad8[2];
    u16 fieldA;
} DungeonCoords;

typedef struct {
    u8 pad0[6];
    s16 field6;
    s32 field8;
    u8 fieldC;
    u8 fieldD;
    u8 fieldE;
    u8 padF[0xD];
    s16 field1C;
    s16 field1E;
} DungeonState;

typedef struct {
    u8 pad0[0x60];
    void *field60;
    u8 pad64[0x24];
    u16 field88;
    s32 field8C;
    s32 field90;
    u8 pad94[4];
    s32 field98;
    void *field9C;
} DungeonData;

typedef struct {
    u8 field0;
    u8 field1;
    u16 field2;
    u16 field4;
    u8 pad6[6];
} DungeonTile;

extern u8 D_80045340[];
extern u8 D_800A871C[];
extern DungeonTile D_800E36C8[];

extern void *func_8003FD64(s32, s32);
extern void func_8004491C(void *, void *);
extern s32 func_80099FDC(void *);
extern s32 func_800A7A38(void *);
extern void func_800BC26C(void *, s32, s32, s32);

void *func_800A8E74(s32 arg0, DungeonCoords *arg1, s32 arg2,
                    DungeonData *arg3, s32 *arg4, volatile s32 arg5) {
    DungeonObject *object;
    DungeonData *data;
    DungeonCoords *coords;
    DungeonState *state;
    DungeonTile *tiles;
    s16 index;
    s32 arg4_value;

    index = arg5;
    object = func_8003FD64(0x110, arg0 - 0x20);
    if (object != NULL) {
        data = (DungeonData *)((u8 *)object + 0x20);
        object->field10 = D_800A871C;
        coords = object->field8;
        state = object->fieldC;
        data->field60 = arg3;
        if (index >= 0) {
            DungeonTile *tile;
            tiles = D_800E36C8;
            tile = &tiles[index];
            coords->field2 = (tile->field0 << 6) + 0x20;
            coords->field6 = (tile->field1 << 6) + 0x20;
            coords->fieldA = tile->field2;
            data->field88 = tile->field4;
        } else {
            coords->field2 = arg1->field2;
            coords->field6 = arg1->field6;
            coords->fieldA = arg1->fieldA;
            data->field88 = arg3->field88;
        }
        func_8004491C(object, D_80045340);
        state->fieldE = 0x80;
        state->fieldD = 0x80;
        state->fieldC = 0x80;
        state->field1E = 0x1000;
        state->field1C = 0x1000;
        state->field6 = 2;
        state->field8 = func_800A7A38(arg4);
        data->field8C = *(s32 *)((u8 *)arg3 - 0x18);
        data->field90 = *(s32 *)((u8 *)arg3 - 0x14);
        arg4_value = *arg4;
        data->field9C = &data->field98;
        *(u8 *)((u8 *)data + 0x13) = 0xFF;
        data->field98 = arg4_value;
        func_80099FDC(object);
        func_800BC26C(object, 0, 0, 0);
    }
    return object;
}
