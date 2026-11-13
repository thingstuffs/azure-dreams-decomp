#ifndef TOWN_SHOP_ITEM_LOOKUP_H
#define TOWN_SHOP_ITEM_LOOKUP_H

int get_item_chk(void);
void *find_item_by_kind_and_type(int item_kind, int item_type);
int find_first_vacant_record(const unsigned char *records, int count);

int find_slot_index_by_address(void *target_addr, void *slot_addr, int slot_count);

#endif
