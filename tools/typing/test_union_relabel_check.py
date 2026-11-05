import unittest

from tools.typing.union_relabel_check import (declaration_swaps, missing_declaration_edits,
                                              stale_uses, swaps_from_diff, unchanged_uses)


class RelabelCheckTest(unittest.TestCase):
    def test_finds_member_left_outside_hunk(self):
        patch = '''@@ -2 +2 @@
-    object->unk_02.s = value;
+    object->unk_02.u = value;
'''
        swaps = swaps_from_diff(patch)
        self.assertEqual(swaps, {('->unk_02.', 's', 'u')})
        self.assertEqual(stale_uses('object->unk_02.u = 1;\nobject->unk_02.s = 2;\n', swaps),
                         [(2, '->unk_02.', 's', 'u')])

    def test_ignores_edits_without_member_swap(self):
        patch = '''@@ -1 +1 @@
-    object->unk_02.s = 1;
+    object->unk_02.s = 2;
'''
        self.assertEqual(swaps_from_diff(patch), set())

    def test_retired_access_does_not_shift_later_member_positions(self):
        patch = '''@@ -1 +1 @@
-    obj->heading.u = face(actor->tile.at00.x, actor->tile.at01.y);
+    obj->heading = face(actor->tile.at00.x, actor->tile.at01.y);
'''
        self.assertEqual(swaps_from_diff(patch), set())

    def test_two_way_swap_audits_unchanged_lines(self):
        patch = '''@@ -1,2 +1,2 @@
-    object->unk_02.s = value;
-    other = object->unk_02.u;
+    object->unk_02.u = value;
+    other = object->unk_02.s;
'''
        swaps = swaps_from_diff(patch)
        self.assertEqual(swaps, {('->unk_02.', 's', 'u'), ('->unk_02.', 'u', 's')})
        old = 'object->unk_02.s = value;\nother = object->unk_02.u;\nleft = object->unk_02.s;\n'
        new = 'object->unk_02.u = value;\nother = object->unk_02.s;\nleft = object->unk_02.s;\n'
        self.assertEqual(unchanged_uses(old, new, swaps), [(3, '->unk_02.', 's', 'u')])

    def test_declaration_swap_without_use_edit_is_visible(self):
        old = 'union { u16 s; s16 u; } unk_02;'
        new = 'union { u16 u; s16 s; } unk_02;'
        self.assertEqual(declaration_swaps(old, new),
                         {('unk_02', 's', 'u'), ('unk_02', 'u', 's')})
        declarations = [('include/test.h', field, before, after)
                        for field, before, after in declaration_swaps(old, new)]
        self.assertEqual(len(missing_declaration_edits(declarations, {})), 2)

    def test_unused_member_does_not_require_a_site_edit(self):
        declarations = [('include/test.h', 'unk_02', 's', 'u'),
                        ('include/test.h', 'unk_02', 'u', 's')]
        source = 'value = object->unk_02.s;\n'
        files = {'src/test.c': (source, 'value = object->unk_02.u;\n',
                                {('->unk_02.', 's', 'u')})}
        self.assertEqual(missing_declaration_edits(declarations, files), [])


if __name__ == '__main__':
    unittest.main()
