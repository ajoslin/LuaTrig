################################################################################
#### Makefile heavily based on TBFE-Engine makefile, created by Tyler Dodge ####
##################### github.com/tyler-dodge/TBFE-Engine #######################
################################################################################

CC=gcc
outName=program/LuaTrig
bin=bin/
src=src/
objs=objs/
model=$(src)model/
view=$(src)view/
util=$(src)util/
libs=-llua `wx-config --cxxflags --libs`

#all the source files
modelFiles=$(model)Condition.cpp $(model)Effect.cpp $(model)Trigger.cpp $(model)LuaEffect.cpp $(model)LuaCondition.cpp $(model)LuaTrigger.cpp $(model)Scenario.cpp $(model)LuaTrig.cpp

utilFiles=$(util)luautil.cpp $(util)aokutil.cpp $(util)fileutil.cpp

viewFiles=$(view)LTMain.cpp $(view)LTFrame.cpp $(view)LTDialog_Settings.cpp $(view)LTDialog_About.cpp

srcFiles=$(modelFiles) $(utilFiles) $(viewFiles)

#Compiled source files
objFiles=$(subst $(src),$(objs),$(srcFiles:.cpp=.o))

#main compilation, final linking
program: $(objFiles)
	g++ $(objFiles) $(libs) -o $(outName)

#Uses makefiles created by dependency generation for source files
include $(objFiles:.o=.d)

#Dependency generation for source files 
$(objs)%.d:$(src)%.cpp 
	$(CC) -MM $(libs) $(CPPFLAGS) $< -o $(objs)$*.P;
	sed -r 's/$(notdir $*.o)/objs\/$(subst /,\/,$*.o)/g' < $(objs)$*.P > $(objs)$*.d;
	rm $(objs)$*.P


#Compile instructions for source files
$(objs)%.o:$(src)%.cpp 
	g++ -c $(DEFINES) $(libs) $< -o $@

clean:
	rm $(objFiles)
	rm $(objFiles:.o=.d)

