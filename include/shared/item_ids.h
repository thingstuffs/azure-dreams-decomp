#ifndef SHARED_ITEM_IDS_H
#define SHARED_ITEM_IDS_H

/* Four-byte item descriptors: ID at +0, category at +1. Category names come
 * from itemCategoryTable and its game text; unrelated layout/format fields
 * and item-action callback modes are not this enum. */
enum ItemKind {
    ITEM_KIND_NONE = 0x0,
    ITEM_KIND_HERB = 0x1,
    ITEM_KIND_FRUIT = 0x2,
    ITEM_KIND_SEED = 0x3,
    ITEM_KIND_BALL = 0x4,
    ITEM_KIND_SCROLL = 0x5,
    ITEM_KIND_CRYSTAL = 0x6,
    ITEM_KIND_BELL = 0x7,
    ITEM_KIND_GLASSES = 0x8,
    ITEM_KIND_LOUPE = 0x9,
    ITEM_KIND_SAND = 0xa,
    ITEM_KIND_COIN = 0xe,
    ITEM_KIND_SWORD = 0xf,
    ITEM_KIND_WAND = 0x10,
    ITEM_KIND_SHIELD = 0x11,
    ITEM_KIND_EGG = 0x12,
    ITEM_KIND_FAMILIAR = 0x13,
    ITEM_KIND_ELEVATOR = 0x14,
    ITEM_KIND_TRAP = 0x15,
};

/* These IDs require their category: equal numbers in other tables differ. */
enum ItemId {
    ITEM_PITA_FRUIT = 0x1,
    ITEM_BLUE_COLLAR = 0x4,
    ITEM_MEAT = 0x6,
    ITEM_WATER_MEDAL = 0x2,
    ITEM_COPPER_COIN = 0x1,
    ITEM_SILVER_COIN = 0x2,
    ITEM_GOLD_COIN = 0x3,
    ITEM_TRAINED_WAND = 0x2,
};

#endif
