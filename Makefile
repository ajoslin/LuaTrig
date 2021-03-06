
#dir where wxwidgets is; if it's in your local bin just leave it blank
wxdir=

CC=gcc
outName=LuaTrig
bin=bin/
src=src/
objs=objs/
lua=$(src)lua/
swig=$(src)swig/
view=$(src)view/
util=$(src)util/
genie=$(src)genie/
control=$(src)control/
objlibs=`$(wxdir)wx-config --cxxflags`
linkerlibs=-llua51 `$(wxdir)wx-config --libs --static` -static-libgcc -static

#C++ Source Files

controlFiles=$(control)LuaFileController.cpp $(control)ScenarioFileController.cpp

genieFiles=$(genie)aok_types.cpp $(genie)Condition.cpp $(genie)ConditionTypes.cpp $(genie)Effect.cpp $(genie)EffectTypes.cpp $(genie)Trigger.cpp $(genie)Scenario.cpp $(genie)util_file.cpp

luaFiles=$(lua)NewTrigger.cpp $(lua)LuaFile.cpp

viewFiles=$(view)LuaTrigMain.cpp $(view)LTFrame.cpp $(view)LTDialog_Settings.cpp $(view)LTDialog_About.cpp $(view)LTDialog_ChooseScen.cpp $(view)LTPage_File.cpp $(view)LTPage_Script.cpp $(view)LTPage_Scen.cpp

srcFiles=$(controlFiles) $(genieFiles) $(luaFiles) $(viewFiles)

#Compiled source files
objFiles=$(subst $(src),$(objs),$(srcFiles:.cpp=.o))

#Swig header files
swigFiles=$(swig)SwigTrigger.i

#Swig wrapper files
swigWrapperFiles=$(subst $(src),$(src),$(swigFiles:.i=.cxx))

#Swig obj files
swigObjFiles=$(subst $(src),$(objs),$(swigFiles:.i=.o))

#declare these as phony so they can be run anytime
.PHONY: $(outName) upx release

#main compilation, final linking
$(outName): $(objFiles) $(swigFiles) $(swigWrapperFiles) $(swigObjFiles) $(objs)resource.o
	g++ $(objFiles) $(swigObjFiles) $(objs)resource.o $(linkerlibs) -o bin/$(outName)

#compress program using upx - windows only
upx:
	upx --best program/$(outName).exe

#put all files in folder for release
release:
	rm -rf release
	mkdir release
	mkdir release/scripts
	cp bin/LuaTrig.exe release/LuaTrig.exe
	cp bin/*.dll release/
	cp README.markdown release/README.txt

$(objs)resource.o: $(src)resource.rc
	windres $(src)resource.rc -o coff -o $(objs)resource.o

#Uses makefiles created by dependency generation for source files
-include $(objFiles:.o=.d)

#Dependency generation for source files 
$(objs)%.d:$(src)%.cpp 
	mkdir -p $(dir $@) 
	$(CC) -MM $(objlibs) $(CPPFLAGS) $< -o $(objs)$*.P;
	sed -r 's/$(notdir $*.o)/objs\/$(subst /,\/,$*.o)/g' < $(objs)$*.P > $(objs)$*.d;
	rm $(objs)$*.P

#Compile instructions for source files
$(objs)%.o:$(src)%.cpp 
	g++ -c $(DEFINES) $(objlibs) $< -o $@

#include dependency generation for swig files
-include $(swigObjFiles:.o=.d)

#dependency gen for swig files
$(objs)%.d:$(src)%.cxx
	mkdir -p $(dir $@) 
	$(CC) -MM $(objlibs) $(CPPFLAGS) $< -o $(objs)$*.P;
	sed -r 's/$(notdir $*.o)/objs\/$(subst /,\/,$*.o)/g' < $(objs)$*.P > $(objs)$*.d;
	rm $(objs)$*.P

#compilation for swig files
$(objs)%.o:$(src)%.cxx
	mkdir -p $(dir $@)
	g++ -c $(DEFINES) $(objlibs) $< -o $@

#swig header generation, .i -> .cxx
$(swigFiles:.i=.cxx):%.cxx:%.i;
	mkdir -p $(dir $@)
	swig -Wall -lua -c++ -o $@ $<

clean:
	rm -rf $(objFiles)
	rm -rf $(objFiles:.o=.d)z
