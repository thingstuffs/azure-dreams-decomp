#include "common.h"

typedef struct ScenePos {
    s16 pad0;
    u16 x;
    s16 pad4;
    u16 y;
    s16 pad8;
    s16 angle;
} ScenePos;

typedef struct RenderState {
    u8 pad0[0xC];
    s32 color;
    u8 pad10[0xC];
    s16 scale0;
    s16 scale1;
    u8 pad20[8];
    s32 source;
} RenderState;

typedef struct TownState {
    u8 pad0[0xC];
    u16 frame;
    s16 alternate;
    u16 *coords;
    u16 x_offset;
    u16 y_offset;
    s32 mode;
} TownState;

typedef struct TownObject {
    void *next;
    void *prev;
    ScenePos *scene;
    RenderState *render;
    void *callback;
} TownObject;

typedef struct TownWork {
    u8 pad0[0x10];
    u16 frame0;
    s16 field12;
    u8 pad14[2];
    s16 active;
    u16 frame1;
} TownWork;

extern void func_80033AE8(s32 arg0);
extern s32 func_80033B2C(s32 arg0);
extern void func_8003DB4C(void *ptr, s32 count);
extern TownObject *func_8003FE78(s32 flags, void *storage, s16 size);
extern void func_8004491C(TownObject *object, void *data);
extern void func_8008EF58(void);
extern void func_8008F01C(void *arg0, ScenePos *scene, void *arg2);
extern void func_8008FCE0(void);
extern void func_8008FD48(void *arg0, ScenePos *scene, void *arg2);
extern void func_8008FF5C(void);
extern void func_8009550C(ScenePos *scene);
extern s32 func_8009F830(s32 arg0, s32 arg1);
extern void func_800A48B0(void *state, ScenePos *scene);
extern void func_800AB084(void);
extern void func_800C01DC(void);
extern s16 func_800C2AE8(ScenePos *scene);

extern TownState D_8006ADBC;
extern s16 D_8006ADD4;
extern s32 D_80080A80;
extern RenderState D_80082E80;
extern u8 D_80083498[];
extern ScenePos D_80083780;
extern u8 D_8008FFC0[];
extern u8 D_800903FC[];
extern u8 D_800970FC[];
extern u8 D_800CFCB4[];
extern u8 D_800D0420[];
extern u8 D_800FE490[];
extern u8 D_80100D98[];
extern s32 D_80100DB0;
extern s32 D_80100E18;

/* Initialize the town scene and configure its object for the current mode. */
void func_8008FFC8(void)
{
    ScenePos *scene;
    RenderState *render;
    TownState *state;
    TownObject *object;
    TownWork *work;
    void *shared_data;
    s32 neutral_color;
    u16 x_offset;
    u16 x_coord;
    u16 y_offset;
    u16 y_coord;
    u16 frame;

    scene = &D_80083780;
    D_80100E18 = 0;
    D_80100DB0 = 0;
    func_8003DB4C(scene, 6);
    render = &D_80082E80;
    func_8003DB4C(render, 0xC);
    render->source = D_80080A80;
    func_8008EF58();

    shared_data = D_800D0420;
    func_8008F01C(D_800CFCB4, scene, shared_data);
    func_8008FCE0();
    func_8008FD48(D_800FE490, scene, shared_data);

    state = &D_8006ADBC;
    if (state->mode == 0x37000C) {
        func_800C01DC();
        return;
    }

    object = func_8003FE78(0, D_80083498, 0x22);
    object->scene = scene;
    object->render = render;

    if (state->alternate != 0) {
        u16 *coords;

        object->callback = D_8008FFC0;
        coords = state->coords;
        scene->x = state->x_offset + coords[0];
        scene->y = state->y_offset + coords[1];
        scene->angle = 0;
        func_800A48B0(D_80100D98, scene);
        return;
    }

    {
        u16 *coords;

        object->callback = D_800903FC;
        func_8004491C(object, D_800970FC);
        neutral_color = 0x808080;
        render->scale1 = 0x1000;
        render->scale0 = 0x1000;

        coords = state->coords;
        x_offset = state->x_offset;
        x_coord = coords[0];
        render->color = neutral_color;
        scene->x = x_offset + x_coord;
        y_offset = state->y_offset;
        y_coord = coords[1];
        scene->angle = -0x80;
        scene->y = y_offset + y_coord;
        scene->angle = func_800C2AE8(scene);
        func_8008FF5C();
        func_8009550C(scene);

        work = (TownWork *)((u8 *)object + 0x20);
        work->field12 = -1;
        frame = state->frame;
        work->frame0 = frame;
        work->frame1 = frame;
        func_80033AE8(0xA4);

        if (func_80033B2C(0x1202) == 0) {
            work->active = 0;
        } else {
            work->active = 1;
        }

        render->source = D_80080A80;
        if ((D_8006ADD4 != 0xC) && (func_8009F830(2, 0x13) != 0)) {
            func_800AB084();
        }
    }
}
