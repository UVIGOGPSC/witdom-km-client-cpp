/*
 * Secret.cpp
 *
 *  Created on: Dec 1, 2016
 *      Author: djarenho
 */

#include "Secret.h"

Secret::Secret() { }

Secret::~Secret() { }


Poco::JSON::Object Secret::jsonSecretBody() {

	Poco::JSON::Object secretBodyJson(true);

	secretBodyJson.set("name", name);
	secretBodyJson.set("expiration", expiration);
	secretBodyJson.set("algorithm", algorithm);
	secretBodyJson.set("bitLength", bitLength);
	secretBodyJson.set("mode", mode);
	secretBodyJson.set("payload", payload);
	secretBodyJson.set("payload_content_type", payloadContentType);
	secretBodyJson.set("payload_content_encoding", payloadContentEncoding);
	secretBodyJson.set("secret_type", secType);


	return secretBodyJson;
}


string Secret::toString() {
	string str = "name: " + name + "\r\n" +
        "secret_ref: " + secRef + "\r\n" +
        "secret_type: " + secType + "\r\n" +
        "created: " + created + "\r\n" +
        "updated: " + updated + "\r\n" +
        "status: " + status + "\r\n" +
        "expiration: " + expiration + "\r\n" +
        "algorithm: " + algorithm + "\r\n" +
        "bit_length: " + std::to_string(bitLength) + "\r\n" +
        "mode: " + mode + "\r\n" +
        "payload: " + payload + "\r\n" +
        "payload_content_type: " + payloadContentType + "\r\n" +
        "payload_content_encoding: " + payloadContentEncoding + "\r\n" +
//            "content_types: " + contentTypes + "\r\n" +
        "creator_id: " + creatorId;
    return str;
}
