/******************************************************************************\

  CAMotics is an Open-Source simulation and CAM software.
  Copyright (C) 2011-2019 Joseph Coffland <joseph@cauldrondevelopment.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

\******************************************************************************/

#pragma once


#include "MachineNode.h"

#include <cbang/Catch.h>
#include <cbang/SmartPointer.h>


namespace GCode {
  class MachineAdapter : public MachineNode, public MachineInterface {
    class _ {
      const MachineAdapter &adapter;
    public:
      _(const MachineAdapter *adapter) : adapter(*adapter) {
        CBANG_TRY_CATCH_ERROR(adapter->enter());
      }
      ~_() {CBANG_TRY_CATCH_ERROR(adapter.exit());}
    };

  public:
    MachineAdapter(const cb::SmartPointer<MachineInterface> &next = 0) :
      MachineNode(next) {}

    virtual void enter() const {}
    virtual void exit() const {}

    // From MachineInterface
    void start() override {_ _(this); next->start();}
    void end() override {_ _(this); next->end();}

    double getFeed() const override {_ _(this); return next->getFeed();}
    void setFeed(double feed) override {_ _(this); next->setFeed(feed);}
    feed_mode_t getFeedMode() const override
      {_ _(this); return next->getFeedMode();}
    void setFeedMode(feed_mode_t mode) override
      {_ _(this); next->setFeedMode(mode);}

    double getSpeed() const override {_ _(this); return next->getSpeed();}
    void setSpeed(double speed) override {_ _(this); next->setSpeed(speed);}

    spin_mode_t getSpinMode(double *max = 0) const override
      {_ _(this); return next->getSpinMode(max);}
    void setSpinMode(spin_mode_t mode = REVOLUTIONS_PER_MINUTE,
                     double max = 0) override
      {_ _(this); next->setSpinMode(mode, max);}

    void setPathMode(path_mode_t mode, double motionBlending = 0,
                     double naiveCAM = 0) override
      {_ _(this); next->setPathMode(mode, motionBlending, naiveCAM);}

    void changeTool(unsigned tool) override {_ _(this); next->changeTool(tool);}

    void input(port_t port, input_mode_t mode, double timeout) override
      {_ _(this); next->input(port, mode, timeout);}
    void seek(port_t port, bool active, bool error) override
      {_ _(this); next->seek(port, active, error);}
    void output(port_t port, double value) override
      {_ _(this); next->output(port, value);}

    Axes getPosition() const override {_ _(this); return next->getPosition();}
    cb::Vector3D getPosition(axes_t axes) const override
      {_ _(this); return next->getPosition(axes);}
    void setPosition(const Axes &position) override
      {_ _(this); next->setPosition(position);}

    void dwell(double seconds) override {_ _(this); next->dwell(seconds);}
    void move(const Axes &position, int axes, bool rapid, double time) override
      {_ _(this); next->move(position, axes, rapid, time);}
    void arc(const cb::Vector3D &offset, const cb::Vector3D &target,
             double angle, plane_t plane) override
      {_ _(this); next->arc(offset, target, angle, plane);}

    Transforms &getTransforms() override
      {_ _(this); return next->getTransforms();}

    void pause(pause_t type) override {_ _(this); next->pause(type);}

    double get(address_t addr, Units units) const override
      {_ _(this); return next->get(addr, units);}
    void set(address_t addr, double value, Units units) override
      {_ _(this); next->set(addr, value, units);}

    bool has(const std::string &name) const override
      {_ _(this); return next->has(name);}
    double get(const std::string &name, Units units) const override
      {_ _(this); return next->get(name, units);}
    void set(const std::string &name, double value, Units units) override
      {_ _(this); next->set(name, value, units);}
    void clear(const std::string &name) override {_ _(this); next->clear(name);}

    const cb::LocationRange &getLocation() const override
      {_ _(this); return next->getLocation();}
    void setLocation(const cb::LocationRange &location) override
      {_ _(this); next->setLocation(location);}

    void comment(const std::string &s) const override
      {_ _(this); next->comment(s);}
    void message(const std::string &s) override {_ _(this); next->message(s);}
    void gprint(const std::string &s) const override
      {_ _(this); next->gprint(s);}
  };
}
