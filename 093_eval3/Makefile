flag=-ggdb3 -Wall -Werror -pedantic -std=gnu++98

cyoa-step4:cyoa-step4.cpp cyoa-step3.hpp cyoa-step3 
	g++ -o cyoa-step4 $(flag) cyoa-step4.cpp

cyoa-step3:cyoa-step3.cpp cyoa-step3.hpp cyoa-step2 
	g++ -o cyoa-step3 $(flag) cyoa-step3.cpp    

cyoa-step2:cyoa-step2.cpp cyoa-step2.hpp cyoa-step1          
	g++ -o cyoa-step2 $(flag) cyoa-step2.cpp

cyoa-step1:cyoa-step1.cpp cyoa-step1.hpp	   
	g++ -o cyoa-step1 $(flag) cyoa-step1.cpp   



