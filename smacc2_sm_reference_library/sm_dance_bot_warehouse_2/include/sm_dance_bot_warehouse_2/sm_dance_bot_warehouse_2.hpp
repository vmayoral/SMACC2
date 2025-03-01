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

#include <smacc2/smacc.hpp>

#include <sensor_msgs/msg/laser_scan.hpp>

// CLIENT BEHAVIORS
#include <ros_timer_client/client_behaviors/cb_ros_timer.hpp>

#include <multirole_sensor_client/client_behaviors/cb_default_multirole_sensor_behavior.hpp>

#include <nav2z_client/client_behaviors.hpp>
#include <nav2z_client/nav2z_client.hpp>

using namespace cl_nav2z;

#include <sm_dance_bot_warehouse_2/clients/cl_led/client_behaviors/cb_led_off.hpp>
#include <sm_dance_bot_warehouse_2/clients/cl_led/client_behaviors/cb_led_on.hpp>

#include <sm_dance_bot_warehouse_2/clients/cl_lidar/client_behaviors/cb_lidar_sensor.hpp>
#include <sm_dance_bot_warehouse_2/clients/cl_lidar/components/cp_forward_obstacle_detector.hpp>

#include <sm_dance_bot_warehouse_2/clients/cl_nav2z/components/cp_square_shape_bondary.hpp>

#include <sm_dance_bot_warehouse_2/clients/cl_temperature_sensor/client_behaviors/cb_custom_condition_temperature_sensor.hpp>

#include <sm_dance_bot_warehouse_2/clients/cl_service3/client_behaviors/cb_service3.hpp>
#include <sm_dance_bot_warehouse_2/clients/cl_string_publisher/client_behaviors/cb_string_publisher.hpp>

#include <ros_publisher_client/client_behaviors/cb_default_publish_loop.hpp>
#include <ros_publisher_client/client_behaviors/cb_muted_behavior.hpp>
#include <ros_publisher_client/client_behaviors/cb_publish_once.hpp>

#include <ros_publisher_client/cl_ros_publisher.hpp>

using namespace sm_dance_bot_warehouse_2::cl_lidar;
using namespace sm_dance_bot_warehouse_2::cl_service3;
using namespace sm_dance_bot_warehouse_2::cl_string_publisher;
using namespace sm_dance_bot_warehouse_2::cl_temperature_sensor;
using namespace sm_dance_bot_warehouse_2::cl_led;

//STATE REACTORS
#include <sr_all_events_go/sr_all_events_go.hpp>
#include <sr_conditional/sr_conditional.hpp>
#include <sr_event_countdown/sr_event_countdown.hpp>

using namespace smacc2::state_reactors;

// ORTHOGONALS
#include <sm_dance_bot_warehouse_2/orthogonals/or_led.hpp>
#include <sm_dance_bot_warehouse_2/orthogonals/or_navigation.hpp>
#include <sm_dance_bot_warehouse_2/orthogonals/or_obstacle_perception.hpp>
#include <sm_dance_bot_warehouse_2/orthogonals/or_service3.hpp>
#include <sm_dance_bot_warehouse_2/orthogonals/or_string_publisher.hpp>
#include <sm_dance_bot_warehouse_2/orthogonals/or_temperature_sensor.hpp>
#include <sm_dance_bot_warehouse_2/orthogonals/or_timer.hpp>
#include <sm_dance_bot_warehouse_2/orthogonals/or_updatable_publisher.hpp>

namespace sm_dance_bot_warehouse_2
{
//STATE FORWARD DECLARATIONS
class StAcquireSensors;
class StEventCountDown;

class StNavigateUndoMotion;
class StNavigateToWaypoint1;
class StNavigateToWaypointsX;

class StRotateDegrees1;
class StRotateDegrees2;
class StRotateDegrees3;
class StRotateDegrees4;
class StRotateDegrees5;
class StRotateDegrees6;

class StNavigateReverse1;
class StNavigateReverse2;
class StNavigateReverse3;
class StForwardAisle;
class StNavigateUndoMotionLeaf;
class StNavigateNextWaypoint;
class StNavigateUndoMotion2;

//SUPERSTATE FORWARD DECLARATIONS
//MODE STATES FORWARD DECLARATIONS
class MsDanceBotRunMode;
class MsDanceBotRecoveryMode;

namespace SS1
{
class SsRadialPattern1;
}

namespace SS2
{
class SsRadialPattern2;
}

namespace SS3
{
class SsRadialPattern3;
}

namespace SS4
{
class SsFPattern1;
}

namespace SS5
{
class SsSPattern1;
}

namespace SS6
{
class SsSPattern2;
}

// custom smd_dance_bot event
struct EvGlobalError : sc::event<EvGlobalError>
{
};

}  // namespace sm_dance_bot_warehouse_2

using namespace sm_dance_bot_warehouse_2;
using namespace cl_ros_timer;
using namespace smacc2;

namespace sm_dance_bot_warehouse_2
{
/// \brief Advanced example of state machine with smacc that shows multiple techniques
///  for the development of state machines
struct SmDanceBotWareHouse2 : public smacc2::SmaccStateMachineBase<SmDanceBotWareHouse2, MsDanceBotRunMode>
{
  int counter_1;
  bool rt_ready_flag;

  typedef mpl::bool_<false> shallow_history;
  typedef mpl::bool_<false> deep_history;
  typedef mpl::bool_<false> inherited_deep_history;

  using SmaccStateMachineBase::SmaccStateMachineBase;

  void onInitialize() override
  {
    this->setGlobalSMData("counter_1", counter_1);
    this->setGlobalSMData("rt_ready_flag", rt_ready_flag);

    this->createOrthogonal<OrNavigation>();
    this->createOrthogonal<OrObstaclePerception>();
    this->createOrthogonal<OrLED>();
    this->createOrthogonal<OrTemperatureSensor>();
    this->createOrthogonal<OrStringPublisher>();
    this->createOrthogonal<OrService3>();
    this->createOrthogonal<OrTimer>();
    this->createOrthogonal<OrUpdatablePublisher>();
  }
};

}  // namespace sm_dance_bot_warehouse_2

//MODE STATES
#include <sm_dance_bot_warehouse_2/modestates/ms_dance_bot_run_mode.hpp>

#include <sm_dance_bot_warehouse_2/modestates/ms_dance_bot_recovery_mode.hpp>

//SUPERSTATES
#include <sm_dance_bot_warehouse_2/superstates/ss_f_pattern_1.hpp>
#include <sm_dance_bot_warehouse_2/superstates/ss_radial_pattern_1.hpp>
#include <sm_dance_bot_warehouse_2/superstates/ss_radial_pattern_2.hpp>
#include <sm_dance_bot_warehouse_2/superstates/ss_radial_pattern_3.hpp>
#include <sm_dance_bot_warehouse_2/superstates/ss_s_pattern_1.hpp>
#include <sm_dance_bot_warehouse_2/superstates/ss_s_pattern_2.hpp>

//STATES
#include <sm_dance_bot_warehouse_2/states/st_acquire_sensors.hpp>
#include <sm_dance_bot_warehouse_2/states/st_event_count_down.hpp>

#include <sm_dance_bot_warehouse_2/states/st_navigate_to_waypoints_x.hpp>

#include <sm_dance_bot_warehouse_2/states/st_navigate_undo_motion.hpp>
#include <sm_dance_bot_warehouse_2/states/st_navigate_undo_motion_leaf.hpp>
#include <sm_dance_bot_warehouse_2/states/st_navigate_next_waypoint.hpp>
#include <sm_dance_bot_warehouse_2/states/st_navigate_undo_motion_2.hpp>

#include <sm_dance_bot_warehouse_2/states/st_navigate_reverse_2.hpp>
#include <sm_dance_bot_warehouse_2/states/st_navigate_reverse_3.hpp>
#include <sm_dance_bot_warehouse_2/states/st_forward_aisle.hpp>
#include <sm_dance_bot_warehouse_2/states/st_navigate_to_waypoint_1.hpp>
#include <sm_dance_bot_warehouse_2/states/st_rotate_degrees_1.hpp>
#include <sm_dance_bot_warehouse_2/states/st_rotate_degrees_2.hpp>
#include <sm_dance_bot_warehouse_2/states/st_rotate_degrees_3.hpp>
#include <sm_dance_bot_warehouse_2/states/st_rotate_degrees_4.hpp>
#include <sm_dance_bot_warehouse_2/states/st_rotate_degrees_5.hpp>
#include <sm_dance_bot_warehouse_2/states/st_rotate_degrees_6.hpp>
