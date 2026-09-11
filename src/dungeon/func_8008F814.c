#include "common.h"

typedef struct Slot {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
} Slot;

typedef struct Ent {
    u8 a;
    u8 b;
    u8 pad[10];
} Ent;

typedef struct Sys {
    s32 f0;
    s32 f4;
    s32 f8;
} Sys;

typedef struct Ctx {
    u8 pad0[0xA2];
    u16 flags;
    u8 pad1[0x18];
    void *link;
    u8 pad2[0x3B];
    u8 done;
    s32 total;
    s16 mode;
} Ctx;

typedef struct Item {
    u8 pad[0x24];
    u8 kind;
    u8 sub;
} Item;

typedef struct Unit {
    u8 pad[0x88];
    s16 id;
} Unit;

extern Sys D_80083160;
extern u8 D_80081485[16];
extern u16 D_80013714[8];
extern u16 D_80012094;
extern u16 D_80012096;
extern Slot D_800E3548[];
extern Ent D_800E36C8[];
extern char D_80088A80[];
extern char D_80088A84[];
extern char D_800E0A76[];
extern char D_800E0A83[];
extern char D_800E0A90[];
extern char D_800E0AA1[];
extern char D_800E0ABC[];
extern char D_800E0AD8[];
extern char D_800E0AFA[];
extern char D_800E0B07[];

s32 func_800A70E4(s32, s32, s32);
void func_80095DD0(Ctx *, char *, Item *, Unit *);
s32 func_800990FC(void);
char *func_8009929C(s32, s32);
char *func_80099194(char *, char *);
char *func_80099368(Slot *, char *);
void func_80099290(char *);
void func_800A5720(s32);
s32 func_80098FB0(void);
s32 func_80098FF8(void);
void func_8009F644(Unit *, s32, s32, s32);
u8 *func_8009F868(void);
void func_8009F988(void);
s32 func_800438E4(void);
void func_800B4C7C(s32, Unit *, s32, s32);
void func_8009A3D0(s32, s32, s32);

/* Picks up an item, applying special effects or moving it into inventory. */
s32 func_80094F74(Ctx *ctx, char *text, Item *item, Unit *unit) {
    Sys *sys;
    s32 item_lookup;
    s16 item_id;
    char *message;
    s32 message_handle;
    s32 free_entry;
    s32 free_slot;
    s16 slot_index;
    s16 entry_index;
    s32 pickup_value;
    Slot *ground_item;
    Slot *named_item;
    Slot *special_item;
    Slot *stored_item;
    Slot *consumed_item;
    u16 *state_page;
    s32 unused_three;
    void **inventory_slot;
    u8 *active_effect;
    s32 consumed_id;
    s16 stored_id;
    u32 *pickup_slot;
    Slot *ground_items;
    Slot *special_items;
    Slot *consumed_items;
    u8 *inventory_page;
    u8 *entity_page;
    Ent *entities;
    s32 item_kind;

    sys = &D_80083160;
    item_lookup = func_800A70E4(item->kind, item->sub, unit->id);
    item_id = item_lookup;
    if (item_id < 0) {
        if (ctx->mode < 0) {
            return 1;
        }
        func_80095DD0(ctx, text, item, unit);
        return 0;
    }
    message_handle = func_800990FC();
    message = func_8009929C(8, message_handle);
    if (D_80081485[0] != 0) {
        func_80099290(func_80099194(D_80088A80, func_80099368(&D_800E3548[item_id], func_80099194(D_800E0A76, message))));
        func_800A5720(message_handle);
        return 1;
    }
    free_slot = func_80098FB0();
    free_entry = func_80098FF8();
    if ((D_80013714[0] & 1) == 0) {
        if ((sys->f8 & 0x20) != 0) {
            func_8009F644(unit, 64, 0, 0);
            func_80099290(func_80099194(D_80088A80, func_80099368(&D_800E3548[item_id], func_80099194(D_800E0A83, message))));
            func_800A5720(message_handle);
            return 1;
        }
    } else {
        active_effect = func_8009F868();
        if (active_effect != 0) {
            if ((active_effect[1] & 0xF8) == 0x40) {
                return 1;
            }
            func_8009F988();
        }
    }
    ground_items = D_800E3548;
    ground_item = &ground_items[(s16) item_lookup];
    if ((ground_item->b1 == 14) || ((ground_item->b1 == 12) && (ground_item->b0 == 4)) || ((ground_item->b1 == 18) && (ground_item->b0 == 1))) {
        named_item = &D_800E3548[(s16) item_lookup];
        message = func_80099368(named_item, message);
        if (named_item->b1 == 14) {
            message = func_80099194(D_80088A84, message);
        } else {
            message = func_80099194(D_800E0A90, message);
        }
        special_items = D_800E3548;
        ctx->flags |= 0x80;
        special_item = &special_items[(s16) item_lookup];
        item_kind = special_item->b1;
        if (item_kind == 12) {
            ASM_USE2(special_item, item_kind);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            message = func_80099194(D_800E0ABC, func_8009929C(10, func_80099194(D_800E0AA1, func_8009929C(10, message))));
            ctx->done = 1;
            state_page = (u16 *) 0x80010000;
            if (D_80012094 != 3) {
                state_page[0x104B] = 3;
            } else {
                do {
                    state_page[0x104B] = 5;
                } while (0);
            }
            *(u16 *) 0x8001209A = 0;
        } else if (item_kind == 14) {
            pickup_value = func_800438E4();
            ctx->total += pickup_value;
            func_800B4C7C(151, unit, (s16) pickup_value, 1);
        }
        consumed_id = (s16) item_lookup;
        pickup_slot = (u32 *) 0x80010298;
        consumed_items = D_800E3548;
        consumed_item = &consumed_items[consumed_id];
        *pickup_slot = *(u32 *) consumed_item;
        consumed_item->b0 = 0;
        consumed_item->b1 = 0;
        func_8009A3D0(D_800E36C8[consumed_id].a, D_800E36C8[consumed_id].b, 0x800);
        ctx->link = pickup_slot;
    } else {
        slot_index = free_slot;
        entry_index = free_entry;
        if ((slot_index < 0) || (entry_index < 0)) {
            message = func_80099194(D_80088A80, func_80099368(&D_800E3548[(s16) item_lookup], func_80099194(D_800E0AFA, func_8009929C(10, func_80099194(D_800E0AD8, message)))));
        } else {
            stored_id = item_lookup;
            stored_item = &D_800E3548[stored_id];
            message = func_80099194(D_800E0B07, func_80099368(stored_item, message));
            inventory_slot = (void **) 0x80010248 + slot_index;
            *inventory_slot = *(void **) stored_item;
            inventory_page = (u8 *) 0x80010000;
            *(void ***) (inventory_page + (entry_index * 4) + 0x29C) = inventory_slot;
            ctx->flags |= 0x80;
            stored_item->b0 = 0;
            stored_item->b1 = 0;
            entity_page = (u8 *) 0x800E0000;
            ASM_KEEP_NV(entity_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            entities = (Ent *) (entity_page + 0x36C8);
            func_8009A3D0(entities[stored_id].a, entities[stored_id].b, 0x800);
            ctx->link = inventory_slot;
        }
    }
    func_80099290(message);
    func_800A5720(message_handle);
    return 1;
}
