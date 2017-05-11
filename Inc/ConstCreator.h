#ifndef CONST_CREATOR_H
#define CONST_CREATOR_H

#include "ui_ConstCreatorDialog.h"

class ConstCreator : public QWidget
{
  private:
    //member variables
    Ui_ConstCreatorDialog* m_ui;

  public:
    //constructors
    ConstCreator(QWidget* parent = nullptr);
    ~ConstCreator();

    //public functions

    //getters

    //setters

  signals:

  public slots:
}; //end class ConstCreator

#endif //end #ifndef CONST_CREATOR_H
