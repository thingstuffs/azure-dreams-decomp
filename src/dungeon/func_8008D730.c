#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_800419EC();
extern s32 func_80042900();
extern s32 func_80042B68();
extern s32 func_80048A44();
extern s32 func_800997FC();
extern s32 func_800A2B04();

extern u16 D_80013714;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80083460_count __asm__("D_80083460");
extern s32 D_8008ACDC;
extern u8 D_800DCFF8[];
extern u8 D_800E0597;
extern u8 D_800E05C3;


typedef struct S_80092E90_0 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_80092E90_0;   /* global in func_80092E90 */

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

typedef struct S_80092E90_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80092E90_6;   /* actorBase in func_80092E90 */

typedef struct S_80092E90_7_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80092E90_7_pre;   /* the 0x14 bytes before node in func_80092E90, addressed as node[-1] */

typedef struct S_80092E90_7 {
    u8 pad_00[0x5C];
    void * unk_5C;
} S_80092E90_7;   /* node in func_80092E90 */

typedef struct S_80092E90_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80092E90_8;   /* endBase in func_80092E90 */

typedef struct S_80092E90_9 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80092E90_9;   /* ((S_80092E90_7_pre *)node)[-1].unk_00 in func_80092E90 */

/* Move toward the target tile, process matching list entries, and advance the effect state. */
void func_80092E90(void *controller, void *motion, void *actor, void *entry)
{
    register void *list_head ASM_REG("$21") = entry;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *player;
    s32 found_match;
    s32 tile_origin;
    s32 target_pos;
    register s32 effect_id ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    register s32 match_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 frames_left;
    s16 move_frames;
    s16 *move_state;
    u16 frame_count;
    u8 state;
    void *count_state;
    void *end_state;
    void *node;

    move_state = (s16 *)&D_80083460;
    move_frames = ((S_80092E90_0 *)move_state)->unk_04;
    if (move_frames != 0) {
        target_pos = ((S_80092E90_1 *)actor)->unk_24 << 6;
        tile_origin = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 =
            ((target_pos - tile_origin) << 16) / move_frames;
        tile_origin = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v;
        tile_origin -= 0x20;
        target_pos = ((S_80092E90_1 *)actor)->unk_25 << 6;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            ((target_pos - tile_origin) << 16) / ((S_80092E90_0 *)move_state)->unk_04;
    } else {
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
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
    effect_id = 0x10;
    if (!(((S_80092E90_1 *)actor)->unk_14 & 0xE000)) {
        return;
    }
    func_800419EC(effect_id, 8);
    (*(void * *)((u8 *)actor + (0x2C))) = D_800DCFF8;
    func_80048A44(
        actor,
        D_800DCFF8[((D_80083228 + ((S_80092E90_5 *)list_head)->unk_2A + 0x100) >> 9) & 7],
        0,
        1);
    ((S_80092E90_4 *)controller)->unk_9B++;
    return;

finish_effect:
    if (!(((S_80092E90_1 *)actor)->unk_14 & 0xE000)) {
        return;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    found_match = 0;
    if (!(D_80013714 & 8)) {
        node = (u8 *)((S_80092E90_5 *)list_head)->unk_5C + 0x20;
        player = D_80082E80;
        do {
            if ((((S_80092E90_6 *)player)->unk_26 ==
                 ((S_80092E90_9 *)(((S_80092E90_7_pre *)node)[-1].unk_00))->unk_26) &&
                ((func_80042900(node, 1) << 16) != 0)) {
                func_80042B68(node, 1);
                found_match = 1;
            }
            node = (u8 *)((S_80092E90_7 *)node)->unk_5C + 0x20;
        } while (node != list_head);

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

    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((S_80092E90_1 *)actor)->unk_24, ((S_80092E90_1 *)actor)->unk_25);
    ((S_80092E90_4 *)controller)->unk_8C = &D_8008ACDC;
    end_state = &D_80083460;
    ((S_80092E90_8 *)end_state)->unk_0A--;
}
