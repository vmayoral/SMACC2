// Copyright 2021 RobosoftAI Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*****************************************************************************************************************
 *
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/

#pragma once

#include <smacc2/smacc.hpp>
#include <nav2z_client/nav2z_client.hpp>
#include <nav2z_client/client_behaviors.hpp>

namespace sm_husky_barrel_search_1
{
using namespace smacc2::default_events;
using namespace cl_nav2z;
using namespace smacc2;
using sm_husky_barrel_search_1::cl_led_array::CbSequenceColorBlinking;

// STATE DECLARATION
struct StLedBlinkingCommuncation : smacc2::SmaccState<StLedBlinkingCommuncation, SmHuskyBarrelSearch1>
{
  using SmaccState::SmaccState;

  // TRANSITION TABLE
  typedef mpl::list<Transition<EvCbSuccess<CbSleepFor, OrNavigation>, StExitBase>,
                    Transition<EvCbFailure<CbSleepFor, OrNavigation>, StLedBlinkingCommuncation>>
      reactions;

  // STATE FUNCTIONS
  static void staticConfigure()
  {
    configure_orthogonal<OrLedArray, CbSequenceColorBlinking>();
    configure_orthogonal<OrNavigation, CbSleepFor>(6s);
  }

  void runtimeConfigure()
  {
  }
};
}  // namespace sm_husky_barrel_search_1
