import unittest
from triage import calls_in, analyze
from test_headers import mkroot, COMMON
class CallTests(unittest.TestCase):
    def test_nested_commas_and_address_use(self):
        self.assertEqual(list(calls_in('f(g(1,2), a[3]); use(f); f();', {'f'})),
                         [('f',2,False),('f',None,True),('f',0,False)])

    def test_member_call_is_not_a_global_call(self):
        self.assertEqual(list(calls_in('object.f(1); ptr->f(2); f(3);', {'f'})),[('f',1,False)])

    def test_equal_prototypes_do_not_resolve_duplicate_ownership(self):
        td,root=mkroot({'include/common.h':COMMON,
            'src/engine/a.c':'#include "common.h"\nvoid f(void) {}\n',
            'src/engine/b.c':'#include "common.h"\nvoid f(void) {}\n',
            'src/engine/c.c':'#include "common.h"\nextern void f(s32,s32);\nvoid c(void) { f(1,2); }\n'})
        self.addCleanup(td.cleanup)
        rows=[r for r in analyze(root) if r['name']=='f']
        self.assertTrue(rows)
        self.assertTrue(all(r['status']=='hold' and r['reason']=='multiple_definition_ownership' for r in rows))

    def test_generated_prototype_is_not_caller_evidence(self):
        td,root=mkroot({'include/common.h':COMMON,
            'include/engine.h':'/* maintained by tools/headers */\nvoid f(void);\n',
            'src/engine/a.c':'#include "common.h"\nvoid f(void) {}\n',
            'src/engine/c.c':'#include "common.h"\nextern void f(s32,s32);\nvoid c(void) { f(1,2); }\n'})
        self.addCleanup(td.cleanup)
        rows=[r for r in analyze(root) if r['name']=='f']
        self.assertEqual(rows[0]['status'],'candidate')

    def test_raw_alias_calls_count_toward_consensus(self):
        td,root=mkroot({'include/common.h':COMMON,
            'config/names.tsv':'0x80000000\tfunc_80000000\trenamed\tevidence\n',
            'src/engine/a.c':'#include "common.h"\nvoid renamed(void) {}\n',
            'src/engine/c.c':'#include "common.h"\nextern void func_80000000(s32,s32);\nvoid c(void) { func_80000000(1,2); }\n'})
        self.addCleanup(td.cleanup)
        rows=[r for r in analyze(root) if r['name']=='renamed']
        self.assertEqual(rows[0]['status'],'candidate')
        self.assertEqual(rows[0]['arities'],{2:1})

    def test_raw_alias_address_use_keeps_signature_held(self):
        td,root=mkroot({'include/common.h':COMMON,
            'config/names.tsv':'0x80000000\tfunc_80000000\trenamed\tevidence\n',
            'src/engine/a.c':'#include "common.h"\nvoid renamed(void) {}\n',
            'src/engine/c.c':'#include "common.h"\nextern void func_80000000();\nextern void renamed(s32,s32);\nvoid *cb=func_80000000;\nvoid c(void) { renamed(1,2); }\n'})
        self.addCleanup(td.cleanup)
        rows=[r for r in analyze(root) if r['name']=='renamed']
        self.assertEqual(rows[0]['reason'],'address_taken_or_noncall_use')

    def test_live_alias_alternatives_are_ambiguous(self):
        td,root=mkroot({'include/common.h':COMMON,
            'config/names.tsv':'0x80000000\tfunc_80000000\trenamed\tevidence\n',
            'src/engine/a.c':'#include "common.h"\nvoid func_80000000(void) {}\n',
            'src/engine/b.c':'#include "common.h"\nvoid renamed(void) {}\n',
            'src/engine/c.c':'#include "common.h"\nextern void func_80000000(s32,s32);\nvoid c(void) { func_80000000(1,2); }\n'})
        self.addCleanup(td.cleanup)
        rows=analyze(root)
        self.assertTrue(rows)
        self.assertTrue(all(r['reason']=='alias_binding_ambiguous' for r in rows))

    def test_parameter_shadow_does_not_supply_direct_call_evidence(self):
        td,root=mkroot({'include/common.h':COMMON,
            'src/engine/a.c':'#include "common.h"\nvoid f(void) {}\n',
            'src/engine/c.c':'#include "common.h"\ntypedef void (*Fn)(s32,s32);\nextern void f(s32,s32);\nvoid c(Fn f) { f(1,2); }\n'})
        self.addCleanup(td.cleanup)
        rows=[r for r in analyze(root) if r['name']=='f']
        self.assertEqual(rows[0]['reason'],'address_taken_or_noncall_use')

    def test_variadic_definition_is_not_given_fixed_unused_formals(self):
        td,root=mkroot({'include/common.h':COMMON,
            'src/engine/a.c':'#include "common.h"\nvoid f(s32 first,...) {}\n',
            'src/engine/c.c':'#include "common.h"\nextern s32 f(s32,s32,s32);\nvoid c(void) { f(1,2,3); }\n'})
        self.addCleanup(td.cleanup)
        rows=[r for r in analyze(root) if r['name']=='f']
        self.assertEqual(rows[0]['reason'],'unsupported_definition')

    def test_added_formal_uses_builtin_when_common_alias_is_not_visible(self):
        td,root=mkroot({'include/common.h':COMMON,
            'src/engine/a.c':'void f(void) {}\n',
            'src/engine/c.c':'#include "common.h"\nextern void f(s32);\nvoid c(void) { f(1); }\n'})
        self.addCleanup(td.cleanup)
        rows=[r for r in analyze(root) if r['name']=='f']
        self.assertEqual(rows[0]['proposed'],'void f(int unused_arg0)')
