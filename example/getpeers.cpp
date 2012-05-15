/*
 * getpeers.cpp
 *
 *  Created on: May 13, 2012
 *      Author: narendran
 */

#include <iostream>
#include <event.h>
#include <stdlib.h>
#include <libcage/cage.hpp>
#include <boost/python.hpp>

libcage::cage *cage;

void printPeers(){
	cage->print_state();
}

void createCage_firstnode(char * portnum){
	std::cout<<"\nLog : Into createCage\n";
	event_init();
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
	event_dispatch();
	std::cout<<"\nLog : Out of createCage\n";
	return;
}

void join_callback(bool result){
	if(result)
		std::cout<<"Join Success";
	else
		std::cout<<"join Failure";
	printPeers();
}

void createCage_joinnode(char * portnum,char * host, char * destination_port){
	std::cout<<"\nLog : Into createCage\n";
	event_init();
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
	std::cout<<"\nLog : Enter Join network";
	int dest_port = atoi(destination_port);
	cage->join(host,dest_port,&join_callback);
	event_dispatch();
}

/*
 * Following module generates the python wrappers
 */
BOOST_PYTHON_MODULE(libcagepeers){
	using namespace boost::python;
	def("createCage_firstnode",createCage_firstnode);
	def("createCage_joinnode",createCage_joinnode);
}


int main(int argc, char **argv)
{
	// One module for creating the global cage instance
	// One module to return the list of peers present in cage instance in the form of an STL list

	/*createCage(argv[1]);
	if(argc>=4)
	{
		std::cout<<"\nMore parameters detected";
		join(argv[2],argv[3]);
	}
	else
	{
		printPeers();
	}

	return 0;*/
}



