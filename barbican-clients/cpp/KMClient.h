/*
 * KMClient.h
 *
 *  Created on: Nov 31, 2016
 *      Author: djarenho
 */

#ifndef BARBICAN_CLIENTS_CPP_KMCLIENT_H_
#define BARBICAN_CLIENTS_CPP_KMCLIENT_H_

#include <string>
#include "Poco/URI.h"
#include "SecretService.h"

using namespace std;
using namespace Poco;



class KMClient {
public:
	SecretService	 *secretService;
//	ContainerService *containerService;
//	OrderService 	 *orderService;

	KMClient(URI endpoint, string xAuthToken, string xProjectId);
	virtual ~KMClient();


//	SecretService* getSecrets() {
//		return secretService;
//	}
//	ContainerService getContainers() {
//		return containerService;
//	}
//
//	OrderService getOrders() {
//		return orderService;
//	}

};

#endif /* BARBICAN_CLIENTS_CPP_KMCLIENT_H_ */
