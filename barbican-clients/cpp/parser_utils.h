/*
 * utils.h
 *
 *  Created on: Dec 2, 2016
 *      Author: djarenho
 */

#ifndef BARBICAN_CLIENTS_CPP_PARSER_UTILS_H_
#define BARBICAN_CLIENTS_CPP_PARSER_UTILS_H_


bool is_valid_string(Poco::Dynamic::Var evalVar, string property) {

	if ( evalVar.isEmpty() ) {
		std::cout << property << " not found" << std::endl;
		return false;
	}
	if ( !evalVar.isString() ) {
		std::cout << property << " is not string" << std::endl;
		return false ;
	}
//	std::string secRef = evalVar.toString();
	if ( !evalVar.toString().size() ) {
		std::cout << property << " is empty" << std::endl;
		return false;
	}
	return true;
}


bool is_valid_int(Poco::Dynamic::Var evalVar, string property) {

	if ( evalVar.isEmpty() ) {
		std::cout << property << " not found" << std::endl;
		return false;
	}
	if ( !evalVar.isInteger() ) {
		std::cout << property << " is not integer" << std::endl;
		return false ;
	}

	try {
		int intVar = evalVar.convert<int>();
	} catch(...) {
		std::cout << property << " failed converting into integer" << std::endl;
		return false;
	}
	return true;
}


bool is_valid_arrayjson(Poco::Dynamic::Var evalVar, string property) {

	if ( evalVar.isEmpty() ) {
		std::cout << property << " not found" << std::endl;
		return false;
	}
	if ( evalVar.type() != typeid(Poco::JSON::Array::Ptr) ) {
		std::cout << property << " is not a valid json array" << std::endl;
		return false ;
	}

    try {
    	Poco::JSON::Array::Ptr arrVar = evalVar.extract<Poco::JSON::Array::Ptr>();
    } catch (Poco::InvalidAccessException & iae) {
    	std::cout << property << " has no elements to extract" << std::endl;
    } catch (Poco::BadCastException & bce) {
    	std::cout << property << " failed extracting the json array" << std::endl;
    }
    return true;
}



bool is_valid_objson(Poco::Dynamic::Var evalVar, string property) {

	if ( evalVar.isEmpty() ) {
		std::cout << property << " not found" << std::endl;
		return false;
	}
	if ( evalVar.type() != typeid(Poco::JSON::Object::Ptr) ) {
		std::cout << property << " is not a valid json object" << std::endl;
		return false ;
	}
	return true;
}


bool is_SecretMetadata_objson(Poco::JSON::Object::Ptr secretMetadata) {

	string property = "status";
	if ( !is_valid_string(secretMetadata->get( property ), property)) {
		cout << "No valid " << property << "." << endl;
		return false;
	}

	property = "created";
	if ( !is_valid_string(secretMetadata->get( property ), property)) {
		cout << "No valid " << property << "." << endl;
		return false;
	}

	property = "updated";
	if ( !is_valid_string(secretMetadata->get( property ), property)) {
		cout << "No valid " << property << "." << endl;
		return false;
	}

	property = "expiration";
	if ( !is_valid_string(secretMetadata->get( property ), property)) {
		cout << "No valid " << property << "." << endl;
//		return false;
	}

	property = "algorithm";
	if ( !is_valid_string(secretMetadata->get( property ), property)) {
		cout << "No valid " << property << "." << endl;
		return false;
	}

	property = "bitLength";
	if ( !is_valid_int(secretMetadata->get( property ), property)) {
		cout << "No valid " << property << "." << endl;
		return false;
	}

	property = "mode";
	if ( !is_valid_string(secretMetadata->get( property ), property)) {
		cout << "No valid " << property << "." << endl;
		return false;
	}

	property = "name";
	if ( !is_valid_string(secretMetadata->get( property ), property)) {
		cout << "No valid " << property << "." << endl;
		return false;
	}

	property = "secret_ref";
	if ( !is_valid_string(secretMetadata->get( property ), property)) {
		cout << "No valid " << property << "." << endl;
		return false;
	}

	property = "secret_type";
	if ( !is_valid_string(secretMetadata->get( property ), property)) {
		cout << "No valid " << property << "." << endl;
		return false;
	}

	property = "content_types";
	if ( !is_valid_objson(secretMetadata->get( property ), property)) {
		cout << "No valid " << property << "." << endl;
		return false;
	}

	return true;

}


#endif /* BARBICAN_CLIENTS_CPP_PARSER_UTILS_H_ */
