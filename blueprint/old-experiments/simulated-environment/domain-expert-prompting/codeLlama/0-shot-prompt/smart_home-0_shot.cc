#include "ns3/core-module.h"
            #include "ns3/network-module.h"
            #include "ns3/internet-module.h"
            #include "ns3/point-to-point-module.h"
            #include "ns3/applications-module.h"
            #include "ns3/wifi-module.h"
            #include "ns3/mobility-module.h"
            #include "ns3/yans-wifi-helper.h"
            #include "ns3/on-off-helper.h"
            #include "ns3/inet-socket-address.h"
            #include "ns3/packet-sink-helper.h"
            #include "ns3/ssid.h"
            #include "ns3/internet-stack-helper.h"
            #include "ns3/ipv4-address-helper.h"

            using namespace ns3;

            int main(int argc, char *argv[]) {

                // Set up the nodes
                NodeContainer wifiNodes;
                wifiNodes.Create(3);

                // Set up the mobility for WiFi nodes
                Ptr<ListPositionAllocator> allocatorAPWiFi = CreateObject<ListPositionAllocator>();
                allocatorAPWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5));
                allocatorAPWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5));
                allocatorAPWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5));
                MobilityHelper mobility;
                mobility.SetPositionAllocator(allocatorAPWiFi);
                mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
                mobility.Install(wifiNodes);

                // Set up the mobility for WiFi nodes
                Ptr<ListPositionAllocator> allocatorStaWiFi = CreateObject<ListPositionAllocator>();
                allocatorStaWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5));
                allocatorStaWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5));
                allocatorStaWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5));
                mobility.SetPositionAllocator(allocatorStaWiFi);
                mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
                mobility.Install(wifiNodes);

                // Set up the YansWifiChannelHelper
                YansWifiChannelHelper wifiChannel;
                wifiChannel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
                wifiChannel.SetPropagationLoss("ns3::FriisPropagationLossModel");

                // Set up the YansWifiPhyHelper
                YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default();
                wifiPhy.SetPcapDataLinkType(YansWifiPhyHelper::DLT_IEEE802_11_RADIO);

                // Set up the wifi MAC
                WifiMacHelper wifiMac;
                wifiMac.SetType("ns3::StaWifiMac",
                                "Ssid", SsidValue(ssid),
                                "ActiveProbing", BooleanValue(false));

                // Set up the wifi channel
                wifiPhy.SetChannel(wifiChannel.Create());

                // Add the station and the AP to the wifi MAC
                NetDeviceContainer staDevices;
                staDevices = wifi.Install(wifiPhy, wifiMac, wifiNodes);

                // Set up the IP addresses for the AP and the stations
                Ipv4AddressHelper ipv4;
                ipv4.SetBase("192.168.1.0", "255.255.255.0");
                Ipv4InterfaceContainer staInterface;
                staInterface = ipv4.Assign(staDevices);

                // Set up the applications
                UdpServerHelper server(9);
                ApplicationContainer serverApps = server.Install(wifiNodes.Get(1));
                serverApps.Start(Seconds(1.0));
                serverApps.Stop(Seconds(10.0));

                UdpClientHelper client(staInterface.GetAddress(1), 9);
                client.SetAttribute("MaxPackets", UintegerValue(1000000));
                client.SetAttribute("Interval", TimeValue(Seconds(1.0)));
                client.SetAttribute("PacketSize", UintegerValue(1024));

                ApplicationContainer clientApps = client.Install(wifiNodes.Get(0));
                clientApps.Start(Seconds(2.0));
                clientApps.Stop(Seconds(10.0));

                // Set up the tracker for the UDP flow
                AsciiTraceHelper ascii;
                Ptr<TrafficTraceHelper> traceHelper = ascii.CreateInterceptor("ns3::UdpSocketFactory", "PacketSink");
                PacketSinkHelper packetSinkHelper("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), 9));
                ApplicationContainer sinkApps = packetSinkHelper.Install(wifiNodes.Get(2));
                sinkApps.Start(Seconds(0.0));
                sinkApps.Stop(Seconds(10.0));

                // Run the simulation
                Simulator::Stop(Seconds(10.0));
                Simulator::Run();
                Simulator::Destroy();

                return 0;
            }