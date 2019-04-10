/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2019 Beijing Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author:  <email@email.com>
 */

#include "ControllerApp.hpp"

#include "ns3/ptr.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/packet.h"
#include "ns3/callback.h"
#include "ns3/string.h"
#include "ns3/boolean.h"
#include "ns3/uinteger.h"
#include "ns3/integer.h"
#include "ns3/double.h"

#include "ns3/names.h"


#include "utils/ndn-ns3-packet-tag.hpp"
#include "utils/ndn-rtt-mean-deviation.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/ref.hpp>

NS_LOG_COMPONENT_DEFINE("ControllerApp");

namespace ns3 {
namespace ndn {


// Necessary if you are planning to use ndn::AppHelper
NS_OBJECT_ENSURE_REGISTERED(ControllerApp);

TypeId
ControllerApp::GetTypeId()
{
  static TypeId tid = TypeId("ControllerApp")
  .SetGroupName("Ndn")
  .SetParent<ndn::App>()
  .AddConstructor<ControllerApp>()
      .AddAttribute ("Prefix","Prefix, for which producer has the data",
                   StringValue ("/"),
                   MakeNameAccessor (&ControllerApp::m_prefix),
                   MakeNameChecker ())
    .AddAttribute ("Postfix", "Postfix that is added to the output data (e.g., for adding producer-uniqueness)",
                   StringValue ("/"),
                   MakeNameAccessor (&ControllerApp::m_postfix),
                   MakeNameChecker ())
    .AddAttribute ("PayloadSize", "Virtual payload size for Content packets",
                   UintegerValue (1024),
                   MakeUintegerAccessor (&ControllerApp::m_virtualPayloadSize),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("Freshness", "Freshness of data packets, if 0, then unlimited freshness",
                   TimeValue (Seconds (0.5)),
                   MakeTimeAccessor (&ControllerApp::m_freshness),
                   MakeTimeChecker ())
    .AddAttribute ("Signature", "Fake signature, 0 valid signature (default), other values application-specific",
                   UintegerValue (0),
                   MakeUintegerAccessor (&ControllerApp::m_signature),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("KeyLocator", "Name to be used for key locator.  If root, then key locator is not used",
                   NameValue (),
                   MakeNameAccessor (&ControllerApp::m_keyLocator),
                   MakeNameChecker ())
    ;
  return tid;
}


ControllerApp::ControllerApp()
{
  NS_LOG_FUNCTION_NOARGS ();
  m_seq = 0;
}


// inherited from Application base class.
void
ControllerApp::StartApplication()
{
  NS_LOG_FUNCTION_NOARGS();
  App::StartApplication();
  // equivalent to setting interest filter for "/prefix" prefix
  ndn::FibHelper::AddRoute(GetNode(), "/edu.bit.cn/", m_face, 0); 
}

void
ControllerApp::StopApplication()
{
  NS_LOG_FUNCTION_NOARGS();
  App::StopApplication();
}

void
ControllerApp::OnInterest(std::shared_ptr<const ndn::Interest> interest)
{
  ndn::App::OnInterest(interest); 
  // forward call to perform app-level tracing
  // do nothing else (receive interest from consumer)
  std::cout << "Controller received an interest packet. Name: " << interest->getName() << "\n";
  std::cout << "Source node for Hello packets->  " << Names::FindName(GetNode())<<endl;

}

void
ControllerApp::OnData(std::shared_ptr<const ndn::Data> data)
{
  ndn::App::OnData(data); 
  std::cout << "Controller received a data packet. Name: " << data->getName() << "\n";
  
}


} //  namespace ndn
} //  namespace ns3