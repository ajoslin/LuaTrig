CC=gcc
outputName=LuaTrig
libs=-llua51
src=src/
sources=$(src)Condition.cpp $(src)Effect.cpp $(src)Trigger.cpp $(src)Scenario.cpp $(src)LuaTrigger.cpp $(src)LuaEffect.cpp $(src)LuaCondition.cpp $(src)util.cpp $(src)LuaTrig.cpp
main=$(src)Main.cpp



program: my_util.o effect.o condition.o trigger.o luautil.o luatrigger.o luaeffect.o luacondition.o luatrig.o scenario.o 
	g++ -Wall my_util.o effect.o condition.o trigger.o luautil.o luatrigger.o luaeffect.o luacondition.o luatrig.o scenario.o  -o LuaTrig -llua51

my_util: my_util.cpp 
	g++ -c -Wall my_util.cpp -o my_util.o

condition: Condition.cpp 
	g++ -c -Wall Condition.cpp -o condition.o

effect: Effect.cpp 
	g++ -c -Wall -Effect.cpp -o effect.o

luaeffect: LuaEffect.cpp 
	g++ -c -Wall LuaEffect.cpp -o luaeffect.o

luacondition: LuaCondition.cpp 
	g++ -c -Wall LuaCondition.cpp -o luacondition.o

luatrigger: LuaTrigger.cpp
	g++ -c -Wall LuaTrigger.cpp -o luatrigger.o

main: LuaTrig.cpp 
	g++ -c -Wall LuaTrig.cpp -o Main.o

luautil: LuaUtil.cpp
	g++ -c -Wall LuaUtil.cpp -o luautil.o

scenario: Scenario.cpp
	g++ -c -Wall Scenario.cpp -o scenario.o

trigger: Trigger.cpp
	g++ -c -Wall Trigger.cpp -o trigger.o

clean:
	rm -rf *.o
	rm -rf *.gch