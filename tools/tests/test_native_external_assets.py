"""Cross-container native views must use the proven map of their actual asset."""
import json,tempfile,unittest
from pathlib import Path
from unittest.mock import patch
from gate import overlay_module_gate as G

class ExternalAssets(unittest.TestCase):
 def setUp(self):
  self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup);self.root=Path(self.tmp.name)
  self.map=dict(asset='work/disc/containers/TOWN_TOWN.BIN',file_start=0xB000,file_end=0x96000,delta=0x8007D760,basis='Observed transfer and RAM payload equality',kind='rowbase',container='town',region='xfer_town_B000')
  self.view=dict(symbol='D_800D0118',kind='data',vma=0x800D0118,foff=0x529B8,view_bytes=16,asset=self.map['asset'],owner='retail_asset:'+self.map['asset'],map='resident',evidence='evidence.json')
  self.record=dict(region='xfer_town_B000',base_confidence='proven',foff_start='0xB000',foff_end='0x96000',delta='0x8007D760')
 def validate(self,family='town'):
  (self.root/'evidence.json').write_text(json.dumps(dict(views={self.view['symbol']:self.view},maps={'resident':self.map})))
  with patch.object(G,'ranges',side_effect=lambda root,container:[self.record] if container==family else []):G.validate_asset(self.root,self.view)
 def test_town_view_uses_town_map(self):self.validate()
 def test_town_view_cannot_borrow_dungeon_map(self):
  with self.assertRaisesRegex(ValueError,'load-map evidence differs'):self.validate('dungeon')
 def test_wrong_container_asset_pair_is_rejected(self):
  self.map['container']='dungeon'
  with self.assertRaisesRegex(ValueError,'asset/container differs'):self.validate()
 def test_unknown_container_is_rejected(self):
  self.map['container']='invented'
  with self.assertRaisesRegex(ValueError,'asset/container differs'):self.validate()
 def test_changed_proven_map_is_rejected(self):
  self.record['delta']='0x8007D800'
  with self.assertRaisesRegex(ValueError,'load-map evidence differs'):self.validate()
 def test_view_cannot_cross_resident_extent(self):
  self.view['foff']=self.map['file_end']-8;self.view['vma']=self.view['foff']+self.map['delta']
  with self.assertRaisesRegex(ValueError,'asset load map differs'):self.validate()
 def test_legacy_dungeon_evidence_remains_valid(self):
  self.map.pop('container');self.map['asset']='work/disc/containers/DUNGEON_DUNGEON.BIN';self.view['asset']=self.map['asset'];self.view['owner']='retail_asset:'+self.map['asset'];self.validate('dungeon')
if __name__=='__main__':unittest.main()
