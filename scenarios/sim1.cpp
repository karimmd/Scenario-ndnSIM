#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ndnSIM-module.h"
#include "ns3/file-aggregator.h"
#include "ns3/ndnSIM/helper/ndn-link-control-helper.hpp"


#include "../extensions/ControllerApp.hpp"
#include "../extensions/ControllerStrategy.hpp"

namespace nfd_fw = nfd::fw;

// Calling Main Functions
namespace ns3 {

int
main(int argc, char* argv[])

{

  // Read optional command-line parameters (e.g., enable visualizer with ./waf --run=<> --visualize
  CommandLine cmd;
  cmd.Parse (argc, argv);

  // Reading a Topology File from a given directory
  AnnotatedTopologyReader topologyReader("", 25);
  topologyReader.SetFileName("/home/userx/ndnSIM/experiment01/topologies/topo2.txt");
  topologyReader.Read();

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  
  // CS Policies
	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Nocache");
	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Random", "MaxSize", "100");
	ndnHelper.SetOldContentStore("ns3::ndn::cs::Freshness::Random", "MaxSize", "100");
	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Probability::Random", "MaxSize", "100");
	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Stats::Random","MaxSize",  "100");
	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Lfu", "MaxSize", "100");
  //ndnHelper.SetOldContentStore("ns3::ndn::cs::Fifo", "MaxSize", "100");
  //ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru");
	//ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru", "MaxSize", "100");
	ndnHelper.InstallAll();
  topologyReader.ApplyOspfMetric();                                            

  // Getting containers for multiple consumers and producers
  Ptr<Node> consumer1 = Names::Find<Node>("C1");
  Ptr<Node> producer1 = Names::Find<Node>("P1"); 
  // Getting containers for controller
  Ptr<Node> controller = Names::Find<Node>("R0");

  // Available forwarding strategy
	//ndn::StrategyChoiceHelper::InstallAll("/edu.bit.cn/", "/localhost/nfd/strategy/best-route");
  // Custom Forwarding Strategy
  ndn::StrategyChoiceHelper::Install<nfd_fw::ControllerStrategy>(Names::Find<Node>("R0"), "/edu.bit.cn/");       

  // Install NDN applications

  // Installing applications for Consumer 
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
  consumerHelper.SetAttribute("Frequency", StringValue("1")); // 1 interests a second  
  // Installing applications for the consumer-1
  consumerHelper.SetPrefix("/edu.bit.cn/");   //We are defining "Content Prefix" 
  ApplicationContainer app1 = consumerHelper.Install(consumer1);
  
  // Initialization of Controller Application
  ndn::AppHelper app("ControllerApp");
  ApplicationContainer app2 = app.Install(controller);

  // Installing applications for Producer
  ndn::AppHelper producerHelper("ns3::ndn::Producer");
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));  
  // Installing applications for the producer-1
  producerHelper.SetPrefix("/edu.bit.cn/");
  ApplicationContainer app3 = producerHelper.Install(producer1);
  

  // Manual Routing 
  ndn::FibHelper::AddRoute("C1", "/edu.bit.cn/", "R1", 0);
  ndn::FibHelper::AddRoute("R1", "/edu.bit.cn/", "R0", 0);
  ndn::FibHelper::AddRoute("R0", "/edu.bit.cn/", "R2", 0);
  ndn::FibHelper::AddRoute("R1", "/edu.bit.cn/", "R2", 0);
  ndn::FibHelper::AddRoute("R2", "/edu.bit.cn/", "P1", 0);

  ndn::FibHelper::AddRoute("C1", "/edu.bit.cn/", "R3", 0);
  ndn::FibHelper::AddRoute("R3", "/edu.bit.cn/", "R0", 0);
  ndn::FibHelper::AddRoute("R0", "/edu.bit.cn/", "R4", 0);
  ndn::FibHelper::AddRoute("R3", "/edu.bit.cn/", "R4", 0);
  ndn::FibHelper::AddRoute("R4", "/edu.bit.cn/", "P1", 0);

  ndn::FibHelper::AddRoute("C1", "/edu.bit.cn/", "R5", 0);
  ndn::FibHelper::AddRoute("R5", "/edu.bit.cn/", "R0", 0);
  ndn::FibHelper::AddRoute("R0", "/edu.bit.cn/", "R6", 0);
  ndn::FibHelper::AddRoute("R5", "/edu.bit.cn/", "R6", 0);
  ndn::FibHelper::AddRoute("R6", "/edu.bit.cn/", "P1", 0);
  
  // Trace Results as Txt File
  //ndn::CsTracer::InstallAll("/home/usery/ndnSIM/my-simulations/results/ndn_Cs_tracer.txt", Seconds(1.0));
  //ndn::L3RateTracer::InstallAll("/home/usery/ndnSIM/my-simulations/results/ndn_L3_rate_trace.txt", Seconds(1.0));
  //ndn::AppDelayTracer::InstallAll("/home/usery/ndnSIM/my-simulations/results/ndn_app_delays_trace.txt");
  //L2RateTracer::InstallAll("/home/usery/ndnSIM/my-simulations/results/ndn_l2_drop_trace.txt", Seconds(1.0));
 
  // Define Time-length For Application
	//app1.Start(Seconds (10.0));
  //app2.Start(Seconds (20.0));
  
  // Schedule simulation time and run the simulation
  Simulator::Stop(Seconds(30.0));

  //Simulator::Schedule(Seconds(5.0), ndn::LinkControlHelper::FailLinkByName, "R1", "R2");
  //Simulator::Schedule(Seconds(15.0), ndn::LinkControlHelper::UpLinkByName, "R1", "R2");

  Simulator::Run();
  Simulator::Destroy();

  return 0;
  }

  } // namespace ns3

  int
  main(int argc, char* argv[])
  {
  return ns3::main(argc, argv);
  }
