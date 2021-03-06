//
// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See https://alice-o2.web.cern.ch/ for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

///
/// @author  Laurent Aphecetche

#include <AliMpSegmentation.h>
#include "readmapping.h"
#include "de.h"
#include "seg.h"
#include "mapping.h"
#include <algorithm>

Mapping::Mapping()
{
  ddlStore();
}

AliMpDDLStore* Mapping::ddlStore()
{
  static AliMpDDLStore* ddlStore = nullptr;
  static AliMpSegmentation* mseg = nullptr;
  if (!ddlStore) { readMapping(ddlStore, mseg); }
  return ddlStore;
}

AliMpSegmentation* Mapping::mseg()
{
  static AliMpSegmentation* mseg = AliMpSegmentation::Instance();
  return mseg;
}

std::vector<int> Mapping::deids()
{
  static std::vector<int> v = get_deids(ddlStore());
  return v;
}

std::vector<AliMpVSegmentation*> Mapping::b_segs()
{
  static std::vector<AliMpVSegmentation*> v = get_segs(mseg(), deids(), AliMp::kBendingPlane);
  return v;
};

std::vector<AliMpVSegmentation*> Mapping::nb_segs()
{
  static std::vector<AliMpVSegmentation*> v = get_segs(mseg(), deids(), AliMp::kNonBendingPlane);
  return v;
};

AliMpVSegmentation* getSegmentation(std::string segname, AliMp::PlaneType plane)
{
  Mapping m;

  const std::vector<AliMpVSegmentation*>& segs = (plane == AliMp::kBendingPlane ? m.b_segs() : m.nb_segs());

  auto ix = std::find_if(segs.begin(), segs.end(),
                         [&](AliMpVSegmentation* seg) { return get_segtype(*seg) == segname; });

  if (ix != segs.end()) {
    return *ix;
  }
  return nullptr;
}
