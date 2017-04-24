#ifndef VAR_CREATOR_H
#define VAR_CREATOR_H

//custom widget includes
#include "SingleVarCreator.h"
#include "MultiVarCreator.h"

//UI include
//#include "VarCreator_UI.h"
#include "ui_VarCreator.h"

class VarCreator: public QWidget, private VarCreator_UI
{
};

#endif //end ifndef VAR_CREATOR_H
