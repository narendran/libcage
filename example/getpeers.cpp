/*
 * getpeers.cpp
 *
 *  Created on: May 13, 2012
 *      Author: narendran
 */

#include <iostream>
#include <event.h>
#include <libcage/cage.hpp>
#include <boost/python.hpp>

libcage::cage *cage;

void printPeers(){
	cage->print_state();
	return;
}

void createCage(char * portnum){
	event_init();
	std::cout<<"\nLog : Into createCage\n";
	int port = atoi(portnum);
	cage = new libcage::cage;
	std::cout<<"\nAbout to start cage on port "<<port<<"\n";
	// Open a port for other nodes to communicate
	/*
	 * TODO : Get IP, port number and if it should be stored in DTUN
	 * for now make it default to 10000. Later get the parameters from ICM agent
	 */
	if(!cage->open(PF_INET,port))
	{
		std::cout<<"Could not open port for P2P routing communication\n";
		return;
	}
	std::cout<<"Cage instance listening on port "<<port;
	cage->set_global();
	printPeers();
	event_dispatch();
	std::cout<<"\nLog : Out of createCage\n";
	return;
}

BOOST_PYTHON_MODULE(libcage){
	using namespace boost::python;
	def("createCage",createCage);
}


int main(int argc, char **argv)
{
	// One module for creating the global cage instance
	// One module to return the list of peers present in cage instance in the form of an STL list
	createCage(argv[1]);
	printPeers();
	return 1;
}



