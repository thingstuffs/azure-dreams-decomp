#ifndef MODULES_TOWN_PLAYER_INIT_H
#define MODULES_TOWN_PLAYER_INIT_H

#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/object_node.h"
#include "shared/position_query.h"
#include "shared/tile_object.h"

typedef struct func_80092868_ScenePos {
    s16 pad0;
    u16 x;
    s16 pad4;
    u16 y;
    s16 pad8;
    s16 angle;
} func_80092868_ScenePos;

typedef struct func_80092868_RenderState {
    u8 pad0[0xC];
    s32 color;
    u8 pad10[0xC];
    s16 scale0;
    s16 scale1;
    u8 pad20[8];
    s32 source;
} func_80092868_RenderState;

typedef struct func_80092868_TownState {
    u8 pad0[0xC];
    u16 frame;
    s16 alternate;
    u16 *coords;
    u16 x_offset;
    u16 y_offset;
    s32 mode;
} func_80092868_TownState;

typedef struct func_80092868_TownObject {
    void *next;
    void *prev;
    func_80092868_ScenePos *scene;
    func_80092868_RenderState *render;
    void *callback;
} func_80092868_TownObject;

typedef struct func_80092868_TownWork {
    u8 pad0[0x10];
    u16 frame0;
    s16 field12;
    u8 pad14[2];
    s16 active;
    u16 frame1;
} func_80092868_TownWork;

typedef struct func_80092AB0_S_80090210_0 {
    s32 unk_00;
    u8 pad_04[0x10];
    s32 * unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
    u8 pad_1C[0xA];
    s16 unk_26;
} func_80092AB0_S_80090210_0;

typedef struct func_80092AB0_S_80090210_1 {
    u8 pad_00[0x28];
    s32 unk_28;
} func_80092AB0_S_80090210_1;

typedef struct func_80092AB0_S_80090210_2 {
    u8 pad_00[0x438];
    union { s32 (*s)(); s32 u; } unk_438;                         
} func_80092AB0_S_80090210_2;

typedef struct func_80092C18_S_80090378_0 {
    s32 unk_00;
} func_80092C18_S_80090378_0;

typedef void (*func_80092C9C_ObjectCallback)(void *, s32, s32);

typedef void (*func_80092C9C_ActorCallback)(void *, void *, s32);

typedef struct func_80092C9C_S_800903FC_1 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x2];
    u16 unk_16;
} func_80092C9C_S_800903FC_1;

typedef struct func_80092C9C_S_800903FC_2 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x17];
    u8 unk_3B;
} func_80092C9C_S_800903FC_2;

typedef struct func_80092C9C_S_800903FC_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} func_80092C9C_S_800903FC_3;

typedef struct func_80092C9C_S_800903FC_4 {
    u8 pad_00[0x8];
    void * unk_08;
} func_80092C9C_S_800903FC_4;

void func_8008FFC8(void);
void func_80090210(void);
void func_80090378(void);
void plt_init_sleep_set(void);
void func_800903BC(void);
void func_800903DC(void);
void func_800903FC(void *owner, EntityRec *node_in, s32 mode);
void func_8009065C(void *context, void *input, void *record);
s32 func_800909A0();
void func_80090A04(void *record);
void func_80090A64(void);
void func_80090A6C(void);

extern void func_80033AE8(s32 flag_id);
extern s32 func_80033B2C(s32 bit_id);
extern void func_8003DB4C(void *ptr, s32 count);
extern func_80092868_TownObject *func_8003FE78(s32 flags, void *storage, s16 size);
extern void func_8004491C(func_80092868_TownObject *object, void *data);
extern void func_8008EF58(void);
extern void func_8008F01C(void *node, func_80092868_ScenePos *scene, void *value_0c);
extern void func_8008FCE0(void);
extern void func_8008FD48(void *record, func_80092868_ScenePos *scene, void *value_0c);
extern void func_8008FF5C(void);
extern void func_8009550C(void *owner);
extern s32 func_8009F830(s32 first_value, s32 second_value);
extern void func_800A48B0(void *, void *);
extern void func_800AB084(void);
extern void func_800C01DC(void);
extern s16 func_800C2AE8(func_80092868_ScenePos *scene);
void func_80033AA8();
s32 func_80048D20();
s32 func_80048D40();
void func_80094984();
extern void func_80098868(void *owner, void *node_in, s32 mode);
void func_80098928();
void func_80099764();
extern s32 func_800352FC(void);
extern void func_8008B158(void *owner);
extern s32 func_8008C180(s16 owner, s16 node_in);
extern void func_8008F664(void *owner, void *node_in);
extern void func_8009539C(void *owner);
extern void func_800953D0(void *owner);
extern void func_80095460(void *owner);
extern void func_80095910(void *owner);
extern s32 func_8009593C(void *owner);
extern s16 func_80095978(void *owner, void *node_in);
extern void func_80095A94(void *owner, s16 node_in, void *mode);
extern void func_80096FF4(void *owner);
extern void func_800A573C(void *owner, void *node_in, s32 mode);
extern s32 func_800C1D44(u16 owner);
extern s32 func_8003BD84(s32, s32);
extern void func_800489F4(void *, u8, s8, s32);
extern void func_80048AC8(void *, s32);
extern s16 func_80094AA0(s16, s16, s32);
extern s32 func_80095360(s16);
extern void func_80095544(void *);
extern void func_80096868(void *, void *, void *);

extern func_80092868_TownState D_8006ADBC;
extern s16 D_8006ADD4[];
extern s32 D_80080A80;
extern u8 D_8008FFC0[];
extern u8 D_800970FC[];
extern u8 D_800CFCB4[];
extern u8 D_800D0420[];
extern u8 D_800FE490[];
extern u8 D_80100D98[];
extern s32 D_80100DB0[];
extern s32 D_80100E18[];
extern s32 D_800834B8;
extern s32 D_80097D54;
extern u8 D_800D0078[];
extern s32 D_800D0438;
extern s32 D_800D0178;
extern u8 D_80082BC0[];
extern s32 D_80097D2C[3];
extern u8 D_800A5638[];
extern s32 D_80091260;
extern s32 D_80091528;
extern s16 D_800D01F8[];

#endif
