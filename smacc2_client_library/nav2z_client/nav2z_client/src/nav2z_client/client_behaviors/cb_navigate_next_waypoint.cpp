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

#include <nav2z_client/client_behaviors/cb_navigate_next_waypoint.hpp>

namespace cl_nav2z
{
CbNavigateNextWaypoint::CbNavigateNextWaypoint(std::optional<NavigateNextWaypointOptions> options)
{
  if (options) options_ = *options;
}

CbNavigateNextWaypoint::~CbNavigateNextWaypoint() {}

void CbNavigateNextWaypoint::onEntry()
{
  waypointsNavigator_ = nav2zClient_->getComponent<WaypointNavigator>();

  this->navigationCallback_ = std::make_shared<cl_nav2z::ClNav2Z::SmaccNavigateResultSignal>();

  this->getStateMachine()->createSignalConnection(
    *navigationCallback_, &CbNavigateNextWaypoint::onNavigationResult, this);

  auto goalHandle = waypointsNavigator_->sendNextGoal(options_, navigationCallback_);

  auto waypointname = waypointsNavigator_->getCurrentWaypointName();

  if (waypointname)
  {
    RCLCPP_INFO(
      getLogger(), "[CbNavigateNextWaypoint] current iteration waypoints i: %ld with name '%s'",
      waypointsNavigator_->getCurrentWaypointIndex(), waypointname->c_str());
  }
  else
  {
    RCLCPP_INFO(
      getLogger(), "[CbNavigateNextWaypoint] current iteration waypoints i: %ld",
      waypointsNavigator_->getCurrentWaypointIndex());
  }
}

void CbNavigateNextWaypoint::onExit() { waypointsNavigator_->stopWaitingResult(); }

}  // namespace cl_nav2z
