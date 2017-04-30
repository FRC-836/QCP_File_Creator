#ifndef NEW_DIALOG_H
#define NEW_DIALOG_H

//ui include
//#include "NewDialog_UI.h"
#include "ui_NewDialog.h"

class NewDialog: public QWidget
{
  private:
    //member variables
    Ui_NewDialog* m_ui;

  public:
    //constructors
    NewDialog(QWidget* parent = 0);
    ~NewDialog();

    //public functions

    //getters

    //setters
};

#endif //end ifndef NEW_DIALOG_H
