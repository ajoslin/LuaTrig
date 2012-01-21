%module Scenario
%{
#include "../genie/ECTypes.h"
%}
%include "../genie/ECTypes.h"

%include SwigEffect.i
%include SwigCondition.i

%{
#include "../lua/NewTrigger.h"
%}

%include "../lua/NewTrigger.h"

