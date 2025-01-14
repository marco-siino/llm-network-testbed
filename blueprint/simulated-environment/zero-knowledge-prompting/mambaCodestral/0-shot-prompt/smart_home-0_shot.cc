To generate the NS3 code based on the given blueprint, you can follow these steps:

1. Create a new file with a .cc extension, for example, "smart_home.cc".
2. Open the file and write the following code:

```cpp
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"

using namespace ns3;

int main(int argc, char *argv[])
{
  // Create the nodes for each device
  NodeContainer nodes;
  nodes.Create(6);

  // Create the Wi-Fi module
  WifiHelper wifi;
  wifi.SetStandard(WIFI_PHY_STANDARD_80211a);
  wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager", "DataMode", StringValue("OfdmRate6MbpsBW10MHz"));

  // Create the Wi-Fi network
  YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
  YansWifiPhyHelper phy = YansWifiPhyHelper::Default();
  phy.SetChannel(channel.Create());

  // Add the Wi-Fi network to the nodes
  NetDeviceContainer devices;
  devices = wifi.Install(phy, nodes);

  // Assign IP addresses to the devices
  Ipv4AddressHelper address;
  address.SetBase("192.168.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces = address.Assign(devices);

  // Set up the routing module
  Ipv4GlobalRoutingHelper::PopulateRoutingTables();

  // Simulate the network
  Simulator::Stop(Seconds(10.0));
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}
```

This code creates a simple Wi-Fi network with 6 devices (Smart Home components), assigns IP addresses to them, and simulates the network for 10 seconds. You can customize the code further according to your specific requirements.

To compile and run the code, you'll need to have NS3 installed and set up on your system. Refer to the NS3 documentation for instructions on how to do this.