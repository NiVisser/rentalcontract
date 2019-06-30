#include <eosiolib/eosio.hpp>
#include <string> 
#include <vector>
#include <unordered_map>


using namespace std;
using namespace eosio;
class [[eosio::contract]] rentcontract : public eosio::contract {

  private:

    struct [[eosio::table]] room_info {
      uint64_t              id;
      name                  username;
      uint64_t              floorlevel;
      double                breedtegraad; //= 53.24182501922634;
      double                lengtegraad; //= 6.533235624642657;
      
      auto primary_key() const { return id ;}
    };
    typedef eosio::multi_index<name("rooms"), room_info> rooms_table;
    rooms_table finalrooms;
    
    
    struct [[eosio::table]] room_record {
      uint64_t              id;
      uint64_t              roomnameid;
      name                  username;
      uint64_t              fromdate; //= 1558013816;
      uint64_t              todate; //= 1558137600;

      auto primary_key() const { return id ;}
    };
    typedef eosio::multi_index<name("records"), room_record> records_table;
    records_table finalrecords;

  public:

    rentcontract( name receiver, name code, datastream<const char*> ds ):contract(receiver, code, ds), finalrooms(receiver, receiver.value), finalrecords(receiver, receiver.value){}

    [[eosio::action]]
    void addroom(uint64_t _floorlevel, name username, double  _breedtegraad, double _lengtegraad);
    [[eosio::action]]
    void rentroom(uint64_t _roomnameid, name username, uint64_t _fromdate, uint64_t _todate);
    [[eosio::action]]
    void checkowner(uint64_t _roomnameid, name username, uint64_t _time);
    [[eosio::action]]
    void removeroom(uint64_t _roomnameid);
    [[eosio::action]]
    void removerecord(uint64_t _roomnameid);
};