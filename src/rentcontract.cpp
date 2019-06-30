#include "rentcontract.hpp"

//listing rooms for users to rent
void rentcontract::addroom(uint64_t _floorlevel, name username, double _breedtegraad, double _lengtegraad) {
  // Ensure this action is authorized by user
  require_auth(username);
  
    finalrooms.emplace(username,  [&](auto& new_room) {
        new_room.id = finalrooms.available_primary_key();
        new_room.username = username;
        new_room.floorlevel = _floorlevel;
        new_room.breedtegraad = _breedtegraad;
        new_room.lengtegraad = _lengtegraad;
    });
}

//function for users to rent rooms
void rentcontract::rentroom(uint64_t _roomnameid, name username, uint64_t _fromdate, uint64_t _todate) {
  // Ensure this action is authorized by user
  require_auth(username);
  
  for(auto& item : finalrooms) { 
    if (item.id == _roomnameid) {
        finalrecords.emplace(username,  [&](auto& rent_room) {
                    rent_room.id = finalrecords.available_primary_key();
                    rent_room.roomnameid = _roomnameid;
                    rent_room.username = username;
                    rent_room.fromdate = _fromdate;
                    rent_room.todate = _todate;
      });
    }
  }
}


//check ownership function
void rentcontract::checkowner(uint64_t _roomnameid, name username, uint64_t _time){
   // find where _time is =>fromdate && < todate
    //std::vector<uint64_t> markedId;
      for(auto& item : finalrecords) {
        if (item.roomnameid == _roomnameid && item.username == username && item.fromdate > _time && item.todate < _time) {
          eosio::print("Owner: true");
          //markedId.push_back(item.id);   
      }
      else {
          eosio::print("Owner: false");
      }
        
    }
    
}
//remove room from listing
void rentcontract::removeroom(uint64_t _roomnameid){
    require_auth(_self);
    std::vector<uint64_t> idForDeletion;
    // find items which are for the named room
    for(auto& item : finalrooms) {
        if (item.id == _roomnameid) {
            idForDeletion.push_back(item.id);   
        }
    }
    
    //  delete each row of roomname
    for (uint64_t id : idForDeletion) {
        auto itr = finalrooms.find(id);
        if (itr != finalrooms.end()) {
            finalrooms.erase(itr);
            eosio::print("Successfully deleted the room from the rooms table ... :)");
        }
    }
}
void rentcontract::removerecord(uint64_t _roomnameid){
require_auth(_self);
    std::vector<uint64_t> idForDeletion;
    // find items which are for the named room
    for(auto& item : finalrecords) {
        if (item.id == _roomnameid) {
            idForDeletion.push_back(item.id);   
        }
    }
    
    //  delete each row of roomname
    for (uint64_t id : idForDeletion) {
        auto itr = finalrecords.find(id);
        if (itr != finalrecords.end()) {
            finalrecords.erase(itr);
            eosio::print("Successfully deleted record from the records table... :)");
        }
    }
}

EOSIO_DISPATCH(rentcontract, (addroom)(rentroom)(checkowner)(removeroom)(removerecord))



