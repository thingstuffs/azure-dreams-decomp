#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_800A71F0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800A71F0_0;

typedef struct S_800A71F0_1 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_800A71F0_1;

typedef struct S_800A71F0_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A71F0_2;

typedef struct S_800A71F0_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800A71F0_3;

typedef struct S_800A71F0_4 {
    u8 pad_00[0x54];
    s32 unk_54;
    u8 pad_58[0x38];
    s16 unk_90;
} S_800A71F0_4;

typedef struct S_800A71F0_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800A71F0_5;
void func_80033CD8(void *block_data, s32 registration_id);
struct Dst;
struct Elem;
void func_8003DB94(struct Dst *state, struct Elem *entries, short index);
void *func_8003FD64();
void copy_indexed_motion_value_and_advance();
typedef struct S_800A7338_0 S_800A7338_0;
void invoke_emote_object_callback(S_800A7338_0 *object);
extern s32 D_800D0DF0;

/* Creates a positioned object and initializes its state and sprite. */
s32 create_positioned_sprite_object(void *position, s32 state_value, s32 graphic_id) {
    void *object;
    void *object_state;
    void *transform;
    void *sprite;

    object = func_8003FD64(0x136, ((s32 *)&D_80083498.next));
    if (object == 0) {
        return 0;
    }
    object_state = object + 0x20;
    transform = ((S_800A71F0_0 *)object)->unk_08;
    sprite = ((S_800A71F0_0 *)object)->unk_0C;
    ((S_800A71F0_1 *)transform)->unk_00 = (s32) ((S_800A71F0_2 *)position)->unk_00;
    ((S_800A71F0_1 *)transform)->unk_04 = (s32) ((S_800A71F0_2 *)position)->unk_04;
    (*(s32 *)((u8 *)transform + 8)) = (s32) (((S_800A71F0_2 *)position)->unk_08 + 0xFFDC0000);
    ((S_800A71F0_1 *)transform)->unk_0C = (s32) D_800D0DF0;
    ((S_800A71F0_1 *)transform)->unk_10 = (s32) ((S_800A71F0_3 *)(&D_800D0DF0))->unk_04;
    ((S_800A71F0_0 *)object)->unk_10 = &invoke_emote_object_callback;
    ((S_800A71F0_4 *)object_state)->unk_54 = state_value;
    ((S_800A71F0_4 *)object_state)->unk_90 = 2;
    copy_indexed_motion_value_and_advance(object_state, transform, sprite);
    ((S_800A71F0_5 *)sprite)->unk_1E = 0x1000;
    ((S_800A71F0_5 *)sprite)->unk_1C = 0x1000;
    ((S_800A71F0_5 *)sprite)->unk_0C = 0x808080;
    func_8003DB94(sprite, graphic_id, 0);
    func_80033CD8(object_state, func_80045340);
    return (s32) object;
}
