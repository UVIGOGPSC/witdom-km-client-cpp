FROM ubuntu:14.04
LABEL Description="This image starts a container to easily deploy a C++ client for communications of the SSP component with the KM."

#########################
#### Setup container ####
#########################

RUN apt-get update && apt-get install -y \
	# build-essential \
	openssl libssl-dev \
	libz-dev \
	g++ \
	wget \
	cmake 


#### Install POCO framework ####

WORKDIR /home
RUN wget https://pocoproject.org/releases/poco-1.7.6/poco-1.7.6-all.tar.gz
RUN tar -xvf poco-1.7.6-all.tar.gz
WORKDIR poco-1.7.6-all
RUN ./configure ; make -j4 ; make install
#RUN ./configure --include-path=/usr/local/ssl/include --library-path=/usr/local/ssl/lib ; make


#######################
#### Build Client  ####
#######################

# Copy files #
WORKDIR /SSP-client
ADD integration-tests /SSP-client/integration-tests/
ADD barbican-clients /SSP-client/barbican-clients/
ADD CMakeLists.txt /SSP-client/CMakeLists.txt
ADD *.pem /SSP-client/

# Compile API #
RUN cmake . 
RUN make


#####################
#### Run client  ####
#####################

CMD ./SSP-client https://127.0.0.1:35357 Th1s1SaRaNd0mT0k3N

# Expose SSP client public endpoint
#EXPOSE 3389

