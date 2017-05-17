#ifndef SINGLE_VAR_CREATOR_H
#define SINGLE_VAR_CREATOR_H

//ui include
#include "ui_SingleVarCreator.h"

#include "QcpVariable.h"

#include <iostream>

class SingleVarCreator: public QWidget
{
    Q_OBJECT

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

  signals:
    void variableCreated(const QcpVariable& variable);
    void valuesChanged();
    void constRequest(const QString& varName, QcpVariable& variable);

  public slots:
    void variableTypeChanged(int index);
    void addButtonClicked();
    void clearButtonClicked();
    void variableNameChanged(const QString& newText);
    void variableValuesChanged();
}; //end class SingleVarCreator: public QWidget

#endif //end ifndef SINGLE_VAR_CREATOR_H
