Here is the corresponding NS3 code for the given blueprint:
```
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/wifi-spectrum-value-helper.h"
#include "ns3/spectrum-module.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/on-off-helper.h"
#include "ns3/inet-socket-address.h"
#include "ns3/packet-sink-helper.h"
#include "ns3/ssid.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/ipv4-address-helper.h"

using namespace ns3;

int main (int argc, char *argv[])
{
  // Set up the Wi-Fi standard
  WifiHelper wifi;
  wifi.SetStandard(WIFI_STANDARD_80211a);

  // Declare YansWifiChannelHelper with "wifichannel", to avoid conflict in the code variables
  YansWifiChannelHelper wifiChannel;
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default();
  wifiPhy.SetChannel(wifiChannel.Create());

  // Initialize YansWifiPhyHelper using "YansWifiPhyHelper::Default()"
  YansWifiChannelHelper wifiChannelHelper;
  wifiPhy.SetChannel(wifiChannelHelper.Create());

  // Set up mobility for Wi-Fi nodes
  MobilityHelper mobility;
  Ptr<ListPositionAllocator> allocatorAPWiFi = CreateObject<ListPositionAllocator>();
  allocatorAPWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5)); // position for AP-001
  allocatorAPWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5)); // position for SH-001
  allocatorAPWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5)); // position for ST-001
  mobility.SetPositionAllocator(allocatorAPWiFi);

  Ptr<ListPositionAllocator> allocatorStaWiFi = CreateObject<ListPositionAllocator>();
  allocatorStaWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5)); // position for SDL-001
  allocatorStaWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5)); // position for SSC-001
  allocatorStaWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5)); // position for SLB-001
  mobility.SetPositionAllocator(allocatorStaWiFi);

  mobility.Install();

  // Set up Wi-Fi nodes
  WifiHelper wifi;
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                "DataMode", StringValue ("OfdmRate6MbpsBw10MHz"));

  // Set up network devices for Wi-Fi nodes
  NetDeviceContainer wifiDevices;
  wifiDevices = wifi.Install(wifiPhy, wifi.GetRemoteStationManager(), wifiNodes);

  // Set up Internet stack for Wi-Fi nodes
  InternetStackHelper stack;
  stack.Install(wifiNodes);

  // Set up IP addresses for Wi-Fi nodes
  Ipv4AddressHelper address;
  address.SetBase("192.168.1.0", "255.255.255.0");
  address.Assign(wifiDevices);

  // Set up UDP flow for Wi-Fi nodes
  OnOffHelper onoff("ns3::UdpSocketFactory", Address());
  onoff.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1.0]"));
  onoff.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0.0]"));
  ApplicationContainer app = onoff.Install(wifiNodes.Get(0));

  // Set up packet sink for Wi-Fi nodes
  PacketSinkHelper packetSinkHelper("ns3::UdpSocketFactory", InetSocketAddress (wifiNodes.Get(1)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(), 9));
  app = packetSinkHelper.Install(wifiNodes.Get(1));

  // Run the simulation
  Simulator::Stop(Seconds(10.0));
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}
```