"""An include can replace an unused identical alias without changing active layouts."""
import sys
import unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parent))
import plan as P
import rewrite as R
from test_headers import COMMON,mkroot

class UnusedTypedefInclude(unittest.TestCase):
    def plan(self, local='typedef s32 UnusedAlias;\n', header='typedef s32 UnusedAlias;\n'):
        td,root=mkroot({'include/common.h':COMMON,
                       'include/engine.h':'#include "common.h"\n'+header+'s32 real(s32 v);\n',
                       'src/engine/real.c':'#include "common.h"\ns32 real(s32 v) { return v; }\n',
                       'src/town/caller.c':'#include "common.h"\n'+local+'extern s32 real(s32 v);\ns32 caller(void) { return real(3); }\n'})
        self.addCleanup(td.cleanup)
        plan=P.build(root,scope_files=['src/town/caller.c'])
        return root,plan,plan.tus['src/town/caller.c']
    def test_unused_identical_alias_moves_with_header(self):
        root,plan,tp=self.plan()
        self.assertNotIn('include/engine.h',tp.holds)
        edit=R.tu_edit(tp,lambda r:plan.fn_for_def(r.definition).header)
        old=(root/'src/town/caller.c').read_text();new=R.edit_tu(old,edit)
        self.assertNotIn('typedef s32 UnusedAlias;',new)
        self.assertIn('#include "engine.h"',new)
        self.assertIn('s32 caller(void) { return real(3); }',new)
        self.assertEqual(R.edit_tu(old,edit,[]),old)
    def test_used_alias_keeps_clash(self):
        _,_,tp=self.plan('typedef s32 UnusedAlias;\nUnusedAlias state;\n')
        self.assertEqual(tp.holds['include/engine.h'],'typedef_clash:UnusedAlias')
    def test_different_type_keeps_clash(self):
        _,_,tp=self.plan(header='typedef u32 UnusedAlias;\n')
        self.assertEqual(tp.holds['include/engine.h'],'typedef_clash:UnusedAlias')
    def test_macro_reference_keeps_clash(self):
        _,_,tp=self.plan('typedef s32 UnusedAlias;\n#define LOCAL_TYPE UnusedAlias\n')
        self.assertEqual(tp.holds['include/engine.h'],'typedef_clash:UnusedAlias')
    def test_conditional_alias_keeps_clash(self):
        _,_,tp=self.plan('#if 1\ntypedef s32 UnusedAlias;\n#endif\n')
        self.assertEqual(tp.holds['include/engine.h'],'typedef_clash:UnusedAlias')
    def test_held_include_keeps_typedef(self):
        root,plan,tp=self.plan()
        tp.holds['include/engine.h']='proof_error';tp.add.remove('include/engine.h')
        edit=R.tu_edit(tp,lambda r:plan.fn_for_def(r.definition).header)
        old=(root/'src/town/caller.c').read_text()
        new=R.edit_tu(old,edit)
        self.assertIn('typedef s32 UnusedAlias;',new)
        self.assertIn('extern s32 real(s32 v);',new)
        self.assertNotIn('#include "engine.h"',new)

if __name__=='__main__':unittest.main()
