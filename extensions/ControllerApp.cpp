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

#include "utils/ndn-ns3-packet-tag.hpp"
#include "utils/ndn-rtt-mean-deviation.hpp"

#include <ndn-cxx/lp/tags.hpp>

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

  .AddAttribute("StartSeq", "Initial sequence number", IntegerValue(0),
              MakeIntegerAccessor(&ControllerApp::m_seq), MakeIntegerChecker<int32_t>())

  .AddAttribute("Prefix", "Name of the Interest", StringValue("/"),
              MakeNameAccessor(&ControllerApp::m_interestName), MakeNameChecker())
  
  .AddAttribute("LifeTime", "LifeTime for interest packet", StringValue("2s"),
              MakeTimeAccessor(&ControllerApp::m_interestLifeTime), MakeTimeChecker())

  .AddConstructor<ControllerApp>();
  
  return tid;
}


ControllerApp::ControllerApp()
{

}


void
ControllerApp::StartApplication()
{
  NS_LOG_FUNCTION_NOARGS();

  App::StartApplication();
  
  ndn::FibHelper::AddRoute(GetNode(), "/edu.bit.cn/", m_face, 0); // equivalent to setting interest filter for "/prefix" prefix

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
  ndn::App::OnInterest(interest); // forward call to perform app-level tracing
  
  // do nothing else (receive interest from consumer)
  
  NS_LOG_DEBUG("Requesting Interest from Consumer" << interest->getName());  

}

void
ControllerApp::OnData(std::shared_ptr<const ndn::Data> data)
{
  ndn::App::OnData(data); // forward call to perform app-level tracing
  
  // do nothing else (receive data from producer)
  
  NS_LOG_DEBUG("Requesting Data from Producer" << data->getName());  

}

} //  namespace ndn
} //  namespace ns3