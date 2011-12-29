
CC=gcc
outName=program/LuaTrig
bin=bin/
src=src/
objs=objs/
lua=$(src)lua/
view=$(src)view/
util=$(src)util/
genie=$(src)genie/
libs=-llua `wx-config --cxxflags --libs`

#C++ Source Files

genieFiles=$(genie)aok_types.cpp $(genie)Condition.cpp $(genie)Effect.cpp $(genie)Trigger.cpp $(genie)Scenario.cpp $(genie)util_file.cpp

luaFiles=$(lua)NewTrigger.cpp $(lua)LCondition.cpp $(lua)LEffect.cpp $(lua)LuaFile.cpp

viewFiles=$(view)LTMain.cpp $(view)LTFrame.cpp $(view)LTDialog_Settings.cpp $(view)LTDialog_About.cpp $(view)LTDialog_TriggerGen.cpp $(view)LTDialog_ChooseScen.cpp $(view)LTPage_FileBase.cpp $(view)LTPage_Script.cpp $(view)LTPage_Scen.cpp

srcFiles=$(genieFiles) $(luaFiles) $(viewFiles)

#Compiled source files
objFiles=$(subst $(src),$(objs),$(srcFiles:.cpp=.o))

#Swig header files
swigFiles=$(lua)NewTriggerSwig.i $(lua)LEffectSwig.i $(lua)LConditionSwig.i

#Swig wrapper files
swigWrapperFiles=$(subst $(src),$(src),$(swigFiles:.i=.cxx))

#Swig obj files
swigObjFiles=$(subst $(src),$(objs),$(swigFiles:.i=.o))

#main compilation, final linking
.PHONY: $(outName)
$(outName): $(objFiles) $(swigWrapperFiles) $(swigObjFiles) $(objs)resource.o
	g++ $(objFiles) $(swigObjFiles) $(objs)resource.o $(libs) -o $(outName)

$(objs)resource.o: $(src)resource.rc
	windres $(src)resource.rc -o coff -o $(objs)resource.o

#Uses makefiles created by dependency generation for source files
-include $(objFiles:.o=.d)

#Dependency generation for source files 
$(objs)%.d:$(src)%.cpp 
	$(CC) -MM $(libs) $(CPPFLAGS) $< -o $(objs)$*.P;
	sed -r 's/$(notdir $*.o)/objs\/$(subst /,\/,$*.o)/g' < $(objs)$*.P > $(objs)$*.d;
	rm $(objs)$*.P

#Compile instructions for source files
$(objs)%.o:$(src)%.cpp 
	g++ -c $(DEFINES) $(libs) $< -o $@

#include dependency generation for swig files
-include $(swigObjFiles:.o=.d)

#dependency gen for swig files
$(objs)%.d:$(src)%.cxx
	mkdir -p $(dir $@) 
	$(CC) -MM $(libs) $(CPPFLAGS) $< -o $(objs)$*.P;
	sed -r 's/$(notdir $*.o)/objs\/$(subst /,\/,$*.o)/g' < $(objs)$*.P > $(objs)$*.d;
	rm $(objs)$*.P

#compilation for swig files
$(objs)%.o:$(src)%.cxx
	mkdir -p $(dir $@)
	g++ -c $(DEFINES) $(libs) $< -o $@

#swig header generation, .i -> .cxx
$(swigFiles:.i=.cxx):%.cxx:%.i;
	mkdir -p $(dir $@)
	swig -lua -c++ -o $@ $<

clean:
	rm $(objFiles)
	rm $(objFiles:.o=.d)
