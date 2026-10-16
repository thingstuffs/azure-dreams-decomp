#include "modules/town_player_init.h"

/* Initialize the town scene and configure its object for the current mode. */
void townInitializeSceneForMode(void)
{
    EntityRec *scene;
    TileObject *render;
    func_80092868_TownState *state;
    func_80092868_TownObject *object;
    func_80092868_TownWork *work;
    void *shared_data;
    s32 neutral_color;
    u16 x_offset;
    u16 x_coord;
    u16 y_offset;
    u16 y_coord;
    u16 frame;

    scene = &D_80083780;
    D_80100E18[0] = 0;
    D_80100DB0[0] = 0;
    zeroWords(scene, 6);
    render = &D_80082E80;
    zeroWords(render, 0xC);
    render->unk_028 = D_80080A80;
    func_8008EF58();

    shared_data = D_800D0420;
    townHandleInsertInitializeTwoValuesStatusFlags(D_800CFCB4, scene, shared_data);
    func_8008FCE0();
    townInitializeTheStoreTwoValuesSetStateFlags(D_800FE490, scene, shared_data);

    state = &D_8006ADBC;
    if (state->mode == 0x37000C) {
        townInitializeObjectAtCurrentPosition();
        return;
    }

    object = initializeSceneObjectInBuffer(0, ((u8 *)(&D_80083498)), 0x22);
    object->scene = scene;
    object->render = render;

    if (state->alternate != 0) {
        u16 *coords;

        object->callback = D_8008FFC0;
        coords = state->coords;
        scene->x.w.i = state->x_offset + coords[0];
        scene->y.w.i = state->y_offset + coords[1];
        scene->z.w.i = 0;
        townCopyEntityRecordFields(D_80100D98, scene);
        return;
    }

    {
        u16 *coords;

        object->callback = townRebuildMenuNodeList;
        func_8004491C(object, D_800970FC);
        neutral_color = 0x808080;
        render->unk_01E = 0x1000;
        render->unk_01C = 0x1000;

        coords = state->coords;
        x_offset = state->x_offset;
        x_coord = coords[0];
        *(s32 *)(&render->unk_00C) = neutral_color;
        scene->x.w.i = x_offset + x_coord;
        y_offset = state->y_offset;
        y_coord = coords[1];
        scene->z.w.i = -0x80;
        scene->y.w.i = y_offset + y_coord;
        scene->z.w.i = townQueryLoweredTransformPosition(scene);
        townInitializeSixGlobalPointersCorrespondingStorageBlocks();
        townRunTheThreeUpdateRoutinesContext(scene);

        work = (func_80092868_TownWork *)((u8 *)object + 0x20);
        work->field12 = -1;
        frame = state->frame;
        work->frame0 = frame;
        work->frame1 = frame;
        clearResidentBitmapBit(0xA4);

        if (testResidentBitmapBit(0x1202) == 0) {
            work->active = 0;
        } else {
            work->active = 1;
        }

        render->unk_028 = D_80080A80;
        if ((D_8006ADD4[0] != 0xC) && (func_8009F830(2, 0x13) != 0)) {
            townCreatePersonObject();
        }
    }
}
