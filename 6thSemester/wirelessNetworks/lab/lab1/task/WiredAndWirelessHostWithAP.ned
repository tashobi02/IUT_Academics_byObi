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
    @display("bgb=1692,1053");
    submodules:
        visualizer: <default(firstAvailableOrEmpty("IntegratedCanvasVisualizer"))> like IIntegratedVisualizer if typename != "" {
            parameters:
                @display("p=154,306;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                assignDisjunctSubnetAddresses = false;
                @display("p=122,198;is=s");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
            parameters:
                @display("p=153,521;is=s");
        }
        wirelessHost1: WirelessHost {
            parameters:
                @display("p=121,97");
        }
        wiredHost1: StandardHost {
            parameters:
                @display("p=344,408");
        }
        wiredHost2: StandardHost {
            parameters:
                @display("p=856,572");
        }
        router: Router {
            parameters:
                @display("p=593,198");
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
