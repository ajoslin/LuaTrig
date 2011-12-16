outname=LuaTrig
libs=-llua -lluabind
src=src/
include=include/
objects=$(src)Condition.o $(src)Effect.o $(src)Trigger.o $(src)Scenario.o $(src)lua/LuaTrigger.o $(src)lua/LuaEffect.o $(src)lua/LuaCondition.o $(src)aokutil.o $(src)fileutil.o $(src)LuaTrig.o

program: $(objects)
	g++ -Wall -o $(outname) $(libs) $(objects)
	
Condition.o: $(src)Condition.cpp $(include)Condition.h
	g++ -Wall -o Condition.o -c Condition.cpp

Effect.o: $(src)Effect.cpp $(include)Effect.h
	g++ -Wall -o Effect.o -c Effect.cpp

Trigger.o: $(src)Trigger.cpp $(include)Trigger.h
	g++ -Wall -o Trigger.o -c Trigger.cpp

Scenario.o: $(src)Scenario.cpp $(include)Scenario.h
	g++ -Wall -o Scenario.o -c Scenario.cpp

LuaTrigger.o: $(src)lua/LuaTrigger.cpp $(include)lua/LuaTrigger.h
	g++ -Wall -o LuaTrigger.o -c LuaTrigger.cpp

LuaEffect.o: $(src)lua/LuaEffect.cpp $(include)lua/LuaEffect.h
	g++ -Wall -o LuaEffect.o -c LuaEffect.cpp

LuaCondition.o: $(src)lua/LuaCondition.cpp $(include)lua/LuaCondition.h
	g++ -Wall -o LuaCondition.o -c LuaCondition.cpp

aokutil.o: $(src)aokutil.cpp $(include)aokutil.h
	g++ -Wall -o aokutil.o -c aokutil.cpp

fileutil.o: $(src)fileutil.cpp $(include)fileutil.h
	g++ -Wall -o fileutil.o -c fileutil.cpp

LuaTrig.o: $(src)LuaTrig.cpp $(include)LuaTrig.h
	g++ -Wall -o LuaTrig.o -c LuaTrig.cpp

clean:
	rm -rf *.o
	rm -rf *.gch