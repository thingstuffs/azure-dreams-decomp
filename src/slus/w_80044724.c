#include "common.h"
#include "shared/game_work.h"

/* Update the four saved vectors and return 1 if any coordinate changed, otherwise return 0. */
s32 func_80044724(void)
{
    GameView *source;
    struct S_80083178State *saved;

    source = &gameWork.view;
    saved = &D_80083CE8;

    if (source->unk_094 != saved->v[0].x
        || source->unk_096 != saved->v[0].y
        || source->unk_098 != saved->v[0].z
        || source->unk_09C != saved->v[1].x
        || source->unk_09E != saved->v[1].y
        || source->unk_0A0 != saved->v[1].z
        || source->unk_0A4 != saved->v[2].x
        || source->unk_0A6 != saved->v[2].y
        || source->unk_0A8 != saved->v[2].z
        || source->unk_0AC != saved->v[3].x
        || source->unk_0AE != saved->v[3].y
        || source->viewAngle != saved->v[3].z) {
    D_80083CE8.v[0] = *(struct S_80083178Vector *)&source->unk_094;
    D_80083CE8.v[1] = *(struct S_80083178Vector *)&source->unk_09C;
    D_80083CE8.v[2] = *(struct S_80083178Vector *)&source->unk_0A4;
    D_80083CE8.v[3] = *(struct S_80083178Vector *)&source->unk_0AC;
        return 1;
    }
    return 0;
}
