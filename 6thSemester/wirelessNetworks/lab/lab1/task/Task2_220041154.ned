//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package inet.examples.wireless.wiredandwirelesshostswithap;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.node.inet.WirelessHost;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;
import ned.IdealChannel;


network WiredAndWirelessHostsWithAP
{
    @display("bgb=2171,1304");
    submodules:
        visualizer: <default(firstAvailableOrEmpty("IntegratedCanvasVisualizer"))> like IIntegratedVisualizer if typename != "" {
            parameters:
                @display("p=170,952;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                assignDisjunctSubnetAddresses = false;
                @display("p=170,831;is=s");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
            parameters:
                @display("p=167,683;is=s");
        }
        wirelessHost1: WirelessHost {
            parameters:
                @display("p=816,45");
        }
        wirelessHost2: WirelessHost {
            parameters:
                @display("p=62,140");
        }
        wiredHost1: StandardHost {
            parameters:
                @display("p=324,411");
        }
        wiredHost2: StandardHost {
            parameters:
                @display("p=704,392");
        }
        router: Router {
            parameters:
                @display("p=545,208");
        }
        accessPoint: AccessPoint {
            parameters:
                @display("p=325,44");
        }
    connections:
        accessPoint.ethg++ <--> Eth100M <--> router.ethg++;
        wiredHost1.ethg++ <--> Eth100M <--> accessPoint.ethg++;
        wiredHost2.ethg++ <--> Eth100M <--> router.ethg++;
}
