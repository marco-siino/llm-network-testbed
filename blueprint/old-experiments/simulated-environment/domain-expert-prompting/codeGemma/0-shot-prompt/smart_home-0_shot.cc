#include "ns3/yans-wifi-helper.h"
            #include "ns3/on-off-helper.h"
            #include "ns3/inet-socket-address.h"
            #include "ns3/packet-sink-helper.h"
            #include "ns3/ssid.h"
            #include "ns3/internet-stack-helper.h"
            #include "ns3/ipv4-address-helper.h"

            int main()
            {
                // Set up the simulation
                NS_LOG_INFO("Starting simulation...");
                
                // Set up the network
                // Create the nodes
                Ptr<Node> sh = CreateObject<Node>();
                Ptr<Node> ap = CreateObject<Node>();
                Ptr<Node> st = CreateObject<Node>();
                Ptr<Node> slb = CreateObject<Node>();
                Ptr<Node> sdl = CreateObject<Node>();
                Ptr<Node> ssc = CreateObject<Node>();
                
                // Set the node names
                sh->SetName("SH-001");
                ap->SetName("AP-001");
                st->SetName("ST-001");
                slb->SetName("SLB-001");
                sdl->SetName("SDL-001");
                ssc->SetName("SSC-001");
                
                // Set the node positions
                Ptr<ListPositionAllocator> allocatorAPWiFi = CreateObject<ListPositionAllocator>();    
                allocatorAPWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5));
                mobility.SetPositionAllocator(allocatorAPWiFi); 
                
                Ptr<ListPositionAllocator> allocatorStaWiFi = CreateObject<ListPositionAllocator>();    
                allocatorStaWiFi->Add(Vector(38.10351066811096, 13.3459399220741, 1.5));
                mobility.SetPositionAllocator(allocatorStaWiFi); 
                
                mobility.Install(wifiNodes);
                
                // Set up the network interfaces
                // Set up the internet stack
                InternetStackHelper internetStackHelper;
                internetStackHelper.Install(sh);
                internetStackHelper.Install(ap);
                internetStackHelper.Install(st);
                internetStackHelper.Install(slb);
                internetStackHelper.Install(sdl);
                internetStackHelper.Install(ssc);
                
                // Set up the IP addresses
                Ipv4AddressHelper addressHelper;
                addressHelper.SetBase("192.168.1.0", "255.255.255.0");
                addressHelper.Assign(sh->GetObject<Ipv4Interface>());
                addressHelper.Assign(ap->GetObject<Ipv4Interface>());
                addressHelper.Assign(st->GetObject<Ipv4Interface>());
                addressHelper.Assign(slb->GetObject<Ipv4Interface>());
                addressHelper.Assign(sdl->GetObject<Ipv4Interface>());
                addressHelper.Assign(ssc->GetObject<Ipv4Interface>());
                
                // Set up the Wi-Fi
                // Set the Wi-Fi standard
                wifi.SetStandard(WIFI_STANDARD_80211a);
                
                // Set up the Wi-Fi channel
                YansWifiChannelHelper wifiChannelHelper = YansWifiChannelHelper::Default();
                Ptr<YansWifiChannel> channel = wifiChannelHelper.Create();
                wifi.SetChannel(channel);
                
                // Set up the Wi-Fi phy
                YansWifiPhyHelper wifiPhyHelper = YansWifiPhyHelper::Default();
                Ptr<YansWifiPhy> phy = wifiPhyHelper.Create();
                wifi.SetPhy(phy);
                
                // Set up the Wi-Fi mac
                YansWifiMacHelper wifiMacHelper = YansWifiMacHelper::Default();
                Ptr<YansWifiMac> mac = wifiMacHelper.Create();
                wifi.SetMac(mac);
                
                // Set up the Wi-Fi ssid
                WifiSsid ssid = WifiSsid("SmartHome");
                mac->SetAttribute("Ssid", ssid);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice>();
                wifiNetDevice->SetAttribute("Phy", phy);
                wifiNetDevice->SetAttribute("Mac", mac);
                wifiNetDevice->SetAttribute("Mode", StringValue("g"));
                wifiNetDevice->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi stack
                WifiStackHelper wifiStackHelper = WifiStackHelper::Default();
                wifiStackHelper.Install(wifiNode);
                
                // Set up the Wi-Fi node
                Ptr<WifiNode> wifiNode = CreateObject<WifiNode>();
                wifiNode->SetAttribute("Mode", StringValue("g"));
                wifiNode->SetAttribute("Channel", UintegerValue(1));
                
                // Set up the Wi-Fi interface
                Ptr<WifiNetDevice> wifiNetDevice = CreateObject<WifiNetDevice