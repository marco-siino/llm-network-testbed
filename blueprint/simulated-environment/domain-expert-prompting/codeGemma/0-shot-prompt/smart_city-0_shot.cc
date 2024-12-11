#include "ns3/yans-wifi-helper.h"
            #include "ns3/on-off-helper.h"
            #include "ns3/inet-socket-address.h"
            #include "ns3/packet-sink-helper.h"
            #include "ns3/ssid.h"
            #include "ns3/internet-stack-helper.h"
            #include "ns3/ipv4-address-helper.h"

            int main()
            {
                // Set up simulation parameters
                int numWifiNodes = 3;
                int numLoRaNodes = 2;
                double simulationTime = 10.0;

                // Create nodes
                NodeContainer wifiNodes;
                NodeContainer loRaNodes;
                for (int i = 0; i < numWifiNodes; i++)
                {
                    wifiNodes.Create();
                }
                for (int i = 0; i < numLoRaNodes; i++)
                {
                    loRaNodes.Create();
                }

                // Set up mobility for WiFi nodes
                Ptr<ListPositionAllocator> allocatorAPWiFi = CreateObject<ListPositionAllocator>();
                allocatorAPWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5));
                allocatorAPWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5));
                allocatorAPWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5));
                MobilityHelper mobility;
                mobility.SetPositionAllocator(allocatorAPWiFi);
                mobility.Install(wifiNodes);

                // Set up mobility for LoRa nodes
                Ptr<ListPositionAllocator> allocatorLoRa = CreateObject<ListPositionAllocator>();
                allocatorLoRa->Add(Vector(38.10863528672466, 13.34050633101243, 1.5));
                allocatorLoRa->Add(Vector(38.0998337384608, 13.337136092765382, 1.5));
                mobility.SetPositionAllocator(allocatorLoRa);
                mobility.Install(loRaNodes);

                // Set up LoRa
                // ...

                // Set up WiFi
                // ...

                // Set up traffic
                // ...

                // Run simulation
                Simulator::Stop(Seconds(simulationTime));
                Simulator::Run();

                return 0;
            }<eos>