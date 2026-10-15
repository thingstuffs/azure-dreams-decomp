"""Accounting memoization: content invalidation, cross-row reads and byte order."""
import collections
import json
import os
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
from row_cache import RowCache, FactInputs, text_key, content_key
import call_arity
import census


class RowCacheTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)

    def test_selective_content_invalidation_and_field_counter_order(self):
        calls = []
        def compute():
            calls.append(1)
            return dict(level=3, evidence=[], pins=collections.Counter({'z':1,'a':1}))
        cache = RowCache(self.root, 'test')
        a = cache.get('a', [text_key('source'), text_key('raw'), dict(cfg='2.7.2')], compute)
        cache.get('b', ['unchanged'], compute)
        cache.save()
        cache = RowCache(self.root, 'test')
        a2 = cache.get('a', [text_key('source'), text_key('raw'), dict(cfg='2.7.2')], compute)
        self.assertEqual(json.dumps(a), json.dumps(a2))
        self.assertEqual(list(a2['pins']), ['z','a'])
        a2['evidence'].append('not cached')
        self.assertEqual(cache.new['a']['value']['evidence'], [])
        self.assertEqual(len(calls), 2)
        cache.save()
        for changed in ([text_key('source2'),text_key('raw'),dict(cfg='2.7.2')],
                        [text_key('source'),text_key('raw2'),dict(cfg='2.7.2')],
                        [text_key('source'),text_key('raw'),dict(cfg='2.8.0')]):
            cache = RowCache(self.root, 'test')
            cache.get('a', changed, compute)
            self.assertEqual(cache.stats['misses'], 1)

    def test_bad_file_old_schema_and_value_corruption_are_misses(self):
        cache = RowCache(self.root, 'test'); cache.path.parent.mkdir(parents=True)
        for data in ('{bad', '[]', '{"schema": 0,"rows":{}}'):
            cache.path.write_text(data)
            cache = RowCache(self.root, 'test')
            self.assertEqual(cache.get('a', [], lambda: {'level':0}), {'level':0})
        cache.save()
        doc=json.loads(cache.path.read_text());doc['rows']['a']['value']['level']=5
        cache.path.write_text(json.dumps(doc))
        cache=RowCache(self.root,'test')
        self.assertEqual(cache.get('a',[],lambda:{'level':0}),{'level':0})
        self.assertEqual(cache.stats['corrupt'],1)

    def test_disabled_cache_neither_reads_nor_writes(self):
        cache=RowCache(self.root,'test');cache.get('a',[],lambda:5);cache.save()
        before=cache.path.read_bytes()
        with patch.dict(os.environ,AZURE_ROW_CACHE='0'):
            cache=RowCache(self.root,'test')
            self.assertEqual(cache.get('a',[],lambda:0),0)
            cache.save()
        self.assertEqual(before,cache.path.read_bytes())

    def test_cross_row_callee_parameters_invalidate_caller_but_body_does_not(self):
        # Real arity index parser, no compile and no implementation-shaped key.
        row=dict(id='town/caller',container='town',func='func_80000004')
        facts=FactInputs.__new__(FactInputs)
        facts.code='code';facts.names='names';facts.void='void'
        facts.sites={'town/func_80000004':['PASSTHRU|func_80000000|1']}
        facts.arity=call_arity
        with patch.object(call_arity,'_name_tables',return_value=({}, {}, {}, {})):
            keys=[]
            for text in ('void func_80000000(int a) { f(a); }',
                         'void func_80000000(int a) { g(a); }',
                         'void func_80000000(int a, int b) { g(a); }'):
                index=call_arity.DefIndex.from_texts([('town','callee',text)])
                with patch.object(call_arity,'default_def_index',return_value=index):
                    keys.append(content_key(facts.for_row(row)))
        self.assertEqual(keys[0],keys[1]);self.assertNotEqual(keys[0],keys[2])

    def test_mapping_order_corruption_is_detected(self):
        cache=RowCache(self.root,'test');cache.get('a',[],lambda:{'z':1,'a':2});cache.save()
        doc=json.loads(cache.path.read_text())
        doc['rows']['a']['value']={'a':2,'z':1}
        cache.path.write_text(json.dumps(doc))
        cache=RowCache(self.root,'test')
        self.assertEqual(list(cache.get('a',[],lambda:{'z':1,'a':2})),['z','a'])
        self.assertEqual(cache.stats['corrupt'],1)

if __name__=='__main__':unittest.main()


class UnnamedDataRows(unittest.TestCase):
    def test_data_without_a_function_has_no_named_call_arity_dependencies(self):
        from row_cache import FactInputs
        facts=object.__new__(FactInputs);facts.code='code';facts.names='names';facts.void='void';facts.sites={}
        self.assertEqual(facts.for_row(dict(container='main',func=None,defs=[])),['code','names','void',[],[]])
        facts.sites={'main/a':['PASSTHRU|callee|site']}
        from types import SimpleNamespace
        facts.arity=SimpleNamespace(default_def_index=lambda:SimpleNamespace(callee_params=lambda *a:['arg']))
        self.assertEqual(facts.for_row(dict(id='main/data',container='main',func=None,defs=['a']))[-1],[('callee',['arg'])])
