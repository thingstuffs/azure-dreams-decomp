struct Tbl {
    unsigned char unk0[4];
    unsigned char unk4;
    unsigned char unk5[3];
};

struct Ent {
    unsigned char unk0[14];
    unsigned char unkE;
    unsigned char unkF[4];
    unsigned char unk13;
};

extern unsigned char catalog_scroll_offset[];
extern struct Tbl catalog_detail_images[];

/* Update entry flags from the global value and the entry's table threshold. */
void update_catalog_scroll_availability(struct Ent *entry)
{
    unsigned char flags;

    if (catalog_scroll_offset[0] != 0) {
        entry->unkE |= 1;
    } else {
        entry->unkE &= 0xFE;
    }
    if (catalog_scroll_offset[0] < ((catalog_detail_images[entry->unk13].unk4 - 3) << 4)) {
        flags = entry->unkE | 2;
    } else {
        flags = entry->unkE & 0xFD;
    }
    entry->unkE = flags;
}
