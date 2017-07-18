#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//#include <weintek/weintek-hal-wrapper.h>
//#include <weintek/machine.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

using boost::property_tree::ptree;

static std::ostringstream outbuf;
static std::ifstream scan_data;
std::string outstr;
std::string strbuf;


struct wifi_info {
    std::string bssid;
    int frequency;
    int signal_level;
    std::string security;
    std::string ssid;
};

int main()
{
    ptree pt;
    ptree bssid;    //create bssid object
    ptree node;     //bssid node
    std::string unused, line;

    scan_data.open("wifi_scan_result.txt");

    std::getline(scan_data, unused);  // get first line(unused)

    std::getline(scan_data, line);

    if(!line.empty())
    {
        std::istringstream iss(line);
        parse_wifi_info(iss, wifi_info)
    }

    outbuf.clear();


    node.put("ssid", "D-LINK 300");
    node.put("signal level", "-48");
    node.put("security", "WPA-PSK-CCMP+TKIP");

    //add_child("node_name", ptree);
    pt.add_child("00:0c:26:11:22:23", node);

    node.put("ssid", "coldnew EDIMAX4");
    node.put("signal level", "-50");
    node.put("security", "WPA-PSK2-CCMP+TKIP");

    //add_child("node_name", ptree);
    pt.add_child("00:0c:26:77:88:99", node);



    write_json(outbuf, pt, false);

    outstr.clear();
    strbuf.clear();


    strbuf = outbuf.str();

    outstr.assign(reinterpret_cast<const char*>(strbuf.c_str()));

    fprintf(stdout, "%s\n",  outstr.c_str());

	return 0;
}
