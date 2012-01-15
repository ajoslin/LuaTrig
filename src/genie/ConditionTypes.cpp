#include "ConditionTypes.h"
#include "ECTypesCpp.h"

//almost all of the classes are fully defined in the .h file, but a few have some functions in cpp too.
//we use macros to define these functions
//
//The parameters that need to be cpp defined are:
//Location, Area, Diplo, Resource, Unit Group, Unit Type, and Unitlist
//

AREA_CPP(Condition_BringObjectToArea);

UTYPE_CPP(Condition_OwnObjects);
UGROUP_CPP(Condition_OwnObjects);

UTYPE_CPP(Condition_OwnFewerObjects);
UGROUP_CPP(Condition_OwnFewerObjects);

AREA_CPP(Condition_ObjectsInArea);
UTYPE_CPP(Condition_ObjectsInArea);
UGROUP_CPP(Condition_ObjectsInArea);

RESOURCE_CPP(Condition_AccumulateAttribute);