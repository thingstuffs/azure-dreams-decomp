#ifndef TOWN_MENU_CATALOG_H
#define TOWN_MENU_CATALOG_H

/* The two catalog cursor handlers dispatch these phases from object +4.
 * They populate the entry number, hide the cursor, then position it. */
enum CatalogCursorPhase {
    CATALOG_CURSOR_NUMBER = 1,
    CATALOG_CURSOR_HIDE = 2,
    CATALOG_CURSOR_POSITION = 3,
};

#endif
