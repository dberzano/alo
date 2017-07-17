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

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include "genMotifType.h"
#include <array>

using namespace o2::mch::mapping;

std::array<std::pair<int, int>,47> Non64Motifs = {
  std::make_pair<int, int>(4, 48),
  std::make_pair<int, int>(5, 63),
  std::make_pair<int, int>(7, 46),
  std::make_pair<int, int>(8, 32),
  std::make_pair<int, int>(16, 48),
  std::make_pair<int, int>(17, 56),
  std::make_pair<int, int>(18, 40),
  std::make_pair<int, int>(19, 40),
  std::make_pair<int, int>(31, 48),
  std::make_pair<int, int>(32, 48),
  std::make_pair<int, int>(41, 62),
  std::make_pair<int, int>(42, 48),
  std::make_pair<int, int>(47, 62),
  std::make_pair<int, int>(48, 62),
  std::make_pair<int, int>(49, 49),
  std::make_pair<int, int>(50, 39),
  std::make_pair<int, int>(51, 32),
  std::make_pair<int, int>(52, 50),
  std::make_pair<int, int>(55, 57),
  std::make_pair<int, int>(56, 40),
  std::make_pair<int, int>(58, 58),
  std::make_pair<int, int>(61, 60),
  std::make_pair<int, int>(76, 52),
  std::make_pair<int, int>(77, 56),
  std::make_pair<int, int>(78, 55),
  std::make_pair<int, int>(79, 60),
  std::make_pair<int, int>(80, 62),
  std::make_pair<int, int>(81, 60),
  std::make_pair<int, int>(82, 59),
  std::make_pair<int, int>(83, 46),
  std::make_pair<int, int>(85, 31),
  std::make_pair<int, int>(86, 57),
  std::make_pair<int, int>(87, 60),
  std::make_pair<int, int>(88, 63),
  std::make_pair<int, int>(89, 57),
  std::make_pair<int, int>(92, 58),
  std::make_pair<int, int>(93, 54),
  std::make_pair<int, int>(95, 48),
  std::make_pair<int, int>(96, 54),
  std::make_pair<int, int>(97, 60),
  std::make_pair<int, int>(99, 60),
  std::make_pair<int, int>(158, 48),
  std::make_pair<int, int>(183, 56),
  std::make_pair<int, int>(184, 56),
  std::make_pair<int, int>(185, 56),
  std::make_pair<int, int>(186, 56),
  std::make_pair<int, int>(201, 48)
};

BOOST_AUTO_TEST_SUITE(o2_mch_mapping)
BOOST_AUTO_TEST_SUITE(motiftype)

BOOST_AUTO_TEST_CASE(NumberOfMotifTypes)
{
  BOOST_CHECK_EQUAL(ArrayOfMotifTypes.size(), 210);
}

BOOST_AUTO_TEST_CASE(NumberOfNon64Motifs)
{
  BOOST_CHECK_EQUAL(Non64Motifs.size(),47);
}

BOOST_AUTO_TEST_CASE(NumberOfPads) {

  for ( auto i = 0; i <ArrayOfMotifTypes.size(); ++i ) {
    const MotifType& mt = ArrayOfMotifTypes[i];
    auto f = std::find_if(Non64Motifs.begin(),Non64Motifs.end(),[&](const std::pair<int,int>& p) { return p.first == i; });
    if ( f == Non64Motifs.end() ) {
      BOOST_CHECK_EQUAL(mt.NofPads(),64);
    }
    else {
      BOOST_CHECK_EQUAL(mt.NofPads(),f->second);
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
