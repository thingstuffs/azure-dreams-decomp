#include "common.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"


extern s32 func_800419EC();
extern s32 func_80042900();
extern s32 func_80042B68();
extern s32 func_80048A44();
extern s32 func_800997FC();
extern s32 func_800A2B04();

extern s32 D_80083460_count __asm__("D_80083460");
extern s32 D_8008ACDC;
extern u8 D_800DCFF8[];
extern u8 D_800E0597;
extern u8 D_800E05C3;


typedef struct S_80092E90_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80092E90_1;   /* arg2 in func_80092E90 */


typedef struct S_80092E90_3 {
    u8 pad_00[0x4];
    union { s16 n; volatile u16 v; u16 n2; } unk_04;   /* accessed as both */
} S_80092E90_3;   /* countBase in func_80092E90 */

typedef struct S_80092E90_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80092E90_4;   /* arg0 in func_80092E90 */

typedef struct S_80092E90_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x30];
    void * unk_5C;
} S_80092E90_5;   /* savedArg3 in func_80092E90 */

typedef struct S_80092E90_7_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80092E90_7_pre;   /* the 0x14 bytes before node in func_80092E90, addressed as node[-1] */

typedef struct S_80092E90_7 {
    u8 pad_00[0x5C];
    void * unk_5C;
} S_80092E90_7;   /* node in func_80092E90 */

typedef struct S_80092E90_9 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80092E90_9;   /* ((S_80092E90_7_pre *)node)[-1].unk_00 in func_80092E90 */

/* Move toward the target tile, process matching list entries, and advance the effect state. */
void func_80092E90(void *controller, EntityRec *motion, void *actor, void *entry)
{
    s32 found_match;
    s32 tile_origin;
    s32 target_pos;
    s16 match_result;
    s16 frames_left;
    s16 move_frames;
    u16 frame_count;
    u8 state;
    void *count_state;
    void *node;

    move_frames = dungeonStatus.unk_04;
    if (move_frames != 0) {
        target_pos = ((S_80092E90_1 *)actor)->unk_24 << 6;
        tile_origin = motion->x.w.i - 0x20;
        motion->unk_0C =
            ((target_pos - tile_origin) << 16) / move_frames;
        tile_origin = motion->y.w.i;
        tile_origin -= 0x20;
        target_pos = ((S_80092E90_1 *)actor)->unk_25 << 6;
        motion->unk_10 =
            ((target_pos - tile_origin) << 16) / dungeonStatus.unk_04;
    } else {
        motion->unk_0C = 0;
        motion->unk_10 = 0;
    }
    count_state = &D_80083460_count;
    frames_left = ((S_80092E90_3 *)count_state)->unk_04.n;
    frame_count = ((S_80092E90_3 *)count_state)->unk_04.v;
    if (frames_left != 0) {
        ((S_80092E90_3 *)count_state)->unk_04.n2 = frame_count - 1;
    }

    state = ((S_80092E90_4 *)controller)->unk_9B;
    if (state == 0) {
        goto start_effect;
    }
    if (state == 1) {
        goto finish_effect;
    }
    return;

start_effect:
    if (!(((S_80092E90_1 *)actor)->unk_14 & 0xE000)) {
        return;
    }
    func_800419EC(0x10, 8);
    (*(void * *)((u8 *)actor + (0x2C))) = D_800DCFF8;
    func_80048A44(
        actor,
        D_800DCFF8[((gameWork.view.viewAngle + ((S_80092E90_5 *)entry)->unk_2A + 0x100) >> 9) & 7],
        0,
        1);
    ((S_80092E90_4 *)controller)->unk_9B++;
    return;

finish_effect:
    if (!(((S_80092E90_1 *)actor)->unk_14 & 0xE000)) {
        return;
    }

    found_match = 0;
    if (!((*(u16 *)0x80013714) & 8)) {
        node = (u8 *)((S_80092E90_5 *)entry)->unk_5C + 0x20;
        do {
            if ((D_80082E80.unk_026 ==
                 ((S_80092E90_9 *)(((S_80092E90_7_pre *)node)[-1].unk_00))->unk_26) &&
                ((func_80042900(node, 1) << 16) != 0)) {
                func_80042B68(node, 1);
                found_match = 1;
            }
            node = (u8 *)((S_80092E90_7 *)node)->unk_5C + 0x20;
        } while (node != entry);

        match_result = found_match;
        {
            void *message;
            if (match_result != 0) {
                message = &D_800E0597;
            } else {
                message = &D_800E05C3;
            }
            func_800997FC(message);
        }
    }

    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, ((S_80092E90_1 *)actor)->unk_24, ((S_80092E90_1 *)actor)->unk_25);
    ((S_80092E90_4 *)controller)->unk_8C = &D_8008ACDC;
    dungeonStatus.unk_0A--;
}
