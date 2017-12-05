#Author:         Christopher Beaudoin
#Major:          CS Software Development
#Creation Date:  November 29, 2017
#Due Date:       November 30,2017
#Course:         CSC328 010
#Professor:      Dr. Frye
#Assignment:     Rock Paper Scissors
#Filename:       makefile
#Purpose:        make the client or server for RPS
#******************************************************************************************/

client: rpsClient.o
	g++ -o client rpsClient.o

rpsClient.o: rpsClient.cpp
	g++ -c rpsClient.cpp

server: rpsServer.o
	g++ -o server rpsServer.o

rpsServer.o: rpsServer.cpp
	g++ -c rpsServer.cpp