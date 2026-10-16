#ifndef MODULES_TOWN_TOWN_WINDOWS_H
#define MODULES_TOWN_TOWN_WINDOWS_H

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800CFCC4.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct {
    s16 x0;
    s16 y0;
    s16 pad4;
    s16 pad6;
    s16 x1;
    s16 y1;
} func_8009F66C_CoordPair;

typedef struct func_8009F6D4_S_8009CE34_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} func_8009F6D4_S_8009CE34_0;

typedef struct func_8009F788_S_8009CEE8_0 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x8];
    s32 * unk_0C;
} func_8009F788_S_8009CEE8_0;

typedef struct func_8009F880_S_8009CFE0_0 {
    u8 pad_00[0x84];
    u16 unk_84;
    u16 unk_86;
    u8 pad_88[0x10];
    void * unk_98;
} func_8009F880_S_8009CFE0_0;

typedef struct func_8009F880_S_8009CFE0_1 {
    u8 pad_00[0x1];
    u8 unk_01;
    s16 unk_02;
} func_8009F880_S_8009CFE0_1;

typedef struct func_8009F880_S_8009CFE0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} func_8009F880_S_8009CFE0_2;

typedef struct func_8009FAAC_S_8009D20C_1 {
    u8 pad_00[0x1];
    u8 unk_01;
    s16 unk_02;
} func_8009FAAC_S_8009D20C_1;

typedef struct func_8009FAAC_S_8009D20C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} func_8009FAAC_S_8009D20C_2;

typedef void (*func_8009FCC4_Callback)(void *, void *, void *);

typedef struct func_8009FCC4_S_8009D424_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u32 unk_10;
} func_8009FCC4_S_8009D424_0;

typedef struct func_8009FCC4_S_8009D424_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} func_8009FCC4_S_8009D424_1;

typedef struct func_8009FCC4_S_8009D424_2 {
    u8 pad_00[0x84];
    u16 unk_84;
} func_8009FCC4_S_8009D424_2;

typedef struct func_8009FCC4_S_8009D424_3 {
    u8 pad_00[0x48];
    s32 unk_48;
    u8 pad_4C[0x22];
    u16 unk_6E;
    s8 unk_70;
    s8 unk_71;
    u16 unk_72;
    u8 pad_74[0x12];
    u16 unk_86;
    u8 pad_88[0xB];
    s8 unk_93;
    s8 unk_94;
    u8 unk_95;
    u8 unk_96;
    u8 pad_97[0x1];
    s32 unk_98;
} func_8009FCC4_S_8009D424_3;

typedef struct func_8009FCC4_S_8009D424_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} func_8009FCC4_S_8009D424_4;

typedef struct func_8009FCC4_S_if_b1_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} func_8009FCC4_S_if_b1_0;

typedef struct func_8009FCC4_S_if_b2_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} func_8009FCC4_S_if_b2_0;

typedef struct func_8009FE60_GlobalADBC { u8 pad0[0x18]; s16 field18; s16 field1A; } func_8009FE60_GlobalADBC;

typedef struct func_8009FE60_TownState {
    s32 field0;
    s32 field4;
    s32 field8;
    u8 pad0C[0xC];
    void * field18;
    void * field1C;
    void * field20;
    void * field24;
    u8 pad28[8];
    void * field30;
    void * field34;
    void * field38;
    void * field3C;
    void * field40;
} func_8009FE60_TownState;

typedef struct func_8009FE60_TownSystemScratch {
    void *state;
    u8 payload[1];
} func_8009FE60_TownSystemScratch;

typedef void (*func_8009FE60_InitCallback)(void *, s32, s32);

typedef void (*func_8009FE60_ListCallback)(void);

typedef struct func_8009FFDC_S_8009D73C_0 {
    u8 pad_00[0xC];
    s32 * unk_0C;
} func_8009FFDC_S_8009D73C_0;

typedef struct func_800A0070_S_8009D7D0_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} func_800A0070_S_8009D7D0_0;

typedef struct func_800A00A8_S_8009D808_0 {
    u16 unk_00;
    u16 unk_02;
} func_800A00A8_S_8009D808_0;

typedef struct func_800A00A8_S_8009D808_1 {
    u16 unk_00;
    u16 unk_02;
} func_800A00A8_S_8009D808_1;

typedef struct func_800A00A8_S_8009D808_2 {
    u16 unk_00;
    u16 unk_02;
} func_800A00A8_S_8009D808_2;

typedef struct func_800A00A8_S_8009D808_3 {
    s16 unk_00;
    s16 unk_02;
} func_800A00A8_S_8009D808_3;

typedef struct func_800A01E0_S_8009D940_0 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
} func_800A01E0_S_8009D940_0;

typedef struct func_800A01E0_S_8009D940_1 {
    s16 unk_00;
    s16 unk_02;
} func_800A01E0_S_8009D940_1;

typedef struct func_800A01E0_S_8009D940_2 {
    s16 unk_00;
    s16 unk_02;
} func_800A01E0_S_8009D940_2;

typedef struct func_800A0284_S_8009D9E4_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
} func_800A0284_S_8009D9E4_0;

typedef struct func_800A0284_S_8009D9E4_1 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} func_800A0284_S_8009D9E4_1;

typedef struct func_800A02F0_S_8009DA50_1 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x4];
    u16 unk_10;
    u16 unk_12;
    u8 pad_14[0x4];
    u16 unk_18;
    u16 unk_1A;
} func_800A02F0_S_8009DA50_1;

typedef struct func_800A02F0_S_8009DA50_2 {
    u8 unk_00;
    u8 unk_01;
    s16 unk_02;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    s32 unk_08;
    s32 unk_0C;
    u16 unk_10;
    u16 unk_12;
} func_800A02F0_S_8009DA50_2;

typedef struct func_800A05E0_S_8009DD40_0_pre {
    u16 unk_00;
} func_800A05E0_S_8009DD40_0_pre;

typedef struct {
               u8 pad[0x4D];
               u8 unk4D;
               u8 pad2[0x2];
               void (*unk50)(void *, void *, s32, s32);
} func_800A06C8_EntityLike;

typedef struct func_800A075C_S_func_8009DEBC_0 {
    u8 pad_00[0x15];
    u8 unk_15;
    u8 pad_16[0x37];
    u8 unk_4D;
    u8 pad_4E[2];
    void (*unk_50)(void *, void *, s32, s32);
    u8 pad_54[0x58];
    u8 unk_AC;
} func_800A075C_S_func_8009DEBC_0;

typedef struct func_800A075C_S_func_8009DEBC_1 {
    s32 *unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
} func_800A075C_S_func_8009DEBC_1;

typedef struct func_800A0824_S_8009DF84_0 {
    s32 * unk_00;
    u8 pad_04[0x21];
    u8 unk_25;
    u8 pad_26[0x96];
    u8 unk_BC;
} func_800A0824_S_8009DF84_0;

typedef struct func_800A0878_Copy84 {
    s32 word[21];
} func_800A0878_Copy84;

typedef struct func_800A0C10_TownRecord {
    u8 bytes[0x54];
} func_800A0C10_TownRecord;

typedef struct func_800A0C10_TownIndexEntry {
    u8 value;
    u8 pad[3];
} func_800A0C10_TownIndexEntry;

typedef struct func_800A0C10_TownPage {
    u8 pad[0x980];
    func_800A0C10_TownIndexEntry entries[0x40];
} func_800A0C10_TownPage;

typedef struct func_800A0C74_S_8009E3D4_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} func_800A0C74_S_8009E3D4_0;

typedef struct func_800A0D8C_S_8009E4EC_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} func_800A0D8C_S_8009E4EC_0;

typedef struct func_800A0FB4_S_func_8009E714_0 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x1E];
    u16 unk_6C;
    u8 pad_6E[0x2A];
    void *unk_98;
} func_800A0FB4_S_func_8009E714_0;

typedef struct func_800A0FB4_S_func_8009E714_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} func_800A0FB4_S_func_8009E714_1;

typedef struct func_800A0FB4_S_func_8009E714_2 {
    u16 unk_00;
} func_800A0FB4_S_func_8009E714_2;

typedef struct func_800A10FC_S_8009E85C_0_pre {
    s32 (*unk_00)(void *, void *, void *);
    u8 pad_04[0xC];
} func_800A10FC_S_8009E85C_0_pre;

typedef struct func_800A10FC_S_8009E85C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} func_800A10FC_S_8009E85C_1;

typedef struct func_800A10FC_S_8009E85C_2 {
    u8 pad_00[0x8];
    s32 * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    union { u16 s; u16 u; } unk_14;                         
} func_800A10FC_S_8009E85C_2;

typedef struct func_800A10FC_S_8009E85C_4 {
    u8 pad_00[0x6C];
    s16 unk_6C;
} func_800A10FC_S_8009E85C_4;

typedef struct func_800A10FC_S_8009E85C_5_pre {
    s32 (*unk_00)(void *, void *, void *);
    u8 pad_04[0xC];
} func_800A10FC_S_8009E85C_5_pre;

typedef struct func_800A10FC_S_8009E85C_6 {
    u8 pad_00[0xA94];
    s32 unk_A94;
} func_800A10FC_S_8009E85C_6;

typedef struct TownWindowItemRecord { u8 pad_00[0x14]; u8 unk_14; u8 pad_15[0x37]; u8 kind; u8 type; s8 value; u8 unk_4F; } TownWindowItemRecord;

#define NULL 0
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
#define TOWN_SYSTEM_SCRATCH ((func_8009FE60_TownSystemScratch *)0x80016000U)
#define COPY_TABLE_ADDRESS ((func_800A0878_Copy84 *)0x800102F0)
#define BYTE_AT(base, offset) (*(u8 *)((u8 *)(base) + (offset)))
#define HALF_AT(base, offset) (*(u16 *)((u8 *)(base) + (offset)))
#define WORD_AT(base, offset) (*(s32 *)((u8 *)(base) + (offset)))
#define POINTER_AT(base, offset) (*(void **)((u8 *)(base) + (offset)))
#define BU(p, off) (*(u8 *)((u8 *)(p) + (off)))
#define WD(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define PP(p, off) (*(u8 **)((u8 *)(p) + (off)))
#define TB(idx, off) (D_80010000[(idx) * 4 + (off)])

void townInitializeObjectTransformAndState(s32 slot_id, void *object, s32 object_id);
s32 *townInitializeSharedScriptData(void);
void **townScaleCoordinatesAndAppendPointers(s32 firstX, s32 firstY, s32 secondX, s32 secondY, func_8009F66C_CoordPair *coords);
void func_8009CE34(void);
void townBuildEntriesAndUpdateState(void);
void townUpdateSharedStateAndClearFlag(void);
void townBuildEntryListAndProcessItems(void);
s32 townClassifyObjectAgainstBounds(func_8009F880_S_8009CFE0_0 *object, void *position_data);
s32 townClassifyRecordByStateAndPosition(Rec_D_80082D58 *record, void *position_data);
s32 townCreateObjectAndInitializeRenderState(s32 callback_id, s32 angle_index, s32 state_94, u8 state_95, u8 state_96, u8 height_mode, s32 state_48, s16 coord_x, s16 coord_z, s32 state_98);
void townInitAndPublishScriptState(void **entries);
void townProcessZeroTerminatedEntryLists(void **entries);
void townClearRecord20StatusBytes(s8 *records);
void townComputeFourPointCoordinateBounds(void *points, func_800A00A8_S_8009D808_2 *max_point, func_800A00A8_S_8009D808_1 *min_point);
void townCollectOverlappingRectangles(func_800A01E0_S_8009D940_1 *query_max, func_800A01E0_S_8009D940_2 *query_min, void **entries, void **matches);
void townRectangleToFourCorners(func_800A0284_S_8009D9E4_0 *rectangle, func_800A0284_S_8009D9E4_1 *vertices);
void townProcessEligibleEntries(func_800A02F0_S_8009DA50_2 *entries, void *bounds, s32 origin_x, s32 origin_y);
void townSetObjectStateForMode(void *owner, void *object, s32 mode, s32 flags);
void townCleanupOrDispatchObject(void *object, s32 source, s32 context);
void townInvokeEntityCallbackAndFollowUp(func_800A06C8_EntityLike *entity, s32 callback_id, s32 callback_data);
void townDispatchObjectOrSwitchAlternateState(func_800A075C_S_func_8009DEBC_0 *object, s32 source, s32 context);
void townResetObjectHandlerAndSavedByte(void *object, void *context);
void *townCreateConfiguredObject(void *object_data, void *source_position, s32 alternate_callback);
s32 townStoreRecordValueAndTableLookup(void);
s32 townGetSelectedTableEntry(void);
s32 townInitializeSharedStateFromTable(void);
s32 townPassSharedDataToWindowHandler(void);
s32 townGetWindowModeValue(void);
s32 townGetCurrentHighBitFlag(void);
s32 kewn_namewin_open(void);
s32 kewn_namewin_close_check(void);
s32 t_soukowin_open(void);
s32 t_soukowin_close_check(void);
void townSetObjectTypesAndResource(void *object, s32 index, void *output);
void townUpdateObjectPulseBrightness(func_800A0FB4_S_func_8009E714_0 *object, s32 context, func_800A0FB4_S_func_8009E714_1 *primitive);
void townInitializeEntityFromTableAndCallback(void *entity, func_800A10FC_S_8009E85C_1 *placement, func_800A10FC_S_8009E85C_2 *state);

extern void func_8004491C(s32, void *);
void *initializeSceneObjectInBuffer();
void townUpdateMapWorldExtents();
void townDispatchParameterizedOrDefault();
void townRunDualContextCallbacks();
s32 testResidentBitmapBit();
s32 townCheckFourVectorHalfTurnGaps();
extern void *func_8003FD64(s32 size, void *template);
extern s16 townQueryLoweredTransformPosition(void *);
extern void runtimeSetRecordValueAndBuffer(void *, void *);
extern void func_8008AC84(s32);
extern void townEnsurePackedResourceList(u8 *entries_in);
s32 func_8003DB94();
s32 func_80047784();
s32 func_80033D08();
extern void func_800478B8(void *callback_data);
void townUnlinkSceneListNode();
s32 townUpdateObjectAndClearStatusFields();
extern void townSetStateBytesFromFlags(s32 flags, u8 *state);
extern s32 func_8009706C(s32 state);
s32 func_80033CD8();
extern s32 lookupItemCategoryMappedValue(s32 type, s32 value);
extern void townConfigureTheSetModeN4(void *object, void *part_a, void *table);
extern void townInitializeOptionalObjectState(void *object, void *part_a, void *part_b, void *callback);
extern void townInitializeObjectAndMaybePlaySound(void *object, void *object_again, void *part_a, void *part_b);
extern void del_t_item_w_ptr(void *object_data);
s32 restoreActorStatsFromSnapshot();
s32 loadAndOpenMonsterStatusDisplay();
void townProcessObjectPointerArray();
extern s32 func_8004B854(s32 first, void *data, s32 value);
extern u32 strcpy();
extern void *func_8009F830();
void townClearGlobal80110EC0Global80082A39();
s32 open_twin_souko();
extern void townConfigureTheSetModeN3();
extern void townInitializeEntityFlagsTransformTypeDependentVariant();
extern s32 townIsUnk18N12Unk1ABetweenN37N41();
extern s32 func_800644B8();
u32 scaleRandomToUnsignedHalfwordLimit();

extern u8 D_80046398[];
extern s32 *D_801007F4;
extern s32 D_80100900[];
extern s32 D_801006D0;
extern s32 D_801007F8[];
extern u16 D_80082D08[];
extern s16 D_8006ADD4;
extern u32 D_800D3950[];
extern u16 D_800D5070[];
extern func_8009FE60_GlobalADBC D_8006ADBC;
extern void *D_8006ADC0[];
extern s32 D_80082A38[];
extern u8 D_80082A80[];
extern u8 D_80082BC0[];
extern u8 D_800D2EA4[];
extern u8 D_800D381C[];
extern u8 D_800D3CC8[];
extern u8 D_800D401C[];
extern func_8009FE60_TownState D_801131B8;
extern s32 D_80081458[];
extern s32 D_800D07A4[];
extern s16 D_800D07AC;
extern s32 D_8006E240;
extern u8 D_800D073C[];
extern u8 D_800D0754[];
extern u8 D_800D076C[];
extern u8 D_800D0788[];
extern func_800A0878_Copy84 D_80100AF8;
extern void *D_80100B0C;
extern TownWindowItemRecord *D_800CFCC4;
extern s32 D_800D0910[];
extern s32 D_80100A10;
extern s32 D_80100AF4;
extern func_800A0C74_S_8009E3D4_0 *D_80100AF0;
extern s32 D_80100A08;
extern u8 D_80010000[];
extern u8 T_80010000[];
extern s32 D_800D09C8[];

#endif
