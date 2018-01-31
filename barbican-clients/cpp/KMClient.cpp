/*
 * KMClient.cpp
 *
 *  Created on: Nov 31, 2016
 *      Author: djarenho
 */

#include "KMClient.h"

#include "SecretService.h"

using namespace std;
using namespace Poco;

KMClient::KMClient(URI endpoint, string xAuthToken, string xProjectId) {

	secretService = new SecretService(endpoint, xAuthToken, xProjectId);
//	containerService = new ContainerService(endpoint, xAuthToken, xProjectId);
//	orderService = new OrderService(endpoint, xAuthToken, xProjectId);
}

KMClient::~KMClient() {
	// TODO Auto-generated destructor stub
}

