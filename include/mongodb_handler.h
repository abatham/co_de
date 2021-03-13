#pragma once 

#include <cstdint>
#include <string>

#include "bsoncxx/builder/stream/document.hpp"
#include "bsoncxx/json.hpp"
#include "bsoncxx/oid.hpp"
#include "mongocxx/client.hpp"
#include "mongocxx/database.hpp"
#include "mongocxx/uri.hpp"

#include "character_size.h"


namespace local{
    // const std::string kMongoURI = "mongodb+srv::/0.0.0.0:27017";
    const std::string kMongoURI = "mongodb+srv::/localhost:27017";
    const std::string kMongoDB = "test";
    const std::string kMongoCollection = "MarioKartCharacters";

    class MongoDbHandler{
        public:
        //Ctor
        MongoDbHandler()
            //:uri(mongocxx::uri(kMongoURI)),
            :uri(mongocxx::uri::k_default_uri),
            client(mongocxx::client(uri)),
            db(client[kMongoDB])
            {}

        bool AddCharacterToDB(const std::string& char_name, const std::string& size, const int16_t& winCount)
        {
            mongocxx::collection collection = db[kMongoCollection];
            auto builder = bsoncxx::builder::stream::document{};

            bsoncxx::document::value docToAdd = builder << "characterName" << char_name 
                                                        << "size" << size 
                                                        << "wins" << winCount << bsoncxx::builder::stream::finalize;
            
            collection.insert_one(docToAdd.view());
            return true;
        }
        bool UpdateWins(const std::string& char_id){
            mongocxx::collection collection = db[kMongoCollection];
            auto builder = bsoncxx::builder::stream::document{};

            bsoncxx::oid docId(char_id);
            bsoncxx::document::value queryDoc = builder << "_id" << docId << bsoncxx::builder::stream::finalize;

            bsoncxx::document::value updateDoc = builder << "$inc" << bsoncxx::builder::stream::open_document
                                                                    << "wins" << 1 << bsoncxx::builder::stream::close_document
                                                                    << bsoncxx::builder::stream::finalize ;
            
            bsoncxx::stdx::optional<mongocxx::result::update> queryRes = collection.update_one(queryDoc.view(), updateDoc.view());

            if (queryRes)
            {
                return queryRes->modified_count() != 0;
            }
            return false;
        }
        bool RemoveCharacterFromDB(const std::string& char_id){
            mongocxx::collection collection = db[kMongoCollection];
            auto builder = bsoncxx::builder::stream::document{};
            bsoncxx::oid docId(char_id);

            bsoncxx::document::value remDoc = builder << "_id" << docId << bsoncxx::builder::stream::finalize;

            bsoncxx::stdx::optional<mongocxx::result::delete_result> queryRes = collection.delete_one(remDoc.view());

            if (queryRes)
            {
                return queryRes->deleted_count() != 0;
            }
            return false;
        }
        private:
        mongocxx::uri uri;
        mongocxx::client client;
        mongocxx::database db;
    };
}