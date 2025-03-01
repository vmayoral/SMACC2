// Copyright 2021 MyName/MyCompany Inc.
// Copyright 2021 RobosoftAI Inc. (template)
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
 *****************************************************************************************************************/

#pragma once

#include "rclcpp/rclcpp.hpp"
#include "smacc2/smacc.hpp"

namespace sm_multi_ur5_sim
{
// SMACC2 classes
using smacc2::Transition;
using smacc2::default_transition_tags::SUCCESS;
using namespace smacc2;

// STATE DECLARATION
struct StMoveCartesianRelative2 : smacc2::SmaccState<StMoveCartesianRelative2, SmTestMoveitUr5Sim>
{
  using SmaccState::SmaccState;

  // TRANSITION TABLE
  typedef boost::mpl::list<
    Transition<EvCbSuccess<CbMoveCartesianRelative2, OrArm>, StAttachObject, SUCCESS>,
    Transition<EvCbFailure<CbMoveCartesianRelative2, OrArm>, StMoveCartesianRelative2, ABORT> // retry
    >

    reactions;

  // STATE FUNCTIONS
  static void staticConfigure()
  {
    geometry_msgs::msg::Vector3 position;
    position.x = -0.01;
    position.y = 0.0;
    position.z = 0.01;
    configure_orthogonal<OrArm, CbMoveCartesianRelative2>("tool0", "tool0", position);
  }

  void runtimeConfigure() { RCLCPP_INFO(getLogger(), "Entering StMoveCartesianRelative2"); }

  void onEntry() { RCLCPP_INFO(getLogger(), "On Entry!"); }

  void onExit(ABORT)
  {
    rclcpp::sleep_for(1s);
    RCLCPP_INFO(getLogger(), "On Exit!");
  }
};
}  // namespace sm_multi_ur5_sim
