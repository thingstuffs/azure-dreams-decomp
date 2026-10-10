#ifndef DUNGEON_OVL_1918800_H
#define DUNGEON_OVL_1918800_H
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "m2c_compat.h"
typedef struct PackedVector {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} PackedVector __attribute__((packed));
typedef struct Pair16 {
    s16 x;
    s16 y;
} Pair16;
typedef struct {
    s16 x;
    u16 y;
} Copy4;
typedef struct {
    Copy4 entries[8];
} __attribute__((packed)) Copy24;
extern s16 D_800266BC;
extern const PackedVector D_80024004;
extern const PackedVector D_8002400C;
extern const Copy24 D_80024014;
struct CountdownRecord;
struct Func818F9D8CState;
struct OutView;
struct PacketView;
struct PointRecord;
struct Position;
struct ProjectileSelf;

void func_8002405C(void *screen_pos, u8 *wave, void *context, s32 *ordering_table, s32 draw_control);
void func_80024CD4(s32 draw_param_a, s32 draw_param_b, struct Position *restore_area, struct Position *draw_pos, u32 clear_area, s32 draw_option);
s32 func_80024EDC(struct PointRecord *start_node, EntityRec *start_coords);
s32 func_8002512C(void);
void func_8002515C(EntityRec *state, EntityRec *position);
void func_80025228( ObjectNodeHeader *parent, s16 field_34, s32 field_28, s16 field_52, s16 offset_x, s16 offset_y, s16 offset_z);
void func_80025348(struct CountdownRecord *record);
void func_80025398(void *effect, void *unused, void *primitive);
void func_8002558C(struct Func818F9D8CState *state, s32 unused, u8 *out);
void func_80025648(void *state, void *position_out, void *effect_arg);
void func_8002592C(struct ProjectileSelf *self, struct OutView *position, struct PacketView *render_data);
s32 func_8003DE58(void *, void *, void *, s32);
ObjectNodeHeader *func_8003FC64(s32);
s32 rand(void);
#endif
