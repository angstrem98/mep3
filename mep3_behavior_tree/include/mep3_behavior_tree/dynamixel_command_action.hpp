// Copyright 2021 Memristor Robotics
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

#ifndef MEP3_BEHAVIOR_TREE__DYNAMIXEL_COMMAND_ACTION_HPP_
#define MEP3_BEHAVIOR_TREE__DYNAMIXEL_COMMAND_ACTION_HPP_

#include <string>

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "mep3_behavior_tree/bt_action_node.hpp"
#include "mep3_msgs/action/dynamixel_command.hpp"

namespace mep3_behavior_tree
{
class DynamixelCommandAction
  : public mep3_behavior_tree::BtActionNode<mep3_msgs::action::DynamixelCommand>
{
public:
  explicit DynamixelCommandAction(
    const std::string & xml_tag_name, const BT::NodeConfiguration & config)
  : mep3_behavior_tree::BtActionNode<mep3_msgs::action::DynamixelCommand>(
      xml_tag_name, "dynamixel_command", config)
  {
  }

  void on_tick() override;
  BT::NodeStatus on_success() override;
  BT::NodeStatus on_aborted() override;
  BT::NodeStatus on_cancelled() override;

  static BT::PortsList providedPorts()
  {
    return providedBasicPorts(
      {BT::InputPort<_Float64>("position"), BT::InputPort<_Float64>("velocity"),
        BT::InputPort<_Float64>("tolerance"), BT::InputPort<_Float64>("timeout"),
        BT::OutputPort<int8_t>("result")});
  }
};

void DynamixelCommandAction::on_tick()
{
  _Float64 position, velocity, tolerance, timeout;

  getInput("position", position);
  getInput("velocity", velocity);
  getInput("tolerance", tolerance);
  getInput("timeout", timeout);

  goal_.position = position;
  goal_.velocity = velocity;
  goal_.tolerance = tolerance;
  goal_.timeout = timeout;
}

BT::NodeStatus DynamixelCommandAction::on_success()
{
  setOutput("result", 0);
  return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus DynamixelCommandAction::on_aborted()
{
  setOutput("result", 2);
  return BT::NodeStatus::FAILURE;
}

BT::NodeStatus DynamixelCommandAction::on_cancelled()
{
  setOutput("result", 2);
  return BT::NodeStatus::FAILURE;
}

}  // namespace mep3_behavior_tree

#endif  // MEP3_BEHAVIOR_TREE__DYNAMIXEL_COMMAND_ACTION_HPP_
