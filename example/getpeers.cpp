/*
 * getpeers.cpp
 *
 *  Created on: May 13, 2012
 *      Author: narendran
 */

#include <iostream>
#include <event.h>
#include <stdlib.h>
#include <exception>
#include <string>
#include <vector>
#include <libcage/cage.hpp>
#include <boost/python.hpp>
#include <boost/thread.hpp>

libcage::cage *cage;

void printPeers(){
	cage->print_state();
}

void openCage_firstnode(char * portnum){
		event_init();
		int port = atoi(portnum);
		cage = new libcage::cage;
		std::cout<<"\nAbout to start cage on port "<<port<<"\n";
		try
		{
			if(!cage->open(PF_INET,port))
			{
				std::cout<<"Could not open port for P2P routing communication\n";
				return;
			}
		}catch(std::exception &e){
			std::cout<<"Port cannot be opened due to an exception. Message : "<<e.what()<<"\n";
		}
		std::cout<<"Cage instance listening on port "<<port;
		cage->set_global();
		std::cout<<"\nLog : Out of createCage\n";
		event_dispatch();
}

void createCage_firstnode(char * portnum){
	std::cout<<"\nLog : Into createCage\n";
	boost::thread workerThread(openCage_firstnode,portnum);
	return;
}

void join_callback(bool result){
	if(result)
		std::cout<<"Join Success";
	else
		std::cout<<"join Failure";
	printPeers();
}

void openCage_joinnode(char * portnum,char * host, char * destination_port){
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

void createCage_joinnode(char * portnum,char * host, char * destination_port){
	std::cout<<"\nLog : Into createCage\n";
	boost::thread workerThread(openCage_joinnode,portnum,host,destination_port);
	std::cout<<"\nLog : OUt of createCage\n";

}

int getPort()
{
	return cage->get_port();
}

std::vector<std::string>  getPeers()
{
	std::cout<<"Log : Entered into getPeers function";
	return cage->get_Peerlist();
}

/*
 * Vector to Python List converter
 */

template<class T>
struct VecToList
{
    static PyObject* convert(const std::vector<T>& vec)
    {
        boost::python::list* l = new boost::python::list();
        for(size_t i = 0; i < vec.size(); i++)
            (*l).append(vec[i]);

        return l->ptr();
    }
};


/*
 * Following module generates the python wrappers
 */
BOOST_PYTHON_MODULE(libcagepeers){
	using namespace boost::python;
	def("createCage_firstnode",createCage_firstnode);
	def("createCage_joinnode",createCage_joinnode);
	def("getPort",getPort);
	to_python_converter<std::vector<std::string,class std::allocator<std::string> >, VecToList<std::string> >();
	def("getPeers",getPeers);
}

int main(int argc, char **argv){

}

