// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

///
/// @author  Laurent Aphecetche

#ifndef ALO_JSONMAP_CODEGEN_GOIMPLEMENTATION_H
#define ALO_JSONMAP_CODEGEN_GOIMPLEMENTATION_H

#include <string>
#include "rapidjson/document.h"

namespace jsonmap
{
namespace codegen
{
namespace go
{
void generateDetElemId2SegType(const rapidjson::Value& catsegs, const rapidjson::Value& detection_elements);
void generateCodeForCathodeSegmentations(const rapidjson::Value& catsegs, const rapidjson::Value& motiftypes,
                                         const rapidjson::Value& jsonPadSizes,
                                         const rapidjson::Value& detection_elements,
                                         const rapidjson::Value& bergs);
} // namespace go
} // namespace codegen
} // namespace jsonmap
#endif
