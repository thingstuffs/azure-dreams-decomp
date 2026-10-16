#ifndef DUNGEON_FLOOR_SPAWNS_H
#define DUNGEON_FLOOR_SPAWNS_H
#include "common.h"
#include "modules/dungeon_floor_switch_owners.h"
#include "m2c_compat.h"
#include "shared/dungeon_item_entries.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_floor.h"
#include "shared/object_node.h"
typedef struct {
    u8 x;
    u8 y;
    s8 pad[10];
} floor_spawns_isolated_8028B110_DungeonPosition;
typedef struct {
    u8 x;
    u8 y;
    u8 pad2[2];
    s16 field4;
    u8 pad6;
    u8 field7;
    s32 field8;
} floor_spawns_isolated_8028B18C_DungeonRecord;
typedef struct {
    u16 flags;
    u8 pad2[18];
} floor_spawns_isolated_8028B18C_DungeonItem;
typedef struct {
    u8 pad0[12];
    floor_spawns_isolated_8028B18C_DungeonItem *entries;
    u8 pad10[4];
} floor_spawns_isolated_8028B18C_DungeonGroup;
typedef struct floor_spawns_isolated_8028B660_S_8001E660_0 {
    u8 pad_00[0xFB];
    u8 unk_FB;
} floor_spawns_isolated_8028B660_S_8001E660_0;
typedef struct floor_spawns_isolated_8028B824_S_8001E824_0 {
    u8 unk_00;
    u8 unk_01;
    s8 unk_02;
    s8 unk_03;
} floor_spawns_isolated_8028B824_S_8001E824_0;
typedef struct {
    u16 flags;
    u8 pad2[18];
} floor_spawns_isolated_8028B994_DungeonItem;
typedef struct {
    u8 pad0[2];
    u8 count;
    u8 pad3[9];
    floor_spawns_isolated_8028B994_DungeonItem *entries;
    u8 pad10[4];
} floor_spawns_isolated_8028B994_DungeonGroup;
typedef struct floor_spawns_isolated_8028BAA4_ItemCategoryRow {
    u8 pad_00[0xC];
    s32 item_table;
} floor_spawns_isolated_8028BAA4_ItemCategoryRow;
typedef struct {
    u8 x;
    u8 y;
    u8 pad2[2];
    s16 height;
    u8 pad6;
    u8 flag7;
    s32 object;
} floor_spawns_isolated_8028BC54_DungeonCell;
typedef struct floor_spawns_isolated_8028BF0C_S_8001EF0C_0 {
    u8 pad_00[0x11];
    u8 unk_11;
    s8 unk_12;
    u8 pad_13[0x5];
    u32 unk_18;
    u8 pad_1C[0x27];
    union { u8 s; s8 u; } unk_43;   
} floor_spawns_isolated_8028BF0C_S_8001EF0C_0;
typedef struct floor_spawns_isolated_8028BF0C_S_8001EF0C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
} floor_spawns_isolated_8028BF0C_S_8001EF0C_1;
typedef struct {
    u8 type;
    u8 state;
    u8 unk2;
    u8 unk3;
} floor_spawns_isolated_8028BF0C_SpawnMeta;
typedef struct {
    u8 pad0[6];
    u8 x;
    u8 y;
    s32 value;
    s32 zero;
    s16 unk10;
    s16 unk12;
    u16 flags;
    u16 pad16;
} floor_spawns_isolated_8028BF0C_SpawnPosition;
typedef struct {
    u32 initial[1];
    s32 limits[1];
} floor_spawns_isolated_8028BF0C_SpawnTables;
typedef void *(*SpawnFunc)(s32, s32, s32, s32);
#define floor_spawns_isolated_8028BF0C_PAGE_8008 ((u8 *)0x80080000)
typedef struct floor_spawns_isolated_8028C354_S_8001F354_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} floor_spawns_isolated_8028C354_S_8001F354_0;
typedef struct floor_spawns_isolated_8028C354_S_8001F354_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} floor_spawns_isolated_8028C354_S_8001F354_1;
extern void func_8009A21C(s16 x, s16 y, u16 flags);
extern s32 selectDungeonSpawnTile(u8 *, u8 *);
extern s16 func_800A6928(s32, s32);
extern s32 func_800A6D30(void);
extern s32 func_800A71F4(void);
extern s32 func_800A7A38(u8 *item);
extern s16 dungeonGetSurfaceHeightAtCoordinates(s32, s32);
extern u8 D_800DDC9C[];
extern s16 D_80081468[3];
extern s32 D_800E3D6C[];
extern s32 func_80033BC0(s32);
extern s32 func_800A697C(s32, s32);
extern s16 D_8001F6F8[];
extern s32 randomDungeonRange16(s32, s32);
extern u8 D_80010000[];
extern floor_spawns_isolated_8028BF0C_SpawnTables D_800835E4[];
extern s32 D_800835E8[];
extern floor_spawns_isolated_8028BF0C_SpawnPosition D_800E39C8[];
extern u8 *D_800735C4[];
extern u8 D_800DF258[];
extern void func_8003DB94(void *, s32, s32);
extern void func_80042640(void *, s32);
extern SpawnFunc func_800A0B94(s32 resource_id, u8 *resource_entry, s32 wait_for_read);
extern void retainSpawnResource(s32, s32);
extern s32 func_800A1618(s32, s32);
extern void raiseEntityLevel(void *, s32);
extern s16 func_800BCB04(s32 x, s32 y, s16 min_height);
extern s32 func_8004491C();
extern s32 D_80044BB0[3];
extern s32 D_800A5AF0[3];
extern void func_8004E634(s16, u8 *);
extern void *D_8001F5B4[];
extern u8 D_80077DE8[];
extern u8 D_80077E00[];
s32 isFloorItemTileOccupied(s32 excluded_slot, s16 x, s16 y);
void populateFloorItemRecords(void);
s32 selectFloorItemWithSpecialOverrides(s8 *out_group, s8 *out_index, s32 unused, s32 skip_special);
void clearDungeonCellEntries(void);
void buildCumulativeItemWeights(void);
s32 selectWeightedFloorItem(s8 *category_out, s8 *item_out);
void generateRandomDungeonItemDrops(void);
void restoreSpawnsAndPlaceFloorTraps(void);
void clearDungeonObjectEntries(void);
void createTintedDungeonObject(s16 x, s16 y, s16 tinted, s32 render_param);
void drawDungeonValueAndLabel(void);
extern u8 D_800E36C8[];
extern u8 D_8001F6F0[];
extern u8 D_80073414[];
extern u8 D_8008146C[];
extern u8 D_800E3648[];
#endif
