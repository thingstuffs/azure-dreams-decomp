"""Prototype requests publish through the ordinary extern planner and its holds."""
import json
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
import extern_bulk as B
import plan as P
import rewrite as R
from test_headers import COMMON, mkroot


class RequestedPrototypeTest(unittest.TestCase):
    def root(self, extra=None):
        files = {'include/common.h': COMMON,
                 'include/engine.h': '#ifndef ENGINE_H\n#define ENGINE_H\n#include "common.h"\n#endif\n',
                 'include/imports.h': '#include "common.h"\ns32 func_80001000(s32 value);\n',
                 'src/engine/real.c': '#include "common.h"\ns32 real(s32 value) { return value; }\n',
                 'src/town/caller.c': '#include "imports.h"\ns32 caller(void) { return func_80001000(3); }\n'}
        files.update(extra or {})
        td, root = mkroot(files)
        self.addCleanup(td.cleanup)
        return root

    def build(self, root):
        return P.build(root, scope_files=['src/town/caller.c'], requests={'src/town/caller.c': {'real'}})

    def test_request_adds_owner_include_and_prototype_without_respell(self):
        root = self.root()
        plan = self.build(root)
        tp = plan.tus['src/town/caller.c']
        self.assertIn('include/engine.h', tp.add)
        self.assertEqual(tp.append['include/engine.h'], ['real'])
        self.assertFalse(tp.remove)
        edit = R.tu_edit(tp, lambda r: plan.fn_for_def(r.definition).header)
        after = R.edit_tu((root/'src/town/caller.c').read_text(), edit)
        self.assertIn('#include "engine.h"', after)
        self.assertIn('func_80001000(3)', after)
        header = R.append_text(plan, 'include/engine.h', ['real'], (root/'include/engine.h').read_text())
        self.assertIn('s32 real(s32 value);', header)

    def test_consumer_conflict_holds_the_request(self):
        root = self.root({'src/town/consumer.c': '#include "engine.h"\nextern s32 real(s16 value);\n'})
        plan = self.build(root)
        tp = plan.tus['src/town/caller.c']
        self.assertIn('consumer_conflict', tp.holds['include/engine.h'])
        self.assertNotIn('include/engine.h', tp.add)

    def test_prototype_floor_applies_to_requests(self):
        root = self.root({'ledger/prototype_floors.jsonl': json.dumps({'name': 'real'})+'\n'})
        bulk = B.Bulk(root, ['src/town/caller.c'], False, lambda *_: True,
                      log=lambda *_: None, names={'real'}, requests={'src/town/caller.c': {'real'}})
        self.assertIn(('src/town/caller.c', 'include/engine.h'), bulk.held)
        self.assertIn('prototype_floor:real', [why for _, _, why in bulk.holds])

    def test_existing_prototype_is_still_an_include_request(self):
        root = self.root({'include/engine.h': '#include "common.h"\ns32 real(s32 value);\n'})
        bulk = B.Bulk(root, ['src/town/caller.c'], False, lambda *_: True,
                      log=lambda *_: None, names={'real'}, requests={'src/town/caller.c': {'real'}})
        self.assertIn('include/engine.h', bulk.jobs['src/town/caller.c'][1]['add'])

    def test_default_plan_does_not_request_other_names(self):
        root = self.root()
        plan = P.build(root, scope_files=['src/town/caller.c'])
        self.assertNotIn('include/engine.h', plan.tus['src/town/caller.c'].add)

    def test_existing_include_can_request_only_a_header_append(self):
        root = self.root({'src/town/caller.c': '#include "imports.h"\n#include "engine.h"\n'
                           's32 caller(void) { return func_80001000(3); }\n'})
        bulk = B.Bulk(root, ['src/town/caller.c'], False, lambda *_: True,
                      log=lambda *_: None, names={'real'}, requests={'src/town/caller.c': {'real'}})
        bulk._base['include/engine.h'] = (root/'include/engine.h').read_text()
        texts = bulk.texts()
        self.assertNotIn('src/town/caller.c', texts)
        self.assertIn('s32 real(s32 value);', texts['include/engine.h'])


if __name__ == '__main__':
    unittest.main()
