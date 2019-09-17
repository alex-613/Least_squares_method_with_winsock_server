/**
* @file functions.h
* @author Alex Ranne
* @date 2nd of September, 2019
* @brief Functions header file of the project, declears all functions used.
*
*
*
*
*/

#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <WS2tcpip.h>


//Least squares optimization
Eigen::MatrixXd matrixGen(int rows, int cols);
Eigen::MatrixXd quaternionConv2R(double ANGLE, int x, int y, int z);
Eigen::MatrixXd predefinedTransformation(Eigen::MatrixXd points, Eigen::MatrixXd R, int translation[3]);
Eigen::MatrixXd centroidFinding(Eigen::MatrixXd points, Eigen::MatrixXd pointsNew);
Eigen::MatrixXd findH(Eigen::MatrixXd points, Eigen::MatrixXd pointsNew, Eigen::MatrixXd centroids);
Eigen::MatrixXd singleValueDecomposition(Eigen::MatrixXd H);
Eigen::MatrixXd findTranslation(Eigen::MatrixXd centroids, Eigen::MatrixXd X);

//WINSOCK
void initialization();
void binding(SOCKET in, sockaddr_in serverHint);
std::vector<Eigen::MatrixXd> receivingloop(SOCKET in, sockaddr_in client, int clientLength, int pcln);
void termination(SOCKET in);
