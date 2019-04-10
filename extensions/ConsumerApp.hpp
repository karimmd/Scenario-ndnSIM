/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2011-2015  Regents of the University of California.
 *
 * This file is part of ndnSIM. See AUTHORS for complete list of ndnSIM authors and
 * contributors.
 *
 * ndnSIM is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * ndnSIM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ndnSIM, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef CONSUMER_APP_H_
#define CONSUMER_APP_H_

#include <ndn-cxx/data.hpp>
#include <ndn-cxx/encoding/tlv.hpp>

#include "ns3/ndnSIM-module.h"
#include "ns3/integer.h"
#include "ns3/string.h"
#include "apps/ndn-app.hpp"
#include "NFD/rib/rib-manager.hpp"
#include "ns3/ndnSIM/helper/ndn-strategy-choice-helper.hpp"

namespace nfd_rib = nfd::rib;
namespace nfd_fw = nfd::fw;

namespace ns3 {
namespace ndn {

class ConsumerApp : public ndn::App 

{

public:
  // register NS-3 type "ConsumerApp"
  static TypeId
  GetTypeId();

  // (overridden from ndn::App) Processing upon start of the application
  virtual void
  StartApplication();

  // (overridden from ndn::App) Processing when application is stopped
  virtual void
  StopApplication();

  // (overridden from ndn::App) Callback that will be called when Interest arrives
  virtual void
  OnInterest(std::shared_ptr<const ndn::Interest> interest);

  virtual void
  SendInterest();

  //virtual void
  //SendInterest(const string& interestName);

  // (overridden from ndn::App) Callback that will be called when Data arrives
  virtual void
  OnData(std::shared_ptr<const ndn::Data> contentObject);

private:
  //void
  //SendInterest();

  //Specific to Consumer
  //Name m_interestName;
};

} // namespace ndn
} // namespace ns3

#endif // CONSUMER_APP_H_
