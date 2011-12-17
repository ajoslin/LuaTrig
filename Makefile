outname=LuaTrig
libs=-llua51
src=src/
include=include/
objects=$(src)Condition.o $(src)Effect.o $(src)Trigger.o $(src)Scenario.o $(src)LuaTrigger.o $(src)LuaEffect.o $(src)LuaCondition.o $(src)aokutil.o $(src)fileutil.o $(src)luautil.o $(src)LuaTrig.o $(src)Main.o

program: $(objects)
	g++ -Wall -o $(outname) $(objects) $(libs)

Main.o: $(src)Main.cpp $(include)Main.h
	g++ -Wall -o $(src)Main.o -c $(src)Main.cpp
	
Condition.o: $(src)Condition.cpp $(include)Condition.h
	g++ -Wall -o $(src)Condition.o -c $(src)Condition.cpp

Effect.o: $(src)Effect.cpp $(include)Effect.h
	g++ -Wall -o $(src)Effect.o -c $(src)Effect.cpp

Trigger.o: $(src)Trigger.cpp $(include)Trigger.h
	g++ -Wall -o $(src)Trigger.o -c $(src)Trigger.cpp

Scenario.o: $(src)Scenario.cpp $(include)Scenario.h
	g++ -Wall -o $(src)Scenario.o -c $(src)Scenario.cpp

LuaTrigger.o: $(src)LuaTrigger.cpp $(include)LuaTrigger.h
	g++ -Wall -o $(src)LuaTrigger.o -c $(src)LuaTrigger.cpp

LuaEffect.o: $(src)LuaEffect.cpp $(include)LuaEffect.h
	g++ -Wall -o $(src)LuaEffect.o -c $(src)LuaEffect.cpp

LuaCondition.o: $(src)LuaCondition.cpp $(include)LuaCondition.h
	g++ -Wall -o $(src)LuaCondition.o -c $(src)LuaCondition.cpp

aokutil.o: $(src)aokutil.cpp $(include)aokutil.h
	g++ -Wall -o $(src)aokutil.o -c $(src)aokutil.cpp

fileutil.o: $(src)fileutil.cpp $(include)fileutil.h
	g++ -Wall -o $(src)fileutil.o -c $(src)fileutil.cpp

luautil.o: $(src)luautil.cpp $(include)luautil.h
	g++ -Wall -o $(src)luautil.o -c $(src)luautil.cpp

LuaTrig.o: $(src)LuaTrig.cpp $(include)LuaTrig.h
	g++ -Wall -o $(src)LuaTrig.o -c $(src)LuaTrig.cpp

clean:
	rm -rf $(src)*.o