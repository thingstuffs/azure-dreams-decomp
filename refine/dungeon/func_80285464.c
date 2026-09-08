#include "common.h"

typedef struct MapCell {
    s16 kind;
    u16 value;
    s16 flags;
} MapCell;

typedef struct DungeonCfg {
    MapCell *cells;
    u8 pad04[16];
    s16 shift_x;
    s16 shift_y;
    s16 mask_x;
    s16 mask_y;
    s16 span_x;
    s16 span_y;
} DungeonCfg;

typedef struct Room {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
    u8 pad08[2];
    s16 active;
    u8 pad0C[2];
    s16 count;
    u8 *tiles;
} Room;

typedef struct RoomCell {
    u8 a;
    u8 b;
    u16 c;
} RoomCell;

typedef struct Ent8 {
    s16 kind;
    s16 x;
    s16 y;
    s16 value;
} Ent8;

typedef struct RecA {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
} RecA;

typedef struct RecB {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    s16 f4;
    s16 f6;
    s32 f8;
} RecB;

typedef struct RecC {
    u8 pad00[6];
    u8 f6;
    u8 f7;
    s32 f8;
    u8 pad0C[12];
} RecC;

typedef struct RecD {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
} RecD;

#define ROOM_CELL(r, n) (*(RoomCell *)&D_800E2C40[((n) << 2) + ((r) << 6)])

extern void func_8003E4FC(s32, s32, s32);
extern void func_8003F320(void);
extern s32 func_800199C8(s16);
extern void func_8009A21C(s32, s32, s32);
extern s32 func_800A7A38(RecA *);
extern void func_8004068C(u8 *, u8 *);
extern s32 func_800BCA68(s32, s32);

extern s32 D_8001F604[];
extern s16 D_8001F586;
extern u8 *D_8008148C;
extern u8 *D_80081480;
extern s16 D_8008146E;
extern DungeonCfg D_8008333C;
extern s32 D_800DF258[];
extern Room D_800E2970[];
extern s32 D_800E296C;
extern u8 D_800E2C40[];
extern RecA D_800E3548[];
extern RecD D_800E3648[];
extern RecB D_800E36C8[];
extern RecC D_800E39C8[];
extern Ent8 D_800E3CD8[];
extern s32 D_800E3D6C;
extern u8 D_800EA000[];

/* Loads dungeon layout data into rooms, map cells, and placed records. */
void func_80018464(s16 layout_number)
{
    DungeonCfg *cfg;
    MapCell *map;
    RecB *placed_record;
    u8 *data;
    u16 *room_header;
    s32 entry_index;
    s16 layout_index;
    s32 x_or_marker;
    register s32 layout_id ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 map_value;
    u16 tile_value;
    u16 shift_y;

    layout_index = layout_number - 1;
    layout_id = D_8001F604[layout_index];
    data = D_8008148C;
    D_80081480 = data;
    cfg = &D_8008333C;
    map = cfg->cells;
    func_8003E4FC(6, layout_id, 0);
    func_8003F320();
    entry_index = 0;

    room_header = (u16 *)(data + 4);
    cfg->shift_x = ((u16 *)data)[0];
    cfg->mask_x = (1 << cfg->shift_x) - 1;
    shift_y = ((u16 *)data)[1];
    cfg->span_x = 64 << cfg->shift_x;
    cfg->shift_y = shift_y;
    cfg->mask_y = (1 << cfg->shift_y) - 1;
    cfg->span_y = 64 << cfg->shift_y;

    while (room_header[2] != 0) {
        D_800E2970[entry_index].active = 1;
        D_800E2970[entry_index].x = room_header[0];
        D_800E2970[entry_index].y = room_header[1];
        D_800E2970[entry_index].w = room_header[2];
        D_800E2970[entry_index].h = room_header[3];
        D_800E2970[entry_index].count = 0;
        data = (u8 *)(room_header + 4);
        ASM_KEEP_NV(room_header);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        while (*data != 0) {
            D_800E2970[entry_index].tiles = &D_800E2C40[entry_index << 6];
            ROOM_CELL(entry_index, D_800E2970[entry_index].count).a = *data++;
            ROOM_CELL(entry_index, D_800E2970[entry_index].count).b = *data++;
            ROOM_CELL(entry_index, D_800E2970[entry_index].count).c = *data;
            data += 2;
            D_800E2970[entry_index].count++;
        }
        entry_index++;
        data += 2;
        room_header = (u16 *)data;
    }
    data = (u8 *)(room_header + 4);
    ASM_KEEP_NV(data);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    D_8008146E = entry_index;
    entry_index = 0;
    while (*data != 0) {
        D_800E3CD8[entry_index].kind = data[2] + 2;
        D_800E3CD8[entry_index].x = data[0];
        D_800E3CD8[entry_index].y = data[1];
        tile_value = map[data[0] + (data[1] << cfg->shift_x)].value - 32;
        map[data[0] + (data[1] << cfg->shift_x)].value = tile_value;
        D_800E3CD8[entry_index].value = tile_value;
        if (D_800E3CD8[entry_index].kind == 2) {
            map[data[0] + (data[1] << cfg->shift_x)].kind = 1;
        }
        func_8009A21C(data[0], data[1], 32);
        entry_index++;
        data += 4;
    }
    if (func_800199C8(entry_index) != 0) {
        entry_index++;
    }
    D_8001F586 = 1;
    entry_index++;
    while (entry_index < 4) {
        D_800E3CD8[entry_index].kind = 0;
        entry_index++;
    }

    data += 2;
    entry_index = 0;
    while ((x_or_marker = *data) != 0) {
        if (x_or_marker == 99) {
            D_800E3D6C |= 2;
            data += 6;
            break;
        }
        data++;
        D_800E36C8[entry_index].f0 = x_or_marker;
        D_800E36C8[entry_index].f1 = *data++;
        D_800E3548[entry_index].f0 = *data++;
        D_800E3548[entry_index].f1 = *data++;
        D_800E3548[entry_index].f3 = *data++;
        D_800E3548[entry_index].f2 = *data++;
        D_800E36C8[entry_index].f8 = func_800A7A38(&D_800E3548[entry_index]);
        entry_index++;
    }
    while (entry_index < 64) {
        D_800E3548[entry_index].f1 = 0;
        D_800E3548[entry_index].f0 = 0;
        entry_index++;
    }

    data += 2;
    entry_index = 0;
    while ((x_or_marker = *data) != 0) {
        if (x_or_marker == 99) {
            D_800E3D6C |= 8;
            data += 6;
            break;
        }
        data++;
        D_800E39C8[entry_index].f6 = x_or_marker;
        D_800E39C8[entry_index].f7 = *data++;
        D_800E3648[entry_index].f0 = *data++;
        D_800E3648[entry_index].f1 = *data++;
        D_800E3648[entry_index].f3 = *data++;
        D_800E3648[entry_index].f2 = *data++;
        D_800E39C8[entry_index].f8 = D_800DF258[D_800E3648[entry_index].f0];
        func_8009A21C(D_800E39C8[entry_index].f6, D_800E39C8[entry_index].f7, 32);
        entry_index++;
    }

    data += 2;
    while (*data != 0) {
        D_800E296C |= 0x10000000;
        D_800E39C8[entry_index].f6 = *data++;
        D_800E39C8[entry_index].f7 = *data++;
        D_800E3648[entry_index].f0 = *data++;
        D_800E3648[entry_index].f1 = *data++;
        D_800E3648[entry_index].f3 = *data++;
        D_800E3648[entry_index].f2 = *data++;
        entry_index++;
    }
    data += 2;
    while (entry_index < 32) {
        D_800E3648[entry_index].f1 = 0;
        D_800E3648[entry_index].f0 = 0;
        entry_index++;
    }

    func_8004068C(data, D_800EA000);
    for (entry_index = 0; D_800E3548[entry_index].f1 != 0; entry_index++) {
        placed_record = &D_800E36C8[entry_index];
        map_value = func_800BCA68(placed_record->f0 << 6, placed_record->f1 << 6);
        placed_record->f4 = map_value;
        *(s16 *)&placed_record->f2 = map_value;
    }
}
