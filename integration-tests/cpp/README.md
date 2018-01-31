WITDOM - SSP Client for KM
==========================

This repository contains a C++ client for the communication between the Secure Signal Processing protection component and the Key Manager in WITDOM.

It implements the the following methods:
- Secret.store
- Secret.list
- Secret.get
- Secret.get_payload
- Secret.delete

The REST API and HTTPS works using a certificate that might be self-signed.
To create a new selfsigned certificate, follow the instructions of the file 'howto_create_certificate.txt'.

The SSP client makes use of the [POCO library](http://pocoproject.org/download/) complete edition.





# Deployment of the SSP Service using Dockerfile


### Prerequisites

**Docker** is required to deploy the SSP Service 


## Installation 

1. **Build docker image** named _ssp-client-img_ run: 

    ````bash
    $ sudo docker build -t ssp-client-img
    ````
This step will take a while to complete.

2. **Create and run the docker container** named _ssp-cli_ with the previously created image, and forward its listening port to the local machine:
 
    ````
    $ sudo docker run -t --name ssp-cli -p 127.0.0.1:3389:3389 ssp-client-img
    ````

    Note: for external communications (accept requests from outside of the container), this IP must be changed to the local machine IP where the container is being run. 

3. **First execution of SSP client** is run automatically on creation:

    It will use the _Dockerfile_ default parameters (endpoint and token). Once started the SSP Client container, you can access the filesystem to perform manual executions anytime with custom parameters.

	````
	$ sudo docker exec -it ssp-cli bash
	````

4. **Run the client** from the container filesystem anytime by typing:
 
```
    $ cd /SSP-client
    $ ./SSP-client https://127.0.0.1:35357 anothertokenorthesame
```

5. Remember you can access the **SSP client container logs** to check the status of the server and previous requests: 

    ````
    $ sudo docker logs ssp-cli
    ````

## Managing the SSP container

As any other docker containers, you can: 

* **Access the filesystem** inside the container: You will be able to navigate and operate any shell command.
````
$ sudo docker exec -it ssp-cli bash
````
* **Stop** the container: 
````
$ sudo docker stop ssp-cli
````
* **Restart** the container: The container must exist previously. Once created at first by the _run_ command, a container may be restarted anytime while it has not been removed.
````
$ sudo docker start ssp-cli
````
* **Remove** the container: The container must be previously stopped, otherwise, you will need to add the **-f** flag.
````
$ sudo docker rm [-f] ssp-cli
````


# Local deployment of the SSP Service

### Prerequisites

**Cmake** is required to compile the SSP client locally. If not installed, open a terminal and run:
```
    sudo apt-get install -y cmake
```

## Compilation

For the compilation, just enter into the project folder and run:
```
    $ cmake .
    $ make
```
This command will generate the executable file **SSP-client** in the project folder. 

You can run cmake from another folder to build the makefile and subsequent executable file inside that folder,  always addressing the cmake command to the **CMakeLists.txt** folder, as follows: 
```
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
```

## Run

To run the client just type: 

You may run it in background like: 
```
    $ cd /SSP-client
    $ ./SSP-client https://127.0.0.1:35357 anothertokenorthesame
```


