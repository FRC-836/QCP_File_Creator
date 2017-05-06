#ifndef MULTI_VAR_CREATOR_H
#define MULTI_VAR_CREATOR_H

//ui include
#include "ui_MultiVarCreator.h"

class MultiVarCreator: public QWidget
{
  private:
    //member variables
    Ui_MultiVarCreator* m_ui;

  public:
    //constructors
    MultiVarCreator(QWidget* parent = 0);
    ~MultiVarCreator();

    //public functions

    //getters

    //setters
}; //end class MultiVarCreator: public QWidget

#endif //end ifndef MULTI_VAR_CREATOR_H
