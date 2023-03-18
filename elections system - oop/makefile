Ass5: main.o PoliticalSys.o DemocraticLeader.o SocialDemocrat.o SocialRepublican.o Party.o DemocraticParty.o RepublicanParty.o Politician.o RepublicanLeader.o
	g++ main.o PoliticalSys.o DemocraticLeader.o SocialDemocrat.o SocialRepublican.o Party.o DemocraticParty.o RepublicanParty.o Politician.o RepublicanLeader.o -o Ass5 

PoliticalSys.o:  PoliticalSys.cpp PoliticalSys.h DemocraticLeader.h DemocraticParty.h SocialDemocrat.h	RepublicanLeader.h RepublicanParty.h SocialRepublican.h
		g++ -c PoliticalSys.cpp

DemocraticLeader.o:  DemocraticLeader.cpp DemocraticLeader.h Politician.h
		g++ -c DemocraticLeader.cpp

SocialDemocrat.o:  SocialDemocrat.cpp SocialDemocrat.h Politician.h
		g++ -c SocialDemocrat.cpp

SocialRepublican.o:  SocialRepublican.cpp SocialRepublican.h Politician.h
		g++ -c SocialRepublican.cpp	

RepublicanLeader.o:  RepublicanLeader.cpp RepublicanLeader.h Politician.h
		g++ -c RepublicanLeader.cpp

Party.o:  Party.cpp Party.h
		g++ -c Party.cpp						

DemocraticParty.o:  DemocraticParty.cpp DemocraticParty.h Party.h
		g++ -c DemocraticParty.cpp

RepublicanParty.o:  RepublicanParty.cpp RepublicanParty.h Party.h
		g++ -c RepublicanParty.cpp

Politician.o:  Politician.cpp Politician.h
		g++ -c Politician.cpp		

clean: 
	rm -f *.o
