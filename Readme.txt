Author:         Christopher Beaudoin
Major:          CS Software Development
Start Date:     November 25, 2017
Due Date:       November 30,2017
Course:         CSC328 010
Professor:      Dr. Frye
Assignment:     Rock Paper Scissors

File Names:
      rpsServer.cpp
      rpsClient.cpp
      Makefile
      makefile.harry

Description: This is a client server application of Rock-Paper-Scissors, extra credit for Lizard-Spock.
      Two clients connect to a server to play a game of Rock-Paper-Scissors(-Lizard-Spock) with the
      server acting as referee.
  Note: The extra credit of Lizard-Spock is included
  Note: The server should run on harry but the client does not

Rules for Rock-Paper-Scissors
            Scissors cuts Paper
            Paper covers Rock
            Rock crushes Scissors

Rules for Rock-Paper-Scissors-Lizard-Spock
            Scissors cuts Paper
            Paper covers Rock
            Rock crushes Lizard
            Lizard poisons Spock
            Spock smashes Scissors
            Scissors decapitates Lizard
            Lizard eat Paper
            Paper disproves Spock
            Spock vaporizes Rock
            Rock crushes Scissors

Compile: when compiling you must chose which part you want to compile
    acad
        make (server/client)
    harry
        /usr/ccs/bin/make (server/client) -f makefile.harry

Protocol:
  Note:
    If you are only playing Rock-Paper-Scissors just omit options 4 and 5 and the rest stays the same.
  Client:
    The client must accept two command-line arguments, the server’s port number and hostname.
      "Usage: client Port# Hostname"
    The client should connect to the server using a TCP connection.
    The client should then send ready '0' to the server.
    The client should read go '0' from the server get the choice from the user and send it to the server.
      (1-Rock,2-Paper,3-Scissors,4-Lizard,5-Spock)
    The client should then read the result of the round and update the local counter accordingly.
      (2-win,0-lose,1-tie)
    The client should repeat the last two steps until it receives stop '9' from the server.
    The client should then output the number of rounds played and the number of win/lose/tie.
    The client should then terminate.

  Server:
    The server must accept two command-line arguments, the port number and the number of iterations (rounds).
      "Usage: server Port#  #Rounds"
    The server should then accept 2 clients.
    Once both clients are connected the server should read ready '0' from both clients
    The server should send go '0' to both clients.
    The server should then read the players choice from both clients.
      (1-Rock,2-Paper,3-Scissors,4-Lizard,5-Spock)
    The server should then decide the winner and send the results back to both clients according to who won.
      (2-win,0-lose,1-tie)
    The server should then decrement the number of rounds.
    If the number of rounds is still greater then 0 the server should repeat the last four steps.
    If the number is 0 the server should send stop '9' to both clients.
    The server should then terminate.

Task Times:
  Task: estimated time -- actual time

  Design: 40 minutes -- 50 minutes
  Coding: 4 hours -- 3 hours
  Testing: 1 hour -- 3.5 hours
  Debugging: 30 minutes -- 3.5 hours

  Total: 6 hours 10 minutes -- 10 hours 50 minutes
