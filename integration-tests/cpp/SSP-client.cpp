//============================================================================
// Name        : SSP-client.cpp
// Author      : djarenho
// Version     : 1.0
// Copyright   : 
// Description : Client for invoking KM services in C++, Ansi-style
//============================================================================

#include "../../barbican-clients/cpp/KMClient.h"
#include "../../barbican-clients/cpp/SecretService.h"
#include "../../barbican-clients/cpp/Secret.h"

#include <memory>
#include <iostream>
#include "utility"
#include <string>
#include <fstream>

#include "Poco/StreamCopier.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/SharedPtr.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/ConsoleCertificateHandler.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"

#include "Poco/Net/NetSSL.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>

using namespace Poco;
using namespace Poco::Net;




class SSLInitializer {
public:
    SSLInitializer() { Poco::Net::initializeSSL(); }
    ~SSLInitializer() { Poco::Net::uninitializeSSL(); }
};

int main(int argc, char** argv)
{
    SSLInitializer sslInitializer;

    SharedPtr<InvalidCertificateHandler> ptrCert = new ConsoleCertificateHandler(false);
    Context::Ptr ptrContext = new Context(Context::CLIENT_USE, "", "", /*rootcert.pem*/"cacert.pem", Context::VERIFY_ONCE);
    SSLManager::instance().initializeClient(0, ptrCert, ptrContext);

    if (argc < 3) {
    	cout << "Arguments must be provided in the following order:" << endl;
    	cout << " - 1: Endpoint " << std::endl;
    	cout << " - 2: Token " << std::endl;
//    	cout << " - 3: ProjectId " << std::endl;
    	return -1;
    }

    // Parse input arguments

    URI endpoint(argv[1]);
    string token = argv[2];
//    string project = argv[3];

    KMClient km(endpoint, token, "");

    Secret sec;

    std::cout << "\n## Store a secret:" << std::endl;
    km.secretService->store(sec);

    std::cout << "\n## List secrets:" << std::endl;
    km.secretService->list();

    std::cout << "\n## Get secret metadata:" << std::endl;
    km.secretService->get("mySecret");

    std::cout << "\n## Get secret:" << std::endl;
    km.secretService->get_payload("mySecret");

    std::cout << "\n## Delete secret:" << std::endl;
    km.secretService->delete_secret("mySecret");

















    std::cout << " \n- Client finished -"<< std::endl;
    return 0;
}





//#include <iostream>
//
////#include <Python.h>
//#include <boost/python.hpp>
//
//using namespace boost::python;
//
//
//using namespace std;
//
//int main() {
//	Py_Initialize();
//	cout << "Hallo" << endl; // prints Hallo
//	return 0;
//}


//struct World
//{
//    void set(std::string msg) { mMsg = msg; }
//    std::string greet() { return mMsg; }
//    std::string mMsg;
//};
//
//BOOST_PYTHON_MODULE(classes)
//{
//    class_<World>("World")
//        .def("greet", &World::greet)
//        .def("set", &World::set)
//    ;
//};
