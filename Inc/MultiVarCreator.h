#ifndef MULTI_VAR_CREATOR_H
#define MULTI_VAR_CREATOR_H

//ui include
#include "ui_MultiVarCreator.h"

#include "QcpVariable.h"
#include "CommandOptions.h"

#include <vector>
#include <iostream>

class MultiVarCreator: public QWidget
{
    Q_OBJECT

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

  signals:
    void variablesCreated(std::vector<QcpVariable>& variables);
    void valuesChanged();
    void constRequest(const QString& varName, QcpVariable& variable);

  public slots:
    void commonTypeChanged(int index);
    void suffixesChanged();
    void valuesTabChanged(int newTabIndex);
    void addButtonClicked();
    void clearButtonClicked();

}; //end class MultiVarCreator: public QWidget

#endif //end ifndef MULTI_VAR_CREATOR_H
