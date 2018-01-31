/*
 * SecretService.cpp
 *
 *  Created on: Nov 31, 2016
 *      Author: djarenho
 */

#include "SecretService.h"

//#include <iostream>
//#include <fstream>

#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include <Poco/JSON/Parser.h>

#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"

#include "parser_utils.h"	// is_valid_string(Poco::Dynamic::Var)
#include "Secret.h"

using namespace std;
using namespace Poco;
using namespace Poco::Net;



SecretService::SecretService(URI url, string xAuthToken, string xProjectId) :
				endpoint(url), authToken(xAuthToken), projectId(xProjectId) { }

SecretService::~SecretService() { }



void SecretService::list() {

	HTTPClientSession session(endpoint.getHost(), endpoint.getPort());
//	HTTPSClientSession session(endpoint.getHost(), endpoint.getPort());
//	endpoint.setPath( endpoint.getHost() + ":" + std::to_string(endpoint.getPort()) );
	std::string method = HTTPRequest::HTTP_GET;

    // REQUEST
    HTTPRequest request(method, /*"http://" + endpoint.getPath() +*/ "/v1/secrets");
    request.setContentType("application/json");
	// Inject Token authToken
    request.add("Accept", "application/json");
    request.add("X-Project-Id", projectId);
    request.add("X-Auth-Token", authToken);

    std::ostream& o = session.sendRequest(request);
    Poco::JSON::Stringifier::stringify( "" , o );


    // RESPONSE
    HTTPResponse response;
    response.setStatus(Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);	// 503 as default (just in case)
    std::cout << "Waiting for Response.." << std::endl;
    std::istream& rs = session.receiveResponse(response);

    string jsonResponse;
    int inputsize = Poco::StreamCopier::copyToString( rs, jsonResponse);
    std::cout << "\tHTTP_CODE: " << response.getStatus() << std::endl;
    cout << "\tResponse body: " << jsonResponse << endl;		// print out response body

    // Parse response
    JSON::Parser loParser;
    loParser.parse( jsonResponse );
    Poco::DynamicAny loParsedJsonResult = loParser.result();
    Poco::JSON::Object::Ptr secretsListJson = loParsedJsonResult.extract<Poco::JSON::Object::Ptr>();

    string property = "total";
    Poco::Dynamic::Var evalVar = secretsListJson->get( property );
	if ( !is_valid_int(evalVar, property))
		return;

	int total = evalVar.convert<int>();


	property = "secrets";
	evalVar = secretsListJson->get( property );
	if ( !is_valid_arrayjson(evalVar, property))
		return;

	Poco::JSON::Array::Ptr arraySecretMetadata = evalVar.extract<Poco::JSON::Array::Ptr>();
	Poco::JSON::Object::Ptr secretMetadata;

	for (int i = 0; i<total; ++i) {

		try {
			secretMetadata = arraySecretMetadata->getObject(i);
//			secretMetadata = evalVar.extract<Poco::JSON::Object::Ptr>();
		} catch (Poco::InvalidAccessException & iae) {
			cout << "Failed getting 'SecretMetadata[" << i << "]': Empty item" << endl;
			continue;
		} catch (Poco::BadCastException & bce) {
			cout << "Failed getting 'SecretMetadata[" << i << "]': Invalid item" << endl;
			continue;
		}

		if( !is_SecretMetadata_objson(secretMetadata)) {
			cout << "Failed getting 'SecretMetadata[" << i << "]': Invalid parameters" << endl;
			continue;
		}
	}

	std::cout << "Secrets listed." << std::endl;
}


Secret SecretService::get(string uuid){

	HTTPClientSession session(endpoint.getHost(), endpoint.getPort());
	std::string method = HTTPRequest::HTTP_GET;

    // REQUEST
    HTTPRequest request(method, endpoint.getPath() + "/v1/secrets/" + uuid);
    request.setContentType("application/json");
	// Inject Token authToken
    request.add("Accept", "application/json");
    request.add("X-Project-Id", projectId);
    request.add("X-Auth-Token", authToken);

    std::ostream& o = session.sendRequest(request);
    Poco::JSON::Stringifier::stringify( "" , o );


    // RESPONSE
    HTTPResponse response;
    response.setStatus(Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);	// 503 as default (just in case)
    std::cout << "Waiting for Response.." << std::endl;
    std::istream& rs = session.receiveResponse(response);

    string jsonResponse;
    int inputsize = Poco::StreamCopier::copyToString( rs, jsonResponse);
    std::cout << "\tHTTP_CODE: " << response.getStatus() << std::endl;
    cout << "\tResponse body: " << jsonResponse << endl;		// print out response body

    // Parse response
    JSON::Parser loParser;
    loParser.parse( jsonResponse );
    Poco::DynamicAny loParsedJsonResult = loParser.result();
    Poco::Dynamic::Var evalVar = loParsedJsonResult.extract<Poco::JSON::Object::Ptr>();

    Secret sec;
    string property = "secretMetadata";
//    Poco::Dynamic::Var evalVar = secretMetadata->get( property );
	if ( !is_valid_objson(evalVar, property)) {
		sec.setStatus("INVALID");
		return sec;
	}

	Poco::JSON::Object::Ptr secretMetadata= evalVar.extract<Poco::JSON::Object::Ptr>();
	if( !is_SecretMetadata_objson( secretMetadata ) ) {
		cout << "Failed getting 'SecretMetadata': Invalid parameters" << endl;
		sec.setStatus("INVALID");
		return sec;
	}

	// Catch the metadata and wrap it into secret class...
//	sec = new secret(evalVar);
	// ... or rebuild it with 'getters'

	std::cout << "Secret '" << uuid << "' metadata retrieved." << std::endl;
	return sec;

}


// To be revised..
Secret SecretService::get_payload(string uuid){

	HTTPClientSession session(endpoint.getHost(), endpoint.getPort());
	std::string method = HTTPRequest::HTTP_GET;

    // REQUEST
    HTTPRequest request(method, endpoint.getPath() + "/v1/secrets/" + uuid + "/payload");
    request.setContentType("application/json");
	// Inject Token authToken
//    request.add("Accept", "application/json");
//    request.add("Accept", "text/plain");
    request.add("Accept", "application/octet-stream");
    request.add("X-Project-Id", projectId);
    request.add("X-Auth-Token", authToken);

    std::ostream& o = session.sendRequest(request);
    Poco::JSON::Stringifier::stringify( "" , o );

    // RESPONSE
    HTTPResponse response;
    response.setStatus(Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);	// 503 as default (just in case)
    std::cout << "Waiting for Response.." << std::endl;
    std::istream& rs = session.receiveResponse(response);

    string jsonResponse;
    int inputsize = Poco::StreamCopier::copyToString( rs, jsonResponse);
    std::cout << "\tHTTP_CODE: " << response.getStatus() << std::endl;
    cout << "\tResponse body: " << jsonResponse << endl;		// print out response body

    std::vector<unsigned char> cstr(jsonResponse.c_str(), jsonResponse.c_str() + jsonResponse.size() + 1);
    cout << "cstr.size() = " << cstr.size() << endl;
    cout << "result[1]: ";
    cout << to_string( cstr[18] ) << endl;

    // Parse response
    JSON::Parser loParser;
    loParser.parse( jsonResponse );
    Poco::DynamicAny loParsedJsonResult = loParser.result();
//    Poco::Dynamic::Var evalVar = loParsedJsonResult.extract<Poco::JSON::Object::Ptr>();
    Poco::Dynamic::Var evalVar = loParsedJsonResult.extract<char*>();

    cout << "result[1]: ";
    cout << evalVar.at(1) << endl;

    Secret sec;
    string property = "secretMetadata";
//    Poco::Dynamic::Var evalVar = secretMetadata->get( property );
	if ( !is_valid_objson(evalVar, property)) {
		sec.setStatus("INVALID");
		return sec;
	}

	Poco::JSON::Object::Ptr secretMetadata= evalVar.extract<Poco::JSON::Object::Ptr>();
	if( !is_SecretMetadata_objson( secretMetadata ) ) {
		cout << "Failed getting 'SecretMetadata': Invalid parameters" << endl;
		sec.setStatus("INVALID");
		return sec;
	}

	// Catch the payload to construct a secret class...
//	sec = new secret(payload);
	// ... or rebuild it with 'getters'

	return sec;

}



void SecretService::store(Secret& secret) {

	HTTPClientSession session(endpoint.getHost(), endpoint.getPort());
	std::string method = HTTPRequest::HTTP_POST;

	// Get the Json obj
	Poco::JSON::Object secObj = secret.jsonSecretBody();


    stringstream ss;
    secObj.stringify(ss);
//    StreamCopier::copyStream(ss, std::cout);
//    cout << "ss = " << ss << endl;

    // REQUEST
    HTTPRequest request(method, /*endpoint.getPath() +*/ "/v1/secrets");
    request.setContentType("application/json");
    request.setContentLength( ss.str().size());
	// Inject Token authToken
    request.add("Accept", "application/json");
    request.add("X-Project-Id", projectId);
    request.add("X-Auth-Token", authToken);

    std::ostream& o = session.sendRequest(request);
    Poco::JSON::Stringifier::stringify( secObj, o );
//    cout << "request.getURI(): " << request.getURI() << endl;


    // RESPONSE
    HTTPResponse response;
    response.setStatus(Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);	// 503 as default (just in case)
    cout << "Waiting for Response.." << endl;
    std::istream& rs = session.receiveResponse(response);

    string jsonResponse;
    int jsonsize = StreamCopier::copyToString( rs, jsonResponse);
    cout << "HTTP_CODE: " << response.getStatus() << endl;
    cout << "\tResponse body: " << jsonResponse << endl;		// print out response body



    // STORE LOCAL CACHE (store ref-secret pair at client)

    // Parse response
    JSON::Parser loParser;
    loParser.parse( jsonResponse );
    Poco::DynamicAny loParsedJsonResult = loParser.result();
    Poco::JSON::Object::Ptr secretResponseJson = loParsedJsonResult.extract<Poco::JSON::Object::Ptr>();

    string property = "secret_ref";
	Poco::Dynamic::Var evalVar = secretResponseJson->get( property );
	if ( !is_valid_string(evalVar, property))
		return;

//    std::string secRef = evalVar.toString();
	string uuid = get_uuid( evalVar.toString() );

    secretsPool[ uuid ] = secret;
    cout << "Secret '" << uuid << "' stored." << endl;

}


void SecretService::delete_secret(string uuid) {

	HTTPClientSession session(endpoint.getHost(), endpoint.getPort());
	std::string method = HTTPRequest::HTTP_DELETE;
	std::cout << "Preparing DELETE.." << std::endl;

    // REQUEST
    HTTPRequest request(method, endpoint.getPath() + "/v1/secrets/" + uuid);
    request.setContentType("application/json");
	// Inject Token authToken
    request.add("Accept", "application/json");
    request.add("X-Project-Id", projectId);
    request.add("X-Auth-Token", authToken);

    std::cout << "Sending Request.." << std::endl;
    std::ostream& o = session.sendRequest(request);
    Poco::JSON::Stringifier::stringify( "" , o );

    // RESPONSE
    HTTPResponse response;
    response.setStatus(Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);	// 503 as default (just in case)
    std::cout << "Waiting for Response.." << std::endl;
    std::istream& rs = session.receiveResponse(response);

    string jsonResponse;
    int jsonsize = StreamCopier::copyToString( rs, jsonResponse);
    std::cout << "HTTP_CODE: " << response.getStatus() << std::endl;
    cout << "\tResponse body: " << jsonResponse << endl;		// print out response body

    std::cout << "Secret '" << uuid << "' deleted." << std::endl;
}



string SecretService::get_uuid( string ref ) {

    URI uri(ref);
    string path = uri.getPath();

    return path.substr(12);		// skip "/v1/secrets/"
}


string SecretService::encodeKey_to_base64str ( vector<unsigned char> key ) {

	stringstream str;
	Poco::Base64Encoder encoder( str );

	for (auto k : key) {
		encoder << k;
	}
	encoder.close();

	cout << "\tKey_base64: " << str.str() << endl;

	return str.str();
}

vector<unsigned char> SecretService::decodeBase64str_to_key ( string payload ) {

	stringstream str;
	str.str( payload );
	Base64Decoder decoder(str);

	vector<unsigned char> key;
	std::string s;
	unsigned char c = decoder.get();
	while (c != -1) {
		s += c;
//		cout << "c: " << c << endl;
		key.push_back( c );
		c = decoder.get();
	}
	cout << "Recovered Key: " << s << endl;

	return key;
}
