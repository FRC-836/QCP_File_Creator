#ifndef SINGLE_VAR_CREATOR_H
#define SINGLE_VAR_CREATOR_H

//ui include
//#include "SingleVarCreator_UI.h"
#include "ui_SingleVarCreator.h"

class SingleVarCreator: public QWidget
{
  private:
    //member variables
    Ui_SingleVarCreator* m_ui;

  public:
    //constructors
    SingleVarCreator(QWidget* parent = 0);
    ~SingleVarCreator();

    //public functions

    //getters

    //setters
};

#endif //end ifndef SINGLE_VAR_CREATOR_H
