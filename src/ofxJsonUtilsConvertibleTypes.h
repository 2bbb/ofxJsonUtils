//
//  ofxJsonUtilsConvertibleTypes.h
//  ofxJsonUtilsFix
//
//  Created by 2bit on 2019/11/30.
//

#ifndef ofxJsonUtilsConvertibleTypes_h
#define ofxJsonUtilsConvertibleTypes_h

#include "../libs/bbb/json/utils/common.hpp"
#include "ofConstants.h"
#include "ofParameter.h"

#pragma mark BSON

inline std::vector<std::uint8_t> ofxLoadBinary(const std::filesystem::path &filename) {
    ofFile file{filename};
    if(file.exists()) {
        std::vector<uint8_t> binary{std::istream_iterator<std::uint8_t>(file), std::istream_iterator<std::uint8_t>()};
        return binary;
    } else {
        ofLogError("ofxLoadBinary") << "Error loading binary from " << filename.string() << ": file doesn't exist";
        return {};
    }
}

template <typename type>
inline bool ofxWriteVectorToFile(const std::vector<type> &vec, ofFile &file) {
    file.write((char *)&vec[0], vec.size());
}

inline ofJson ofxParseBson(const std::vector<std::uint8_t> &bson)
{
    ofJson json;
    try {
        json = ofJson::from_bson(bson);
    } catch(std::exception &e) {
        ofLogError("ofxParseBson") << "Error can't parse bson to json: " << e.what();
    } catch(...) {
        ofLogError("ofxParseBson") << "Error can't parse bson to json";
    }
    return json;
}

inline ofJson ofxLoadBson(const std::filesystem::path& filename) {
    return ofxParseBson(ofxLoadBinary(filename));
}

inline std::vector<std::uint8_t> ofxConvertToBson(const ofJson &json) {
    std::vector<std::uint8_t> bson;
    try {
        bson = ofJson::to_bson(json);
    } catch(std::exception &e) {
       ofLogError("ofxConvertToBson") << "Error can't parse bson from json: " << e.what();
    } catch(...) {
       ofLogError("ofxConvertToBson") << "Error can't parse bson from json";
    }
    return bson;
}

inline bool ofxSaveJsonAsBson(const std::filesystem::path& filename, const ofJson & json){
    ofFile bsonFile(filename, ofFile::WriteOnly);
    try {
        auto &&bson = ofxConvertToBson(json);
        ofxWriteVectorToFile(bson, bsonFile);
    } catch(std::exception & e) {
        ofLogError("ofxSaveJsonAsBson") << "Error saving json as bson to " << filename.string() << ": " << e.what();
        return false;
    } catch(...) {
        ofLogError("ofxSaveJsonAsBson") << "Error saving json as bson to " << filename.string();
        return false;
    }
    return true;
}

#pragma mark CBOR

inline ofJson ofxParseCbor(const std::vector<std::uint8_t> &cbor)
{
    ofJson json;
    try {
        json = ofJson::from_cbor(cbor);
    } catch(std::exception &e) {
        ofLogError("ofxParseCbor") << "Error can't parse cbor to json: " << e.what();
    } catch(...) {
        ofLogError("ofxParseCbor") << "Error can't parse cbor to json";
    }
    return json;
}

inline ofJson ofxLoadCbor(const std::filesystem::path& filename) {
    return ofxParseCbor(ofxLoadBinary(filename));
}

inline std::vector<std::uint8_t> ofxConvertToCbor(const ofJson &json) {
    std::vector<std::uint8_t> bson;
    try {
        bson = ofJson::to_cbor(json);
    } catch(std::exception &e) {
       ofLogError("ofxConvertToCbor") << "Error can't parse cbor from json: " << e.what();
    } catch(...) {
       ofLogError("ofxConvertToCbor") << "Error can't parse cbor from json";
    }
    return bson;
}

inline bool ofxSaveJsonAsCbor(const std::filesystem::path& filename, const ofJson & json){
    ofFile cborFile(filename, ofFile::WriteOnly);
    try {
        auto &&cbor = ofxConvertToCbor(json);
        ofxWriteVectorToFile(cbor, cborFile);
    } catch(std::exception & e) {
        ofLogError("ofxSaveJsonAsCbor") << "Error saving json as cbor to " << filename.string() << ": " << e.what();
        return false;
    } catch(...) {
        ofLogError("ofxSaveJsonAsCbor") << "Error saving json as cbor to " << filename.string();
        return false;
    }
    return true;
}

#pragma mark MessagePack

inline ofJson ofxParseMessagePack(const std::vector<std::uint8_t> &cbor)
{
    ofJson json;
    try {
        json = ofJson::from_msgpack(cbor);
    } catch(std::exception &e) {
        ofLogError("ofxParseMessagePack") << "Error can't parse msgpack to json: " << e.what();
    } catch(...) {
        ofLogError("ofxParseMessagePack") << "Error can't parse msgpack to json";
    }
    return json;
}

inline ofJson ofxLoadMessagePack(const std::filesystem::path& filename) {
    return ofxParseMessagePack(ofxLoadBinary(filename));
}

inline std::vector<std::uint8_t> ofxConvertToMessagePack(const ofJson &json) {
    std::vector<std::uint8_t> bson;
    try {
        bson = ofJson::to_msgpack(json);
    } catch(std::exception &e) {
       ofLogError("ofxConvertToMessagePack") << "Error can't parse msgpack from json: " << e.what();
    } catch(...) {
       ofLogError("ofxConvertToMessagePack") << "Error can't parse msgpack from json";
    }
    return bson;
}

inline bool ofxSaveJsonAsMessagePack(const std::filesystem::path& filename, const ofJson & json){
    ofFile msgpackFile(filename, ofFile::WriteOnly);
    try {
        auto &&msgpack = ofxConvertToMessagePack(json);
        ofxWriteVectorToFile(msgpack, msgpackFile);
    } catch(std::exception & e) {
        ofLogError("ofxSaveJsonAsMessagePack") << "Error saving json as msgpack to " << filename.string() << ": " << e.what();
        return false;
    } catch(...) {
        ofLogError("ofxSaveJsonAsMessagePack") << "Error saving json as msgpack to " << filename.string();
        return false;
    }
    return true;
}

#pragma mark UBJSON

inline ofJson ofxParseUBJson(const std::vector<std::uint8_t> &cbor)
{
    ofJson json;
    try {
        json = ofJson::from_ubjson(cbor);
    } catch(std::exception &e) {
        ofLogError("ofxParseUBJson") << "Error can't parse ubjson to json: " << e.what();
    } catch(...) {
        ofLogError("ofxParseUBJson") << "Error can't parse ubjson to json";
    }
    return json;
}

inline ofJson ofxLoadUBJson(const std::filesystem::path& filename) {
    return ofxParseMessagePack(ofxLoadBinary(filename));
}

inline std::vector<std::uint8_t> ofxConvertToUBJson(const ofJson &json) {
    std::vector<std::uint8_t> bson;
    try {
        bson = ofJson::to_ubjson(json);
    } catch(std::exception &e) {
       ofLogError("ofxConvertToUBJson") << "Error can't parse ubjson from json: " << e.what();
    } catch(...) {
       ofLogError("ofxConvertToUBJson") << "Error can't parse ubjson from json";
    }
    return bson;
}

inline bool ofxSaveJsonAsUBJson(const std::filesystem::path& filename, const ofJson & json){
    ofFile ubjsonFile(filename, ofFile::WriteOnly);
    try {
        auto &&ubjson = ofxConvertToUBJson(json);
        ofxWriteVectorToFile(ubjson, ubjsonFile);
    } catch(std::exception & e) {
        ofLogError("ofxSaveJsonAsUBJson") << "Error saving json as ubjson to " << filename.string() << ": " << e.what();
        return false;
    } catch(...) {
        ofLogError("ofxSaveJsonAsUBJson") << "Error saving json as ubjson to " << filename.string();
        return false;
    }
    return true;
}

#endif /* ofxJsonUtilsConvertibleTypes_h */
