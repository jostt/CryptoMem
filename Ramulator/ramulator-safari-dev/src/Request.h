#ifndef __REQUEST_H
#define __REQUEST_H

#include <vector>
#include <functional>

using namespace std;

namespace ramulator
{

class Request
{
public:
    bool is_first_command;
    bool read = false;
    bool written = false;
    bool enc = false;
    long addr;
    long dest_addr;
    bool pre = false;
    bool row_mode = false;
    int col_counter = 0;
    bool done = false;
    bool once = false;
    bool first_time = true;
    bool completed = false;
    bool encryption_done = false;
    int encryption_counter = 0;
    int encryption_cycles = 85; //Hodjat 85
    bool entered = false;
    bool set_by_me = false;
    int counter = 0;
    
    //Link<HMC>* linkwr;
    // long addr_row;
    vector<int> addr_vec;
    vector<int> addr_vec2, addr_vec3, addr_vec4, addr_vec5, addr_vec6, addr_vec7, addr_vec0, intermediate;
    vector<int> row_addr0, row_addr1, row_addr2, row_addr3, row_addr4, row_addr5, row_addr6, row_addr7, row_intermediate;
    
    long reqid = -1;
    // specify which core this request sent from, for virtual address translation
    int coreid = -1;
    
    enum class Type
    {
        READ,
        WRITE,
        REFRESH,
        POWERDOWN,
        SELFREFRESH,
        EXTENSION,
        ENCRYPT,
        DECRYPT,
        ENCRYPTROW,
        DECRYPTROW,
        MAX
    } type;

    long arrive = -1;
    long depart;
    long arrive_hmc;
    long depart_hmc;

    int burst_count = 0;
    int transaction_bytes = 0;
    function<void(Request&)> callback; // call back with more info

    Request(long addr, Type type, int coreid)
        : is_first_command(true), addr(addr), coreid(coreid), type(type),
      callback([](Request& req){}) {}

    Request(long addr, Type type, function<void(Request&)> callback, int coreid)
        : is_first_command(true), addr(addr), coreid(coreid), type(type), callback(callback) {}
    
    Request(long addr, Type type, function<void(Request&)> callback, int coreid, long dest_addr)
        : is_first_command(true), addr(addr), dest_addr(dest_addr), coreid(coreid), type(type), callback(callback) {}

    Request(vector<int>& addr_vec, Type type, function<void(Request&)> callback, int coreid)
        : is_first_command(true), addr_vec(addr_vec), coreid(coreid), type(type), callback(callback) {}

    Request() {}

};

} /*namespace ramulator*/

#endif /*__REQUEST_H*/

