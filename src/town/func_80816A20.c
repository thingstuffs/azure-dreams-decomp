#include "common.h"

typedef struct TownDraw24 {
    s16 unk00;
    s16 unk02;
    void *unk04;
    u32 unk08;
    s16 unk0C;
    s16 unk0E;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u16 flags;
    u8 pad18[0x10];
} TownDraw24;

typedef struct TownDraw32 {
    s16 unk00;
    s16 unk02;
    void *unk04;
    void *unk08;
    void *unk0C;
    u32 unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    u8 pad20[0x10];
} TownDraw32;

typedef struct TownTransform {
    s32 value[3];
} TownTransform;

typedef struct TownData {
    u8 pad00[0x0C];
    u32 color;
    u8 pad10[0x0C];
    s16 angle1C;
    s16 angle1E;
} TownData;

typedef struct TownPart TownPart;
typedef struct TownObject TownObject;

struct TownPart {
    u8 pad00[4];
    TownObject *child;
    u8 pad08[0xA4];
    TownPart *root;
};

struct TownObject {
    u8 pad00[8];
    TownTransform *transform;
    TownData *data;
    void (*callback)(void *);
    u8 pad14[0x0C];
    TownPart part;
};

extern u8 D_8002017C[];
extern u8 D_80020260[];
extern u8 D_80020360[];
extern u8 D_800203F4[];
extern u8 D_80020488[];
extern u8 D_80020510[];
extern void func_80020DF0(void *);
extern void func_8002191C(void *);
extern u8 D_80026DC8[];
extern void *D_80026EE0[];
extern void *D_80026F04[];
extern void *D_80026F08[];
extern s16 D_800272A0[];
extern s16 D_800272B0[];
extern s32 D_800272C0[];
extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_800F2F28[];

extern void func_800206F4(void *, TownDraw32 *);
extern void func_80020788(void *, TownDraw24 *);
extern void func_80033B9C(s32);
extern void func_8003DB94(TownData *, void *, s32);
extern void func_8003E188(s32, void *);
extern TownObject *func_8003FD64(s32, void *);
extern void func_8004491C(TownObject *, void *);
extern void func_80053DA8(s32);
extern void func_8008F0A4(TownPart *, TownTransform *, void *);

/* Initializes the town display objects, panel lines, and image tiles. */
s32 func_80020A20(void)
{
    TownDraw32 tile;
    TownDraw24 draw;
    TownDraw24 *draw_ptr;
    TownPart *root_part;
    TownObject *object;
    TownPart *object_part;
    TownData *object_data;
    s16 *filled_entry;
    s16 *zero_entry;
    void **images;
    s32 index;
    s32 initial_value;

    root_part = 0;
    func_80053DA8(0x704);
    func_80033B9C(0xA5);
    func_8003E188(0x3D, root_part);
    func_8003E188(0x3E, root_part);

    object = func_8003FD64(1, D_80083498);
    if (object != 0) {
        root_part = &object->part;
        object->callback = func_8002191C;
    }

    object = func_8003FD64(0x136, D_80083498);
    root_part->child = object;
    if (object != 0) {
        object->callback = func_80020DF0;
        func_8004491C(object, D_80045340);

        object_part = &object->part;
        object_data = object->data;
        object->transform->value[0] = 0x03A00000;
        object->transform->value[1] = 0x01E00000;
        object->transform->value[2] = 0x00200000;
        object_part->root = root_part;
        object_data->angle1E = 0x1000;
        object_data->angle1C = 0x1000;
        func_8003DB94(object_data, D_800F2F28, 0);
        object_data->color = 0x00808080;
        func_8008F0A4(object_part, object->transform, D_80026DC8);
    }

    index = 7;
    initial_value = 0x30;
    zero_entry = D_800272B0;
    filled_entry = zero_entry + 7;
    zero_entry = D_800272A0;
    zero_entry += 7;
    do {
        *zero_entry = 0;
        *filled_entry = initial_value;
        filled_entry--;
        index--;
        zero_entry--;
    } while (index >= 0);

    draw_ptr = &draw;
    D_800272C0[0] = 0x3020;
    draw.unk0C = 0x30;
    draw.unk0E = 0xA0;
    draw.unk10 = 0xE0;
    draw.unk12 = 0x22;
    draw.unk14 = 2;
    draw.unk08 = 0x404040;
    draw.unk00 = 0;
    draw.unk02 = 0x10;
    draw.unk04 = root_part;
    draw.flags |= 3;
    func_80020788(D_8002017C, draw_ptr);

    draw.unk0C = 0x7A;
    draw.unk0E = 0x40;
    draw.unk10 = 0x50;
    draw.unk12 = 0x10;
    draw.unk14 = 2;
    draw.unk08 = 0;
    draw.unk00 = 0;
    draw.unk02 = 0x10;
    draw.unk04 = root_part;
    draw.flags |= 0xFFFD;
    func_80020788(D_80020260, draw_ptr);

    draw.unk0E = 0xA2;
    draw.unk10 = 1;
    draw.unk12 = 0x1E;
    draw.unk14 = 0;
    draw.unk08 = 0x808080;
    draw.unk00 = 0;
    draw.unk04 = root_part;
    index = 8;
    do {
        draw.unk0C = 0x60 + index * 0x10;
        func_80020788(D_80020360, &draw);
        index--;
    } while (index >= 0);

    draw.unk0C = 0x32;
    draw.unk0E = 0xB0;
    draw.unk10 = 0xDC;
    draw.unk12 = 1;
    func_80020788(D_80020360, &draw);

    tile.unk10 = 0x808080;
    tile.unk14 = 0x34;
    tile.unk16 = 0xB6;
    tile.unk18 = 3;
    tile.unk1C = 2;
    tile.unk1A = 0x7C80;
    tile.unk00 = 0;
    tile.unk02 = 0x10;
    tile.unk0C = root_part;
    tile.unk04 = D_80026F04[0];
    func_800206F4(D_800203F4, &tile);

    {
        void **image_base = D_80026EE0;

        images = image_base;
    }
    tile.unk16 = 0xA4;
    index = 8;
    do {
        tile.unk04 = images[index];
        tile.unk14 = 0x64 + index * 0x10;
        func_800206F4(D_800203F4, &tile);
        index--;
    } while (index >= 0);

    tile.unk14 = 0xF4;
    tile.unk16 = 0xB6;
    tile.unk04 = D_800272C0;
    func_800206F4(D_80020510, &tile);

    tile.unk14 = 0x7E;
    tile.unk16 = 0x44;
    tile.unk04 = D_80026F08[0];
    func_800206F4(D_80020488, &tile);
    return 0;
}
