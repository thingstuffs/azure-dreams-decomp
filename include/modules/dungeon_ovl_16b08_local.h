#ifndef DUNGEON_OVL_16B08_LOCAL_H
#define DUNGEON_OVL_16B08_LOCAL_H
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "records/Rec_func_8009431C_arg0.h"
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6D14_InitState;
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6DBC_InitState;
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6EC0_InitState;
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6F00_InitState;
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6F40_InitState;
M2C_UNK func_80094984();
extern void func_80091F64(void);
extern M2C_UNK D_800D00A0;
M2C_UNK func_800948DC();
extern void func_8009204C(void);
extern M2C_UNK D_800D00B0;
extern void func_800920F4(void);
extern void func_80090F00(void);
extern M2C_UNK D_800D00C0;
extern void func_8009221C(void);
extern u8 D_800D00B8[16];
M2C_UNK func_80094C1C();
extern void func_80092320(void);
extern M2C_UNK D_800D0108;
M2C_UNK SD_Call();
extern void func_800924EC(void);
extern M2C_UNK D_800D0110;
extern u8 D_800D0118[];
extern void func_80090E78(void);
extern void func_80092698(void);
extern M2C_UNK D_800D0120;
extern u8 D_800D0128[];
extern void func_800927EC(void);
extern void func_80092A84(void);
extern M2C_UNK D_800D0130;
extern void func_80092CD4(void);
extern M2C_UNK D_800D0140;
extern u8 D_800D0148[];
extern void func_80092DA8(void);
extern void func_80092ECC(void);
extern u8 D_800D0138[];
extern void func_80092FF0(void);
extern void func_800930E4(void);
void func_80094268(Rec_func_80094268_arg0 *object);
void func_800942B0(Rec_func_80094268_arg0 *object, EntityRec *state, M2C_UNK setupArg);
void func_8009431C(Rec_func_8009431C_arg0 *record);
void func_80094330(Rec_func_80094268_arg0 *object);
void func_80094378(M2C_UNK **object);
void func_800943B8(Rec_func_80094268_arg0 *object, M2C_UNK setup_arg, M2C_UNK context, M2C_UNK setup_extra);
void func_80094414(M2C_UNK **object, M2C_UNK unused, M2C_UNK context);
void func_80094474(ovl_16b08_local_7FFF6D14_InitState *state, void *unused, void *context);
void func_800944BC(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK context);
void func_8009451C(ovl_16b08_local_7FFF6DBC_InitState *state, void *unused, void *context);
void func_8009455C(Rec_func_80094268_arg0 *object, M2C_UNK setup_arg, M2C_UNK context, M2C_UNK setup_extra);
void func_800945B8(M2C_UNK **outputSlot, EntityRec *state, M2C_UNK initContext);
void func_80094620(ovl_16b08_local_7FFF6EC0_InitState *state, void *unused, void *context);
void func_80094660(ovl_16b08_local_7FFF6F00_InitState *state, void *unused, void *context);
void func_800946A0(ovl_16b08_local_7FFF6F40_InitState *state, void *argument, void *context);
void func_800946FC(Rec_func_80094268_arg0 *record);
#endif
