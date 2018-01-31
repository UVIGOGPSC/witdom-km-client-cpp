/*
 * Secret.h
 *
 *  Created on: Dec 1, 2016
 *      Author: djarenho
 */

#ifndef BARBICAN_CLIENTS_CPP_SECRET_H_
#define BARBICAN_CLIENTS_CPP_SECRET_H_

#include <string>

#include <Poco/JSON/Object.h>

using namespace std;
//using namespace Poco;


class Secret {

	string secRef = "secRef";
	string secType = "opaque";
	string name = "name";
	string created = "created";
	string updated = "updated";
	string status = "status";
	string expiration = "";
	string algorithm = "algorithm";
	int bitLength = 0;
	string mode = "mode";
	string payload = "payload";
	string payloadContentType = "text/plain";
	string payloadContentEncoding = "base64";
//	Map<string, string> contentTypes;
	string creatorId = "creatorId";
public:
	Secret();
	virtual ~Secret();

	Poco::JSON::Object jsonSecretBody();

    string toString();

	 string getRef() {
		return secRef;
	}

	 string getName() {
		return name;
	}

	 string getType() {
		return secType;
	}

	 string getCreated() {
		return created;
	}

	 string getStatus() {
		return status;
	}

	 string getExpiration() {
		return expiration;
	}

	 string getAlgorithm() {
		return algorithm;
	}

	 int getBitLength() {
		return bitLength;
	}

	 string getMode() {
		return mode;
	}

	 string getPayload() {
		return payload;
	}

	 string getPayloadContentType() {
		return payloadContentType;
	}

	 string getPayloadContentEncoding() {
		return payloadContentEncoding;
	}

	 void setRef(string ref1) {
		 secRef = ref1;
	}

	 void setName(string name1) {
		 name = name1;
	}

	 void setType(string type1) {
		 secType = type1;
	}

	 void setCreated(string created1) {
		 created = created1;
	}

	 void setStatus(string status1) {
		 status = status1;
	}

	 void setExpiration(string expiration1) {
		 expiration = expiration1;
	}

	 void setAlgorithm(string algorithm1) {
		 algorithm = algorithm1;
	}

	 void setBitLength(int bitLength1) {
		 bitLength = bitLength1;
	}

	 void setMode(string mode1) {
		 mode = mode1;
	}

	 void setPayload(string payload1) {
		 payload = payload1;
	}

	 void setPayloadContentType(string payloadContentType1) {
		 payloadContentType = payloadContentType1;
	}

	 void setPayloadContentEncoding(string payloadContentEncoding1) {
		 payloadContentEncoding = payloadContentEncoding1;
	}

};

#endif /* BARBICAN_CLIENTS_CPP_SECRET_H_ */
