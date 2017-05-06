#ifndef VAR_CREATOR_H
#define VAR_CREATOR_H

//#include "VarCreator_UI.h"
#include "ui_VarCreator.h"

class VarCreator: public QWidget
{
  private:
    //member variables
    Ui_VarCreator* m_ui;

  public:
    //constructors
    VarCreator(QWidget* parent = 0);
    ~VarCreator();

    //public functions

    //getters

    //setters

  signals:

  public slots:

};

#endif //end ifndef VAR_CREATOR_H
