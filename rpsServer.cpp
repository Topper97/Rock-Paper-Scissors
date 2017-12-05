//Author:         Christopher Beaudoin
//Major:          CS Software Development
//Creation Date:  November 25, 2017
//Due Date:       November 30,2017
//Course:         CSC328 010
//Professor:      Dr. Frye
//Assignment:     Rock Paper Scissors
//Filename:       rpsServer.cpp
//Purpose:        have 2 clients connect then referee a game of Rock Paper Scissors
//                Lizard Spock was added as extra credit (Rules according to Sheldon Cooper)
/******************************************************************************************/

#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sstream>

using namespace std;

int stoi(string);
int findWinner(char,char);
int playGame(int,int,int);
int endOfGame(int,int);

int main(int argc,char **argv)
{

  //check if 3 arguments if not show usage clause
  if (argc!=3)//Usage
    cout<<"Usage: "<<argv[0]<<" Port#  #Rounds"<<endl;
  else
  {
    int rounds = stoi(argv[2]);
    if (rounds<=0)
    {
      cout<<"Usage: "<<argv[0]<<" Port#  #Rounds"<<endl;
      return 0;
    }
    //Borrowed from passicesock.c on 11/20/17 with some modifications
    struct sockaddr_in sin;	/* an Internet endpoint address		*/
    int s;
    int port;
    port=stoi(argv[1]);
    sin.sin_family = AF_INET;
  	sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port=htons(port);
    /* Allocate a socket */
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
      perror("Error creating socket:  ");
      return 0;
    }
    int a[] = {1};
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &a, sizeof(int)) < 0)
    {
      perror("setsockopt(SO_REUSEADDR) failed");
      return 0;
    }

    /* Bind the socket */
    if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("Error binding socket:  ");
        return 0;
    }
    if (listen(s, 2) < 0)
    {
        perror("Error listening on given port:  ");
        return 0;
    }
    //end borrowed code
    //if want to leave server open after game done start loop here
    //accept connection to player 1
    unsigned int slen;
    slen=sizeof(sin);
    int player1;
    player1 = accept(s,(struct sockaddr *)&sin, &slen);
    if (player1 < 0)
    {
      perror("Error, unable to accept player 1: ");
      return 0;
    }
    cout<<"connected to player 1"<<endl;

    //accept connection to player 2
    int player2;
    player2 = accept(s,(struct sockaddr *)&sin, &slen);
    if (player2 < 0)
    {
      perror("Error, unable to accept player 2: ");
      return 0;
    }
    cout<<"connected to player 2"<<endl;

    //recive ready from both Clients
    char p1[1]; char p2[1];
    int result = read(player1,p1,1);
    if (result < 0)
    {
      perror("Error, unable to read ready from player 1: ");
      return 0;
    }
    result = read(player2,p2,1);
    if (result < 0)
    {
      perror("Error, unable to read ready from player 2: ");
      return 0;
    }
    //cout<<"both clients ready"<<endl;
    //start game

    result=playGame(player1,player2,rounds);
    if (result==0)
    {
      return 0;
    }

    //cout<<"End of rounds"<<endl;
    //no rounds left tell client to show final score and tell to close
    result=endOfGame(player1, player2);
    if (result==0)
    {
      return 0;
    }

    close(player1);
    close(player2);
    close(s);
  }
  return 0;
}

//Function Name: stoi
//Description:   convert a string to an int
//Parameters:    string: string to be converted to an int
//return value:  void
int stoi(string word)
{

    std::stringstream ss;
    ss<<word;
    int num;
    ss>>num;

    return num;
}

//Function Name: winner
//Description:   decides the winner of a RPS game
//                  1-Rock 2-Paper 3-Scissors 4-Lizard 5-Spock
//Parameters:    char: player1's choice
//               char: player2's choice
//return value:  the winner 1-Player1, 2-player2, 0-Tie
int findWinner(char player1, char player2)
{
  //tie
  if (player1==player2)
    return 0;
  //player1 picks Rock
  else if(player1=='1')
  {
    if (player2 == '2' || player2 == '5')
      return 2;
    else
      return 1;
  }
  //player 1 picks Paper
  else if(player1=='2')
  {
    if (player2 == '3' || player2 == '4')
      return 2;
    else
      return 1;
  }
  //player 1 picks Scissors
  else if(player1=='3')
  {
    if (player2 == '1' || player2 == '5')
      return 2;
    else
      return 1;
  }
  //player 1 picks Lizard
  else if(player1=='4')
  {
    if (player2 == '1' || player2 == '3')
      return 2;
    else
      return 1;
  }
  //player 1 picks Spock
  else if(player1=='5')
  {
    if (player2 == '2' || player2 == '4')
      return 2;
    else
      return 1;
  }
}


//Function Name: playGame
//Description:   plays the correct number of rounds of Rock Paper Scissors
//Parameters:    player1: socket descriptor for the first player
//               player2: socket descriptor for the second player
//               beginR: number of rounds to play
//return value:  int: error flag kills program
int playGame(int player1,int player2,int beginR)
{
  int rounds=beginR;
  char p1[1]; char p2[1];
  while (rounds>0)
  {
    int result;
    //send go
    char send[1];
    send[0]='0';
    result=write(player1,send,1);
    if (result<0)
    {
      perror("Error, unable to write go player 1: ");
      return 0;
    }
    result=write(player2,send,1);
    if (result<0)
    {
      perror("Error, unable to write go player 2: ");
      return 0;
    }
    //recieve plays from players
    result = read(player1,p1,1);
    if (result < 0)
    {
      perror("Error, unable to read choice from player 1: ");
      return 0;
    }
    result = read(player2,p2,1);
    if (result < 0)
    {
      perror("Error, unable to read choice from player 2: ");
      return 0;
    }
    //find winner
    int winner = findWinner(*p1,*p2);
    //send clients results
    switch (winner) {
      //Player2 wins
      case 2:
              send[0]='0';
              result=write(player1,send,1);
              if (result<0)
              {
                perror("Error, unable to write winner player 1: ");
                return 0;
              }
              send[0]='2';
              result=write(player2,send,1);
              if (result<0)
              {
                perror("Error, unable to write winner player 2: ");
                return 0;
              }
              break;
      //Player1 wins
      case 1:
              send[0]='2';
              result=write(player1,send,1);
              if (result<0)
              {
                perror("Error, unable to write winner player 1: ");
                return 0;
              }
              send[0]='0';
              result=write(player2,send,1);
              if (result<0)
              {
                perror("Error, unable to write winner player 2: ");
                return 0;
              }
              break;
      //Tie
      default:
              send[0]='1';
              result=write(player1,send,1);
              if (result<0)
              {
                perror("Error, unable to write winner player 1: ");
                return 0;
              }
              result=write(player2,send,1);
              if (result<0)
              {
                perror("Error, unable to write winner player 2: ");
                return 0;
              }
              break;

    }
    rounds=rounds-1;
  }
}

//Function Name: endOfGame
//Description:   tells client end of game and to exit
//Parameters:    player1: socket descriptor for the first player
//               player2: socket descriptor for the second player
//return value:  int: error flag kills program
int endOfGame(int player1, int player2)
{
  int result;
  char send[1];
  send[0]='9';
  result=write(player1,send,1);
  if (result<0)
  {
    perror("Error, unable to write score player 1: ");
    return 0;
  }
  result=write(player2,send,1);
  if (result<0)
  {
    perror("Error, unable to write score player 2: ");
    return 0;
  }
  cout<<"Game Over"<<endl;

}