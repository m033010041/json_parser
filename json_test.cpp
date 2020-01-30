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
    ptree node;     //pt child node
    std::string unused, line;
    struct wifi_info winfo;

    scan_data.open("wifiscanresult.txt");

    if(!scan_data.eof())
        std::getline(scan_data, unused);  // get first line(unused)
    else
        return 0;


    while(std::getline(scan_data, line)){
        if(!scan_data.eof())
        {
            std::cout << line << std::endl;
            std::istringstream iss(line);

            iss >> winfo.bssid;
            iss >> winfo.frequency;
            iss >> winfo.signal_level;
            iss >> winfo.security;

            /* get ssid (include 0x20 character) */

            while((iss >> unused))
            {
                winfo.ssid.append(unused);
                winfo.ssid.append(" ");
            }

            if(winfo.ssid.size() > 0)
                winfo.ssid.erase(winfo.ssid.size()-1);


            node.put("frequency", winfo.frequency);
            node.put("signal level", winfo.signal_level);
            node.put("security", winfo.security);
            node.put("ssid", winfo.ssid);
            pt.add_child(winfo.bssid.c_str(), node);

            /* clean string */
            winfo.ssid.clear();
        }
    }

    outbuf.clear();
    write_json(outbuf, pt, false);

    outstr.clear();
    strbuf.clear();


    strbuf = outbuf.str();

    outstr.assign(reinterpret_cast<const char*>(strbuf.c_str()));

    fprintf(stdout, "%s\n",  outstr.c_str());

	return 0;
}
