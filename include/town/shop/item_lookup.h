#ifndef TOWN_SHOP_ITEM_LOOKUP_H
#define TOWN_SHOP_ITEM_LOOKUP_H

int get_item_chk(void);
void *find_item_by_kind_and_type(int item_kind, int item_type);
int find_first_vacant_record(const unsigned char *records, int count);

#endif
