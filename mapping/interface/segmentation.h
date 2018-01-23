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
/// @author  Laurent Apaduidecetche


#ifndef O2_MCH_MAPPING_SEGMENTATION_H
#define O2_MCH_MAPPING_SEGMENTATION_H

#include "segmentationCInterface.h"
#include <stdexcept>
#include <memory>
#include <iostream>
#include <vector>

namespace o2 {
namespace mch {
namespace mapping {

class Segmentation
{
  public:
    Segmentation(int detElemId, bool isBendingPlane) : mImpl(nullptr), mDualSampaIds{}
    {
      mImpl = mchSegmentationConstruct(detElemId, isBendingPlane);
      if (!mImpl) {
        throw std::runtime_error("Can not create segmentation for DE " + std::to_string(detElemId) +
                                 (isBendingPlane ? " Bending" : " NonBending"));
      }
      std::vector<int> dpid;
      auto addDualSampaId = [&dpid](int dualSampaId) {
        dpid.push_back(dualSampaId);
      };
      auto callback = [](void *data, int dualSampaId) {
        auto fn = static_cast<decltype(&addDualSampaId)>(data);
        (*fn)(dualSampaId);
      };
      mchForEachDualSampa(mImpl, callback, &addDualSampaId);
      mDualSampaIds = dpid;
    }

    ~Segmentation()
    { mchSegmentationDestruct(mImpl); }

    bool isValid(int paduid) const
    {
      return mchSegmentationIsPadValid(mImpl, paduid) > 0;
    }

    int findPadByPosition(double x, double y) const
    {
      return mchSegmentationFindPadByPosition(mImpl, x, y);
    }

    int findPadByFEE(int dualSampaId, int dualSampaChannel) const
    {
      if (dualSampaChannel < 0 || dualSampaChannel > 63) {
        throw std::out_of_range("dualSampaChannel should be between 0 and 63");
      }
      return mchSegmentationFindPadByFEE(mImpl, dualSampaId, dualSampaChannel);
    }

    int id() const
    { return mchSegmentationId(mImpl); }

    int nofDualSampas() const
    { return mDualSampaIds.size(); }

    int dualSampaId(int dualSampaIndex) const
    { return mDualSampaIds[dualSampaIndex]; }

    double padPositionX(int paduid) const
    {
      return mchSegmentationPadPositionX(mImpl, paduid);
    }

    double padPositionY(int paduid) const
    {
      return mchSegmentationPadPositionY(mImpl, paduid);
    }

    double padSizeX(int paduid) const
    {
      return mchSegmentationPadSizeX(mImpl, paduid);
    }

    double padSizeY(int paduid) const
    {
      return mchSegmentationPadSizeY(mImpl, paduid);
    }

    int nofPads() const
    {
      int n{0};
      for (auto i = 0; i < nofDualSampas(); ++i) {
        forEachPadInDualSampa(dualSampaId(i), [&n](int /*paduid*/) { ++n; });
      }
      return n;
    }

    template<typename CALLABLE>
    void forEachPadInDualSampa(int dualSampaId, CALLABLE &&func) const;

  private:
    MchSegmentationHandle mImpl;
    std::vector<int> mDualSampaIds;
};

template<typename CALLABLE>
void Segmentation::forEachPadInDualSampa(int dualSampaId, CALLABLE &&func) const
{
  auto callback = [](void *data, int paduid) {
    auto fn = static_cast<decltype(&func)>(data);
    (*fn)(paduid);
  };
  mchForEachPadInDualSampa(mImpl, dualSampaId, callback, &func);
}

template<typename CALLABLE>
void forEachDetectionElement(CALLABLE &&func)
{
  auto callback = [](void *data, int detElemId) {
    auto fn = static_cast<decltype(&func)>(data);
    (*fn)(detElemId);
  };
  mchForEachDetectionElement(callback, &func);
}

template<typename CALLABLE>
void forOneDetectionElementOfEachSegmentationType(CALLABLE &&func)
{
  auto callback = [](void *data, int detElemId) {
    auto fn = static_cast<decltype(&func)>(data);
    (*fn)(detElemId);
  };
  mchForOneDetectionElementOfEachSegmentationType(callback, &func);
}

}
}
}
#endif
