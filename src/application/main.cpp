#include <iostream>
#include <WS2tcpip.h>
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
#include "functions.h"
#include <vector>
#include <stdio.h>

// Include the Winsock library (lib) file
#pragma comment (lib, "ws2_32.lib")


int main()
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////START OF UDP TRANSMISSION////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////

	/**
	Initialize winsock
	*/

	initialization();


	/**
	Socket creation
	*/

	SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in serverHint;

	binding(in, serverHint);

	/**
	Main setup, the server receives
	*/
	sockaddr_in client;
	int clientLength = sizeof(client);
	int pcln = 2; //Number of point clouds

	std::vector<Eigen::MatrixXd> matrixArray = receivingloop(in, client, clientLength, pcln);

	/**
	Close winsock and clean up
	*/
	termination(in);

	//////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////END OF UDP TRANSMISSION//////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////

	/**
	Extract the data from the matrix, not including the commas
	*/
	std::cout <<"\n"<< matrixArray[0] <<std::endl;
	std::cout <<"\n"<< matrixArray[1] <<std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////Least squares optimization//////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	// Find the centroids

	Eigen::MatrixXd centroids = centroidFinding(matrixArray[0],matrixArray[1]);

	std::cout << "\n" << centroids << std::endl;

	// Find H matrix

	Eigen::MatrixXd H = findH(matrixArray[0], matrixArray[1], centroids);

	std::cout << "\n" << H << std::endl;

	Eigen::MatrixXd X = singleValueDecomposition(H);

	std::cout << "\n" << X << std::endl;

	//Find the t vector

	Eigen::MatrixXd t = findTranslation(centroids, X);

	std::cout << "\n" << t << std::endl;
	std::cin.get();

}