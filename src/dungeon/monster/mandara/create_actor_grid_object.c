#include "shared/actor_status_flags.h"
#include "shared/slus_callbacks.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "dungeon/actor/animation.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "dungeon/monster/beldo.h"
#include "dungeon/monster/cyclone.h"
#include "dungeon/monster/mandara.h"
#include "sdk/libgpu.h"
#include "dungeon/monster/zu.h"

typedef void (*Callback)(void);

typedef struct {
    Callback callbacks[27];
    u8 config[56];
} ActorDefinition;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

extern s32 generate_random_value(void); /* Retail RNG at 0x800A6D30 reads no incoming argument registers, including a3. */
extern s16 set_or_clear_actor_status_slot(ActorRecord *owner, s8 id, s8 value);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern void func_80170B40(void);
extern void func_80171198(void);
extern void func_8017126C(void);
extern void func_801713FC(void);
extern void func_80171444(void);
extern void func_80171740(void);
extern void func_80171784(void);
extern void func_80171794(void);
extern void func_801717C0(void);
extern void func_80172EA8(void);
extern void func_80172EB0(void);
extern void func_80172EB8(void);
extern void func_80172EF8(void);
extern void func_80172F08(void);
extern void func_80172F10(void);
extern void func_80175258(void);
extern void func_80175298(void);

void *create_mandara_actor(s16, s32, s16, s16);

typedef struct S_80FB1000_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FB1000_0;   /* work in create_mandara_actor */

typedef struct S_80FB1000_2 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80FB1000_2;   /* (*(u8 * *)((u8 *)monster + 8)) + (scale + i) * 4 in create_mandara_actor */

/* Creates Mandara with frames at func_80175258, copies its palette row and four strips, and attempts tile
 * placement. */
void *create_mandara_actor(s16 mode, s32 value1, s16 value2, s16 value3)
{
    s16 mode_copy;
    s32 value1_saved;
    s8 value2_byte;
    s16 value3_saved;
    ObjectNodeHeader *created;
    u8 *work = 0;
    ObjectPosition *position;
    SpriteFrameState *monster;
    u8 *actor;
    s32 kind;
    Rect rect;

    value1_saved = value1;
    value3_saved = value3;
    value2_byte = value2;
    value1 = 0x112;
    created = allocate_list_node(value1, &scene_object_list_anchor.next);
    mode_copy = (s32)mode;
    if (created != 0) {
        void *init_object;
        s32 flags0;
        s32 flags1;
        s32 value;
        u8 *entry;
        s32 i;
        s32 scale;

        work = (u8 *)created + 0x20;
        (created ->update_callback) = func_80170B40;
        ((S_80FB1000_0 *)work)->unk_13 = MONSTER_MANDARA;
        register_node(created, project_sprite_chain);

        position = created ->position;
        position->z.w.i = value3_saved;
        monster = created ->sprite;
        monster->tile_y = value2_byte;
        actor = work;
        monster->frameTable = func_80175258;
        monster->tile_x = value1_saved;

        kind = (s32)mode & 3;
        if (kind == 1) {
            flags0 = ((S_80FB1000_0 *)work)->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            flags1 = ((S_80FB1000_0 *)work)->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            ((S_80FB1000_0 *)work)->unk_14 = flags0;
            ((S_80FB1000_0 *)work)->unk_1C = flags1;
        } else if (kind >= 2) {
            flags0 = ((S_80FB1000_0 *)work)->unk_14 | ACTOR_CLASS_ENABLED;
            flags1 = ((S_80FB1000_0 *)work)->unk_1C | ACTOR_PLAYER_SIDE;
            ((S_80FB1000_0 *)work)->unk_14 = flags0;
            ((S_80FB1000_0 *)work)->unk_1C = flags1;
        } else {
            if ((s16)((s32)mode & -4) == 0 &&
                !(((S_80FB1000_0 *)work)->unk_14 & ACTOR_RESIST_SLEEP)) {
                value = generate_random_value();
                if (value & 1) {
                    ((S_80FB1000_0 *)work)->unk_1C |= ACTOR_ASLEEP;
                    value = generate_random_value();
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP, (value & 0x3F) | 0x20);
                    monster->frameTable = func_80175298;
                }
            }
        }

        init_object = created;
        initialize_actor_sprite_and_animation(init_object, position, monster, (s16)mode_copy);
        i = 0;
        value = monster->clut;
        (*(u8 *)((u8 *)actor + 0x9A)) = 0xFF;
        (*(s8 *)((u8 *)actor + 0x9C)) = -1;
        (*(ActorActionHandler *)((u8 *)actor + 0x8C)) = update_long_actor_action;
        (*(s16 *)((u8 *)actor + 0xAE)) = value;

        entry = *(u8 * *)&monster->source;
        while (1) {
            scale = i << 1;
            if (!(entry[0] & 0x20)) {
                break;
            }
            entry += 12;
            i++;
        }
        value = ((S_80FB1000_2 *)(*(u8 * *)&monster->source + (scale + i) * 4))->unk_06 >> 6;
        rect.x = 0;
        rect.y = value;
        rect.w = 0x100;
        rect.h = 1;
        MoveImage(&rect, 0, value - 1);

        rect.w = 0x10;
        rect.x = 0x30;
        rect.y--;
        do {
            MoveImage(&rect, rect.x - 0x30, rect.y);
            rect.x += 0x40;
        } while (rect.x < 0x100);

        try_move_actor_to_valid_position(actor, position, monster, work);
    }
    return work;
}
