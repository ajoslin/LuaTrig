#include "EffectTypes.h"
#include "ECTypesCpp.h"
#include "aok_types.h"
#include <stdio.h>
#include <math.h>

//almost all of the classes are fully defined in the .h file, but a few have some functions in cpp too.
//we use macros to define these functions
//
//The parameters that need to be cpp defined are:
//Location, Area, Diplo, Resource, Unit Group, Unit Type, and Unitlist
//

DIPLO_CPP(Effect_ChangeDiplomacy);

RESOURCE_CPP(Effect_SendTribute);

UIDS_CPP(Effect_UnlockGate);
UIDS_CPP(Effect_LockGate);

LOCATION_CPP(Effect_CreateObject);

LOCATION_CPP(Effect_TaskObject);
AREA_CPP(Effect_TaskObject);
UGROUP_CPP(Effect_TaskObject);
UTYPE_CPP(Effect_TaskObject);
UIDS_CPP(Effect_TaskObject);

LOCATION_CPP(Effect_KillObject);
AREA_CPP(Effect_KillObject);
UGROUP_CPP(Effect_KillObject);
UTYPE_CPP(Effect_KillObject);
UIDS_CPP(Effect_KillObject);

LOCATION_CPP(Effect_RemoveObject);
AREA_CPP(Effect_RemoveObject);
UGROUP_CPP(Effect_RemoveObject);
UTYPE_CPP(Effect_RemoveObject);
UIDS_CPP(Effect_RemoveObject);

LOCATION_CPP(Effect_ChangeView);

LOCATION_CPP(Effect_Unload);
AREA_CPP(Effect_Unload);
UGROUP_CPP(Effect_Unload);
UTYPE_CPP(Effect_Unload);
UIDS_CPP(Effect_Unload);

AREA_CPP(Effect_ChangeOwnership);
UGROUP_CPP(Effect_ChangeOwnership);
UTYPE_CPP(Effect_ChangeOwnership);
UIDS_CPP(Effect_ChangeOwnership);

LOCATION_CPP(Effect_Patrol);
UIDS_CPP(Effect_Patrol);

LOCATION_CPP(Effect_FreezeUnit);
AREA_CPP(Effect_FreezeUnit);
UGROUP_CPP(Effect_FreezeUnit);
UTYPE_CPP(Effect_FreezeUnit);
UIDS_CPP(Effect_FreezeUnit);

AREA_CPP(Effect_DamageObject);
UGROUP_CPP(Effect_DamageObject);
UTYPE_CPP(Effect_DamageObject);
UIDS_CPP(Effect_DamageObject);

LOCATION_CPP(Effect_PlaceFoundation);

UIDS_CPP(Effect_ChangeObjectName);

AREA_CPP(Effect_ChangeObjectHP);
UGROUP_CPP(Effect_ChangeObjectHP);
UTYPE_CPP(Effect_ChangeObjectHP);
UIDS_CPP(Effect_ChangeObjectHP);

AREA_CPP(Effect_ChangeObjectAttack);
UGROUP_CPP(Effect_ChangeObjectAttack);
UTYPE_CPP(Effect_ChangeObjectAttack);
UIDS_CPP(Effect_ChangeObjectAttack);

LOCATION_CPP(Effect_StopUnit);
AREA_CPP(Effect_StopUnit);
UGROUP_CPP(Effect_StopUnit);
UTYPE_CPP(Effect_StopUnit);
UIDS_CPP(Effect_StopUnit);


