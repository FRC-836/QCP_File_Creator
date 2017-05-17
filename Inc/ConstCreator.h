#ifndef CONST_CREATOR_H
#define CONST_CREATOR_H

#include "ui_ConstCreatorDialog.h"

#include "QcpVariable.h"
#include "Creator.h"

#include <iostream>

class ConstCreator : public QWidget
{
    Q_OBJECT

  private:
    //member variables
    Ui_ConstCreatorDialog* m_ui;

  public:
    //constructors
    ConstCreator(Creator* caller, QWidget* parent = nullptr);
    ~ConstCreator();

    //public functions

    //getters

    //setters

  signals:
    void newConstant(const QcpVariable& value);

  public slots:
    void createClicked();
    void cancelClicked();
    void nameChanged(const QString& newText);
    void valueChanged(const QString& newText);
}; //end class ConstCreator

#endif //end #ifndef CONST_CREATOR_H
