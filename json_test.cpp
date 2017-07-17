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

std::string outstr;
std::string strbuf;
int main()
{
    ptree pt;
    outbuf.clear();

    pt.put("ssid", "D-LINK 300");
    pt.put("signal level", "-48");
    pt.put("security", "WPA-PSK-CCMP+TKIP");

    write_json(outbuf, pt, false);

    outstr.clear();
    strbuf.clear();

    strbuf = outbuf.str();

    outstr.assign(reinterpret_cast<const char*>(strbuf.c_str()));

    fprintf(stdout, "%s\n",  outstr.c_str());

	return 0;
}
