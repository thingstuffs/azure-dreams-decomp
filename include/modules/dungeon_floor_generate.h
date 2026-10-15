#ifndef DUNGEON_FLOOR_GENERATE_H
#define DUNGEON_FLOOR_GENERATE_H
#include "common.h"
#include "modules/dungeon_floor_switch_owners.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_item_entries.h"
#include "shared/dir_step.h"
#include "shared/runtime_dispatch.h"
#include "shared/entity_objects.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8001CE44_arg0.h"
#include "shared/record_ptrs.h"
typedef struct floor_generate_isolated_8028444C_S_8001744C_0 {
    s16 unk_00;
} floor_generate_isolated_8028444C_S_8001744C_0;
typedef struct floor_generate_isolated_8028444C_S_8001744C_1 {
    s16 unk_00;
    s16 unk_02;
} floor_generate_isolated_8028444C_S_8001744C_1;
typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
} floor_generate_isolated_80284480_DungeonCell;
typedef struct floor_generate_isolated_80284560_S_80017560_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
} floor_generate_isolated_80284560_S_80017560_0;
typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
} floor_generate_isolated_80284584_DungeonCell;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))
typedef struct {
    s32 words[2];
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
    s32 field_10;
} floor_generate_isolated_802846EC_DungeonEntry;
typedef struct floor_generate_isolated_802847D8_S_800177D8_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    void * unk_10;
} floor_generate_isolated_802847D8_S_800177D8_0;
typedef struct floor_generate_isolated_802847D8_S_800177D8_1 {
    s8 unk_00;
    s8 unk_01;
    s16 unk_02;
} floor_generate_isolated_802847D8_S_800177D8_1;
typedef struct {
    s16 kind;
    s16 x;
    s16 y;
    s16 value;
} floor_generate_isolated_8028484C_SpawnEntry;
typedef struct {
    u16 flags;
    u16 value;
    u16 extra;
} floor_generate_isolated_8028484C_MapCell;
typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
} floor_generate_isolated_80284A9C_Cell;
typedef struct floor_generate_isolated_80284BEC_S_80017BEC_T {
    u8 pad_00[0x4];
    u16 unk_04;
} floor_generate_isolated_80284BEC_S_80017BEC_T;
typedef struct floor_generate_isolated_80284BEC_S_80017BEC_M {
    floor_generate_isolated_80284BEC_S_80017BEC_T *tiles;
    u8 pad_04[0x10];
    s16 unk_14;
} floor_generate_isolated_80284BEC_S_80017BEC_M;
typedef struct {
    u16 x;
    u16 y;
    s16 width;
    s16 height;
    s8 pad[12];
} floor_generate_isolated_80284EBC_DungeonEntry;
typedef struct {
    u16 f0;
    u16 f2;
    u16 flags;
} floor_generate_isolated_80284EBC_DungeonCell;
typedef struct {
    u16 x;
    u16 y;
    u16 flags;
} floor_generate_isolated_80284F88_DungeonCell;
typedef struct floor_generate_isolated_8028516C_DungeonCell {
    s16 unk0;
    s16 unk2;
    u16 flags;
} floor_generate_isolated_8028516C_DungeonCell;
typedef struct floor_generate_isolated_80285464_MapCell {
    s16 kind;
    u16 value;
    s16 flags;
} floor_generate_isolated_80285464_MapCell;
typedef struct floor_generate_isolated_80285464_Room {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
    u8 pad08[2];
    s16 active;
    u8 pad0C[2];
    s16 count;
    u8 *tiles;
} floor_generate_isolated_80285464_Room;
typedef struct floor_generate_isolated_80285464_RoomCell {
    u8 a;
    u8 b;
    u16 c;
} floor_generate_isolated_80285464_RoomCell;
typedef struct floor_generate_isolated_80285464_Ent8 {
    s16 kind;
    s16 x;
    s16 y;
    s16 value;
} floor_generate_isolated_80285464_Ent8;
typedef struct floor_generate_isolated_80285464_RecB {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    s16 f4;
    s16 f6;
    s32 f8;
} floor_generate_isolated_80285464_RecB;
typedef struct floor_generate_isolated_80285464_RecC {
    u8 pad00[6];
    u8 f6;
    u8 f7;
    s32 f8;
    u8 pad0C[12];
} floor_generate_isolated_80285464_RecC;
typedef struct floor_generate_isolated_80285464_RecD {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
} floor_generate_isolated_80285464_RecD;
#define floor_generate_isolated_80285464_ROOM_CELL(r, n) (*(floor_generate_isolated_80285464_RoomCell *)&D_800E2C40[((n) << 2) + ((r) << 6)])
typedef struct {
    s32 seed;
    u16 flags;
    s16 field6;
    s16 field8;
    s16 fieldA;
    u8 padC[4];
    s8 field10;
    s8 field11;
} floor_generate_isolated_80285A70_State13710;
typedef struct {
    u8 pad0000[0x234];
    s32 level;
    u8 pad0238[0x2090 - 0x238];
    s32 mode;
} floor_generate_isolated_80285A70_Page8001;
typedef struct {
    u8 kind;
    u8 arg;
    u8 track;
    u8 table_index;
    u8 special;
} floor_generate_isolated_80285A70_TrackRecord;
typedef struct {
    u8 pad0000[0x296C];
    u32 flags;
} floor_generate_isolated_80285A70_Page800E;
typedef struct {
    s32 seed;
    u16 level;
    s16 ready;
} floor_generate_isolated_80285A70_SaveHead;
typedef struct {
    u8 pad0000[0x234];
    u16 level;
} floor_generate_isolated_80285A70_LevelPage;
typedef struct floor_generate_isolated_80285E80_DungeonRecord80285E80 {
    u8 value;
    u8 level;
} floor_generate_isolated_80285E80_DungeonRecord80285E80;
typedef struct floor_generate_isolated_80285E80_DungeonState80285E80 {
    u8 pad00[0x18];
    floor_generate_isolated_80285E80_DungeonRecord80285E80 *records;
} floor_generate_isolated_80285E80_DungeonState80285E80;
typedef struct floor_generate_isolated_80285E80_Packed16_80285E80 {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
} __attribute__((packed)) floor_generate_isolated_80285E80_Packed16_80285E80;
typedef struct floor_generate_isolated_80285E80_DungeonGlobals80285E80 {
    u8 pad022c[0x22C];
    s32 state_022c;
    u8 pad0230[4];
    s32 floor_0234;
    u8 pad0238[0x2090 - 0x238];
    s32 state_2090;
} floor_generate_isolated_80285E80_DungeonGlobals80285E80;
#define floor_generate_isolated_80285E80_DUNGEON_GLOBALS ((floor_generate_isolated_80285E80_DungeonGlobals80285E80 *)0x80010000)
typedef struct {
    u8 bytes[0x20];
} __attribute__((packed)) floor_generate_isolated_802864C4_Copy32;
typedef struct floor_generate_isolated_80286684_Object {
    s32 field_0;
} floor_generate_isolated_80286684_Object;
typedef struct floor_generate_isolated_80286894_S_80019894_0 {
    u16 unk_00;
    u8 pad_02[0x2];
    s32 unk_04;
    void * unk_08;
} floor_generate_isolated_80286894_S_80019894_0;
typedef struct {
    u16 active;
    s16 value;
    s16 unused;
} floor_generate_isolated_80286A84_DungeonCell;
typedef struct floor_generate_isolated_80286AF8_MapCell {
    s16 kind;
    s16 value;
    u16 flags;
} floor_generate_isolated_80286AF8_MapCell;
typedef struct floor_generate_isolated_80286AF8_DungeonCfg {
    floor_generate_isolated_80286AF8_MapCell *cells;
    u8 pad04[16];
    s16 shift_x;
    s16 shift_y;
    s16 mask_x;
    s16 mask_y;
    s16 span_x;
    s16 span_y;
} floor_generate_isolated_80286AF8_DungeonCfg;
typedef struct floor_generate_isolated_80286AF8_Room {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
    s16 tint;
    s16 active;
    u16 link;
    u8 pad0E[2];
    u8 *tiles;
} floor_generate_isolated_80286AF8_Room;
typedef struct floor_generate_isolated_80286AF8_Pair {
    u8 a;
    u8 b;
} floor_generate_isolated_80286AF8_Pair;
typedef struct {
    s16 x;
    s16 y;
    s16 unk4;
    s16 dir;
} floor_generate_isolated_80287C4C_Pos;
typedef floor_generate_isolated_80286AF8_MapCell floor_generate_isolated_80287C4C_DungeonCell;
typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
    u8 pad08[2];
    s16 active;
    u8 pad0C[8];
} floor_generate_isolated_80287C4C_Room;
typedef struct {
    s16 x;
    s16 y;
    s16 unk4;
    s16 dir;
} floor_generate_isolated_8028906C_Pos;
typedef struct {
    s16 unused[10];
    s16 stride;
} floor_generate_isolated_8028906C_DungeonState;
typedef struct {
    s16 kind;
    s16 value;
    s16 flags;
} floor_generate_isolated_8028906C_DungeonCell;
typedef u32 CoordPair __attribute__((aligned(2)));
typedef struct {
    s16 x;
    s16 y;
    s16 unk4;
    s16 dir;
} floor_generate_isolated_802895E4_Pos;
typedef struct {
    s16 kind;
    s16 value;
    s16 flags;
} floor_generate_isolated_802895E4_DungeonCell;
typedef struct {
    u16 unk0;
    u16 tile;
} floor_generate_isolated_802895E4_Walker;
typedef struct floor_generate_isolated_80289BD4_MapCell {
    u16 unk_00;
    u16 unk_02;
    u16 blocked;
} floor_generate_isolated_80289BD4_MapCell;
typedef struct {
    u8 pad0[4];
    u16 field4;
    u16 field6;
    u16 field8;
    s16 fieldA;
} floor_generate_isolated_80289CEC_Entry;
typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} floor_generate_isolated_80289EC0_Rect;
typedef struct {
    s16 height;
    u16 y;
    u16 flags;
} floor_generate_isolated_80289EC0_Tile;
typedef struct {
    u8 pad0[12];
    u8 *entries;
    u8 pad10[4];
} floor_generate_isolated_8028A0F4_DungeonGroup;
typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} floor_generate_isolated_8028A0F4_DungeonRect;
typedef struct {
    u8 pad0[6];
    u8 px;
    u8 py;
    u8 pad8[16];
} floor_generate_isolated_8028A0F4_DungeonSpot;
typedef struct {
    u8 kind;
    u8 f1;
    u8 f2;
    u8 f3;
} floor_generate_isolated_8028A0F4_DungeonSlot;
typedef struct floor_generate_isolated_8028A328_S_8001D328_0 {
    u8 unk_00;
    u8 pad_01[0x1];
    u8 unk_02;
    u8 pad_03[0x1];
    u16 unk_04;
    u16 unk_06;
} floor_generate_isolated_8028A328_S_8001D328_0;
typedef struct floor_generate_isolated_8028A328_S_8001D328_1 {
    u8 unk_00;
    u8 unk_01;
} floor_generate_isolated_8028A328_S_8001D328_1;
typedef struct floor_generate_isolated_8028A4AC_S_8001D4AC_1 {
    s32 unk_00;
} floor_generate_isolated_8028A4AC_S_8001D4AC_1;
typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 value;
} floor_generate_isolated_8028A5D8_DungeonRect;
typedef struct {
    s16 unused[10];
    s16 stride;
} floor_generate_isolated_8028A5D8_DungeonState;
typedef struct {
    s16 kind;
    s16 value;
    s16 flags;
} floor_generate_isolated_8028A5D8_DungeonCell;
typedef struct {
    u8 unused[0x146E];
    s16 level;
} floor_generate_isolated_8028A5D8_DungeonPage;
typedef struct floor_generate_isolated_8028AC34_S_8001DC34_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} floor_generate_isolated_8028AC34_S_8001DC34_0;
typedef struct floor_generate_isolated_8028AC34_S_8001DC34_1_pre {
    s16 unk_00;
} floor_generate_isolated_8028AC34_S_8001DC34_1_pre;
typedef struct floor_generate_isolated_8028AC34_S_8001DC34_1 {
    s16 unk_00;
} floor_generate_isolated_8028AC34_S_8001DC34_1;
typedef struct {
    s16 unk0;
    u16 value;
    s16 unk4;
} floor_generate_isolated_8028AD84_D_800EA000_Record;
#define M2C_SYNC() 0
typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    s16 unk8;
    s16 active;
    u8 pad[8];
} floor_generate_isolated_8028AE2C_DungeonArea;
extern u8 D_800E2C40[];
extern u16 func_800A4E2C(u8 *, u8 *);
extern void func_8009A21C(s16 x, s16 y, u16 flags);
extern s32 func_800A6D30(void);
s32 func_800BCB04();
extern s32 func_8009A350(s16, s16, s16, u16 *);
extern s32 func_8009A540(u16, s16, s16, s16);
extern void Control_CD(s32, s32, s32);
extern void func_8003F320(void);
extern s32 func_800A7A38(u8 *item);
extern void func_8004068C(u8 *, u8 *);
extern s32 func_800BCA68(s32, s32);
extern s32 D_8001F604[];
extern s16 D_8001F586;
extern s32 D_800DF258[];
extern s32 D_800E296C;
extern s32 D_800E3D6C;
extern void func_80016E6C(void);
extern void func_8004D0C8();
extern void func_80046E38();
extern s32 bzero();
extern s32 rand(void);
extern s32 srand();
extern void func_800A0E44(void);
extern void func_800A6D98();
extern void func_800B0544();
extern void func_800BC228();
extern void func_800C7D54();
extern void func_8001E96C(void);
extern void func_8001F32C(void);
extern void file_load_com();
extern floor_generate_isolated_80285A70_TrackRecord D_8001F62C[];
extern s32 D_8001F588[];
extern u8 D_8001F584;
extern s32 D_8001F594[];
extern u8 D_800F0000[];
extern s8 D_80080A88[12];
extern u8 D_80082E6B[9];
extern s32 func_80033BC0(s32 value);
extern void func_80044698(void);
extern void func_80048088(s16 entity_type);
extern void SD_Call(s32 command, ...);
extern void func_800542BC(void);
extern s32 func_800A6DA4(s32 lower, u16 upper);
extern void func_8003F6D4(s32, void *, s32 *, s32);
extern floor_generate_isolated_802864C4_Copy32 D_8014A000;
extern s8 D_80012D52;
extern void func_8004425C(s32);
extern void func_8004450C(s16);
extern floor_generate_isolated_80286684_Object *D_8006E704[];
extern s8 D_80080AF3;
extern floor_generate_isolated_80286684_Object *D_80080AF4[2];
extern s16 D_80080AFC;
extern s32 D_801BEE40[4];
extern s32 D_801C4640[4];
void func_8003F5E0();
s16 func_8005405C();
M2C_UNK func_8005FE18();
M2C_UNK func_80067014();
extern M2C_UNK D_8006E61C;
extern M2C_UNK D_80080AF0;
extern s32 D_80012090[3];
extern s32 func_800A6928(s32, s32);
extern s32 D_8001F660;
extern s32 D_8001F664;
extern u16 D_8001F66A;
extern u8 D_8001F6A0;
extern s8 D_8001F66C[];
extern void func_800A6D60(s32);
extern u32 func_800A07D0(s16, s16, s16, s16);
extern floor_generate_isolated_8028A0F4_DungeonGroup D_80073414[];
s32 func_8001E660();
extern u8 D_800E3549[];
extern M2C_UNK D_8001F670;
extern u8 D_80080000[];
extern u8 D_800E9FFA[];
void func_8001744C(void);
void func_80017480(s16 start_x, s16 start_y, s16 rect_width, s16 rect_height, u16 mask);
void func_80017530(void);
void func_80017560(void);
s16 func_80017584(s16 start_x, s16 start_y, s16 width, s16 height);
void func_80017668(s16 start_x, s16 y, s16 width, s32 height, u16 fill_value);
void func_800176EC(void);
void func_800177A8(void);
void func_800177D8(s16 row_index, s16 first_byte, s16 second_byte, s16 value);
void func_8001784C(void);
void func_80017A9C(void);
s32 func_80017BEC(s16 region_id);
s16 func_80017EBC(s16 entry_index);
s16 func_80017F88(s16 rect_index, s16 *out_x, s16 *out_y, s16 check_flags);
s16 func_8001816C(s16 record_id, s16 *out_x, s16 *out_y, s32 search_mode);
s32 func_80018304(s16 input_x, s16 input_y, s32 current_height, s16 direction);
void func_80018464(s16 layout_number);
void func_80018A70(void);
s32 func_80018E80(void);
void func_800194C4(s16 resource_index);
void func_80019648(void);
s32 func_80019684(s16 object_index, s16 mode, s16 activate);
s32 func_80019894(s16 resource_index);
s32 func_800199C8(s16 entry_index);
void func_80019A74(void);
void func_80019A84(s16 value);
s32 func_80019AF8(void);
void func_8001A710(void);
s16 func_8001A768(u16 *facing, s32 origin_x, s32 origin_y, s8 *tiles, s32 search_arg, s32 radius,
                  s32 filter_arg);
s32 func_8001ABC8(s16 value_a, s16 value_b);
s16 func_8001AC4C(s16 src_dir, s16 dest_dir, s16 src_idx, s16 dest_idx, u8 *room_marks);
s32 func_8001C06C(floor_generate_isolated_8028906C_Pos *start, floor_generate_isolated_8028906C_Pos *dest, s16 rnd, s16 *outX, s16 *outY);
s16 func_8001C5E4(floor_generate_isolated_802895E4_Pos *start, floor_generate_isolated_802895E4_Pos *dest, s16 rnd, s16 *out_x, s16 *out_y,
                  floor_generate_isolated_802895E4_Walker *walker, s32 *cost);
s16 func_8001CBD4(s16 x, s16 y, s16 dir);
void func_8001CCEC(s16 side, s16 *out_x, s16 *out_y, floor_generate_isolated_80289CEC_Entry *room);
s32 func_8001CE14(s16 value, s32 lower_bound, s16 upper_bound);
void func_8001CE44(Rec_func_8001CE44_arg0 *region, s16 update_id);
void func_8001CEC0(floor_generate_isolated_80289EC0_Rect *rect, s32 rng_input_1);
void func_8001CFB8(void *room, s32 rng_arg1);
void func_8001D0F4(floor_generate_isolated_8028A0F4_DungeonRect *rect, s32 update_id);
void func_8001D328(floor_generate_isolated_8028A328_S_8001D328_0 *region, s32 setup_arg1);
void func_8001D5D8(floor_generate_isolated_8028A5D8_DungeonRect *rect, s32 update_id);
void func_8001D9CC(s16 left_x, s16 top_y, s16 right_x, s16 bottom_y, s32 tile_value_base);
void func_8001DC34(floor_generate_isolated_8028AC34_S_8001DC34_0 *region);
void func_8001DD08(void *step_state, s32 update_id);
void func_8001DD48(void *step_state, s32 update_id);
s16 func_8001DD84(s32 x, s32 y, s32 count, s16 x_step, s16 y_step);
void func_8001DE2C(void);
extern floor_generate_isolated_80286AF8_MapCell D_800EA000[];
extern u8 D_8008146E[];
extern u8 D_8008146C[];
extern u8 D_800E3648[];
extern u8 D_800E36C8[];
extern u8 D_800E39C8[12];
extern u8 D_800E3CD8[];
extern u8 D_8008333C[];
extern u8 D_8008148C[];
extern u8 D_80081480[];
extern u8 D_80081468[];
extern u8 D_800DDC9C[];
extern u8 D_8001F668[];
extern u8 D_8001F6A8[];
extern u8 D_8001F6A4[];
extern u8 D_8001F6E8[];
void func_8001E108(s32 x, s32 y, s16 *tile, s32 kind, s32 amount);
#endif
