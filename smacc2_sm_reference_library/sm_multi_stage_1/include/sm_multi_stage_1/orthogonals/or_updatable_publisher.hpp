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

#pragma once

#include <ros_publisher_client/cl_ros_publisher.hpp>
#include <smacc2/smacc_orthogonal.hpp>
#include <std_msgs/msg/string.hpp>

namespace sm_multi_stage_1
{
using namespace cl_ros_publisher;

class OrUpdatablePublisher : public smacc2::Orthogonal<OrUpdatablePublisher>
{
public:
  virtual void onInitialize() override
  {
    auto ros_publisher_client = this->createClient<ClRosPublisher>();
  }
};
}  // namespace sm_multi_stage_1
