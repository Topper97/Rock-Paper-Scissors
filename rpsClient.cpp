//Author:         Christopher Beaudoin
//Major:          CS Software Development
//Creation Date:  November 25, 2017
//Due Date:       November 30,2017
//Course:         CSC328 010
//Professor:      Dr. Frye
//Assignment:     Rock Paper Scissors
//Filename:       rpsClient.cpp
//Purpose:        Connect to rpsServer then play a game of Rock Paper Scissors with another client
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
string getChoice();
void sendChoice(int,string);

int main(int argc,char **argv)
{

  //check if 3 arguments if not show usage clause
  if (argc!=3)//Usage
    cout<<"Usage: "<<argv[0]<<" Port# Hostname"<<endl;
  else
  {
    struct sockaddr_in client_addr;
    struct hostent *client;
    //Create socket
    int descriptor = socket(AF_INET,SOCK_STREAM,0);
    if (descriptor == -1)
    {
      perror("Error creating socket:  ");
      return 0;
    }

    client=gethostbyname(argv[2]);
    if (client==NULL)
    {
      cout<<"Not a valid host name"<<endl;
      return 0;
    }
    int port = stoi(argv[1]);
    //convert port number to network bite order htons()
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(port);
    memcpy(&client_addr.sin_addr, client->h_addr_list[0], client->h_length);

    //connect to the server
    int result = connect(descriptor, (struct sockaddr *)&client_addr, sizeof(client_addr));
    if (result == -1)
    {
      perror("Error connecting to server:  ");
      return 0;
    }
    //cout<<"Connected to server"<<endl;
    cout<<"You are playing Rock-Paper-Scissors-Lizard-Spock."<<endl;
    cout<<"The rules according to Sheldon Cooper are..."<<endl;
    cout<<"Rock crushes Scissors"<<endl<<"Scissors cut Paper"<<endl;
    cout<<"Paper covers Rock"<<endl<<"Rock crushes Lizard"<<endl;
    cout<<"Lizard poisons Spock"<<endl<<"Spock smashes Scissors"<<endl;
    cout<<"Scissors decapitate Lizard"<<endl<<"Lizard eats Paper"<<endl;
    cout<<"Paper disproves Spock"<<endl<<"Spock vaporizes Rock"<<endl;
    cout<<"Enjoy your game."<<endl;
    //send ready
    char send[1];
    send[0]='0';
    result = write(descriptor,send,1);
    //recive go
    char go[1];
    //vars to hold wins loses and Tie
    int win=0; int loses=0; int tie=0;
    do
    {
      result=read(descriptor,go,1);
      if (result<0)
      {
        perror("Error connecting to server:  ");
        return 0;
      }
      if (go[0]=='0')
      {
        //prompt for choice
        string choice=getChoice();
        //send choice
        sendChoice(descriptor,choice);

        //recive result
        char conclusion[1];
        result=read(descriptor,conclusion,1);
        if (result<0)
        {
          perror("Error connecting to server:  ");
          return 0;
        }
        //print results
        switch (conclusion[0])
        {
          //win
          case '2':
                  win++;
                  cout<<"You won this round"<<endl;
                  break;
          //lose
          case '0':
                  loses++;
                  cout<<"You lose this round"<<endl;
                  break;
          //tie
          default:
                  tie++;
                  cout<<"This round was a tie"<<endl;
        }
      }
    }while(go[0] == '0');
    //print the final results
    int total=win+loses+tie;
    cout<<endl<<"You played "<<total<<" round(s)"<<endl;
    cout<<win<<" Wins"<<endl;
    cout<<loses<<" Loses"<<endl;
    cout<<tie<<" Ties"<<endl;
    close(descriptor);
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
//get choice from user
//Function Name: getChoice
//Description:   gets the choice from the user and returns it
//Parameters:    none
//return value:  string: the users choice
string getChoice()
{
  cout<<"Please enter your choice for playing Rock(R)-Paper(P)-Scissors(S)-Lizard(L)-Spock(K)"<<endl;
  string choice;
  getline(cin,choice);
  choice=choice.substr(0,1);
  while (choice!= "R" && choice!="r" && choice!="P" && choice!="p" && choice!="S" && choice!="s" && choice!="K" && choice!="k" && choice!="L" && choice!="l")
  {
    cout<<"Bad Choice"<<endl<<"Please enter your choice for playing Rock(R)-Paper(P)-Scissors(S)-Lizard(L)-Spock(K)"<<endl;
    getline(cin,choice);
    choice=choice.substr(0,1);
  }
  return choice;
}

//Function Name: sendChoice
//Description:   sends the users choice to the server in the form a numbers
//Parameters:    string: the users choice
//               int: file descriptor
//return value:  void
void sendChoice(int descriptor, string choice)
{
  int result;
  char send[1];
  if (choice=="R" || choice=="r")
  {
    send[0]='1';
    result = write(descriptor,send,1);
  }
  else if (choice=="P" || choice=="p")
  {
    send[0]='2';
    result = write(descriptor,send,1);
  }
  else if (choice=="S" || choice=="s")
  {
    send[0]='3';
    result = write(descriptor,send,1);
  }
  else if (choice=="L" || choice=="l")
  {
    send[0]='4';
    result = write(descriptor,send,1);
  }
  else if (choice=="K" || choice=="k")
  {
    send[0]='5';
    result = write(descriptor,send,1);
  }
}
