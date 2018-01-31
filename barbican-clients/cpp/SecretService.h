/*
 * SecretService.h
 *
 *  Created on: Nov 31, 2016
 *      Author: djarenho
 */

#ifndef BARBICAN_CLIENTS_CPP_SECRETSERVICE_H_
#define BARBICAN_CLIENTS_CPP_SECRETSERVICE_H_

#include <map>
#include "Poco/URI.h"

using namespace std;
using namespace Poco;

class Secret;

class SecretService {
	URI endpoint;
	string authToken = "";
	string projectId = "nullProject";

	map<string, Secret> secretsPool;

	string get_uuid( string ref );
	string encodeKey_to_base64str ( vector<unsigned char> key );
	vector<unsigned char> decodeBase64str_to_key ( string payload );


public:
	SecretService(URI url, string xAuthToken, string xProjectId);
	virtual ~SecretService();

	void	list();
	Secret	get(string name);
	Secret 	get_payload(string name);
	void	store(Secret& secret);
	void	delete_secret(string uuid);
};

#endif /* BARBICAN_CLIENTS_CPP_SECRETSERVICE_H_ */
